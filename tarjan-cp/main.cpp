#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


constexpr int NMAX = 20010, MMAX = 100010;
vector<int> g[NMAX];

bool vis[NMAX]{}, cps[NMAX]{};
int dfn[NMAX]{}, low[NMAX], dfn_cnt{ 0 };


void tarjan(int r, int f)
{
	dfn[r] = low[r] = ++dfn_cnt;
	vis[r] = true;

	int children = 0;

	for (auto v: g[r])
	{
		if (!dfn[v])
		{
			tarjan(v, f);
			low[r] = min(low[r], low[v]);

			if (dfn[r] <= low[v])
			{
				children++;
				if (r != f || children >= 2)
				{
					cps[r] = true;
				}
			}
		}
		else if(vis[v])
		{
			low[r] = min(low[r], dfn[v]);
		}
	}
}

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int x = 0, y = 0;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	for (int i = 1; i <= n; i++)
	{
		if(!vis[i])
		{
			tarjan(i, i);
		}
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (cps[i])
		{
			cnt++;
		}
	}
	cout << cnt << endl;
	for (int i = 1; i <= n; i++)
	{
		if (cps[i])
		{
			cout << i << " ";
		}
	}

	return 0;
}
