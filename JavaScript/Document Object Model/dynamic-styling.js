/* MODIFY STYLESHEETS VIA JAVASCRIPT */
try {
  // Add `<style>` element to DOM
  var style = document.createElement("style");
  style.innerHTML = "body { margin: 0 }";

  document.head.appendChild(style)
} catch (error) {
  try {
    // Add `<style>` element to DOM
    var style = document.createElement("style");
    style.appendChild(document.createTextNode("body { margin: 0 }"));

    document.head.appendChild(style)
  } catch (error) {
    if (document.styleSheets.length) {
      try {
        // Add rule to DOM `CSSStyleSheet` rules list
        if ("function" == typeof(document.styleSheets[0].insertRule))
          // -- may be `appendRule(...)`, instead
          document.styleSheets[0].insertRule(
            "body { margin: 0 }",
            document.styleSheets[0].cssRules.length
          );

        // Add rule to DOM `CSSStyleSheet` rules list
        else if ("function" == typeof(document.styleSheets[0].addRule))
          document.styleSheets[0].addRule(
            "body", "margin: 0 !important; padding: 0",
            document.styleSheets[0].cssRules.length
          )
      } catch (error) {
        // Add to interpreted CSS..?
        document.styleSheets[0].cssText += "body { margin: 0 }"
      }
    }
  }
}
