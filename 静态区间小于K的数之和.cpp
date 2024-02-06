#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using i64 = long long;

const int N = 2e5 + 5;
int n, q;
i64 a[N];

struct PersistentSegmentTree {
    int idx = 0, len = 0;
    i64 tmp[N], rt[N];
    struct Node {
        int ls, rs;
        i64 val;
    } tree[N << 5];
    void init(int n, i64 *arr) {
        for (int i = 1; i <= n; i++) {
            tmp[i] = arr[i];
        }
        sort(tmp + 1, tmp + n + 1);
        len = unique(tmp + 1, tmp + n + 1) - tmp - 1;
        for (int i = 1; i <= n; i++) {
            arr[i] = lower_bound(tmp + 1, tmp + len + 1, arr[i]) - tmp;
            rt[i] = insert(rt[i - 1], 1, len, arr[i]);
        }
    }
    int insert(int p, int l, int r, int pos) {
        tree[++idx] = tree[p], p = idx, tree[p].val += tmp[pos];
        if (l == r) {
            return p;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            tree[p].ls = insert(tree[p].ls, l, mid, pos);
        } else {
            tree[p].rs = insert(tree[p].rs, mid + 1, r, pos);
        }
        return p;
    }
    i64 query(int u, int v, int l, int r, i64 k) {
        if (tmp[r] <= k) {
            return tree[v].val - tree[u].val;
        } else if (l == r) {
            return 0;
        }
        int mid = (l + r) >> 1;
        if (tmp[mid] >= k) {
            return query(tree[u].ls, tree[v].ls, l, mid, k);
        } else {
            return tree[tree[v].ls].val - tree[tree[u].ls].val +
                query(tree[u].rs, tree[v].rs, mid + 1, r, k);
        }
    }
    i64 query(i64 l, i64 r, i64 k) {
        return query(rt[l - 1], rt[r], 1, len, k);
    }
} pst;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    pst.init(n, a);
    cin >> q;
    i64 lst = 0;
    while (q--) {
        i64 l, r, k;
        cin >> l >> r >> k;
        l ^= lst, r ^= lst, k ^= lst;
        lst = pst.query(l, r, k);
        cout << lst << endl;
    }
    return 0;
}
