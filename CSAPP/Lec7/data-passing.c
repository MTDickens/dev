long my_function(long x, long y, long *dest) {
    long t = x * y;
    *dest = t;
    return t;
}

int main () {
    long d;
    my_function(2l, 3l, &d);
    return 0;
}