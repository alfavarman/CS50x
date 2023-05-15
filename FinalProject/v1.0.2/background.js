// variable for switch
var isOn = true;

// Load switch state from storage
chrome.storage.local.get('isOn', function(result) {
  if (result.isOn !== undefined) {
    isOn = result.isOn;
    updateIcon(isOn);
    updateContentScripts(isOn);
  }
});


chrome.action.onClicked.addListener((tab, info) => {
  console.log("Extension icon clicked");
  // set switch
  isOn = !isOn;
  // set icon
  updateIcon(isOn);
  // inform content script
  updateContentScripts(isOn);
  // save switch state to storage
  chrome.storage.local.set({isOn: isOn});
  });

// functions definitions //
function updateIcon(isOn) {
  console.log("updateIcon fun execute with isOn variable: " + isOn);
  const iconPath = isOn ? {
    "16": "./icons/active16.png",
    "32": "./icons/active32.png",
    "48": "./icons/active48.png",
    "128": "./icons/active128.png"
  } : {
    "16": "./icons/inactive16.png",
    "32": "./icons/inactive32.png",
    "48": "./icons/inactive48.png",
    "128": "./icons/inactive128.png"
  };
  chrome.action.setIcon({path: iconPath});
}

function updateContentScripts(isOn) {
  console.log("updateContentScripts fun execute with isOn variable: " + isOn);
  const contentScripts = chrome.scripting;
  if (isOn) {
    contentScripts.register({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        { file: "./css/block.css" }
      ]
    });
  } else {
    contentScripts.unregister({
      matches: [
        "https://www.facebook.com/*",
        "https://www.netflix.com/*"
      ],
      css: [
        { file: "./css/block.css" }
      ]
    });
  }
}

console.log("Extension loaded");