typedef struct ListNode
{
	ListNode(int data)
	:val(data)
	, _next(NULL)
	{}

	ListNode* _next;
	int val;
}Node,*pNode;


//合并两个有序链表，合并以后的链表依然有序
#if 0

pNode MergeList(pNode list1,pNode list2)
{
	assert(list1);
	assert(list2);
	if (list1 == NULL&&list2 == NULL)
	{
		return NULL;
	}
	if (list1 == NULL)
	{
		return list2;
	}
	if (list2 == NULL)
	{
		return list1;
	}
	pNode pNewHead = NULL;
	pNode cur1 = list1;
	pNode cur2 = list2;
	if (cur1->_data < cur2->_data)
	{
		pNewHead = cur1;
		cur1 = cur1->_next;
	}
	else
	{
		pNewHead = cur2;
		cur2 = cur2->_next;
	}
	pNewHead->_next = NULL;
	pNode tmp = pNewHead;
	while (cur1&&cur2)
	{
		if (cur1->_data < cur2->_data)
		{
			tmp->_next = cur1;
			cur1 = cur1->_next;
		}
		else
		{
			tmp->_next = cur2;
			cur2 = cur2->_next;
		}
		tmp = tmp->_next;
		tmp->_next = NULL;
	}
	if (cur1 != NULL)
	{
		tmp->_next = cur1;
	}
	if (cur2 != NULL)
	{
		tmp->_next = cur2;
	}
	return pNewHead;
}

pNode DMergeList(pNode list1, pNode list2)
{
	assert(list1);
	assert(list2);
	if (list1 == NULL&&list2 == NULL)
		return NULL;
	if (list1 == NULL)
		return list2;
	if (list2 == NULL)
		return list1;
	pNode pNewHead = NULL;
	pNode cur1 = list1;
	pNode cur2 = list2;
	if (cur1->_data < cur2->_data)
	{
		pNewHead = cur1;
		cur1 = cur1->_next;
	}
	else
	{
		pNewHead = cur2;
		cur2 = cur2->_next;
	}
	pNewHead->_next = NULL;
	pNode tmp = NULL;
	if (cur1 == NULL || cur2 == NULL)
	{
		tmp = pNewHead;
		tmp->_next = DMergeList(cur1, cur2);
	}
	return pNewHead;
}
pNode Creat1()
{
	pNode head;
	pNode n1 = new Node(1);
	pNode n2 = new Node(3);
	pNode n3 = new Node(5);
	pNode n4 = new Node(7);
	pNode n5 = new Node(9);

	head = n1;
	n1->_next = n2;
	n2->_next = n3;
	n3->_next = n4;
	n4->_next = n5;
	n5->_next = NULL;

	return head;
}
pNode Creat2()
{
	pNode head;
	pNode n6 = new Node(0);
	pNode n7 = new Node(2);
	pNode n8 = new Node(4);
	pNode n9 = new Node(6);
	pNode n0 = new Node(8);

	head = n6;
	n6->_next = n7;
	n7->_next = n8;
	n8->_next = n9;
	n9->_next = n0;
	n0->_next = NULL;

	return head;
}

void Test1()
{
	pNode head1 = Creat1();
	pNode head2 = Creat2();
	pNode NewList = NULL;
	NewList = MergeList(head1, head2);
}
#endif
