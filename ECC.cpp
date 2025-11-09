struct ECC {
    struct DSU {
        vector<int> fa, siz;
        DSU(int n) : fa(n + 1), siz(n + 1, 1) {
            iota(fa.begin(), fa.end(), 0);
        }
        int find(int x) {
            return x == fa[x] ? x : fa[x] = find(fa[x]);
        }
        bool merge(int x, int y) {
            x = find(x), y = find(y);
            if (x == y) {
                return false;
            }
            if (siz[x] > siz[y]) {
                swap(x, y);
            }
            fa[x] = y, siz[y] += siz[x];
            return true;
        }
        bool same(int x, int y) {
            return find(x) == find(y);
        }
        int size(int x) {
            return siz[find(x)];
        }
    };

    int n, m, idx = 0;
    vector<int> dfn, low;
    vector<bool> vis, visE;
    vector<vector<pair<int, int>>> edges;
    DSU dsu;

    ECC(int n, int m) : n(n), m(m), dsu(n) {
        dfn.resize(n + 1);
        low.resize(n + 1);
        vis.assign(n + 1, false);
        visE.assign(m + 1, false);
        edges.resize(n + 1);
    }

    void addEdge(int u, int v, int id) {
        edges[u].push_back({v, id});
        edges[v].push_back({u, id});
    }

    void dfs(int u, int eID) {
        low[u] = dfn[u] = ++idx;
        visE[eID] = true, vis[u] = true;
        for (auto [v, id] : edges[u]) {
            if (!vis[v]) {
                dfs(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] <= dfn[u]) {
                    dsu.merge(u, v);
                }
            } else if (!visE[id]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    vector<vector<int>> getECC() {
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                idx = 0;
                dfs(i, 0);
            }
        }

        vector<vector<int>> comps(n + 1);
        for (int i = 1; i <= n; i++) {
            comps[dsu.find(i)].push_back(i);
        }

        return comps;
    }
};
