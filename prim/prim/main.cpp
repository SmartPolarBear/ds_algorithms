// LG P3366

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

constexpr int NMAX = 5010, MMAX = 200010;

struct edge
{
	int v, next, w;
};

int heads[NMAX]{};
edge edges[MMAX << 1]{};
int ecnt = 0;

void add(int u, int v, int w)
{
	edges[ecnt].v = v;
	edges[ecnt].w = w;
	edges[ecnt].next = heads[u];

	heads[u] = ecnt;

	ecnt++;
}

bool vis[NMAX]{};
int v[NMAX]{}, ans = 0;

bool prim(int n)
{
	memset(v, 0x3f, sizeof(v));
	memset(vis, 0, sizeof(vis));

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push(make_pair(0, 1));

	v[1] = 0;
	int cnt = 0;
	while (!q.empty() && cnt < n)
	{
		auto t = q.top();
		q.pop();

		if (vis[t.second])continue;

		vis[t.second] = true;
		ans += t.first;
		cnt++;

		for (int i = heads[t.second]; ~i; i = edges[i].next)
		{
			if (v[edges[i].v] > edges[i].w)
			{
				v[edges[i].v] = edges[i].w;
				q.push(make_pair(v[edges[i].v], edges[i].v));
			}
		}
	}

	return cnt == n;
}

int main()
{
	int n = 0, m = 0;
	cin >> n >> m;

	memset(heads, -1, sizeof(heads));

	for (int i = 0; i < m; i++)
	{
		int u = 0, v = 0, w = 0;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}

	bool ret = prim(n);
	if (ret)
	{
		cout << ans << "\n";
	}
	else
	{
		cout << "orz" << "\n";
	}
	return 0;
}
