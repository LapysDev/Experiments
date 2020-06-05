/* Modification > String > Encode --- REDACT (Lapys) */
String.encode = function encode(string) {
    var evaluation = "";

    for (var iterator = string.length; ~--iterator; ) {
        var character = string.charAt(iterator);

        if (/[A-Z]/.test(character)) {
            var index = String.prototype.charCodeAt.call(character) + 13;
            var end = String.prototype.charCodeAt.call('Z');
            var start = String.prototype.charCodeAt.call('A');

            evaluation = String.fromCharCode(index > end ? start + (index - end) - 1 : index) + evaluation;
        } else evaluation = character + evaluation;
    }

    return evaluation
};
