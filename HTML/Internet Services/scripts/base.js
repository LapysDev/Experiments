/* Global > ... */
// : Objects
var APPLICATION = {
    COLOR: "#7F007F",
    NAME: "Internet Services"
};

var DOCUMENT = document;
var GLOBAL = "undefined" == typeof(frames) ? ("undefined" == typeof(self) ? ("undefined" == typeof(window) ? ("undefined" == typeof(global) ? ("undefined" == typeof(globalThis) ? (function() { return this })() : globalThis) : global) : window) : self) : frames;

// : Elements -->
var DOCUMENT_ELEMENT = /* html */ DOCUMENT.documentElement;

var BODY = /* body */ DOCUMENT.body || (function() { var childNodes = DOCUMENT_ELEMENT.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("BODY" === childElement.tagName) return childElement } return null })() || (function(body) { DOCUMENT_ELEMENT.appendChild(body); return body })(DOCUMENT.createElement("body"));
var HEAD = /* head */ DOCUMENT.head || (function() { var childNodes = DOCUMENT_ELEMENT.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("HEAD" === childElement.tagName) return childElement } return null })() || (function(head) { DOCUMENT_ELEMENT.appendChild(head); return head })(DOCUMENT.createElement("head"));

var ASIDE = /* aside#aside */ (function() { var childNodes = BODY.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("ASIDE" === childElement.tagName && "aside" == childElement.getAttribute("id")) return childElement } return null })() || (function(aside) { BODY.appendChild(aside); aside.setAttribute("id", "aside"); return aside })(DOCUMENT.createElement("aside"));
var HEADER = /* header#header */ (function() { var childNodes = BODY.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("HEADER" === childElement.tagName && "header" == childElement.getAttribute("id")) return childElement } return null })() || (function(header) { BODY.appendChild(header); header.setAttribute("id", "header"); return header })(DOCUMENT.createElement("header"));
var MAIN = /* main#main */ (function() { var childNodes = BODY.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("MAIN" === childElement.tagName && "main" == childElement.getAttribute("id")) return childElement } return null })() || (function(main) { BODY.appendChild(main); main.setAttribute("id", "main"); return main })(DOCUMENT.createElement("main"));
var FOOTER = /* footer#footer */ (function() { var childNodes = BODY.childNodes; for (var iterator = childNodes.length - 1; ~iterator; --iterator) { var childElement = childNodes.item(iterator); if (childElement.nodeType & Node.ELEMENT_NODE) if ("FOOTER" === childElement.tagName && "footer" == childElement.getAttribute("id")) return childElement } return null })() || (function(footer) { BODY.appendChild(footer); footer.setAttribute("id", "footer"); return footer })(DOCUMENT.createElement("footer"));

