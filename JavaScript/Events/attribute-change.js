var element = document.querySelector('#test');
setTimeout(function() {
  element.setAttribute('data-text', 'whatever');
}, 5000)

var observer = new MutationObserver(function(mutations) {
  mutations.forEach(function(mutation) {
    if (mutation.type == "attributes") {
      console.log("attributes changed")
    }
  });
});

observer.observe(element, {
  attributes: true //configure it to listen to attribute changes
});
