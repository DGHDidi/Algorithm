struct AC {
    static const int ALP = 26;
    int nodes = 0, tot = 0;
    vector<int> fail, pat, deg;
    vector<array<int, ALP>> nxt;

    AC() { clear(); }

    int newNode() {
        array<int, ALP> now;
        now.fill(-1);
        nxt.push_back(now);
        fail.push_back(0);
        return nodes++;
    }

    void clear() {
        nodes = tot = 0;
        fail.clear();
        pat.clear();
        nxt.clear();
        pat.push_back(0);
        newNode();
    }

    int insert(const string &s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (c < 0 || c >= ALP) {
                throw runtime_error("Invalid character");
            }
            if (nxt[u][c] == -1) {
                int z = newNode();
                nxt[u][c] = z;
            }
            u = nxt[u][c];
        }
        int id = (int)pat.size();
        pat.push_back(u);
        tot++;
        return id;
    }

    void build() {
        deg.assign(nodes, 0);
        queue<int> q;
        for (int c = 0; c < ALP; c++) {
            int v = nxt[0][c];
            if (v != -1) {
                fail[v] = 0;
                q.push(v);
            } else {
                nxt[0][c] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < ALP; c++) {
                int v = nxt[u][c];
                if (v != -1) {
                    fail[v] = nxt[fail[u]][c];
                    deg[fail[v]]++;
                    q.push(v);
                } else {
                    nxt[u][c] = nxt[fail[u]][c];
                }
            }
        }
    }

    vector<i64> query(const string &text) {
        vector<bool> vis(nodes, false);
        vector<i64> cnt(nodes, 0);

        int u = 0;
        for (char ch : text) {
            int c = ch - 'a';
            if (c < 0 || c >= ALP) {
                throw runtime_error("Invalid character");
            }
            u = nxt[u][c];
            cnt[u]++;
        }

        auto tmp = deg;
        queue<int> q;
        for (int i = 0; i < nodes; i++) {
            if (!tmp[i]) {
                q.push(i);
                vis[i] = true;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == 0) continue;
            int v = fail[u];
            cnt[v] += cnt[u];
            if (--tmp[v] == 0 && !vis[v]) {
                q.push(v);
                vis[v] = true;
            }
        }

        vector<i64> res(tot + 1, 0);
        for (int i = 1; i <= tot; i++) {
            res[i] = cnt[pat[i]];
        }

        return res;
    }
} ac;
