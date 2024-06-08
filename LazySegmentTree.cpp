template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    vector<Info> tree;
    vector<Tag> lazy;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int _n, Info _v = Info()) {
        init(_n, _v);
    }
    template<class T>
    LazySegmentTree(vector<T> _init) {
        init(_init);
    }
    void init(int _n, Info _v = Info()) {
        init(vector<Info>(_n, _v));
    }
    template<class T>
    void init(vector<T> _init) {
        n = _init.size();
        tree.assign((n << 2) + 5, Info());
        lazy.assign((n << 2) + 5, Tag());
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
    void push(int now) {
        tree[now << 1].apply(lazy[now]), tree[now << 1 | 1].apply(lazy[now]);
        lazy[now << 1].apply(lazy[now]), lazy[now << 1 | 1].apply(lazy[now]);
        lazy[now] = Tag();
    }
    void modify(int now, int l, int r, int pos, const Info &v) {
        if (l == r) {
            tree[now] = v;
            return;
        }
        push(now);
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
        push(now);
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
    void rangeApply(int now, int l, int r, int x, int y, const Tag &v) {
        if (x <= l && r <= y) {
            tree[now].apply(v);
            lazy[now].apply(v);
            return;
        }
        push(now);
        int mid = (l + r) >> 1;
        if (x <= mid) {
            rangeApply(now << 1, l, mid, x, y, v);
        }
        if (mid < y) {
            rangeApply(now << 1 | 1, mid + 1, r, x, y, v);
        }
        pull(now);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n, l, r, v);
    }
    template<class F>
    int findFirst(int now, int l, int r, int x, int y, F check) {
        if (l == r) {
            return check(tree[now]) ? l : -1;
        }
        push(now, l, r);
        int mid = (l + r) >> 1;
        int res = findFirst(now << 1, l, mid, x, y, check);
        if (res == -1) {
            res = findFirst(now << 1 | 1, mid + 1, r, x, y, check);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F check) {
        return findFirst(1, 0, n, l, r, check);
    }
    template<class F>
    int findLast(int now, int l, int r, int x, int y, F check) {
        if (l == r) {
            return check(tree[now]) ? l : -1;
        }
        push(now, l, r);
        int mid = (l + r) >> 1;
        int res = findLast(now << 1 | 1, mid + 1, r, x, y, check);
        if (res == -1) {
            res = findLast(now << 1, l, mid, x, y, check);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F check) {
        return findLast(1, 0, n, l, r, check);
    }
};
