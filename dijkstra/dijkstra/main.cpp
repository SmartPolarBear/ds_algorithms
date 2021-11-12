// LG P4779

#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

constexpr int NMAX = 100010, MMAX = 200010;

struct edge
{
	int v, w, next;
};

int heads[NMAX]{}, ecnt = 0;
edge edges[MMAX << 1]{};

void add(int u, int v, int w)
{
	edges[ecnt].v = v;
	edges[ecnt].w = w;
	edges[ecnt].next = heads[u];
	heads[u] = ecnt++;
}

int dis[NMAX]{};//, path[NMAX];
bool vis[NMAX]{};

void dijkstra(int s)
{
	memset(dis, 0x3f, sizeof(dis));
	memset(vis, 0, sizeof(vis));

	dis[s] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.emplace(0, s);

	while (!q.empty())
	{
		auto t = q.top();
		q.pop();

		if (vis[t.second])continue;

		vis[t.second] = true;
		for (int i = heads[t.second]; ~i; i = edges[i].next)
		{
			if (dis[edges[i].v] > dis[t.second] + edges[i].w)
			{
				dis[edges[i].v] = dis[t.second] + edges[i].w;
				q.emplace(dis[edges[i].v], edges[i].v);
//				path[edges[i].v] = t.second;
			}
		}
	}
}


int main()
{
	memset(heads, -1, sizeof(heads));
	int n = 0, m = 0, s = 0;
	cin >> n >> m >> s;
	for (int i = 0; i < m; ++i)
	{
		int u = 0, v = 0, w = 0;
		cin >> u >> v >> w;
		add(u, v, w);
//		add(v, u, w);
	}

	dijkstra(s);

	for (int i = 1; i <= n; i++)
	{
		cout << dis[i] << " ";
	}

	return 0;
}
