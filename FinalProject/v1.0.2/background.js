// variable for switch
var isOn = true;

// Load switch state from storage
chrome.storage.local.get('isOn', function(result) {
  if (result.isOn !== undefined) {
    isOn = result.isOn;
    updateIcon(isOn);
    executeCss(isOn);
  }
});


chrome.action.onClicked.addListener((tabId, info) => {
  console.log("Extension icon clicked");
  // set switch
  isOn = !isOn;
  // set icon
  updateIcon(isOn);
  // inform content script
  executeCss(isOn);
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
// Example: Execute CSS based on extension status and tab URL changes
function executeCss(isOn) {
  const matches = [
    'https://www.facebook.com/*',
    'https://www.netflix.com/*'
  ];

  if (isOn) {
    chrome.tabs.query({ url: matches }, (tabs) => {
      tabs.forEach((tab) => {
        chrome.scripting.insertCSS({
          target: { tabId: tab.id },
          files: ['./css/block.css']
        });
      });
    });
  } else {
    chrome.tabs.query({ url: matches }, (tabs) => {
      tabs.forEach((tab) => {
        chrome.scripting.removeCSS({
          target: { tabId: tab.id },
          files: ['./css/block.css']
        });
      });
    });
  }
}


console.log("Extension loaded");