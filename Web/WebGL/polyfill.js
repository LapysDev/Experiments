/* Polyfill > ... */
function assert(evaluation, exceptionHandler) { if (!evaluation) if (typeof exceptionHandler == "function") exceptionHandler(new Error("Assertion Failed!")); else throw new Error("Assertion Failed!") }
function defer(handler) { requestAnimationFrame(handler) }
function check(evaluationHandler, onfail, onsuccess = null) { defer(function() { if (typeof evaluationHandler == "function" ? evaluationHandler() : evaluationHandler) (onsuccess === null) || onsuccess(); else { (onfail === null) || onfail(); check(evaluationHandler, onfail || null, onsuccess || null) } }) }
function interval(handler, delay) { setInterval(handler, delay) }
function load(url, preventCache) { const PROMISES = {then: function then(handler) { PROMISES.waiting.push(handler); return PROMISES }, waiting: []}; const XML_HTTP_REQUEST = new XMLHttpRequest; document.pending += 1; XML_HTTP_REQUEST.addEventListener("loadend", function loadend(event) { document.pending -= 1; PROMISES.waiting.foreach(function(promise) { promise.call(XML_HTTP_REQUEST, {status: XML_HTTP_REQUEST.status, statusText: XML_HTTP_REQUEST.status, response: XML_HTTP_REQUEST.response, source: XML_HTTP_REQUEST.responseText, url: url}, event) }); XML_HTTP_REQUEST.removeEventListener("loadend", loadend) }); XML_HTTP_REQUEST.open("GET", url + (preventCache ? ("?cache-prevention-label=" + Math.random()).remove('.') : "")); XML_HTTP_REQUEST.send(); return PROMISES }
function preload(url) { const PROMISES = {then: function then(handler) { PROMISES.waiting.push(handler); return PROMISES }, waiting: []}; const XML_HTTP_REQUEST = new XMLHttpRequest; document.pending += 1; XML_HTTP_REQUEST.addEventListener("loadend", function loadend(event) { document.pending -= 1; PROMISES.waiting.foreach(function(promise) { promise({status: XML_HTTP_REQUEST.status, statusText: XML_HTTP_REQUEST.status, url: url}) }); XML_HTTP_REQUEST.removeEventListener("loadend", loadend) }); XML_HTTP_REQUEST.open("GET", url); XML_HTTP_REQUEST.send(); return PROMISES }
function repeat(repititionHandler, iterationCount) { if ((arguments.length || 1) ^ 1) { const ITERATION_COUNT = iterationCount; while (iterationCount) repititionHandler(ITERATION_COUNT - (iterationCount -= 1) - 1) } }
function timeout(handler, delay) { setTimeout(handler, delay) }

