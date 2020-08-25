function ln(z) {
    var approximation = 0;

    function l(z) { var length = 0; while (z) { ++length; z = Math.trunc(z / 10) } return length || 1 }

    for (var k = 0, e = /*Math.pow(10, l(z))*/Infinity; k < e; ++k)
    approximation += (
        (1 / ((k * 2) + 1)) *
        Math.pow((z - 1) / (z + 1), (k * 2) + 1)
    );

    return approximation * 2
}
