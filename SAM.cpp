struct SuffixAutomaton {
    static const int ALPHA = 26; // 字母表大小，小写英文字母

    struct State {
        int next[ALPHA]; // right-extend 转移
        int link;        // 后缀链接
        int len;         // 该状态代表的最长子串长度
        long long occ;   // endpos 数（出现次数，build 后需调 calc_occ）

        State() {
            memset(next, -1, sizeof(next));
            link = -1;
            len = 0;
            occ = 0;
        }
    };

    vector<State> st;
    int last; // 当前整串对应的状态编号（最新）

    SuffixAutomaton(int maxLen = 0) {
        if (maxLen > 0) init(maxLen);
    }

    // 预分配，准备构造 SAM（maxLen = 原串最大长度）
    void init(int maxLen) {
        st.clear();
        st.reserve(2 * maxLen + 5);
        st.push_back(State()); // 状态 0：初始状态，表示空串
        last = 0;
    }

    // 插入一个字符，在线构造 SAM
    void extend(char ch) {
        int c = ch - 'a';
        int cur = (int)st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;
        st[cur].occ = 1; // 每新建一个状态，起初它作为一个 endpos 出现一次

        int p = last;
        // 1. 沿后缀链接不断补上缺失的转移
        for (; p != -1 && st[p].next[c] == -1; p = st[p].link) {
            st[p].next[c] = cur;
        }

        if (p == -1) {
            // 2. 走到根（-1），直接连到 0
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                // 3. 可以直接挂在 q 下
                st[cur].link = q;
            } else {
                // 4. 需要 clone 状态 q
                int clone = (int)st.size();
                st.push_back(st[q]);        // 复制 q 的所有信息
                st[clone].len = st[p].len + 1;
                // clone.occ 不参与初始统计，在 calc_occ 时统一处理

                for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = clone;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // 用一个字符串一次性 build
    void build(const string &s) {
        init((int)s.size());
        for (char ch : s) extend(ch);
    }

    // 计算每个状态的 occ（endpos 大小）
    // 调用前：每 extend 一次已设 st[cur].occ = 1
    // 调用后：st[v].occ = 原串中所有属于 v 状态的子串的出现次数
    void calc_occ() {
        int sz = (int)st.size();
        vector<int> order(sz);
        iota(order.begin(), order.end(), 0);
        // 按长度从大到小排序，保证先把长的往短的 link 传
        sort(order.begin(), order.end(),
             [&](int a, int b) { return st[a].len > st[b].len; });
        for (int v : order) {
            if (st[v].link != -1) {
                st[st[v].link].occ += st[v].occ;
            }
        }
    }

    // 1) 不同子串个数
    // 公式：sum_{v>0} (len[v] - len[link[v]])
    long long count_distinct_substrings() const {
        long long ans = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            ans += st[v].len - st[st[v].link].len;
        }
        return ans;
    }

    // 2) 最长重复子串长度（出现至少 2 次的子串的最大长度）
    // 先调用 calc_occ()，再用本函数
    int longest_repeated_substring() const {
        int best = 0;
        for (int v = 1; v < (int)st.size(); ++v) {
            if (st[v].occ >= 2) {
                best = max(best, st[v].len);
            }
        }
        return best;
    }

    // 3) 查询某个给定模式串 pat 在原串中出现了多少次
    // 注意：必须先 build + calc_occ 之后再用
    long long count_occurrences(const string &pat) const {
        int v = 0;
        for (char ch : pat) {
            int c = ch - 'a';
            if (st[v].next[c] == -1) return 0;
            v = st[v].next[c];
        }
        return st[v].occ; // 模式串对应状态 v 的 endpos 数
    }

    // 4) 与另一个字符串 t 的最长公共子串长度
    // 用 SAM(s) 去匹配 t
    int lcs_with(const string &t) const {
        int v = 0;       // 当前在 SAM 中的状态
        int l = 0;       // 当前匹配长度
        int best = 0;    // 最佳长度
        // 如果你想要 LCS 的结尾位置，可以额外记一下 pos

        for (char ch : t) {
            int c = ch - 'a';
            if (st[v].next[c] != -1) {
                // 能直接扩展
                v = st[v].next[c];
                ++l;
            } else {
                // 不行，就顺着 link 往上跳，直到有 next[c] 或回到 0
                while (v != -1 && st[v].next[c] == -1) {
                    v = st[v].link;
                }
                if (v == -1) {
                    v = 0;
                    l = 0;
                } else {
                    l = st[v].len + 1;
                    v = st[v].next[c];
                }
            }
            best = max(best, l);
        }
        return best;
    }
};
