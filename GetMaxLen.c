#include <stdlib.h>
#include <iostream>
using namespace std;
#include <string>
#include <string.h>

#include<algorithm>

int main()
{
	string str;
	cin >> str;
	int hashtable[256];
	memset(hashtable, -1, sizeof(hashtable));
	int size = str.size();
	int pos = 0;
	int maxlen = 0;
	for (int i = 0; i<size; i++)
	{
		if (hashtable[str[i]] == -1)
		{
			hashtable[str[i]] = i;
		}
		else
		{
			if (hashtable[str[i]]>=pos)
			{
				pos = hashtable[str[i]] + 1;
			}
			hashtable[str[i]] = i;
		}
		maxlen = maxlen>i - pos + 1 ? maxlen : i - pos + 1;
	}
	cout << maxlen << endl;
	system("pause");
	return 0;
}
