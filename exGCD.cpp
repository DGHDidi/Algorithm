pair<i64, i64> exGCD(i64 x, i64 y) {
    if (y == 0) {
        return {1, 0};
    }
    auto tmp = exGCD(y, x % y);
    return make_pair(tmp.second, tmp.first - (x / y) * tmp.second);
}
