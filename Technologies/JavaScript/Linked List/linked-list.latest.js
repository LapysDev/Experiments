/* Class > Linked List --- NOTE (Lapys) -> Not sure if this is a Stack, though... */
class LinkedList {
    // Modification > Node
    static #Node = class Node {
        // Initialization > (Next Node, Value)
        #nextNode;
        #value;

        // [Constructor]
        constructor(value) {
            // Modification > Target > (Next Node, Value)
            this.#nextNode = null;
            this.#value = value ?? undefined
        }

        // Modification > Next
        get next() {
            // Logic > ...
            if (this instanceof Node) return this.#nextNode;
            else throw new TypeError("Illegal invocation")
        }

        set next(node) {
            // Logic
            if (this instanceof Node)
                // Logic > ...
                if (node instanceof Node) this.#nextNode = node;
                else throw new TypeError("Argument must be an instance of `Node`");

            else
                // Error
                throw new TypeError("Illegal invocation")
        }

        // Method > ...
        toString() { return String(this.valueOf()) }
        valueOf() { return this.#value }
    };

    // Initialization > (Current, First) [Node]
    #current;
    #first;

    // [Constructor]
    constructor() {
        // Modification > Target > (Current, First) [Node]
        this.#current = new LinkedList.#Node;
        this.#first = this.#current
    }

    // Modification > Length
    get length() {
        // Logic
        if (this instanceof LinkedList) {
            // Global > Evaluation
            var evaluation = 0;

            // Loop > Update > Evaluation
            for (var node = this.#first.next; node !== null; node = node.next) evaluation++;

            // Return
            return evaluation
        }

        else
            // Error
            throw new TypeError("Illegal invocation")
    }

    // Method --- NOTE (Lapys) -> The arguments could be a `Node` object or any other odd value.
        // Add
        add(argument) {
            // Logic
            if (this instanceof LinkedList) {
                // Modification > (Target > Current Node)( > Next)
                this.#current.next = typeof argument == "object" && argument instanceof LinkedList.#Node ? argument : new LinkedList.#Node(argument);
                this.#current = this.#current.next
            }

            else
                // Error
                throw new TypeError("Illegal invocation")
        }

        // Includes
        includes(argument) {
            // Logic
            if (this instanceof LinkedList) {
                // Loop > Logic( > Return)
                for (var node = this.#first; node !== null; node = node.next) if (node === argument || node.valueOf() == argument) return true;
                return false
            }

            else
                // Error
                throw new TypeError("Illegal invocation")
        }

        // Remove
        remove(argument) {
            // Logic
            if (this instanceof LinkedList) {
                // Loop > Logic
                for (var current = this.#first, recent = null; current !== null; (recent = current, current = current.next))
                if (current === argument || current.valueOf() == argument) {
                    // Modification > Recent > Next; ...
                    recent.next = current.next;
                    break
                }
            }

            else
                // Error
                throw new TypeError("Illegal invocation")
        }

        // ...
        toString() { return "[object LinkedList]" }
}
