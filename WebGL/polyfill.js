/* Polyfill > ... */
function check(EvaluationHandler, Onfail, Onsuccess) { requestAnimationFrame(function() { if (EvaluationHandler()) (Onsuccess === null) || Onsuccess(); else { (Onfail === null) || Onfail(); check(EvaluationHandler, Onfail || null, Onsuccess || null) } }) }
function repeat(Handler, iterationCount = +0) { const ITERATION_COUNT = iterationCount; while (iterationCount) Handler(ITERATION_COUNT - (iterationCount -= 1) - 1) }

Array.prototype.cutAt = function cutAt(Index) { this.splice(Index, 1) };
Array.prototype.distinctPush = function distinctPush(Element) { var ARGUMENTS_LENGTH = arguments.length; if (ARGUMENTS_LENGTH) { var argumentsIterator = ARGUMENTS_LENGTH; var INCLUDED = []; while (argumentsIterator) { Element = arguments[ARGUMENTS_LENGTH - (argumentsIterator -= 1) - 1]; if (!INCLUDED.includes(Element)) { INCLUDED.push(Element); this.includes(Element) || this.push(Element) } } } return this.length };
Array.prototype.foreach = Array.prototype.forEach;
Array.prototype.free = function free() { this.length = +0 };
Array.prototype.like = function like(Array) { let iterator = this.length; if (iterator ^ Array.length) return false; else { while (iterator) { iterator -= 1; if (this[iterator] != Array[iterator]) return false } return true } };
Array.prototype.remove = function remove(Element) { const LENGTH = this.length; if (LENGTH) { const INDEX = this.indexOf(Element); if (INDEX == LENGTH - 1) this.pop(); else if (~INDEX) this.cutAt(INDEX); return LENGTH - 1 } else return LENGTH };
Array.prototype.shift = function shift() { const ARRAY_LENGTH = this.length; if (ARRAY_LENGTH) { const ARRAY_FIRST_ELEMENT = this[+0]; var arrayIterator = ARRAY_LENGTH; while (arrayIterator) this[ARRAY_LENGTH - (arrayIterator -= 1) - 1] = this[ARRAY_LENGTH - arrayIterator]; this.length = ARRAY_LENGTH - 1; return ARRAY_FIRST_ELEMENT } };

Object.defineProperty(Element.prototype, "role", {configurable: true, enumerable: true, get: function role() { return this.getAttribute("role") }, set: function role(ElementAttributeValue) { this.setAttribute("role", ElementAttributeValue) }});
Object.defineProperty(Element.prototype, "state", {configurable: true, enumerable: true, get: function state() { return this.getAttribute("state") }, set: function state(ElementAttributeValue) { this.setAttribute("state", ElementAttributeValue) }});

const GLOBAL = (function() { try { return Function("return this")() || eval("this") } catch (error) {} return typeof self == "undefined" ? (typeof window == "undefined" ? (typeof global == "undefined" ? undefined : global) : window) : self })();

Object.defineProperty(HTMLElement.prototype, "script", {configurable: true, enumerable: true, get: function script() { return this.getAttribute("script") }, set: function script(JavaScriptEvaluationCode) { eval.tmp = this; eval("(function() {" + JavaScriptEvaluationCode + "}).call(eval.tmp)"); delete eval.tmp; this.setAttribute("script", JavaScriptEvaluationCode) }});

function Iterable(Object) { Object[Symbol.iterator] = function*() { for (const PROPERTY_IDENTIFIER in Object) yield this[PROPERTY_IDENTIFIER] }; return Object };

Math.avg = function avg() { var ARGUMENTS_LENGTH = arguments.length; if (ARGUMENTS_LENGTH) { var argumentsIterator = ARGUMENTS_LENGTH; var sum = arguments[argumentsIterator -= 1]; while (argumentsIterator) sum += arguments[argumentsIterator -= 1]; return sum / ARGUMENTS_LENGTH } else return NaN };
Math.int = function int(Number) { return Number - Number % 1 };
Math.perc = function perc(Base, Exponent) { return Exponent ? Base * (Exponent / 100) : +0 };
Math.degreesToRadians =  function degreesToRadians(Degrees) { return (Math.PI / 180) * Degrees };
Math.radiansToDegrees =  function radiansToDegrees(Radians) { return (180 / Math.PI) * Radians };
Math.sigmoid = function sigmoid(Number) { return Number / (1 + Math.abs(Number)) };

Object.defineProperty(Object.prototype, "def", {configurable: true, enumerable: false, value: function define(PropertyIdentifier, PropertyDescriptor) { Object.defineProperty(this, PropertyIdentifier, typeof PropertyDescriptor == "object" ? PropertyDescriptor : {value: PropertyDescriptor}) }, writable: true});
Object["QUASI_EVENT_HANDLER_DESCRIPTOR"] = function() { let quasiEventHandler = null; return {configurable: true, enumerable: true, get: function() { return quasiEventHandler }, set: function(QuasiEventHandler) { (QuasiEventHandler === null || typeof QuasiEventHandler == "function") && (quasiEventHandler = QuasiEventHandler); }} };

function Sequence(Routine, That, ArgumentListObject) { if (this instanceof Sequence) { this.arguments = ArgumentListObject; this["function"] = Routine; this.that = That } else throw new TypeError("`Sequence` constructor must be called with `new`") };
    Sequence.prototype.invoke = function invoke() { this["function"].apply(this.that, this.arguments) };

String.prototype.remove = function remove(Match) { return String.prototype.replace.call(this, Match, "") };

/* ... */
Array.from(document.all).forEach(function ExecuteDOMElementInlineScript(Element) { const ELEMENT_INLINE_SCRIPT = (Element.getAttribute("script") || "").replace(/ {0,}\n {0,}/g, ' '); ELEMENT_INLINE_SCRIPT && (Element.script = ELEMENT_INLINE_SCRIPT) })
