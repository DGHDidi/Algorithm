template<class Info>
struct SegmentTree {
    int n;
    vector<Info> tree;
    SegmentTree() : n(0) {}
    SegmentTree(int _n, Info _v = Info()) {
        init(_n, _v);
    }
    template<class T>
    SegmentTree(vector<T> _init) {
        init(_init);
    }
    void init(int _n, Info _v = Info()) {
        init(vector<Info>(_n, _v));
    }
    template<class T>
    void init(vector<T> _init) {
        n = _init.size();
        tree.assign((n << 2) + 5, Info());
        function<void(int, int, int)> build = [&](int now, int l, int r) -> void {
            if (l == r) {
                tree[now] = _init[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(now << 1, l, mid);
            build(now << 1 | 1, mid + 1, r);
            pull(now);
            };
        build(1, 0, n);
    }
    void pull(int now) {
        tree[now] = tree[now << 1] + tree[now << 1 | 1];
    }
    void modify(int now, int l, int r, int pos, const Info &v) {
        if (l == r) {
            tree[now] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            modify(now << 1, l, mid, pos, v);
        } else {
            modify(now << 1 | 1, mid + 1, r, pos, v);
        }
        pull(now);
    }
    void modify(int pos, const Info &v) {
        modify(1, 0, n, pos, v);
    }
    Info rangeQuery(int now, int l, int r, int x, int y) {
        if (x <= l && r <= y) {
            return tree[now];
        }
        int mid = (l + r) >> 1;
        Info res = Info();
        if (x <= mid) {
            res = res + rangeQuery(now << 1, l, mid, x, y);
        }
        if (y > mid) {
            res = res + rangeQuery(now << 1 | 1, mid + 1, r, x, y);
        }
        return res;
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    template<class F>
    int findFirst(int now, int l, int r, int x, int y, F &&pred) {
        if (l > y || r < x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(tree[now])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int res = findFirst(now << 1, l, mid, x, y, pred);
        if (res == -1) {
            res = findFirst(now << 1 | 1, mid + 1, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int now, int l, int r, int x, int y, F &&pred) {
        if (l > y || r < x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(tree[now])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int mid = (l + r) >> 1;
        int res = findFirst(now << 1 | 1, mid + 1, r, x, y, pred);
        if (res == -1) {
            res = findFirst(now << 1, l, mid, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F &&pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};
