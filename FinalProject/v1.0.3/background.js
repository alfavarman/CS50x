// variable for switch
var isOn = true;

// global matches
var matches = [
  'https://*.facebook.com/*',
  'https://*.netflix.com/*'
];

// 
chrome.storage.local.get('matches', function(result) {
  if (result.matches === undefined) {
    chrome.storage.local.set({matches: matches});
  }
  else {
    matches = result.matches
  }
});

// Load switch state from storage
chrome.storage.local.get('isOn', function(result) {
  if (result.isOn !== undefined) {
    isOn = result.isOn;
    updateIcon();
    executeCss();
  }
});

chrome.tabs.onCreated.addListener((tab) => {
  // execute if newly open tabs with url.'
  console.log("tabs.oncreated triggered with tab.url: " + tab.url);
  if (tab.url) {
    executeCss(tab.id);
  }
});

chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
  console.log("tabs.onUpdated triggered with tabId: " + tabId);
  if (changeInfo.status === "complete") {
    executeCss(tabId);
  }
});

chrome.webNavigation.onCommitted.addListener((details) => {
  console.log("webNavigation.onCommitted triggered");
  executeCss(details.tabId);
});

chrome.action.onClicked.addListener((tab) => {
  console.log("Extension icon clicked");
  // set switch
  isOn = !isOn;
  // set icon
  updateIcon();
  // inform content script
  executeCss();
  // save switch state to storage
  chrome.storage.local.set({isOn: isOn});
  });

// Context menu 
  chrome.contextMenus.create({
    id: "options",
    title: "Options",
    contexts: ["browser_action"],
  });
  
  // listen for click
  chrome.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === "options") {
      chrome.tabs.create({ url: "options.html" });
    }
  });
  
// functions definitions //
function updateIcon() {
  console.log("updateIcon fun execute with variable isOn value: " + isOn);
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

  // Retrieve the showBadgeText value from storage
  chrome.storage.local.get('showBadgeText', function(result) {
    const showBadgeText = result.showBadgeText !== undefined ? result.showBadgeText : true;

    // Show or hide the badge text based on the showBadgeText value
    const badgeText = showBadgeText ? (isOn ? "ON" : "OFF") : '';
    chrome.action.setBadgeText({ text: badgeText });

    chrome.action.setIcon({ path: iconPath });
  });
}

// Example: Execute CSS based on extension status and tab URL changes
function executeCss(tabId) {
  
  const cssDetails = {
    target: { url: matches },
    files: ["./css/block.css"],
  };

  const injectCss = (tab) => {
    if (isOn) {
      chrome.scripting.insertCSS({ ...cssDetails, target: { tabId: tab.id } });
    } else {
      chrome.scripting.removeCSS({ ...cssDetails, target: { tabId: tab.id } });
    }
  };

  chrome.tabs.query({ url: matches }, (tabs) => {
    tabs.forEach(injectCss);
  });
}


console.log("Extension loaded");