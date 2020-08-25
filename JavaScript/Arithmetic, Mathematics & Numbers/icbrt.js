function icbrt(x) {
    var b = 64 - (32 /* bit width */);
    var r0 = 1, r1;

    if (0 == x) return 0; // cbrt(0)
    r0 <<= (b + 2) / 3; // ceil(b / 3)

    do {
        r1 = r0;
        r0 = (2 * r1 + x / (r1 * r1)) / 3;
    } while (r0 < r1);

    return r1
}
