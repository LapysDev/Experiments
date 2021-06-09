var dragging = false;
var pressing = false;

var target = document.getElementsByTagName("div").item(0) || document.createElement("div");
var targetBounded = false;
var targetBoundsX = 0, targetBoundsY = 0;
var targetBoundsOffsetX = 0, targetBoundsOffsetY = 0;

// ...
document.body.appendChild(target);
with (target.style) {
  backgroundColor = "red";
  height = 300 + "px";
  left = 0;
  position = "fixed";
  top = 0;
  width = 300 + "px"
}

// ...
function onmousedrag(event) {
  var bounds = target.getBoundingClientRect();

  if (false === targetBounded) {
    targetBoundsX = event.x; targetBoundsY = event.y;
    targetBoundsOffsetX = bounds.left; targetBoundsOffsetY = bounds.top;

    targetBounded = (
      (event.x >= bounds.left && event.x <= bounds.right) &&
      (event.y >= bounds.top && event.y <= bounds.bottom)
    )
  }

  else with (target.style) {
    backgroundColor = "blue";
    left = targetBoundsOffsetX + (event.x - targetBoundsX);
    top = targetBoundsOffsetY + (event.y - targetBoundsY)
  }
}

function onmousedragstart(event) {}
function onmousedragend(event) {
  target.style.backgroundColor = "red";
  targetBounded = false
}

// ...
onmousedown = event => { if (false === pressing) pressing = true };
onmouseup = event => {
  if (pressing) {
    dragging = false; pressing = false;
    onmousedragend(event)
  }
};

onmousemove = event => {
  if (false === pressing)
    dragging = false;

  else {
    dragging = true;
    onmousedrag(event)
  }
}
