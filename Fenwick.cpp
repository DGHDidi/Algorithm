{
	"Fenwick Structure": {
		"prefix": "fenwick",
		"body": [
			"template <typename T>",
			"struct Fenwick {",
			"\tint n;",
			"\tvector<T> bit;",
			"",
			"\tFenwick(int _n) : n(_n), bit(n + 1) {}",
			"\tFenwick(vector<T> a) {",
			"\t\tn = a.size(), bit.resize(n + 1);",
			"\t\tfor (int i = 0; i < n; i++) {",
			"\t\t\tadd(i + 1, a[i]);",
			"\t\t}",
			"\t}",
			"",
			"\tint lowbit(int x) {",
			"\t\treturn x & -x;",
			"\t}",
			"",
			"\tvoid add(int pos, T val) {",
			"\t\tfor (int i = pos; i <= n; i += lowbit(i)) {",
			"\t\t\tbit[i] += val;",
			"\t\t}",
			"\t}",
			"",
			"\tT sum(int pos) {",
			"\t\tT res = 0;",
			"\t\tfor (int i = pos; i; i -= lowbit(i)) {",
			"\t\t\tres += bit[i];",
			"\t\t}",
			"\t\treturn res;",
			"\t}",
			"",
			"\tT rangeSum(int l, int r) {",
			"\t\treturn sum(r) - sum(l - 1);",
			"\t}",
			"};"
		],
		"description": "Fenwick Tree"
	}
}
