character = 'L', range = 10000;

console.time("PROCESSING CHARACTER UNICODE");
for (var iterator = 0; iterator ^ range; iterator += 1) {
    var code = iterator;

    if (code < 10) code = "000" + code;
    else if (code < 100) code = "00" + code;
    else if (code < 1e3) code = '0' + code;

    code = code.toString();

    if (eval("'\\u" + code + '\'') == character) {
        console.log("CHARACTER UNICODE", iterator);
        break
    }
}
console.timeEnd("PROCESSING CHARACTER UNICODE")
