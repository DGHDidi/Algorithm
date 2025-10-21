struct Hash {
    int N, P;
    string S;
    vector<mint> pw, ha;

    constexpr Hash() : N{}, P{}, S{} {}
    constexpr Hash(string s, int p) : N{s.size()}, P(p), S(" " + s) {
        pw.assign(N + 5, 0);
        ha.assign(N + 5, 0);
        pw[0] = 1;
        for (int i = 1; i <= N; i++) {
            pw[i] = pw[i - 1] * P;
            ha[i] = ha[i - 1] * P + S[i] - 'a' + 1;
        }
    }
    constexpr mint get(int l, int r) {
        return ha[r] - ha[l - 1] * pw[r - l + 1];
    }
};
