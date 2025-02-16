struct Hungary {
    int n, m;
    vector<vector<int>> G;
    vector<int> match, vis;

    Hungary(int _n, int _m) : n(_n), m(_m), G(n + 1), match(m + 1), vis(m + 1) {}

    void addEdge(int u, int v) {
        G[u].push_back(v);
    }

    bool dfs(int u) {
        for (auto v : G[u]) {
            if (vis[v]) {
                continue;
            }
            vis[v] = 1;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int work() {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            fill(vis.begin(), vis.end(), 0);
            res += dfs(i);
        }
        return res;
    }
};
