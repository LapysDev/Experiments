function getChildElementById(element, id) {
  var list = element.childNodes;

  // ...
  for (var index = list.length; index; ) {
    var node = list.item(--index);

    if (0x1 /* --> Node.ELEMENT_NODE */ === node.nodeType)
    if (id === node.id) return node
  }

  return null
}
