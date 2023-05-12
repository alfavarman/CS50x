// variable for switch
let isOn = true;

chrome.action.onClicked.addListener((tab) => {
  console.log("Extension icon clicked");
  if (tab.button === 0) {
    // set switch
    isOn = !isOn;
    // set icon
    updateIcon(isOn);
    // inform content script
    updateContentScripts(isOn);
  }
});

// functions definitions //

function updateIcon(isOn) {
  const iconPath = isOn ? "./icons/active16.png" : "./icons/inactive16.png";
  chrome.action.setIcon({ path: iconPath });
}

function updateContentScripts(isEnabled) {
  const contentScripts = chrome.contentScripts;
  if (isEnabled) {
    contentScripts.register({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        "./css/block.css"
      ]
    });
  } else {
    contentScripts.unregister({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        "./css/block.css"
      ]
    });
  }
}
