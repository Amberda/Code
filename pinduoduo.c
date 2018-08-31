int c;
int len;
void paili(vector<string>&result, int pos, string temp, set<string>&ret)
{
	if (pos == len)
	{
		ret.insert(temp);
		return;
	}
	for (int i = 0; i < c; ++i)
	{
		paili(result, pos + 1, temp + result[i][pos], ret);
	}
}
int main()
{

	cin >> c >> len;
	vector<string>result;
	for (int i = 0; i < c; ++i)
	{
		string temp;
		cin >> temp;
		result.push_back(temp);
	}
	set<string>ret;
	string temp;
	paili(result, 0, temp, ret);
	for (auto i : result)
	{
		ret.erase(i);
	}
	if (ret.empty())
		cout << "-" << endl;
	else
		cout << *(ret.begin()) << endl;
	return 0;
}
