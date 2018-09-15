struct BuyEat
{
	char ch;
	int index;
};

int main()
{
	int N;
	int M;
	int P;
	cin >> N >> M >> P;
	vector<int> count(N);
	vector<BuyEat> v(M);
	for (int i = 0; i<N; i++)
		cin >> count[i];
	for (int i = 0; i<M; i++)
	{
		cin >> v[i].ch >> v[i].index;
	}
	for (int i = 0; i<M; i++)
	{
		char c = v[i].ch;
		int pos = v[i].index-1;
		if (c == 'A')
			count[pos]++;
		if (c == 'B')
			count[pos]--;
	}
	int res = 1;
	for (int i = 0; i<N; i++)
	{
		int tmp = count[P-1];
		if (P-1 == i || tmp>count[i])
			continue;
		if (tmp<count[i])
			res++;
	}
	cout << res << endl;
	return 0;
}
