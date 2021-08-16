/* ... --- REDACT (Lapys) --- WARN (Lapys) -> Native features are not strictly asserted. */
void function(GLOBAL) {
    /* Constant > Collection ... ->> Keep record of cached `HTMLCollection`s and their mutation observers. */
    var COLLECTION_LIST = {length: 0}; // --> []
    var COLLECTION_OBSERVERS = {length: 0}; // --> []

    /* Class > HTML Collection
        --- NOTE ---
            #Lapys: The features & internals of this "class" are not necessary
                for the demonstration of the following DOM element selection functions.
    */
    function HTMLCollection(document, data, length /* ->> Prepare a base range of properties to self-define onto the `HTMLCollection`. */) {
        var collection = this;

        var defineOwnIndex;
        var documentElement = "object" == typeof document.documentElement ? document.documentElement : document.all[0];
        var information = {
            collection: null,
            constraints: { className: null, id: null, name: null, selector: null, tagName: null },
            valueOf: function valueOf() { return collection }
        };

        // ...
        if (false == (collection instanceof HTMLCollection))
        throw new TypeError("Failed to construct `HTMLCollection`: Please use the `new` operator, this DOM object constructor cannot be called as a function");

        // ... ->> Self-define the properties from `0` to `length` to prevent referencing underlying properties.
        defineOwnIndex = (
            "function" == typeof Object.defineProperty ?
            function defineOwnIndex(index) {
                // ->> Ideally the version of this method works on primitives and not just `Element` objects.
                Object.defineProperty(collection, index, {
                    configurable: true, enumerable: false, get: undefined,
                    set: function(element) {
                        Object.defineProperty(collection, index, {
                            configurable: true, enumerable: true,
                            value: element, writable: false
                        })
                    }
                })
            } :

            "function" == typeof collection.__defineGetter__ && "function" == typeof collection.__defineSetter__ ?
            function defineOwnIndex(index) {
                collection.__defineSetter__(index, function(element) {
                    collection.__defineGetter__(index, function() { return element });
                    collection.__defineSetter__(index, function() { throw new Error("Object doesn't support this property or method") /* --> TypeError */ })
                })
            } :

            function defineOwnIndex(index) {
                // ... ->> Last ditch effort to self-define the `index` property onto the `HTMLCollection`.
                collection[index] = undefined
            }
        );

        // ... ->>
        function updateOwn() {}

        // ... ->> Define this `HTMLCollection` with its own self-referenced indices.
        collection.length = length;
        for (var iterator = length - 1; ~iterator; --iterator) defineOwnIndex(iterator.toString());

        // ... ->> Cache `information` about this `HTMLCollection`. --> COLLECTION_LIST.push(collection);
        for (var constraint in constraints)
        information.constraints[constraint] = constraints[constraint];

        "function" == typeof Object.defineProperty ?
            Object.defineProperty(COLLECTION_LIST, (COLLECTION_LIST.length++).toString(), { configurable: true, enumerable: true, value: information, writable: true }) :
        "function" == typeof COLLECTION_LIST.__defineGetter__ && "function" == typeof COLLECTION_LIST.__defineSetter__ ?
            COLLECTION_LIST.__defineGetter__((COLLECTION_LIST.length++).toString(), function() { return information }) :
        void 0;

        // ... ->> Dynamically update the indices of this `HTMLCollection` to make it live.
        if ("function" /* --> "class" */ == typeof MutationObserver) { // ->> Never `disconnect()`s.
            var observing = false;

            (new MutationObserver(function(mutations, observer) {
                if (observing) return;

                updateOwn();
                observing = true; setTimeout(function() { observing = false })
            })).observe(documentElement, { attributeFilter: [], attributeOldValue: true, attribute: true, characterData: true, characterDataOldValue: true, childList: true, subtree: true })
        }

        else {
            var dummy = document.createElement("div");
            var supportsDOMMutationEvents = false;

            // ...
            if ("function" == typeof dummy.addEventListener) {
                dummy.addEventListener("DOMSubtreeModified", function() { supportsDOMMutationEvents = true });
                dummy.innerHTML = ' '
            }

            // ...
            if (supportsDOMMutationEvents)
                documentElement.addEventListener("DOMSubtreeModified", updateOwn);

            else if ("function" == typeof document.onpropertychange || null === document.onpropertychange) {
                // ...
                "function" == typeof Object.defineProperty ?
                    Object.defineProperty(COLLECTION_OBSERVERS, (COLLECTION_OBSERVERS.length++).toString(), { configurable: true, enumerable: true, value: updateOwn, writable: true }) :
                "function" == typeof COLLECTION_OBSERVERS.__defineGetter__ && "function" == typeof COLLECTION_OBSERVERS.__defineSetter__ ?
                    COLLECTION_OBSERVERS.__defineGetter__((COLLECTION_OBSERVERS.length++).toString(), function() { return updateOwn }) :
                void 0;

                // ...
                document.onpropertychange = function() {
                    for (var iterator = COLLECTION_OBSERVERS.length - 1; ~iterator; --iterator)
                    COLLECTION_OBSERVERS[iterator]()
                }
            }

            else {
                var delay = 0, timeoutID = null;

                // ... ->> Agreeably, the first invocation here to `observe()` is redundant.
                void function observe() {
                    updateOwn();

                    clearTimeout(timeoutID);
                    timeoutID = setTimeout(observe, delay == 100 ? ++delay : delay)
                }()
            }
        }
    }
        // ... --- MINIFY (Lapys)
        HTMLCollection.prototype = {
            // ... ->> Inspired from the native `NodeList` interface.
            entries: function entries() { var collection = this, index = -1; return /* --> Array Iterator */ { next: function next() { (index == collection.length) || ++index; return { done: index == collection.length, value: index == collection.length ? undefined : [index, collection[index]] } } } },
            forEach: function forEach(handler, thisArg) { for (var iterator = 0, length = this.length; iterator != length; ++iterator) handler.call(thisArg, this[iterator], iterator, this) },
            item: function item(index) { index = Number.parseInt(index) || 0; return index < this.length ? this[index] : undefined },
            keys: function keys() { var collection = this, index = -1; return /* --> Array Iterator */ { next: function next() { (index == collection.length) || ++index; return { done: index == collection.length, value: index == collection.length ? undefined : index } } } },
            values: function values() { var collection = this, index = -1; return /* --> Array Iterator */ { next: function next() { (index == collection.length) || ++index; return { done: index == collection.length, value: index == collection.length ? undefined : collection[index] } } } },

            // ... ->> Inspired from the native `HTMLCollection` interface.
            item: function item(index) { var name = arguments[0]; index = Number.parseInt(index) || 0; return index < this.length ? this[index] : (index == name ? null : HTMLCollection.prototype.namedItem.call(this, name)) },
            namedItem: function namedItem(name) { for (var iterator = 0, length = this.length; iterator != length; ++iterator) { var element = this[iterator]; var elementIdentity = element.getAttribute("id"), elementName = element.getAttribute("name"); if ((null !== elementIdentity && elementIdentity == name) || (null !== elementName && elementName == name)) return element } return null },

            // ...
            length: undefined
        };
            // ...
            "function" == typeof Object.defineProperty ? // ->> Ideally the version of this method works on primitives and not just `Element` objects.
                Object.defineProperty(HTMLCollection.prototype, "length", { configurable: true, enumerable: true, get: function length() { throw new TypeError("Illegal invocation") }, set: undefined }) :
            "function" == typeof HTMLCollection.prototype.__defineGetter__ ?
                HTMLCollection.prototype.__defineGetter__("length", function length() { throw new TypeError("Illegal invocation") }) :
            void 0;


    /* Functions
        --- REDACT (Lapys)
        --- WARN ---
            #Lapys: Native features are not strictly asserted.
    */
        // Get Elements By Class Name
        GLOBAL["GetElementsByClassName"] =
        function GetElementsByClassName(document, className) {
            var classList, classTokenCount, collection, matched;
            var evaluation = [];

            // ... ->> Request data to populate the static `HTMLCollection` with.
            // if ("function" == typeof document.getElementsByClassName) { collection = document.getElementsByClassName(className); matched = true }
            if ("undefined" == typeof document.all && undefined !== document.all) { collection = document.all; matched = false }
            else return null;

            // ... ->> The native `document.getElementsByClassName(...)` `HTMLCollection` is unavailable for querying DOM `Element`s of the specified `className`.
            if (false == matched) {
                var classToken = "";

                classList = [];
                classTokenCount = 0;

                for (var iterator = className.length; ~iterator--; ) {
                    var character = ~iterator ? className.charAt(iterator) : null;
                    switch (character) {
                        case null: case ' ': classList.push(classToken); classToken = ""; ++classTokenCount; break;
                        default: classToken = character + classToken
                    }
                }
            }

            // ...
            for (var iterator = 0, length = collection.length; iterator != length; ++iterator) {
                var element = collection[iterator];
                var elementMatched = false;

                // ...
                if (matched) elementMatched = true;
                else {
                    var elementClassName = element.getAttribute("class");

                    if (null !== elementClassName) {
                        var elementClassList = [];
                        var elementClassToken = "";

                        for (var subiterator = elementClassName.length; ~subiterator--; ) {
                            var character = ~subiterator ? elementClassName.charAt(subiterator) : null;
                            switch (character) {
                                case null: case ' ': elementClassList.push(elementClassToken); elementClassToken = ""; break;
                                default: elementClassToken = character + elementClassToken
                            }
                        }

                        if (classTokenCount == elementClassList.length) {
                            var elementClassTokenMatchCount = 0;

                            for (var classListIterator = 0; classTokenCount != classListIterator && elementClassTokenMatchCount == classListIterator; ++classListIterator)
                            for (var elementClassListIterator = elementClassList.length - 1; elementClassTokenMatchCount == classListIterator && ~elementClassListIterator; --elementClassListIterator) {
                                if (classList[classListIterator] == elementClassList[elementClassListIterator])
                                ++elementClassTokenMatchCount
                            }

                            if (classTokenCount == elementClassTokenMatchCount)
                            elementMatched = true
                        }
                    }
                }

                // ...
                if (elementMatched)
                evaluation.push(element)
            }

            // ...
            return evaluation
        };

        // Get Element By ID
        GLOBAL["GetElementById"] =
        function GetElementById(document, identity) {
            var evaluation = null;

            // ...
            if ("function" == typeof document.getElementById)
                evaluation = document.getElementById(identity);

            else if ("undefined" == typeof document.all && undefined !== document.all) {
                var collection = document.all;

                for (var iterator = 0, length = collection.length; null === evaluation && iterator != length; ++iterator) {
                    var element = collection[iterator];
                    var elementIdentity = element.getAttribute("id");

                    // ...
                    if (
                        null !== elementIdentity &&
                        elementIdentity == identity
                    ) evaluation = element
                }
            }

            // ...
            return evaluation
        };

        // Get Elements By Name
        GLOBAL["GetElementsByName"] =
        function GetElementsByName(document, name) {
            var collection, matched;
            var evaluation = [];

            // ...
            if ("function" == typeof document.getElementsByName) { collection = document.getElementsByName(name); matched = true }
            else if ("undefined" == typeof document.all && undefined !== document.all) { collection = document.all; matched = false }
            else return null;

            // ...
            for (var iterator = 0, length = collection.length; iterator != length; ++iterator) {
                var element = collection[iterator];
                var elementMatched = false;

                // ...
                if (matched) elementMatched = true;
                else {
                    var elementName = element.getAttribute("name");
                    elementMatched = null !== elementName && name == elementName
                }

                // ...
                if (elementMatched)
                evaluation.push(element)
            }

            // ...
            return evaluation
        };

        // Get Elements By Tag Name
        GLOBAL["GetElementsByTagName"] =
        function GetElementsByTagName(document, tagName /* --> localName */) {
            var collection, matched;
            var evaluation = [];

            // ...
            if ("function" == typeof document.getElementsByTagName) { collection = document.getElementsByTagName(tagName); matched = true }
            else if (tagName == 'a' && "object" == typeof document.anchors) { collection = document.anchors; matched = true }
            else if (tagName == "applet" && "object" == typeof document.applets) { collection = document.applets; matched = true }
            else if (tagName == "embed" && "object" == typeof document.plugins) { collection = document.plugins; matched = true }
            else if (tagName == "form" && "object" == typeof document.forms) { collection = document.forms; matched = true }
            else if (tagName == "img" && "object" == typeof document.images) { collection = document.images; matched = true }
            else if (tagName == "link" && "object" == typeof document.links) { collection = document.links; matched = true }
            else if (tagName == "object" && "object" == typeof document.embeds) { collection = document.embeds; matched = true }
            else if (tagName == "script" && "object" == typeof document.scripts) { collection = document.scripts; matched = true }
            else if ("undefined" == typeof document.all && undefined !== document.all) { collection = document.all; matched = false }
            else return null;

            // ...
            for (var iterator = 0, length = collection.length; iterator != length; ++iterator) {
                var element = collection[iterator];
                var elementMatched = false;

                // ...
                if (matched) elementMatched = true;
                else {
                    if ('*' == tagName) elementMatched = true;
                    else {
                        var elementTagName = element.tagName;
                        elementMatched = tagName == elementTagName || tagName == elementTagName.toLowerCase()
                    }
                }

                // ...
                if (elementMatched)
                evaluation.push(element)
            }

            // ...
            return evaluation
        };

        // Query Selector
        GLOBAL["QuerySelector"] =
        function QuerySelector(document, selector) {};

        // Query Selector All
        GLOBAL["QuerySelectorAll"] =
        function QuerySelectorAll(document, selector) {}
}("undefined" == typeof(frames) ? ("undefined" == typeof(self) ? ("undefined" == typeof(window) ? ("undefined" == typeof(global) ? ("undefined" == typeof(globalThis) ? (function() { return this })() : globalThis) : global) : window) : self) : frames);