/* Main */
void function Main() {
    // Initialization > ...
    var favoriteIcon = DOCUMENT.createElement("link");
    var metadata = [
        {content: "yes", name: "apple-mobile-web-app-capable"},
        {content: APPLICATION.COLOR, name: "apple-mobile-web-app-status-bar-style"}
        {content: "yes", name: "apple-touch-fullscreen"},
        {content: "LapysDev, lapysdev@gmail.com", name: "author"},
        {content: "Dummy Internet Services website", name: "description"},
        {content: "address=no, date=no, email=no, telephone=no, url=no", name: "format-detection"},
        {content: "!", name: "fragment"},
        {content: "true", name: "HandheldFriendly"},
        {content: "https://www.lapys.dev", name: "identifier-URL"},
        {content: "Lapys, LapysDev", name: "keywords"},
        {content: "en-NG", name: "language"},
        {content: "noarchive, nofollow, noimageindex, noindex, noodp, nosnippet, notranslate", name: "robots"},
        {content: APPLICATION.COLOR, name: "theme-color"},
        {content: location.href, name: "url"},
        {content: "height=device-height, initial-scale=1.0, maximum-scale=1.0, minimal-ui, minimum-scale=1.0, user-scalable=no, width=device-width", name: "viewport"}
    ];

    var loader = DOCUMENT.createElement("div");
    var loaderExitDuration = 333;
    var loaderFeature = DOCUMENT.createElement("div");
    var loaderStylesheet = DOCUMENT.createElement("style");

    // <link href=icon.ico rel="apple-touch-icon"/>
    // <link href=icon.png rel=apple-touch-icon type="image/png"/>
    // <link href=startup-icon.ico rel="apple-touch-startup-image"/>

    // Event > ...
    DOCUMENT.addEventListener("readystatechange", function() { if ("complete" === DOCUMENT.readyState) Initiate(true) });

    /* Phases > Initiate */
    function Initiate(loaded) {
        // Logic
        if (loaded) {
            // ...; Modification > ...
            GLOBAL.setTimeout(function() { loader.parentElement.removeChild(loader) }, loaderExitDuration);
            with (loader.style) {
                opacity = 0;
                top = "-10%";
                transition = loaderExitDuration + "ms ease-out 0s"
            }
        }

        else {
            // Insertion
            BODY.appendChild(loader);
                loader.appendChild(loaderStylesheet);
                loader.appendChild(loaderFeature);

            HEAD.appendChild(favoriteIcon);
            metadata.forEach(function(metadata) {
                var metaElement = DOCUMENT.createElement("meta");

                metaElement.setAttribute("content", metadata.content);
                metaElement.setAttribute("name", metadata.name);

                HEAD.appendChild(metaElement)
            });

            /*
                Company/ Service Meta Tags
                    Apple Meta Tags
                    Apple Tags

                    Blog Catalog Meta Tags
                        <meta name="blogcatalog"/>

                    Internet Explorer Meta Tags
                        <link href=icon.ico rel="shortcut icon"/>

                        <meta content=RevealTrans(Duration=2.0,Transition=2) http-equiv="Page-Enter"/>
                        <meta content=RevealTrans(Duration=3.0,Transition=12) http-equiv="Page-Exit"/>
                        <meta content=chrome=1 http-equiv="X-UA-Compatible"/>


                        <meta content="LapysDev Application" name="application-name"/>
                        <meta content=#0000FF name="msapplication-navbutton-color"/>
                        <meta content=# name="msapplication-starturl"/>
                        <meta content="action-uri=index.html;icon-uri=icon.ico;name=Task Name" name="msapplication-task"/>
                        <meta content="LapysDev Application Tooltip" name="msapplication-tooltip"/>
                        <meta content=height=600;width=800 name="msapplication-window"/>
                        <meta content=true name="mssmarttagspreventparsing"/>
                        <meta content=no name="MSThemeCompatible"/>
                        <meta content=SKYPE_TOOLBAR_PARSER_COMPATIBLE name="SKYPE_TOOLBAR"/>

                    Rails Meta Tags
                        <meta content="authenticity_token" name="csrf-param"/>
                        <meta content=... name="csrf-token"/>

                    TweetMeme Meta Tags
                        <meta name="tweetmeme-title" content="Retweet Button Explained" />

                Create Custom Meta Tags
                <meta content=... name="..."/>

                HTML Link Tags
                <link href=http://feeds.lapys.com/ rel=alternate title=RSS type="application/rss+xml"/>
                <link href=https://www.lapys/archives/ rel=archives title="May 2003"/>
                <link href=https://www.lapys/canonical rel="canonical"/>
                <link href=# rel=EditURI title=... type="application/rsd+xml"/>
                <link href=# rel="first"/>
                <link href=fluid-icon.png rel=fluid-icon type="image/png"/>
                <link href=icon.ico rel="icon"/>
                <link href=https://www.lapys/index/? rel=index title="..."/>
                <link href=# rel="last"/>
                <link href=icon.ico rel="mask-icon"/>
                <link href=https://www.lapys/ rel=me type="text/html"/>
                <link href=javascript:history.go(1) rel=next title="..."/>
                <link href=# rel="pingback"/>
                <link href=javascript:history.go(-1) rel=prev title="OpenSearch and OpenID"/>
                <link href=https://www.lapys/search.xml rel=search title=... type="application/opensearchdescription+xml"/>
                <link href=https://www.lapys/*.php? rel=self type="application/atom+xml"/>
                <link href=icon.ico rel="shortcut icon"/>
                <link href=https://www.lapys/shortlink/ rel="shortlink"/>
                <link href=https://www.lapys/start/? rel=start title="..."/>
                <link href=base.css media="only screen and (max-device-width: 480px)" rel=stylesheet type="text/css"/>

                Open Graph Meta Tags
                    The Open Graph protocol enables any web page to become a rich object in a social graph.
                    For instance, this is used on Facebook to allow any web page to have the same functionality as any other object on Facebook.

                    Open Graph Type Values
                        Article [http://ogp.me/ns/article]
                            article:author [profile array] -> Writers of the article.
                            article:expiration_time [datetime] -> When the article is out of date after.
                            article:modified_time [datetime] -> When the article was last changed.
                            article:published_time [datetime] -> When the article was first published.
                            article:section [string] -> A high-level section name e.g.: Technology e.t.c..
                            article:tag [string array] -> Tag words associated with this article.

                        Book [http://ogp.me/ns/book]
                            book:author [profile array] -> Who wrote this book.
                            book:isbn [string] -> The ISBN.
                            book:release_date [datetime] -> The date the book was released.
                            book:tag [string array] -> Tag words associated with this book.

                        Game
                        Music
                            music.album
                                music:musician [profile] -> The musician that made this song.
                                music:release_date [datetime] -> The date the album was released.
                                music:song [music.song] -> The song on this album.
                                music:song:disc [integer >= 1] -> The same as `music:album:disc` but in reverse.
                                music:song:track [integer >= 1] -> The same as `music:album:track` but in reverse.

                            music.playlist
                                music:creator [profile] -> The creator of this playlist.
                                music:song -> Identical to the ones on `music.album`
                                    music:song:disc
                                    music:song:track

                            music.radio_station
                                music:creator [profile] -> The creator of this station.

                            music.song
                                music:duration [integer >= 1] -> The song`s length in seconds.
                                music:album [music.album array] -> The album this song is from.
                                music:album:disc [integer >= 1] -> Which disc of the album this song is on.
                                music:album:track [integer >= 1] -> Which track this song is.
                                music:musician [profile array] -> The musician that made this song.

                        Profile [http://ogp.me/ns/profile]
                            profile:first_name [string] -> A name normally given to an individual by a parent or self-chosen.
                            profile:gender [enum(male, female)] -> Their gender.
                            profile:last_name [string] -> A name inherited from a family or marriage and by which the individual is commonly known.
                            profile:username [string] -> A short unique string to identify them.

                        Video [http://ogp.me/ns/video]
                            video.episode
                                video:actor -> Identical to `video.movie`.
                                video:actor:role
                                video:director
                                video:duration
                                video:release_date
                                video:series [video.tv_show] -> Which series this episode belongs to.
                                video:tag
                                video:writer

                            video.movie
                                video:actor [profile array] -> Actors in the movie.
                                video:actor:role [string] -> The role they played.
                                video:director [profile array] -> Directors of the movie.
                                video:duration [integer >= 1] -> The movie's length in seconds.
                                video:release_date [datetime] -> The date the movie was released.
                                video:tag [string array] -> Tag words associated with this movie.
                                video:writer [profile array] -> Writers of the movie.

                            video.other
                                A video that doesn't belong in any other category. The metadata is identical to `video.movie`.

                            video.tv_show
                                A multi-episode TV show. The metadata is identical to `video.movie`.

                        Website [http://ogp.me/ns/website]

                    ...
                        <meta content="..." name="fb:page_id"/>

                        <meta content=Nigeria name="og:country-name"/>
                        <meta content="Lapys Arts is a platform for creative expression through the web" name="og:description"/>
                        <meta content=lapysdev@gmail.com name="og:email"/>
                        <meta content=+234-816-092-384-9 name="og:fax_number"/>
                        <meta content=https://www.lapys.arts/icon.ico name="og:image"/>
                        <meta content=37.416343 name="og:latitude"/>
                        <meta content=... name="og:locality"/>
                        <meta content=-122.153013 name="og:longitude"/>
                        <meta content=+234-816-092-384-9 name="og:phone_number"/>
                        <meta content=... name="og:postal-code"/>
                        <meta content=... name="og:region"/>
                        <meta content="Lapys Arts" name="og:site_name"/>
                        <meta content=... name="og:street-address"/>
                        <meta content="Movie Title" name="og:title"/>
                        <meta content=website name="og:type"/>
                        <meta content=https://www.lapys.arts name="og:url"/>

                        <meta content=the property="og:determiner"/>
                        <meta content=http://example.com/ogp.jpg property="og:image"/>
                        <meta content="A shiny red apple with a bite taken out" property="og:image:alt"/>
                        <meta content=300 property="og:image:height"/>
                        <meta content=image/jpeg property="og:image:type"/>
                        <meta content=400 property="og:image:width"/>
                        <meta content=en_GB property="og:locale"/>
                        <meta content=es_ES property="og:locale:alternate"/>
                        <meta content=fr_FR property="og:locale:alternate"/>
                        <meta content=https://secure.example.com/ogp.jpg property="og:image:secure_url"/>
            */

            // Modification > ...
            DOCUMENT.title = APPLICATION.title + (function(title) {
                if (APPLICATION.name == title.trimLeft().toLowerCase())
            })(DOCUMENT.title);

            favoriteIcon.setAttribute("href", "images/icons/favicon.ico");
            favoriteIcon.setAttribute("rel", "shortcut icon");

            loaderStylesheet.innerText = (
                "@keyframes loaderFeatureAnimation {" +
                    "0% { transform: rotateZ(0deg) }" +
                    "to { transform: rotateZ(360deg) }" +
                "}"
            );

            // Style > ...
            with (ASIDE.style) {
                backgroundColor = "#FFFFFF";
                boxShadow = "0 2px 2px rgba(0, 0, 0, .33)";
                display = "block";
                height = "60px";
                outline = "1px solid #CCCCCC";
                width = "100%"
            }

            with (BODY.style) { height = "100%"; margin = 0; width = "100%" }
            with (DOCUMENT_ELEMENT.style) { height = "100%"; width = "100%" }

            with (loader.style) {
                backgroundColor = "#FFFFFF";
                cursor = "wait";
                display = "table-cell";
                left = 0;
                height = "100%";
                opacity = 1;
                position = "fixed";
                textAlign = "center";
                top = 0;
                transition = "";
                verticalAlign = "middle";
                width = "100%"
            }

            with (loaderFeature.style) {
                animation = "750ms linear 0s loaderFeatureAnimation infinite";
                border = "15px solid #333333";
                borderLeftColor = "#0099FF";
                borderRadius = "50%";
                display = "inline-block";
                height = "65px";
                position = "relative";
                top = "40%";
                width = "65px"
            }
        }
    }

    /* ... */
    Initiate(false)
}()
