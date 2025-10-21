struct Comb {
    vector<mint> fac, facInv;

    void init(int n) {
        fac.resize(n + 1), facInv.resize(n + 1);
        fac[0] = facInv[0] = 1;
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i;
        }
        facInv[n] = fac[n].inv();
        for (int i = n; i > 1; i--) {
            facInv[i - 1] = facInv[i] * i;
        }
    }

    mint C(int n, int m) {
        if (m < n || n < 0) {
            return 0;
        }
        return fac[m] * facInv[m - n] * facInv[n];
    }

    mint A(int n, int m) {
        if (m < n || n < 0) {
            return 0;
        }
        return fac[m] * facInv[m - n];
    }
} comb;
