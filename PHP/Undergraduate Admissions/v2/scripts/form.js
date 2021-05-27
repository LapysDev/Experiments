/* ... */
void function() {
    /* Constant > (Inputs, (Login, Sign-Up) Form, Queries, Warning) */
    var inputs = document.getElementsByTagName("input");

    var loginForm = document.getElementById("login");
    var signupForm = document.getElementById("signup");

    var queries = location.href.replace(new RegExp("[^\\?]{0,}\\?", 'g'), "").match(new RegExp("[^=]{1,}(=[^&]{0,}|)", 'g')).map(function(query) { return query.split('=') });

    var warning = document.createElement("div");

    /* Function */
        // Authenticate
        function authenticate(event) {
            // Loop
            for (var iterator = inputs.length - 1; ~iterator; --iterator) {
                // Initialization > Input
                var input = inputs.item(iterator);

                // Logic
                switch (input.getAttribute("type")) {
                    // [Number], [Text]
                    case "number": input.value || (input.value = Number.parseInt(input.getAttribute("min") || 0)) || 0; break;
                    case "text": {
                        // Initialization > (Invalid, Value)
                        var invalid, value = input.value || "";

                        // ...
                        invalid = value.match(new RegExp("[^A-z \-]"));
                        if (null !== invalid) { event.preventDefault(); return warn(input, "Unexpected character '" + ('\'' == invalid ? "&rsquo;" : invalid) + "' used in field") }

                        invalid = value.match(new RegExp("[a-z][A-Z]"));
                        if (null !== invalid) { event.preventDefault(); return warn(input, "Unexpected format used for field") }
                    }
                }
            }
        }

        // Clear
        function clear(duration) {
            // ...
            for (var iterator = inputs.length - 1; ~iterator; --iterator)
            inputs.item(iterator).removeAttribute("state");

            // Modification > Warning > ...
            warning.innerHTML = "";

            warning.setAttribute("hidden", "");
            warning.setAttribute("style", "transition-duration: " + duration + "ms; " + (warning.getAttribute("style") || "").replace(new RegExp("transition\\-duration: [0-9]{1,}ms(;|) {0,}"), ""))
        }

        // Warn
        function warn(input, message) {
            // Constant > Bounds
            var bounds = input.getBoundingClientRect();

            // Modification > ...
            input.setAttribute("state", "invalid");

            warning.innerHTML = message;
            warning.removeAttribute("hidden");
            warning.setAttribute("style", "left: " + bounds.left + "px; top: " + (bounds.top - (bounds.bottom - bounds.top)) + "px")
        }

    /* Insertion */
    document.body.appendChild(warning);

    /* Modification > Warning > Identity */
    warning.setAttribute("id", "warning");

    /* Event > ... */
    onbeforeprint = function() { clear(0e0) };
    onbeforeunload = function() { clear(0e0) };
    onblur = function() { clear(0e0) };
    onmousedown = function() { clear(3e2) };

    loginForm.onsubmit = authenticate;
    signupForm.onsubmit = authenticate;

    // ...
    for (var iterator = queries.length - 1; ~iterator; --iterator) {
        // Constant > (Query, ...)
        var query = queries[iterator];
        var name = query[0];
        var value = query.length > 1 ? query[1] : "";

        // ... Update > (Name, Value)
        for (var trimming = true; trimming; ) switch (name.charAt(0)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': name = name.slice(1); break; default: trimming = false }
        for (var trimming = true; trimming; ) switch (name.charAt(name.length - 1)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': name = name.slice(0, -1); break; default: trimming = false }

        for (var trimming = true; trimming; ) switch (value.charAt(0)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': value = value.slice(1); break; default: trimming = false }
        for (var trimming = true; trimming; ) switch (value.charAt(value.length - 1)) { case ' ': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': value = value.slice(0, -1); break; default: trimming = false }

        // ...
        switch (name) {
            case "submission-error": warn(null == value.match(new RegExp("Student with registration number '[0-9]{8}' already exists")) ? inputs.item(0) : inputs["registrationField"], query.length > 1 ? value : "Error in signing up"); break;
            default: /* Do nothing... */
        }
    }

    for (var iterator = inputs.length - 1; ~iterator; --iterator)
    void function(input) {
        switch (input.getAttribute("type")) {
            // [Number], [Text]
            case "text": /* ... */ break;
            case "number": {
                // Function > Validate
                function validate() {
                    // Initialization > ... Value
                    var maximumLength = input.getAttribute("maxlength");
                    var maximumValue = input.getAttribute("max");
                    var minimumLength = input.getAttribute("minlength");
                    var minimumValue = input.getAttribute("min");

                    var value = input.value;

                    // ... Update > ... Value
                    maximumLength = null === maximumLength ? 48 : Number.parseInt(maximumLength || 0);
                    maximumValue = null === maximumValue ? Infinity : Number.parseInt(maximumValue || 0);
                    minimumLength = null === minimumLength ? 0 : Number.parseInt(minimumLength || 0);
                    minimumValue = null === minimumValue ? -Infinity : Number.parseInt(minimumValue || 0);

                    if (maximumLength < value.length) value = value.slice(0, maximumLength);
                    for (var length = Math.max(0, minimumLength - value.length); length; --length) value = '0' + value;

                    // Logic
                    if (value) {
                        // Update > Value
                        value = Number.parseInt(value);
                        (value > maximumValue) && (value = maximumValue);
                        (value < minimumValue) && (value = minimumValue);

                        // Modification > Input > Value
                        input.value = value
                    }
                }

                // Event > Input > (Change, Focus, Input, Key ..., Select)
                input.onchange = validate;
                input.onfocus = validate;
                input.oninput = validate;
                input.onkeydown = validate;
                input.onselect = validate
            } break;
        }
    }(inputs.item(iterator))
}();
