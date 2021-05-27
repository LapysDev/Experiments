void function() {
    onkeyup = function(event) {
        if ("Escape" == event.key) {
            if ("function" == typeof getSelection) getSelection().removeAllRanges();
            else if ("undefined" != typeof document.selection) document.selection.empty()
        }
    }
}();
