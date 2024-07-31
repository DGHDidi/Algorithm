{
    "Power Function C++": {
        "prefix": "power",
        "body": [
            "template<class T>",
            "constexpr T power(T a, i64 b) {",
            "    T res = 1;",
            "    while (b) {",
            "        if (b & 1) {",
            "            res = res * a;",
            "        }",
            "        b >>= 1;",
            "        a = a * a;",
            "    }",
            "    return res;",
            "}"
        ],
        "description": "Power Function C++"
    }
}
