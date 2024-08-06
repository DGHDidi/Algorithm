struct TwoSat {
    int n;
    vector<int> ans;
    vector<vector<int>> e;

    TwoSat(int _n) : n(_n), ans(_n + 1), e(2 * _n + 1) {}

    void addClause(int u, bool f, int v, bool g) {
        e[u + n * f].push_back(v + n * (!g));
        e[v + n * g].push_back(u + n * (!f));
    }

    bool check() {
        int N = 2 * n + 1, idx = 0, cnt = 0;
        vector<int> ord(N, -1), low(N), on_stack(N), id(N);
        stack<int> stk;
        function<void(int)> dfs = [&](int u) -> void {
            ord[u] = low[u] = idx++;
            stk.push(u), on_stack[u] = true;
            for (int v : e[u]) {
                if (ord[v] == -1) {
                    dfs(v);
                    low[u] = min(low[u], low[v]);
                } else if (on_stack[v]) {
                    low[u] = min(low[u], ord[v]);
                }
            }
            if (ord[u] == low[u]) {
                while (true) {
                    int v = stk.top();
                    stk.pop(), on_stack[v] = false;
                    id[v] = cnt;
                    if (v == u) {
                        break;
                    }
                }
                cnt++;
            }
            };
        for (int i = 1; i <= 2 * n; i++) {
            if (ord[i] == -1) {
                dfs(i);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (id[i] == id[i + n]) {
                return false;
            }
            ans[i] = id[i] < id[i + n];
        }
        return true;
    }

    vector<int> answer() {
        return ans;
    }
};
