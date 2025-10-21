// 二维数点模板
struct CountPoints {
    int n, q, Y; // 点的个数 查询个数 最大纵坐标
    vector<pair<int, int>> points;

    struct Query {
        int x, y, yy, idx, sign;
    };
    vector<Query> queries;

    CountPoints(int _n, int _q, int _Y) : n(_n), q(_q), Y(_Y) {
        points.reserve(n);
        queries.reserve(q * 2);
    }

    void addPoint(int x, int y) {
        points.push_back({x, y});
    }

    void addQuery(int x, int xx, int y, int yy, int idx) {
        if (x > xx || y > yy) {
            cerr << "(!) Invalid Query Range" << endl;
            return;
        }
        queries.push_back({xx, y, yy, idx, 1});
        queries.push_back({x - 1, y, yy, idx, -1});
    }

    vector<int> work() {
        sort(points.begin(), points.end());
        sort(queries.begin(), queries.end(), [](const Query &a, const Query &b) {
            return a.x ^ b.x ? a.x < b.x : a.y < b.y;
            });

        vector<int> ans(q + 1);
        Fenwick<int> fw(Y + 1);
        int p = 0;
        for (const auto &q : queries) {
            while (p < n && points[p].first <= q.x) {
                fw.add(points[p].second, 1);
                p++;
            }
            ans[q.idx] += q.sign * fw.rangeSum(q.y, q.yy);
        }

        return ans;
    }
};
