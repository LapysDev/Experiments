function getElementsByClassName(node, className) /* UPDATE (Lapys) -> Only recognizes ASCII whitespace as the class name delimiter */ {
  var classList = split(className);
  var elements  = [];

  // ...
  function split(name) {
    var index = +0;
    var list  = [""];

    // ...
    for (var subindex = +0; subindex !== name.length; ++subindex) {
      var character = name.charAt(subindex);

      // ...
      if (character === ' ' || character === '\f' || character === '\n' || character === '\r' || character === '\t' || character === '\v') {
        if ("" !== list[index]) index = list.push("") - 1;
        continue
      }

      list[index] += character
    }

    if ("" === list[index])
    list.pop();

    // ...
    return list
  }

  if (+0 !== classList.length) {
    var list       = node.childNodes;
    var queue      = [];
    var queueCount = +0;

    // ...
    while (true) {
      search:
      for (var index = list.length; index; ) {
        var childNode = list.item(--index);

        if (0x1 /* --> Node.ELEMENT_NODE */ === childNode.nodeType) {
          var elementClassName = childNode.className;
          var elementClassList = null;

          // ...
          queueCount = queue.push(childNode.childNodes);
          if (className === elementClassName) { elements.push(childNode); continue search }

          elementClassList = split(elementClassName);
          if (+0 === elementClassList.length) continue search;

          for (var elementClassListIndex = elementClassList.length; elementClassListIndex; )
          if (className === elementClassList[--elementClassListIndex]) { elements.push(childNode); continue search }

          for (var classListIndex = classList.length, classListMatch = true; classListIndex--; ) {
            for (var elementClassListIndex = elementClassList.length; ; ) {
              if (classList[classListIndex] === elementClassList[--elementClassListIndex]) break;
              if (+0 === elementClassListIndex) { classListMatch = false; break }
            }

            if (false === classListMatch) break;
            if (+0 === classListIndex) { elements.push(childNode); continue search }
          }
        }
      }

      if (+0 === queueCount--) break;
      list = queue[+0];

      for (var index = +0; index !== queueCount; ++index) queue[index] = queue[index + 1];
      queue.pop()
    }
  }

  return elements
}
