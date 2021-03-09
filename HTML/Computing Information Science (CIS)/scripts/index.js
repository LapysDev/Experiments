/* ... --- REDACT (Lapys) */
void function() {
    // Constant
        // Carousel, ...
        var carousel = DOCUMENT.getElementById("introduction");

        var description = null, title = null;
        var indicatorList = [];
        var mediaList = [];
        var nextButton = null, previousButton = null;

        // ...
        var currentDate = Date.now();
        var recentDate = currentDate;

    function nextMedia() {
        recentDate = Date.now();

        for (var iterator = mediaList.length - 1; ~iterator; --iterator)
        if ("active" === mediaList[iterator].getAttribute("state")) {
            indicatorList[iterator].removeAttribute("state");
            mediaList[iterator].removeAttribute("state");

            indicatorList[iterator == indicatorList.length - 1 ? 0 : iterator + 1].setAttribute("state", "active");
            mediaList[iterator == mediaList.length - 1 ? 0 : iterator + 1].setAttribute("state", "active");

            break
        }
    }

    function previousMedia() {
        recentDate = Date.now();

        for (var iterator = mediaList.length - 1; ~iterator; --iterator)
        if ("active" === mediaList[iterator].getAttribute("state")) {
            mediaList[iterator].removeAttribute("state");
            indicatorList[iterator].removeAttribute("state");

            indicatorList[(iterator || indicatorList.length) - 1].setAttribute("state", "active");
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
    mediaList = (function(collection) { var list = []; for (var iterator = 0, length = collection.length; iterator != length; ++iterator) list.push(collection.item(iterator)); return list })(carousel["media"].getElementsByTagName("img"));
    nextButton = carousel["buttons"].getElementsByTagName("button").item(1);
    previousButton = carousel["buttons"].getElementsByTagName("button").item(0);
    title = carousel["content"].getElementsByTagName("h1").item(0)

    for (var iterator = 0, length = mediaList.length; iterator != length; ++iterator) {
        var indicator = DOCUMENT.createElement("button");

        carousel["indicators"].getElementsByTagName("div").item(0).appendChild(indicator);

        indicator.onclick = (function(index) {
            return function() {
                for (var iterator = mediaList.length - 1; ~iterator; --iterator)
                if ("active" === mediaList[iterator].getAttribute("state")) {
                    indicatorList[iterator].removeAttribute("state");
                    mediaList[iterator].removeAttribute("state");

                    break
                }

                indicatorList[index].setAttribute("state", "active");
                mediaList[index].setAttribute("state", "active");
                recentDate = Date.now()
            }
        })(iterator);
        indicator.setAttribute("role", "indicator");

        indicatorList.push(indicator)
    }

    indicatorList[0].setAttribute("state", "active");
    mediaList[0].setAttribute("state", "active");

    nextButton.onclick = nextMedia;
    previousButton.onclick = previousMedia;

    GLOBAL.onkeydown = function(event) {
        switch (event.key) {
            case "ArrowLeft": previousMedia(); break;
            case "ArrowRight": nextMedia(); break;
        }
    };

    GLOBAL.setInterval(function() {
        currentDate = Date.now();

        if (currentDate - recentDate >= 3000) {
            nextMedia();
            recentDate = currentDate
        }
    }, 100)
}()
