/* Global > ... */
// : Objects
var DOCUMENT = "undefined" == typeof(document) ? void function() { throw new Error("Document Object Model must exist to launch webpage properly") }() : document;
var GLOBAL = "undefined" == typeof(frames) ? ("undefined" == typeof(self) ? ("undefined" == typeof(window) ? ("undefined" == typeof(global) ? ("undefined" == typeof(globalThis) ? (function() { return this })() : globalThis) : global) : window) : self) : frames;

// : Elements
var DOCUMENT_ELEMENT = DOCUMENT.documentElement;

var BODY = DOCUMENT.body || (function() { for (var childNodes = DOCUMENT_ELEMENT.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("BODY" === childElement.tagName) return childElement } return null })() || (function(element) { DOCUMENT_ELEMENT.appendChild(element); return element })(DOCUMENT.createElement("body"));
var HEAD = DOCUMENT.head || (function() { for (var childNodes = DOCUMENT_ELEMENT.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("HEAD" === childElement.tagName) return childElement } return null })() || (function(element) { DOCUMENT_ELEMENT.appendChild(element); return element })(DOCUMENT.createElement("head"));

var ASIDE = (function() { for (var childNodes = BODY.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("ASIDE" === childElement.tagName || "aside" == childElement.id) return childElement } return null })() || (function(element) { BODY.appendChild(element); element.id = "aside"; return element })(DOCUMENT.createElement("aside"));
var HEADER = (function() { for (var childNodes = BODY.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("HEADER" === childElement.tagName || "header" == childElement.id) return childElement } return null })() || (function(element) { BODY.appendChild(element); element.id = "header"; return element })(DOCUMENT.createElement("header"));
var MAIN = (function() { for (var childNodes = BODY.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("MAIN" === childElement.tagName || "main" == childElement.id) return childElement } return null })() || (function(element) { BODY.appendChild(element); element.id = "main"; return element })(DOCUMENT.createElement("main"));
var FOOTER = (function() { for (var childNodes = BODY.childNodes, iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if ("FOOTER" === childElement.tagName || "footer" == childElement.id) return childElement } return null })() || (function(element) { BODY.appendChild(element); element.id = "footer"; return element })(DOCUMENT.createElement("footer"));

// : ...
var APPLICATION = new function Application(prototype) {
    if (prototype !== Application.prototype) {
        Application.prototype = prototype;
        return new Application(prototype)
    } // return this
}({
    COLOR: "#7F007F",
    NAME: "Internet Services",
    ROOT: false == ~DOCUMENT.URL.lastIndexOf("index") || DOCUMENT.URL.lastIndexOf('/') <= DOCUMENT.URL.lastIndexOf("index.") ? "" : "../"
});