Object.defineProperty(Array.prototype, "clone", {configurable: true, enumerable: false, value: function clone() { let arrayClone = [], arrayIterator = this.length; try { arrayClone = new this.constructor } catch (error) { arrayClone = [] } while (arrayIterator) { arrayIterator -= 1; arrayClone[arrayIterator] = this[arrayIterator] } return arrayClone }, writable: true});
Object.defineProperty(Array.prototype, "cutAt", {configurable: true, enumerable: false, value: function cutAt(index) { Array.prototype.splice.call(this, index, 1) }, writable: true});
Object.defineProperty(Array.prototype, "distinctPush", {configurable: true, enumerable: false, value: function distinctPush(element) { const ARGUMENTS_LENGTH = arguments.length; if (ARGUMENTS_LENGTH) { let argumentsIterator = +0, arrayLength = this.length; while (argumentsIterator ^ ARGUMENTS_LENGTH) { const ARGUMENT = arguments[argumentsIterator]; let iterator = +0; while (iterator ^ argumentsIterator) { if ((argumentsIterator ^ iterator) && arguments[iterator] === ARGUMENT) { iterator = null; break } iterator += 1 } if (iterator !== null) { iterator = arrayLength; while (iterator) if (this[iterator -= 1] === ARGUMENT) { iterator = null; break } if (iterator !== null) { this[arrayLength] = ARGUMENT; arrayLength += 1 } } argumentsIterator += 1 } return arrayLength } return this.length }, writable: true});
Object.defineProperty(Array.prototype, "first", {configurable: true, enumerable: false, get: function first() { return this[+0] }});
Object.defineProperty(Array.prototype, "flat", {configurable: true, enumerable: false, value: (function() { const METHOD = Array.prototype.flat; return function flat(depth) { if (arguments.length) return Array.prototype.flat.call(this, depth); else { const FLAT_ARRAY = []; let flatArrayLength = +0; let branch = this, branchLength = this.length, branchIterator = branchLength; let trees = [], treesLength = +0; while (branchIterator) { const LEAF = branch[branchLength - (branchIterator -= 1) - 1]; if (Array.isArray(LEAF)) { trees[treesLength] = {branch: branch, iterator: branchIterator, length: branchLength}; treesLength += 1; branch = LEAF; branchLength = LEAF.length; branchIterator = branchLength } else { FLAT_ARRAY[flatArrayLength] = LEAF; flatArrayLength += 1 } while (!branchIterator && treesLength) { const BRANCH_DATA = trees[treesLength - 1]; branch = BRANCH_DATA.branch; branchIterator = BRANCH_DATA.iterator; branchLength = BRANCH_DATA.length; treesLength -= 1 } } return FLAT_ARRAY } } })(), writable: true});
Object.defineProperty(Array.prototype, "foreach", {configurable: true, enumerable: false, value: Array.prototype.forEach, writable: true}); delete Array.prototype["forEach"];
Object.defineProperty(Array.prototype, "free", {configurable: true, enumerable: false, value: function free() { this.length = +0; }, writable: true});
Object.defineProperty(Array.prototype, "last", {configurable: true, enumerable: false, get: function last() { return this[this.length - 1] }});
Object.defineProperty(Array.prototype, "like", {configurable: true, enumerable: false, value: function like(array) { let iterator = this.length; if (iterator ^ array.length) return false; else { while (iterator) { iterator -= 1; if (this[iterator] != array[iterator]) return false } return true } }, writable: true});
Object.defineProperty(Array.prototype, "random", {configurable: true, enumerable: false, value: function random() { return this[Math.int(Math.random() * this.length)] }, writable: true});
Object.defineProperty(Array.prototype, "repeat", {configurable: true, enumerable: false, value: function repeat(count) { const LENGTH = this.length, REPEAT = []; let iterator; while (count) { count -= 1; iterator = LENGTH; while (iterator) { iterator -= 1; REPEAT[(count * LENGTH) + (LENGTH - iterator - 1)] = this[LENGTH - iterator - 1] } } return REPEAT }, writable: true});
Object.defineProperty(Array.prototype, "remove", {configurable: true, enumerable: false, value: function remove(element) { let arrayLength = this.length, arrayIterator = arrayLength; while (arrayIterator) if (this[arrayIterator -= 1] === element) { arrayLength -= 1; while (arrayIterator ^ arrayLength) this[arrayIterator] = this[arrayIterator += 1]; this.length = arrayLength; arrayIterator = +0 } return arrayLength }, writable: true});
Object.defineProperty(Array.prototype, "shift", {configurable: true, enumerable: false, value: function shift() { const ARRAY_LENGTH = this.length; if (ARRAY_LENGTH) { const ARRAY_FIRST_ELEMENT = this[+0]; var arrayIterator = ARRAY_LENGTH; while (arrayIterator) this[ARRAY_LENGTH - (arrayIterator -= 1) - 1] = this[ARRAY_LENGTH - arrayIterator]; this.length = ARRAY_LENGTH - 1; return ARRAY_FIRST_ELEMENT } }, writable: true});

Object.defineProperty(Document.prototype, "pending", {configurable: true, enumerable: false, value: +0, writable: true}); // NOTE (Lapys) -> Represents the number of current executing asynchronous processes.

Object.defineProperty(Element.prototype, "role", {configurable: true, enumerable: true, get: function role() { return this.getAttribute("role") }, set: function role(ElementAttributeValue) { this.setAttribute("role", ElementAttributeValue) }});
Object.defineProperty(Element.prototype, "state", {configurable: true, enumerable: true, get: function state() { return this.getAttribute("state") }, set: function state(ElementAttributeValue) { this.setAttribute("state", ElementAttributeValue) }});

