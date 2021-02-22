var body = document.body || document.getElementsByTagName("body").item(0) || (function(body) {
  document.documentElement.appendChild(body);
  return body
})(document.createElement("body"));
var canvas = document.getElementsByTagName("canvas").item(0) || document.createElement("canvas");
var context = canvas.getContext("2d");

var rotation = 0;
var rotation_speed = 7.5e-2;

void function RESET() {
  body.style = "";

  canvas.parentElement && canvas.parentElement.removeChild(canvas)
  canvas.style = "";

  context = canvas.getContext("2d");

  document.documentElement.style = ""
}();

void function INITIATE() {
  body.appendChild(canvas);
  with (body.style) {
    backgroundColor = "#0F0F0F";
    height = "100%";
    margin = 0;
    width = "100%"
  }

  with (canvas.style) {
    backgroundColor = "#0C0C0C";
    left = 0;
    outline = "1px solid #FFFFFF";
    position = "fixed";
    top = 0
  }

  document.documentElement.style.height = "100%"
}();

void function UPDATE() {
  var size = Math.min(
    (body.getBoundingClientRect().bottom - body.getBoundingClientRect().top),
    (body.getBoundingClientRect().right - body.getBoundingClientRect().left)
  ) * (100 / 100);

  canvas.style.height = (canvas.height = size) + "px";
  canvas.style.width = (canvas.width = size) + "px";

  context.beginPath();
    context.lineWidth = "1px";
    context.strokeStyle = "rgba(255, 255, 255, 1)";

    context.translate(size / 2, size / 2);
    context.rotate(rotation += rotation_speed);
    context.translate(-(size / 2), -(size / 2));

    context.moveTo(size * (50 / 100), size * (33 / 100));
    context.lineTo(size * (66 / 100), size * (66 / 100));
    context.lineTo(size * (33 / 100), size * (66 / 100));
    context.lineTo(size * (50 / 100), size * (33 / 100));
    context.stroke();
  context.closePath();

  requestAnimationFrame(UPDATE)
}()
