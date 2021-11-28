#include <iostream>
#include <vector>
#include <queue>

using namespace std;

constexpr int NMAX = 100, MMAX = 200;

struct edge
{
	int u, v, next;
};

int heads[NMAX]{}, indeg[NMAX]{}, ecnt = 0;
edge edges[MMAX << 1]{};

void add(int u, int v)
{
	edges[ecnt].u = u;
	edges[ecnt].v = v;
	edges[ecnt].next = heads[u];
	heads[u] = ecnt++;

	indeg[v]++;
}

bool toposort(int n)
{
	vector<int> result{};
	queue<int> q{};
	int count = 0;
	for (int i = 1; i <= n; i++)
	{
		if (!indeg[i])
		{
			q.push(i);
			result.push_back(i);
			count++;
		}
	}

	while (!q.empty())
	{
		auto t = q.front();
		q.pop();
		for (auto i = heads[t]; ~i; i = edges[i].next)
		{
			indeg[edges[i].v]--;
			if (!indeg[edges[i].v])
			{
				count++;
				q.push(edges[i].v);
				result.push_back(edges[i].v);
			}
		}
	}

	for (auto i: result)
	{
		cout << i << " ";
	}
	cout << endl;

	return count == n;

}

int main()
{
	memset(heads, -1, sizeof(heads));
	memset(indeg, 0, sizeof(indeg));

	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u = 0, v = 0;
		cin >> u >> v;
		add(u, v);
	}

	auto ret = toposort(n);

	cout << ret << endl;
	return 0;
}
