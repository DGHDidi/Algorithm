struct SCC {
    int n, idx = 0, scc_cnt = 0;
    vector<int> scc_id;
    vector<vector<int>> G, scc;

    SCC(int _n) : n(_n + 1), scc_id(_n + 1), G(_n + 1), scc(_n + 1) {}

    void add_edge(int u, int v) {
        G[u].push_back(v);
    }

    void build() {
        vector<int> ord(n, -1), low(n), on_stack(n);
        stack<int> stk;
        function<void(int)> dfs = [&](int u) -> void {
            ord[u] = low[u] = idx++;
            stk.push(u), on_stack[u] = true;
            for (int v : G[u]) {
                if (ord[v] == -1) {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                } else if (on_stack[v]) {
                    low[u] = min(low[u], ord[v]);
                }
            }
            if (ord[u] == low[u]) {
                scc.push_back({});
                while (true) {
                    int v = stk.top();
                    stk.pop(), on_stack[v] = false;
                    scc_id[v] = scc_cnt;
                    scc.back().push_back(v);
                    if (v == u) {
                        break;
                    }
                }
                scc_cnt++;
            }
            };
        for (int i = 1; i < n; i++) {
            if (ord[i] == -1) {
                dfs(i);
            }
        }
    }

    int id(int u) {
        return scc_id[u];
    }

    vector<vector<int>> groups() {
        return scc;
    }
};
