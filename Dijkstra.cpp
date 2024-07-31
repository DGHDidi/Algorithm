{
	"Dijkstra": {
		"prefix": "dijkstra",
		"body": [
			"auto Dijkstra = [&](int s) {",
			"    const i64 INF = 1e18;",
			"    priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<pair<i64, int>>> q;",
			"    vector<i64> dis(n + 1, INF);",
			"    vector<bool> vis(n + 1, false);",
			"    dis[s] = 0, q.emplace(0, s);",
			"    for (int t = 1; t <= n - 1; t++) {",
			"        while (!q.empty() && vis[q.top().second]) {",
			"            q.pop();",
			"        }",
			"        int u = q.top().second;",
			"        vis[u] = true;",
			"        for (auto nxt : e[u]) {",
			"            int v = nxt.first, w = nxt.second;",
			"            if (!vis[v] && dis[u] + w < dis[v]) {",
			"                dis[v] = dis[u] + w;",
			"                q.emplace(dis[v], v);",
			"            }",
			"        }",
			"    }",
			"    return dis;",
			"    };"
		],
		"description": "Dijkstra's algorithm"
	}
}
