/* Initialization */
    // File System
    const fs = require("fs"),

    // Hypertext Transform Protocol
    http = require("http");

/* Initialization  */
    // Host Name
    const HOSTNAME = "127.0.0.1",

    // Port
    PORT = 3000;

// File System > Read File
fs.readFile("pages/test.html" || "index.html", function(error, source) {
    // Logic
    if (error)
        // Error
        throw error;

    else {
        // Initialization > Server
        const SERVER = http.createServer(function(request, response) {
            // Modification > Response > Status Code
            response.statusCode = 200;

            // Response > (Set Header, Write)
            response.setHeader("Content-type", "text/html");
            response.write(source)
        });

        // Server > Listen
        SERVER.listen(PORT, HOSTNAME, function() { console.log("Server listening on \"" + "" + "\"") })
    }
});
