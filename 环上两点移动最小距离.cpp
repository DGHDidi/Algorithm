bool btw(int x, int l, int r) {
    if (l <= r) {
        return l <= x && x <= r;
    } else {
        return l <= x || x <= r;
    }
}

// (al -> bl) (ar -> br)  不能相遇
int solve(int al, int ar, int bl, int br) {
    if (al == ar || bl == br) {
        return INF;
    }
    int ans = 1e9;  
    if (!btw(ar, al, bl) && !btw(bl, ar, br) || !btw(al, ar, br) && !btw(br, al, bl)) ans = min(ans, (bl - al + n) % n + (br - ar + n) % n);//全部顺时针 
    if (!btw(ar, bl, al) && !btw(al, br, ar) || !btw(al, br, ar) && !btw(br, bl, al)) ans = min(ans, (al - bl + n) % n + (ar - br + n) % n);//全部逆时针 
    if (!btw(ar, al, bl) && !btw(bl, br, ar) || !btw(al, br, ar) && !btw(br, al, bl)) ans = min(ans, (bl - al + n) % n + (ar - br + n) % n);//l 顺 r 逆 
    if (!btw(ar, bl, al) && !btw(bl, ar, br) || !btw(al, ar, br) && !btw(br, bl, al)) ans = min(ans, (al - bl + n) % n + (br - ar + n) % n);//l 逆 r 顺 
    return ans;
}