/* Main */
void function Main() {
    // Constant > ...
    var icons = [
        {path: APPLICATION.ROOT + "favicon.ico", rel: "apple-touch-icon", type: "image/x-icon"},
        {path: APPLICATION.ROOT + "images/icons/startup.ico", rel: "apple-touch-startup-image", type: null},
        {path: APPLICATION.ROOT + "favicon.ico", rel: "fluid-icon", type: "image/x-icon"},
        {path: APPLICATION.ROOT + "favicon.ico", rel: "icon", type: null},
        {path: APPLICATION.ROOT + "favicon.ico", rel: "mask-icon", type: null},
        {path: APPLICATION.ROOT + "favicon.ico", rel: "shortcut icon", type: null}
    ];

    var metadata = [
        {content: "yes", name: "apple-mobile-web-app-capable"},
        {content: APPLICATION.COLOR, name: "apple-mobile-web-app-status-bar-style"},
        {content: "yes", name: "apple-touch-fullscreen"},
        {content: APPLICATION.NAME, name: "application-name"},
        {content: "LapysDev, lapysdev@gmail.com", name: "author"},
        {content: "Dummy Internet Services website", name: "description"},
        {content: "address=no, date=no, email=no, telephone=no, url=no", name: "format-detection"},
        {content: "!", name: "fragment"},
        {content: "true", name: "HandheldFriendly"},
        {content: "https://www.lapys.dev", name: "identifier-URL"},
        {content: "Lapys, LapysDev", name: "keywords"},
        {content: "en-NG", name: "language"},
        {content: APPLICATION.COLOR, name: "msapplication-navbutton-color"},
        {content: DOCUMENT.URL, name: "msapplication-starturl"},
        {content: true, name: "mssmarttagspreventparsing"},
        {content: "no", name: "MSThemeCompatible"},
        {content: "noarchive, nofollow, noimageindex, noindex, noodp, nosnippet, notranslate", name: "robots"},
        {content: APPLICATION.COLOR, name: "theme-color"},
        {content: DOCUMENT.URL, name: "url"},
        {content: "height=device-height, initial-scale=1.0, maximum-scale=1.0, minimal-ui, minimum-scale=1.0, user-scalable=no, width=device-width", name: "viewport"}
    ];

    var loader = DOCUMENT.createElement("div");

    var navigation = DOCUMENT.createElement("nav");
    var navigationHome = DOCUMENT.createElement('a');
    var navigationPreview = DOCUMENT.createElement("div");
    var navigationLinks = [
        {content: "About", path: APPLICATION.ROOT + "pages/about.html"},
        {content: "Admissions", path: APPLICATION.ROOT + "pages/admissions.html"},
        {content: "Alumni", path: APPLICATION.ROOT + "pages/alumni.html"},
        {content: "Colleges", path: APPLICATION.ROOT + "pages/colleges.html"},
        {content: "Conferences", path: APPLICATION.ROOT + "pages/conferences.html"},
        {content: "Documents", path: APPLICATION.ROOT + "pages/documents.html"},
        {content: "Journals", path: APPLICATION.ROOT + "pages/journals.html"},
        {content: "Library", path: APPLICATION.ROOT + "pages/library.html"},
        {content: "News", path: APPLICATION.ROOT + "pages/news.html"},
        {content: "Research", path: APPLICATION.ROOT + "pages/research.html"}
    ];

    // Event > Ready State Change
    DOCUMENT.onreadystatechange = function Initiate() {
        switch (DOCUMENT.readyState) {
            case "complete": InitiateAfterDOMLoad(); break;
            default /* -> "interactive" || "loading" */: InitiateBeforeDOMLoad()
        }
    };

    /* Phases > Initiate ... */
    function InitiateBeforeDOMLoad() {
        // Initialization > (Loader, Navigation) ...
        var loaderFeature = DOCUMENT.createElement("div");
        var loaderFeatureContainer = DOCUMENT.createElement("div");

        var navigationHamburger = DOCUMENT.createElement("div");
        var navigationHomeContent = DOCUMENT.createElement("div");
        var navigationHomeIcon = DOCUMENT.createElement("img");
        var navigationHomeLabel = DOCUMENT.createElement("img");
        var navigationPreviewClip = DOCUMENT.createElement("div");
        var navigationPreviewClipIcon = DOCUMENT.createElement("img");

        // Insertion
            // : [Body]
            BODY.appendChild(loader);

            HEADER.appendChild(navigationPreview);
            HEADER.appendChild(navigation);

            loader.appendChild(loaderFeatureContainer);
            loaderFeatureContainer.appendChild(loaderFeature);

            navigation.appendChild(navigationHome);
            navigationHome.appendChild(navigationHomeContent);
            navigationHomeContent.appendChild(navigationHomeIcon);
            navigationHomeContent.appendChild(navigationHomeLabel);
            navigationPreview.appendChild(navigationHamburger);
            navigationPreview.appendChild(navigationPreviewClip);
            navigationPreviewClip.appendChild(navigationPreviewClipIcon);

            for (var iterator = 3; iterator; --iterator) {
                navigationHamburger.appendChild(DOCUMENT.createElement("div"))
            }

            for (var iterator = 0; iterator != navigationLinks.length; ++iterator) {
                var element = DOCUMENT.createElement('a');
                var elementContent = DOCUMENT.createElement("span");

                element.className = "link";
                element.href = navigationLinks[iterator].path || "#";
                elementContent.innerText = navigationLinks[iterator].content;

                element.appendChild(elementContent);
                navigation.appendChild(element)
            }

            // : [Head]
            for (var iterator = icons.length - 1; ~iterator; --iterator) {
                var element = DOCUMENT.createElement("link");

                element.href = icons[iterator].path;
                element.rel = icons[iterator].rel;
                (null === icons[iterator].type) || (element.type = icons[iterator].type);

                HEAD.appendChild(element)
            }

            for (var iterator = metadata.length - 1; ~iterator; --iterator) {
                var element = DOCUMENT.createElement("meta");

                element.content = metadata[iterator].content;
                element.name = metadata[iterator].name;

                HEAD.appendChild(element)
            }

        // Modification > ...
            // Document
            DOCUMENT.title = (function(title) {
                var leftTrimmedTitle = title, rightTrimmedTitle = title;
                var trimmedTitle = title;

                for (var trimming = true; trimming; ) switch (leftTrimmedTitle.charAt(0)) { case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': { leftTrimmedTitle = leftTrimmedTitle.slice(1); trimmedTitle = trimmedTitle.slice(1) } break; default: trimming = false; break }
                for (var trimming = true; trimming; ) switch (rightTrimmedTitle.charAt(rightTrimmedTitle.length - 1)) { case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': { rightTrimmedTitle = rightTrimmedTitle.slice(0, -1); trimmedTitle = trimmedTitle.slice(0, 1) } break; default: trimming = false; break }

                return (
                    APPLICATION.NAME == leftTrimmedTitle.slice(0, APPLICATION.NAME.length) ||
                    APPLICATION.NAME == rightTrimmedTitle.slice(-APPLICATION.NAME.length)
                ) ? trimmedTitle : (APPLICATION.NAME + " | " + rightTrimmedTitle)
            })(DOCUMENT.title);

            // Loader ...
            loader.id = "loader";
            loader.setAttribute("state", "loading");

            loaderFeature.id = "loaderFeature";

            // Navigation ...
            navigation.id = "navigation";
            navigation.setAttribute("state", "compact");

            navigationHamburger.onclick = function() {
                "compact" === navigation.getAttribute("state") ? navigation.removeAttribute("state") : navigation.setAttribute("state", "compact");
                "iconic" === navigationHamburger.getAttribute("state") ? navigationHamburger.removeAttribute("state") : navigationHamburger.setAttribute("state", "iconic")
            };
            navigationHamburger.setAttribute("role", "hamburger");

            navigationHome.className = "link";
            navigationHome.href = APPLICATION.ROOT + "index.html";
            navigationHome.title = APPLICATION.NAME;
            navigationHome.setAttribute("role", "home");

            navigationHomeIcon.src = APPLICATION.ROOT + "images/icons/favicon.png";
            navigationHomeIcon.setAttribute("role", "icon");

            navigationHomeLabel.alt = APPLICATION.NAME;
            navigationHomeLabel.src = APPLICATION.ROOT + "images/miscellaneous/covenant.png";
            navigationHomeLabel.setAttribute("role", "label");

            navigationPreview.id = "preview";

            navigationPreviewClip.setAttribute("role", "clip");
            navigationPreviewClipIcon.setAttribute("role", "icon")
    }

    function InitiateAfterDOMLoad() {
        // ...
        GLOBAL.setTimeout(function() { BODY.removeChild(loader) }, 333);
        loader.setAttribute("state", "completed")
    }
}()
