struct Trie {
    int tot = 0;
    vector<array<int, 26>> tree, cnt;
    Trie(int n) : tree(n + 1), cnt(n + 1) {}
    void insert(const string &s) {
        int u = 0;
        for (char c : s) {
            int v = c - 'a';
            if (!tree[u][v]) {
                tree[u][v] = ++tot;
            }
            u = tree[u][v];
            cnt[u][v]++;
        }
    }
    i64 query(const string &s) {
        int u = 0;
        i64 res = 0;
        for (char c : s) {
            int v = c - 'a';
            if (!tree[u][v]) {
                return res;
            }
            u = tree[u][v];
            res += cnt[u][v];
        }
        return res;
    }
    bool contains(const string &s) {
        int u = 0;
        for (char c : s) {
            int v = c - 'a';
            if (!tree[u][v]) {
                return false;
            }
            u = tree[u][v];
        }
        return true;
    }
};
