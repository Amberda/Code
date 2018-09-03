BinaryTreeNode<T>* GetLastCommomParent(BinaryTreeNode<T>* pRoot,int data1,int data2)
{
    if (pRoot)
    {
        if (data1 < pRoot->_data && data2 < pRoot->_data)
            return _GetLastCommomParent(pRoot->_pLeftChild,data1,data2);
        else if (data1 > pRoot->_data && data2 > pRoot->_data)
            return _GetLastCommomParent(pRoot->_pRightChild, data1, data2);
        else
            return pRoot;
    }
    return NULL;
}
bool FindNode(BinaryTreeNode * pRoot,BinaryTreeNode *pNode)
{
    if (pRoot == NULL || pNode == NULL)
        return false;
    if (pRoot == pNode)
        return true;
    bool found = FindNode(pRoot->_pLeftChild,pNode);
    if (!found)
        return FindNode(pRoot->_pRightChild,pNode);
}

BinaryTreeNode* _GetLastCommomParent(BinaryTreeNode* pRoot, BinaryTreeNode* pNode1, BinaryTreeNode* pNode2)
{
    if (FindNode(pRoot->_pLeftChild, pNode1))
    {
        if (FindNode(pRoot->_pRightChild, pNode2))
            return pRoot;
        else
            return _GetLastCommomParent(pRoot->_pLeftChild,pNode1,pNode2);
    }
    else
    {
        if (FindNode(pRoot->_pLeftChild, pNode2))
            return pRoot;
        else
            return _GetLastCommomParent(pRoot->_pRightChild,pNode1,pNode2);
    }
}
