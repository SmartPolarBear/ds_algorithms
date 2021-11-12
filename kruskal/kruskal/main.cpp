//LG P3366

#include <iostream>
#include <algorithm>

using namespace std;
constexpr int NMAX = 5010, MMAX = 200010;

int fa[NMAX]{};

void init_uf()
{
	for (int i = 0; i < NMAX; i++)
	{
		fa[i] = i;
	}
}

int find_uf(int x)
{
	return x == fa[x] ? x : (fa[x] = find_uf(fa[x]));
}

void merge_uf(int x, int y)
{
	fa[find_uf(x)] = find_uf(y);
}

struct edge
{
	int u, v, w;
};

edge edges[MMAX]{};

int main()
{
	init_uf();

	int n = 0, m = 0;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
	}

	sort(edges, edges + m, [](const edge& a, const edge& b)
	{
		return a.w < b.w;
	});

	int cnt = 0, ans = 0;
	for (int i = 0; i < m; ++i)
	{
		if (find_uf(edges[i].u) == find_uf(edges[i].v))continue;

		cnt++;
		ans += edges[i].w;

		merge_uf(edges[i].u, edges[i].v);
	}

	if (cnt != n - 1)
	{
		cout << "orz" << "\n";
	}
	else
	{
		cout << ans << "\n";
	}

	return 0;
}
