// HTMLCanvasElement in the DOM tree.
var buffers = [
    document.createElement("canvas"),
    document.createElement("canvas")
], bufferContexts = buffers.map(buffer => [buffer.getContext("2d")]);

buffers.forEach(buffer => {
    buffer.height = 150;
    buffer.width = 150
});

bufferContexts[0][0].strokeStyle = "red";
bufferContexts[0][0].strokeRect(25, 25, 50, 50);

setTimeout(function() {
    bufferContexts[1][0].strokeStyle = "blue";
    bufferContexts[1][0].strokeRect(25, 25, 50, 50);

    bufferContexts[0][0].drawImage(buffers[1], 0, 0)
}, 750)

document.body.appendChild(buffers[0])