Object.defineProperty(Function.prototype, "defer", {configurable: true, enumerable: false, value: function defer() { defer(this) }, writable: true});

const GLOBAL = (function() { try { return Function("return this")() || eval("this") } catch (error) {} return typeof self == "undefined" ? (typeof window == "undefined" ? (typeof global == "undefined" ? undefined : global) : window) : self })();

Object.defineProperty(HTMLElement.prototype, "script", {configurable: true, enumerable: true, get: function script() { return this.getAttribute("script") }, set: function script(JavaScriptEvaluationCode) { eval.tmp = this; eval("(function() {" + JavaScriptEvaluationCode + "}).call(eval.tmp)"); delete eval.tmp; this.setAttribute("script", JavaScriptEvaluationCode) }});

function Iterable(ObjectArgument) { Object.defineProperty(ObjectArgument, Symbol.iterator, {configurable: true, enumerable: false, value: function*() { for (const PROPERTY_IDENTIFIER in ObjectArgument) yield this[PROPERTY_IDENTIFIER] }, writable: false}); return ObjectArgument };

Object.defineProperty(Math, "avg", {configurable: true, enumerable: false, value: function avg() { var ARGUMENTS_LENGTH = arguments.length; if (ARGUMENTS_LENGTH) { var argumentsIterator = ARGUMENTS_LENGTH; var sum = arguments[argumentsIterator -= 1]; while (argumentsIterator) sum += arguments[argumentsIterator -= 1]; return sum / ARGUMENTS_LENGTH } else return NaN }, writable: true});
Object.defineProperty(Math, "degreesToRadians", {configurable: true, enumerable: false, value: function degreesToRadians(degrees) { return (Math.PI / 180) * degrees }, writable: true});
Object.defineProperty(Math, "int", {configurable: true, enumerable: false, value: function int(number) { return number - number % 1 }, writable: true});
Object.defineProperty(Math, "perc", {configurable: true, enumerable: false, value: function perc(base, exponent) { return exponent ? base * (exponent / 100) : +0 }, writable: true});
Object.defineProperty(Math, "radiansToDegrees", {configurable: true, enumerable: false, value: function radiansToDegrees(radians) { return (180 / Math.PI) * radians }, writable: true});
Object.defineProperty(Math, "sigmoid", {configurable: true, enumerable: false, value: function sigmoid(number) { return number / (1 + Math.abs(number)) }, writable: true});

Object.defineProperty(Number, "isSafe", {configurable: true, enumerable: false, value: function isSafe(number) { return Number.isFinite(number) && !Number.isNaN(number) }, writable: true});

Object["QUASI_EVENT_HANDLER_DESCRIPTOR"] = function() { let quasiEventHandler = null; return {configurable: true, enumerable: false, get: function() { return quasiEventHandler }, set: function(QuasiEventHandler) { (QuasiEventHandler === null || typeof QuasiEventHandler == "function") && (quasiEventHandler = QuasiEventHandler); }} };
Object.defineProperty(Object.prototype, "assign", {configurable: true, enumerable: false, value: function assign(object) { for (const PROPERTY_IDENTIFIER in object) { const PROPERTY_VALUE = object[PROPERTY_IDENTIFIER]; PROPERTY_VALUE !== null && typeof PROPERTY_VALUE == "object" ? this[PROPERTY_IDENTIFIER].assign(PROPERTY_VALUE) : this[PROPERTY_IDENTIFIER] = PROPERTY_VALUE } return this }, writable: true});
Object.defineProperty(Object.prototype, "clone", {configurable: true, enumerable: false, value: function clone() { try { return Object.assign(new this.constructor, this) } catch (error) {} return Object.assign({}, this) }, writable: true});
Object.defineProperty(Object.prototype, "def", {configurable: true, enumerable: false, value: function define(propertyIdentifier, propertyDescriptor) { Object.defineProperty(this, propertyIdentifier, typeof propertyDescriptor == "object" ? propertyDescriptor : {value: propertyDescriptor}) }, writable: true});
Object.defineProperty(Object.prototype, "desc", {configurable: true, enumerable: false, value: function describe(propertyIdentifier) { return Object.getOwnPropertyDescriptor(this, propertyIdentifier) }, writable: true});
Object.defineProperty(Object.prototype, "hasOwn", {configurable: true, enumerable: false, value: Object.prototype.hasOwnProperty || function hasOwnProperty(propertyIdentifier) { return Object.hasOwnProperty(this, propertyIdentifier) }, writable: true});
Object.defineProperty(Object.prototype, "setOwn", {configurable: true, enumerable: false, value: function setOwn(propertyIdentifier, propertyValue) { this[propertyIdentifier] = propertyValue; return this }, writable: true});

