long incr(long *xp, long y) {
    xp += y;
    return *xp;
}

long call_incr() {  
    long v1 = 15213;
    long v2 = incr(&v1, 3000);
    return v1 + v2;
}