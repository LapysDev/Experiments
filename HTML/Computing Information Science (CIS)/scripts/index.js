/* ... --- REDACT (Lapys) */
void function() {
    // Constant > Carousel
    var carousel = DOCUMENT.getElementById("introduction");

    var description = null, title = null;
    var indicatorList = [];
    var mediaList = [];
    var nextButton = null, previousButton = null;

    function nextMedia() {
        for (var iterator = mediaList.length - 1; ~iterator; --iterator)
        if ("active" === mediaList[iterator].getAttribute("state")) {
            mediaList[iterator].removeAttribute("state");
            mediaList[iterator == mediaList.length - 1 ? 0 : iterator + 1].setAttribute("state", "active");
            break
        }
    }

    function previousMedia() {
        for (var iterator = mediaList.length - 1; ~iterator; --iterator)
        if ("active" === mediaList[iterator].getAttribute("state")) {
            mediaList[iterator].removeAttribute("state");
            mediaList[(iterator || mediaList.length) - 1].setAttribute("state", "active");
            break
        }
    }

    for (var iterator = carousel.childNodes.length - 1; ~iterator; --iterator) {
        var childNode = carousel.childNodes.item(iterator);

        if ("string" == typeof(childNode.tagName))
        carousel[childNode.getAttribute("role")] = childNode
    }

    description = carousel["content"].getElementsByTagName("h2").item(0);
    mediaList = (function(collection) { var list = []; for (var iterator = collection.length - 1; ~iterator; --iterator) list.push(collection.item(iterator)); return list })(carousel["media"].getElementsByTagName("img"));
    nextButton = carousel["buttons"].getElementsByTagName("button").item(1);
    previousButton = carousel["buttons"].getElementsByTagName("button").item(0);
    title = carousel["content"].getElementsByTagName("h1").item(0)

    for (var iterator = mediaList.length; iterator; --iterator) {
        var indicator = DOCUMENT.createElement("button");

        carousel["indicators"].getElementsByTagName("div").item(0).appendChild(indicator);

        indicator.onclick = (function(index) {
            return function() {
                for (var iterator = mediaList.length - 1; ~iterator; --iterator)
                if ("active" === mediaList[iterator].getAttribute("state")) { mediaList[iterator].removeAttribute("state"); break }

                mediaList[index].setAttribute("state", "active")
            }
        })(iterator - 1);
        indicator.setAttribute("role", "indicator");

        indicatorList.push(indicator)
    }

    mediaList[0].setAttribute("state", "active");
    nextButton.onclick = nextMedia;
    previousButton.onclick = previousMedia;

    GLOBAL.onkeydown = function(event) {
        switch (event.key) {
            case "ArrowLeft": previousMedia(); break;
            case "ArrowRight": nextMedia(); break;
        }
    };

    GLOBAL.setInterval(nextMedia, 3e3)
}()
