/* Main */
+(function Main() {
    /* Constant > ... */
    const GLOBAL = (function() { try { return Function("return this")() || eval("this") } catch (error) {} return typeof self == "undefined" ? (typeof window == "undefined" ? (typeof global == "undefined" ? undefined : global) : window) : self })();
    var STRICT;

    /* Function > Add */
    let add = null;

    /* Phase > Initiate */
    function Initiate() {
        /* Function > Load WASM Scripts */
        function LoadWASMScript(Url) { return fetch(Url).then(Response => Response.arrayBuffer()).then(Bits => WebAssembly.compile(Bits)).then(Module => { return new WebAssembly.Instance(Module) }) }

        // ...
        LoadWASMScript("add.wasm").then(WebAssemblyInstance => add = (GLOBAL.add = WebAssemblyInstance.exports["add"]));

        // Return
        return +0
    }

    // ....
    Initiate();

    // Return
    return +0
})();
