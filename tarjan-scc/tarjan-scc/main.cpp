// LG P1536

#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

constexpr int NMAX = 1010, MMAX = 1000010;

struct edge
{
	int v, w, next;
};

edge edges[MMAX << 1]{};
int ecnt{ 0 }, heads[NMAX]{};

void add(int u, int v, int w)
{
	edges[ecnt].v = v;
	edges[ecnt].w = w;
	edges[ecnt].next = heads[u];
	heads[u] = ecnt++;
}

int scc[NMAX]{}, sz[NMAX]{}, scc_cnt{ 0 };
int low[NMAX]{}, dfn[NMAX], dfn_cnt{ 0 };
bool vis[NMAX]{};

stack<int> s{};

void tarjan(int r)
{
	low[r] = dfn[r] = ++dfn_cnt;
	vis[r] = true;
	s.push(r);

	for (int i = heads[r]; ~i; i = edges[i].next)
	{
		auto v = edges[i].v;
		if (!dfn[v])
		{
			tarjan(v);
			low[r] = min(low[r], low[v]);
		}
		else if (vis[v])
		{
			low[r] = min(low[r], dfn[v]);
		}
	}

	if (low[r] == dfn[r])
	{
		scc_cnt++;
		do
		{
			auto top = s.top();
			s.pop();

			scc[top] = scc_cnt;
			sz[scc_cnt]++;

			vis[top] = false;
		} while (!s.empty() && s.top() != r);
	}
}

int main()
{
	while (true)
	{
		memset(edges, 0, sizeof(edges));
		memset(heads, -1, sizeof(heads));

		memset(scc, 0, sizeof(scc));
		memset(sz, 0, sizeof(sz));
		memset(low, 0, sizeof(low));
		memset(dfn, 0, sizeof(dfn));
		memset(vis, 0, sizeof(vis));

		scc_cnt = 0;
		ecnt = 0;
		dfn_cnt = 0;

		while (!s.empty())
		{
			s.pop();
		}

		int n = 0, m = 0;
		cin >> n;
		if (!n)break;
		cin >> m;
		for (int i = 0; i < m; i++)
		{
			int u = 0, v = 0;
			cin >> u >> v;
			add(u, v, 1);
			add(v, u, 1);
		}

		for (int i = 1; i <= n; i++)
		{
			if (!dfn[i])
			{
				tarjan(i);
			}
		}

		cout << scc_cnt - 1 << endl;
	}

	return 0;
}
