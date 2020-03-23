/* Function > Is Palindrome --- REDACT (Lapys) */
function is_palindrome(string) {
    var formattedString = string.toLowerCase().replace(/[^0-9A-Za-z]*/g, "");
    var formattedStringLength = formattedString.length;

    for (var endIterator = formattedStringLength - 1, startIterator = 0; endIterator > startIterator; (--endIterator, ++startIterator))
    if (formattedString.charAt(endIterator) != formattedString.charAt(startIterator))
    return false;

    return true
}
