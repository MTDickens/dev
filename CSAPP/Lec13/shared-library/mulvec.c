void mulvec(long *v1, long *v2, long *vdest, unsigned int size) {
    for (int i = 0; i != size; ++i) {
        vdest[i] = v1[i] * v2[i];
    }
}