// variable for switch
var isOn = true;

browser.browserAction.onClicked.addListener((tab) => {
  // set switch
  isOn = !isOn;
  // set icon
  updateIcon(isOn);
  // inform content script
  updateContentScripts(isOn);
});

// functions definitions //

function updateIcon(isOn) {
  const iconPath = isOn ? "./icons/active16.png" : "./icons/inactive16.png";
  browser.browserAction.setIcon({ path: iconPath});
}

function updateContentScripts(isEnabled) {
  const contentScripts = browser.contentScripts;
  if (isEnabled) {
    contentScripts.register({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        { file: "./block.css" }
      ]
    });
  } else {
    contentScripts.unregister({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        { file: "./block.css" }
      ]
    });
  }
}
