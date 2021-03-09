/* Global > Application */
var APPLICATION = new function Application() {};

/* Main */
void function Main(DOCUMENT, GLOBAL) {
    /* Constant > ... */
    var DOCUMENT_ELEMENT = DOCUMENT.documentElement;

    var BODY = DOCUMENT.body || assertChildElement(DOCUMENT_ELEMENT, "body");
    var HEAD = DOCUMENT.head || assertChildElement(DOCUMENT_ELEMENT, "head");

    var ASIDE = assertChildElement(BODY, "div", "#aside");
    var HEADER = assertChildElement(BODY, "div", "#header");
    var MAIN = assertChildElement(BODY, "div", "#main");
    var FOOTER = assertChildElement(BODY, "div", "#footer");

    /* Function > ... */
    function assertChildElement(parentElement, localName, selector) {
        // Initialization > (Child ..., ...)
        var childElement;
        var childNodes = parentElement.childNodes;

        var attributes = [];
        var classNames = [];
        var identity = null;

        /* [Search] ... */ {
            /* Logic > Loop
                --- NOTE (Lapys) -> Parse CSS selectors as element attributes onto the Child Element.
                --- WARN (Lapys) -> No error handling implemented.
            */
            if (arguments.length > 2)
            for (var iterator = 0, length = selector.length, mode = 0x0; iterator != length; ++iterator) {
                // Initialization > Character ...
                var character = selector.charAt(iterator);

                var characterIsTokenSequence = false;
                var characterIsTokenStart = false;
                var characterIsWhitespace = false;

                // Update > Character Is ...
                switch (character) { case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': characterIsWhitespace = true }
                switch (character) { case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case '_': characterIsTokenStart = true }
                switch (character) { case '$': characterIsTokenSequence = true; break; default: characterIsTokenSequence = characterIsTokenStart }

                // Logic > Update > (Mode, ...)
                if (0x0 == mode)
                switch (character) {
                    case '.': mode = 0x1; break;
                    case '#': identity = ""; mode = 0x2; break;
                    case '[': attributes.push({name: null, value: null}); mode = 0x4; break
                }

                // Logic > ...
                switch (mode) {
                    // [Class]
                    case 0x1: {
                        if (characterIsWhitespace) mode = 0x0;
                        else if ('.' == character) classNames.push("");
                        else classNames.length ? classNames[classNames.length - 1] += character : classNames.push("")
                    } break;

                    // [Identity]
                    case 0x2: {
                        if (characterIsWhitespace) mode = 0x0;
                        else if ('#' == character) identity = "";
                        else identity += character
                    } break;

                    // [Attribute Name]
                    case 0x4: switch (character) {
                        case '~': case '^': break;
                        case '=': mode = 0x8; break;
                        case ']': mode = 0x0; break;
                        default: null === attributes[attributes.length - 1].name ? attributes[attributes.length - 1].name = "" : attributes[attributes.length - 1].name += character
                    } break;

                    // [Attribute Value]
                    case 0x8: {
                        if (']' == character) mode = 0x0;
                        else null === attributes[attributes.length - 1].value ? attributes[attributes.length - 1].value = character : attributes[attributes.length - 1].value += character
                    }
                }
            }

            // Loop --- NOTE (Lapys) -> Correct CSS attribute selector parsing.
            for (var iterator = attributes.length - 1; ~iterator; --iterator) {
                // Initialization > Attribute
                var attribute = attributes[iterator];

                // ...; Logic > ... > Modification > Attribute > Value
                attribute.name = trim(attribute.name);
                if (null !== attribute.value) {
                    // ... --- NOTE (Lapys) -> Un-delimit the CSS attribute value selector.
                    attribute.value = trim(attribute.value);
                    if (
                        ('"' == attribute.value.charAt(0) && '"' == attribute.value.charAt(attribute.value.length - 1)) ||
                        ('\'' == attribute.value.charAt(0) && '\'' == attribute.value.charAt(attribute.value.length - 1))
                    ) attribute.value = attribute.value.slice(1, -1)
                }
            }

            // Loop --- NOTE (Lapys) -> Search the DOM tree for the specified Child Element.
            for (var iterator = childNodes.length - 1; ~iterator; --iterator) {
                // Initialization > Child Node
                var childNode = childNodes.item(iterator);

                // Logic --- NOTE (Lapys) -> Assert the Child Node is an Element.
                if ("string" == typeof(childNode.tagName)) {
                    // Initialization > Matched ... --- NOTE (Lapys) -> Assert the argument specifications of the Child Element.
                    var matchedAttributes = true;
                    var matchedClassNames = true;
                    var matchedIdentity = false;
                    var matchedLocalName = false;

                    // [Matched Attributes] Logic > ... --- REDACT (Lapys)
                    for (var subiterator = attributes.length - 1; ~subiterator && matchedAttributes; --subiterator) {
                        var attribute = attributes[subiterator];
                        var childElementAttributeValue = childNode.getAttribute(attribute.name);

                        // ... Update > Matched Attributes
                        if (null === childElementAttributeValue || attribute.value != childElementAttributeValue)
                        matchedAttributes = false
                    }

                    // [Matched Class Names] Logic > ...
                    for (var subiterator = classNames.length - 1; ~subiterator && matchedClassNames; --subiterator) {
                        // Initialization > Matched ...
                        var className = classNames[subiterator];
                        var matchedClassName = false;

                        // [Matched Class Name] Loop > ... --- REDACT (Lapys)
                        for (var childElementClassName = "", subsubiterator = 0, sublength = childNode.className.length + 1; false == matchedClassName && subsubiterator != sublength; ++subsubiterator) {
                            var character = (childNode.className + ' ').charAt(subsubiterator);

                            switch (character) {
                                case ' ': { if (className == childElementClassName) matchedClassName = true; childElementClassName = "" } break;
                                default: childElementClassName += character
                            }
                        }

                        // ... Update > Matched Class Names
                        if (false == matchedClassName)
                        matchedClassNames = false
                    }

                    // Update > Matched (Identity, Local Name)
                    matchedIdentity = null === identity || identity == childNode.id;
                    matchedLocalName = localName.toLowerCase() == childNode.tagName.toLowerCase();

                    // Logic > Return
                    if (matchedAttributes && matchedClassNames && matchedIdentity && matchedLocalName)
                    return childNode
                }
            }
        }

        /* [Allocate] ... */ {
            // Update > Child Element
            childElement = DOCUMENT.createElement(localName.toLowerCase());

            // ... Modification > Child Element > ...
            for (var iterator = attributes.length - 1; ~iterator; --iterator) childElement.setAttribute(attributes[iterator].name, attributes[iterator].value);
            for (var iterator = classNames.length - 1; ~iterator; --iterator) null === childElement.getAttribute("class") ? childElement.setAttribute("class", classNames[iterator]) : childElement.setAttribute("class", childElement.getAttribute("class") + ' ' + classNames[iterator]);
            (null === identity) || (childElement.id = identity);

            // Insertion
            parentElement.appendChild(childElement);
        }

        // Return
        return childElement
    }

    function map(array, length, callback) { (arguments.length == 2) && (callback = arguments[1], length = array.length); for (var iterator = length - 1; ~iterator; --iterator) callback(array[iterator], iterator, array); return array }

    function trim(string) { return trimRight(trimLeft(string)) }
    function trimLeft(string) { if (string) { for (var trimming = true; trimming; ) switch (string.charAt(0)) { case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': string = string.slice(1); break; default: trimming = false } } return string }
    function trimRight(string) { if (string) { for (var trimming = true; trimming; ) switch (string.charAt(string.length - 1)) { case ' ': case '\f': case '\n': case '\r': case '\t': case '\v': string = string.slice(0, -1); break; default: trimming = false } } return string }

    /* Modification > ... */
        // Application
        APPLICATION["COLOR"] = "#7F007F";
        APPLICATION["NAME"] = "Computing Information Science";
        APPLICATION["ROOT"] = ~DOCUMENT.URL.lastIndexOf("index") || DOCUMENT.URL.lastIndexOf('/') < DOCUMENT.URL.lastIndexOf("index.") ? "" : "../";

        // Global
        GLOBAL["ASIDE"] = ASIDE;
        GLOBAL["BODY"] = BODY;
        GLOBAL["DOCUMENT_ELEMENT"] = DOCUMENT_ELEMENT;
        GLOBAL["FOOTER"] = FOOTER;
        GLOBAL["HEAD"] = HEAD;
        GLOBAL["HEADER"] = HEADER;
        GLOBAL["MAIN"] = MAIN;

        GLOBAL["DOCUMENT"] = DOCUMENT;
        GLOBAL["GLOBAL"] = GLOBAL;

        GLOBAL["map"] = map;
        GLOBAL["trim"] = trim;
        GLOBAL["trimLeft"] = trimLeft;
        GLOBAL["trimRight"] = trimRight;

    /* Event --- REDACT (Lapys) */
        // Document > Ready State Change
        DOCUMENT.onreadystatechange = function Initiate() {
            switch (DOCUMENT.readyState) {
                case "complete": InitiateAfterDOMLoad(); break;
                default /* --> "interactive" || "loading" */: InitiateBeforeDOMLoad()
            }
        };

        // Document > Key Release
        GLOBAL.onkeyup = function(event) {
            if ("Escape" == event.key) {
                if (null !== DOCUMENT.activeElement)
                DOCUMENT.activeElement.blur()
            }
        };

    /* Phase > Initiate ... */
    function InitiateAfterDOMLoad() {
        // Constant > ...
        var loader = DOCUMENT.getElementById("loader");

        // Style > Loader > ...; Deletion
        loader.style.opacity = 0;
        loader.style.top = "-10%";
        GLOBAL.setTimeout(function() { BODY.removeChild(loader) }, +loader.style.transitionDuration.replace(new RegExp("ms|s"), ""))
    }

    function InitiateBeforeDOMLoad() {
        // Constant > ...
            // : [Body]
            var footerAddress = DOCUMENT.createElement("div");
            var footerBottom = DOCUMENT.createElement("div");
            var footerContent = DOCUMENT.createElement("div");
            var footerContentAside = DOCUMENT.createElement("div");
            var footerContentAsidePrompt = DOCUMENT.createElement('a');
            var footerContentNewsletter = DOCUMENT.createElement("div");
            var footerContentNewsletterRegistrar = DOCUMENT.createElement("form");
            var footerContentNewsletterRegistrarField = DOCUMENT.createElement("input");
            var footerContentNewsletterRegistrarSubmit = DOCUMENT.createElement("input");
            var footerContentNewsletterSocials = DOCUMENT.createElement("div");

            footerContent.appendChild(footerContentNewsletter);
                footerContentNewsletter.appendChild(DOCUMENT.createElement("h2"));
                footerContentNewsletter.appendChild(DOCUMENT.createElement('p'));
                footerContentNewsletter.appendChild(footerContentNewsletterRegistrar);
                    footerContentNewsletterRegistrar.appendChild(footerContentNewsletterRegistrarField);
                    footerContentNewsletterRegistrar.appendChild(footerContentNewsletterRegistrarSubmit);
                footerContentNewsletter.appendChild(footerContentNewsletterSocials);
            footerContent.appendChild(footerContentAside);
                footerContentAside.appendChild(DOCUMENT.createElement("h2"));
                footerContentAside.appendChild(DOCUMENT.createElement('p'));
                footerContentAside.appendChild(footerContentAsidePrompt);

            footerAddress.innerHTML = "Orbit Media Studios &bull; 4043 N Ravenswood Ave, Suite 316, Chicago, IL 60613 &bull; Main (773) 348.4581 &bull; Support (773) 353.8314";
            footerAddress.setAttribute("role", "address");

            footerBottom.setAttribute("role", "bottom");
            for (var content = ["Privacy Policy", "Sitemap", "&copy; 2015 Orbit Media Studios"], iterator = 0, length = content.length; iterator != length; ++iterator) {
                var element = DOCUMENT.createElement("div");

                element.innerHTML = content[iterator];
                footerBottom.appendChild(element)
            }

            footerContent.setAttribute("role", "content");

            footerContentAside.getElementsByTagName("h2").item(0).innerText = "Committed to Covenant";
            footerContentAside.getElementsByTagName('p').item(0).innerText = "Our mission is to stimulate the dream of royalty and dream of dignity into our students so that they can begin to develop a royal attitude, cultivate royal habits and form royal character so as to fulfill the Covenant University dream of raising a new generation of leaders.";
            footerContentAside.setAttribute("role", "aside");
            footerContentAsidePrompt.href = APPLICATION.ROOT + "pages/about.html";
            footerContentAsidePrompt.innerHTML = "More about our status &#x27B2;";
            footerContentAsidePrompt.setAttribute("role", "prompt");

            footerContentNewsletter.getElementsByTagName("h2").item(0).innerText = "Stay connected";
            footerContentNewsletter.getElementsByTagName('p').item(0).innerText = "Join over 420,000 people who receive bi-weekly web marketing tips";
            footerContentNewsletter.setAttribute("role", "newsletter");
            footerContentNewsletterRegistrarField.setAttribute("placeholder", "Email Address");
            footerContentNewsletterRegistrarField.type = "text";
            footerContentNewsletterRegistrarSubmit.type = "submit";
            footerContentNewsletterRegistrarSubmit.value = "Sign-Up";
            footerContentNewsletterSocials.setAttribute("role", "socials");
            for (var content = ["facebook.png", "twitter.png", "youtube.png"], iterator = 0, length = content.length; iterator != length; ++iterator) {
                var element = DOCUMENT.createElement("div");
                var elementIcon = DOCUMENT.createElement("img");

                element.appendChild(elementIcon);
                elementIcon.src = APPLICATION.ROOT + "images/icons/" + content[iterator];
                footerContentNewsletterSocials.appendChild(element)
            }

            var loader = DOCUMENT.createElement("div");

            var navigation = DOCUMENT.createElement("div");
            var navigationHome = DOCUMENT.createElement('a');
            var navigationLinks = map([
                {content: "About", path: "pages/about.html"},
                {content: "News", path: "pages/news.html"}
            ], function(navigationLink) { navigationLink.path = APPLICATION.ROOT + navigationLink.path });
            var navigationRegistrar = DOCUMENT.createElement("div");

            // : [Head]
            var icons = map([
                {path: "favicon.ico", rel: "apple-touch-icon", type: "image/x-icon"},
                {path: "images/icons/startup.ico", rel: "apple-touch-startup-image", type: null},
                {path: "favicon.ico", rel: "fluid-icon", type: "image/x-icon"},
                {path: "favicon.ico", rel: "icon", type: null},
                {path: "favicon.ico", rel: "mask-icon", type: null},
                {path: "favicon.ico", rel: "shortcut icon", type: null}
            ], function(icon) { icon.path = APPLICATION.ROOT + icon.path });

            var metadata = [
                {content: "yes", name: "apple-mobile-web-app-capable"},
                {content: APPLICATION.COLOR, name: "apple-mobile-web-app-status-bar-style"},
                {content: "yes", name: "apple-touch-fullscreen"},
                {content: APPLICATION.NAME, name: "application-name"},
                {content: "LapysDev, lapysdev@gmail.com", name: "author"},
                {content: "Dummy website", name: "description"},
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

        // Insertion --- REDACT (Lapys)
        BODY.appendChild(loader);

        FOOTER.appendChild(footerContent);
        FOOTER.appendChild(footerAddress);
        FOOTER.appendChild(footerBottom);

        HEADER.appendChild(navigation);

        loader.appendChild(DOCUMENT.createElement("div"));

        navigation.appendChild(navigationHome); {
            for (var iterator = 0, length = navigationLinks.length; iterator != length; ++iterator) {
                var navigationElement = DOCUMENT.createElement('a');
                var navigationLink = navigationLinks[iterator];

                navigationElement.href = navigationLink.path;
                navigationElement.innerText = navigationLink.content;

                navigation.appendChild(navigationElement)
            }
        } navigation.appendChild(navigationRegistrar);

        navigationHome.appendChild(DOCUMENT.createElement("img"));
        navigationRegistrar.appendChild(DOCUMENT.createElement('a'));

        for (var iterator = icons.length - 1; ~iterator; --iterator) {
            var icon = icons[iterator];
            var iconElement = DOCUMENT.createElement("link");

            iconElement.href = icon.path;
            iconElement.rel = icon.rel;
            (null === iconElement.type) || (iconElement.type = icon.type);

            HEAD.appendChild(iconElement)
        }

        for (var iterator = metadata.length - 1; ~iterator; --iterator) {
            var meta = metadata[iterator];
            var metaElement = DOCUMENT.createElement("meta");

            metaElement.content = meta.content;
            metaElement.name = meta.name;

            HEAD.appendChild(metaElement)
        }

        // Modification > ...
            // Document
            DOCUMENT.title = (
                APPLICATION.NAME == trimRight(DOCUMENT.title).slice(-APPLICATION.NAME.length) ||
                APPLICATION.NAME == trimLeft(DOCUMENT.title).slice(0, APPLICATION.NAME.length)
            ) ? trim(DOCUMENT.title) : (APPLICATION.NAME + " | " + trimRight(DOCUMENT.title));

            // Loader ...
            loader.id = "loader";
            loader.style.transitionDuration = "300ms";

            // Navigation ...
            navigation.id = "navigation"; {
                for (var iterator = navigation.childNodes.length - 1; ~iterator; --iterator)
                navigation.childNodes.item(iterator).className = "link"
            }

            navigationHome.firstChild.src = APPLICATION.ROOT + "images/miscellaneous/banner.png";
            navigationHome.href = APPLICATION.ROOT + "index.html";
            navigationHome.title = APPLICATION.NAME;
            navigationHome.setAttribute("role", "home");

            navigationRegistrar.firstChild.href = APPLICATION.ROOT + "pages/registration.html";
            navigationRegistrar.firstChild.innerText = "Login / Signup";
            navigationRegistrar.setAttribute("role", "registrar")
    }
}("undefined" == typeof(document) ? void function() { throw new Error("Document Object Model must exist to launch webpage properly") }() : document, "undefined" == typeof(frames) ? ("undefined" == typeof(self) ? ("undefined" == typeof(window) ? ("undefined" == typeof(global) ? ("undefined" == typeof(globalThis) ? (function() { return this })() : globalThis) : global) : window) : self) : frames)
