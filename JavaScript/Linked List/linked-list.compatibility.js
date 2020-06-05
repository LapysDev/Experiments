/* Class > Linked List
        --- NOTE (Lapys) -> Not sure if this is a Stack, though...
        --- WARN (Lapys) -> Lacks private methods & properties.
*/
function LinkedList() {
    // Logic
    if (this instanceof LinkedList) {
        // Modification > Target > (Current, First) [Node]
        Object.defineProperty(this, "current", {configurable: false, enumerable: false, value: new LinkedList.Node, writable: true});
        Object.defineProperty(this, "first", {configurable: false, enumerable: false, value: this.current, writable: true})
    }

    else
        // Error
        throw new TypeError("Constructor must be called with `new`")
}

/* Modification > Linked List */
    // Node
    Object.defineProperty(LinkedList, "Node", {
        configurable: false,
        enumerable: false,
        value: (function() {
            /* Class > Node */
            function Node(value) {
                // Logic
                if (this instanceof Node) {
                    // Initialization > Next Node
                    var nextNode = null;

                    // Modification > Target > (Next, Value)
                    Object.defineProperty(this, "next", {
                        configurable: false,
                        enumerable: false,
                        get: function next() {
                            // Logic > ...
                            if (this instanceof Node) return nextNode;
                            else throw new TypeError("Illegal invocation")
                        },
                        set: function next(node) {
                            // Logic
                            if (this instanceof Node)
                                // Logic > ...
                                if (node instanceof Node) nextNode = node;
                                else throw new TypeError("Argument must be an instance of `Node`");

                            else
                                // Error
                                throw new TypeError("Illegal invocation")
                        }
                    });
                    Object.defineProperty(this, "value", {configurable: false, enumerable: false, value: arguments.length ? (value === null || value === undefined ? undefined : value) : undefined, writable: true})
                }

                else
                    // Error
                    throw new TypeError("Constructor must be called with `new`")
            }

            // Modification > (Node > Prototype) > ...
            Object.defineProperty(Node.prototype, "toString", {configurable: false, enumerable: false, value: function toString() { return String(this.valueOf()) }, writable: false});
            Object.defineProperty(Node.prototype, "valueOf", {configurable: false, enumerable: false, value: function valueOf() { return this.value }, writable: false});

            // Return
            return Node
        })(),
        writable: false
    });

    // Prototype
        // Add
        Object.defineProperty(LinkedList.prototype, "add", {
            configurable: false,
            enumerable: false,
            value: function add(argument) {
                // Logic
                if (this instanceof LinkedList) {
                    // Modification > (Target > Current Node)( > Next)
                    this.current.next = typeof argument == "object" && argument instanceof LinkedList.Node ? argument : new LinkedList.Node(argument);
                    this.current = this.current.next
                }

                else
                    // Error
                    throw new TypeError("Illegal invocation")
            },
            writable: false
        });

        // Includes
        Object.defineProperty(LinkedList.prototype, "includes", {
            configurable: false,
            enumerable: false,
            value: function includes(argument) {
                // Logic
                if (this instanceof LinkedList) {
                    // Loop > Logic( > Return)
                    for (var node = this.first; node !== null; node = node.next) if (node === argument || node.valueOf() == argument) return true;
                    return false
                }

                else
                    // Error
                    throw new TypeError("Illegal invocation")
            },
            writable: false
        });

        // Length
        Object.defineProperty(LinkedList.prototype, "length", {
            configurable: false,
            enumerable: false,
            get: function length() {
                // Logic
                if (this instanceof LinkedList) {
                    // Global > Evaluation
                    var evaluation = 0;

                    // Loop > Update > Evaluation
                    for (var node = this.first.next; node !== null; node = node.next) evaluation++;

                    // Return
                    return evaluation
                }

                else
                    // Error
                    throw new TypeError("Illegal invocation")
            }
        });

        // Remove
        Object.defineProperty(LinkedList.prototype, "remove", {
            configurable: false,
            enumerable: false,
            value: function remove(argument) {
                // Logic
                if (this instanceof LinkedList) {
                    // Loop > Logic
                    for (var current = this.first, recent = null; current !== null; (recent = current, current = current.next))
                    if (current === argument || current.valueOf() == argument) {
                        // Modification > Recent > Next; ...
                        recent.next = current.next;
                        break
                    }
                }

                else
                    // Error
                    throw new TypeError("Illegal invocation")
            },
            writable: false
        });

        // ...
        Object.defineProperty(LinkedList.prototype, "toString", {configurable: false, enumerable: false, value: function toString() { return "[object LinkedList]" }, writable: false})
