/* ... */
void function() {
    // Constant > (Cards, Sources) --- NOTE (Lapys) -> Manually fetched content.
    var cards = map([
        {
            description: "...",
            flavor: "A great deal of R&amp;D exploration and AI modeling exploration is underway but moving to sustaining operating practices and ensuring the ongoing knowledge of AI modeling outcomes",
            path: "https://www.forbes.com/sites/cindygordon/2021/02/27/building-ai-leadership-brain-trust-why-is-data-analytics-literacy-key-to-ai-competency-development/?sh=1be52992ca95",
            thumbnail: "439822.jpg",
            title: "Building AI Leadership Brain Trust: Why Is Data Analytics Literacy Key To AI Competency Development?"
        },

        {
            description: "...",
            flavor: "The initiative, Destination Earth, will begin in a few months and is expected to last for a decade. A key component of the program is the creation of a “digital twin” of Earth, which will see climate scientists and computer scientists collaborate at a previously unprecedented level",
            path: "https://www.laboratoryequipment.com/573624-The-Insane-Amount-of-Computing-Power-Needed-to-Create-Earth-s-Digital-Twin/",
            thumbnail: "098762.jpg",
            title: "The Insane Amount of Computing Power Needed to Create Earth's Digital Twin"
        },

        {
            description: "...",
            flavor: "Responding to artificial intelligence's exploding demands on computer networks, Princeton University researchers in recent years have radically increased the speed and slashed the energy use of specialized AI systems.",
            path: "https://eurekalert.org/pub_releases/2021-02/pues-pct022421.php",
            thumbnail: "936429.jpg",
            title: "Pushing computing to the edge by rethinking microchips' design"
        },

        {
            description: "...",
            flavor: "Imagine getting medical checkups, drugs and other therapies tailored to your own genetic makeup. The concept of personalized medicine is based on the idea that medical treatment should not be one size fits all.",
            path: "https://www.forbes.com/sites/japan/2021/02/25/how-japan-is-using-the-worlds-most-powerful-supercomputer-to-accelerate-personalized-medicine/?sh=1157d531382c",
            thumbnail: "192834.jpg",
            title: "How Japan Is Using The World’s Most Powerful Supercomputer To Accelerate Personalized Medicine"
        },

        {
            description: "...",
            flavor: "We are now on the threshold of a new computer technology era more powerful than anything that preceded it: the age of quantum computing. However, this time we have a chance to stop and think carefully about the ethical use of a transformative technology today while we can still shape the future.",
            path: "https://www.scientificamerican.com/article/will-quantum-computers-truly-serve-humanity/",
            thumbnail: "857321.jpg",
            title: "Will Quantum Computers Truly Serve Humanity?"
        }
    ], function(card) { card.thumbnail = APPLICATION.ROOT + "images/news/thumbnail-" + card.thumbnail });
    var sources = DOCUMENT.getElementById("sources");

    // Loop
    for (var iterator = cards.length - 1; ~iterator; --iterator) {
        // Initialization > Card ...
        var card = cards[iterator];

        var cardDescriptionElement = DOCUMENT.createElement("div");
        var cardElement = DOCUMENT.createElement("div");
        var cardFlavorElement = DOCUMENT.createElement("div");
        var cardThumbnailElement = DOCUMENT.createElement("div");
        var cardTitleElement = DOCUMENT.createElement("div");
        var cardPromptElement = DOCUMENT.createElement('a');

        // Insertion
        cardElement.appendChild(cardThumbnailElement);
        cardElement.appendChild(cardTitleElement);
        cardElement.appendChild(cardFlavorElement);
        cardElement.appendChild(cardDescriptionElement);
        cardElement.appendChild(cardPromptElement);

        sources.appendChild(cardElement);


        // Modification > Card ... > ...
        cardDescriptionElement.innerText = card.description;
        cardDescriptionElement.setAttribute("role", "description");

        cardElement.setAttribute("role", "card");
        cardElement.setAttribute("state", iterator & 1 ? "even" : "odd");
        cardElement.setAttribute("tabindex", iterator);

        cardFlavorElement.innerText = card.flavor;
        cardFlavorElement.setAttribute("role", "flavor");

        cardPromptElement.href = card.path;
        cardPromptElement.innerHTML = "Read more&hellip;";
        cardPromptElement.target = "_blank";
        cardPromptElement.setAttribute("role", "prompt");

        cardThumbnailElement.style.backgroundImage = "url(\"" + card.thumbnail + "\")";
        cardThumbnailElement.setAttribute("role", "thumbnail");

        cardTitleElement.innerText = card.title;
        cardTitleElement.title = card.title;
        cardTitleElement.setAttribute("role", "title")
    }
}()