Object.defineProperty(String.prototype, "count", {configurable: true, enumerable: false, value: function count(substring) { if (typeof substring == "string" || substring instanceof String) { let substringCount = +0; const SUBSTRING_LENGTH = substring.length; if (SUBSTRING_LENGTH ^ 1) { let stringIterator = this.length; while (stringIterator) if (this.charAt(stringIterator -= 1) == substring.charAt(SUBSTRING_LENGTH - 1)) { let substringIterator = SUBSTRING_LENGTH - 1; while (stringIterator && substringIterator) { if (this.charAt(stringIterator -= 1) != substring.charAt(substringIterator -= 1)) { stringIterator += 1; substringIterator = +0 } else if (!substringIterator && this.charAt(stringIterator) == substring.first) substringCount += 1 } } } else { let stringIterator = this.length; while (stringIterator) (this.charAt(stringIterator -= 1) == substring) && (substringCount += 1) } return substringCount } else if (substring instanceof RegExp) { let substringSource = substring.source; (substringSource.first == '/' && substringSource.last == '/') && (substringSource = substringSource.slice(1, -1)); substring = new RegExp(substringSource, (substring.flags || substring.options).remove('g') + 'g'); return (String.prototype.match.call(this, substring) || []).length } }, writable: true});
Object.defineProperty(String.prototype, "first", {configurable: true, enumerable: false, get: function first() { return this.charAt(+0) }});
Object.defineProperty(String.prototype, "last", {configurable: true, enumerable: false, get: function first() { return this.charAt(this.length - 1) }});
Object.defineProperty(String.prototype, "remove", {configurable: true, enumerable: false, value: function remove(match) { return String.prototype.replace.call(this, match, "") }, writable: true});

/* ... */
[Audio.prototype, HTMLEmbedElement.prototype, HTMLIFrameElement.prototype, HTMLLinkElement.prototype, HTMLSourceElement.prototype, HTMLVideoElement.prototype, Image.prototype].foreach(function(prototype) { let propertyIdentifier; while (prototype !== null && !prototype.hasOwnProperty(propertyIdentifier = "src")) { let evaluation = false; while (prototype !== null && !(evaluation = prototype.hasOwnProperty(propertyIdentifier = "href"))) { prototype = Object.getPrototypeOf(prototype); break } if (evaluation) break } if (prototype) { const PROPERTY_DESCRIPTOR = Object.getOwnPropertyDescriptor(prototype, propertyIdentifier); ("get" in PROPERTY_DESCRIPTOR || "set" in PROPERTY_DESCRIPTOR) && Object.defineProperty(prototype, propertyIdentifier, {configurable: PROPERTY_DESCRIPTOR.configurable, enumerable: PROPERTY_DESCRIPTOR.enumerable, get: PROPERTY_DESCRIPTOR.get, set: (function() { const METHOD = PROPERTY_DESCRIPTOR.set; return function(url) { const ELEMENT = this; document.pending += 1; ELEMENT.addEventListener("error", function error() { document.pending -= 1; ELEMENT.removeEventListener("error", error) }); ELEMENT.addEventListener("load", function load() { document.pending -= 1; ELEMENT.removeEventListener("load", load) }); return METHOD.call(ELEMENT, url) } })()}) } });
Array.from(document.all).foreach(function ExecuteDOMElementInlineScript(element) { const ELEMENT_INLINE_SCRIPT = (element.getAttribute("script") || "").replace(/ {0,}\n {0,}/g, ' '); ELEMENT_INLINE_SCRIPT && (element.script = ELEMENT_INLINE_SCRIPT) });
