// Variable for switch
var isOn = true;

// Global matches
var matches = [
  'https://*.facebook.com/*',
  'https://*.netflix.com/*'
];

// Load matches from storage or set default values
chrome.storage.local.get('matches', function(result) {
  if (result.matches === undefined) {
    chrome.storage.local.set({ matches: matches });
  } else {
    matches = result.matches;
  }
});

// Load switch state from storage or set default value to true
chrome.storage.local.get('isOn', function(result) {
  if (result.isOn !== undefined) {
    isOn = result.isOn;
  } else {
    chrome.storage.local.set({ isOn: isOn });
  }
  updateIcon();
  updateBadgeText();
});

// Event listeners
chrome.tabs.onCreated.addListener((tab) => {
  if (tab.url) {
    executeCss(tab.id);
  }
});

chrome.tabs.onUpdated.addListener((tabId, changeInfo, tab) => {
  if (changeInfo.status === 'complete') {
    executeCss(tabId);
  }
});

chrome.webNavigation.onCommitted.addListener((details) => {
  executeCss(details.tabId);
});

chrome.action.onClicked.addListener((tab) => {
  isOn = !isOn;
  updateIcon();
  updateBadgeText();
  executeCss();
  chrome.storage.local.set({ isOn: isOn });
});

// Context menu
chrome.contextMenus.create({
  id: 'options',
  title: 'Options',
  contexts: ['browser_action'],
});

// Listen for click on context menu
chrome.contextMenus.onClicked.addListener((info, tab) => {
  if (info.menuItemId === 'options') {
    chrome.tabs.create({ url: 'options.html' });
  }
});

// Function to update the icon
function updateIcon() {
  const iconPath = isOn
    ? {
        '16': './icons/active16.png',
        '32': './icons/active32.png',
        '48': './icons/active48.png',
        '128': './icons/active128.png',
      }
    : {
        '16': './icons/inactive16.png',
        '32': './icons/inactive32.png',
        '48': './icons/inactive48.png',
        '128': './icons/inactive128.png',
      };

  chrome.action.setIcon({ path: iconPath });
}

// Function to update the badge text
function updateBadgeText() {
  // Retrieve the showBadgeText value from storage or set default value to true
  chrome.storage.local.get('showBadgeText', function(result) {
    const showBadgeText = result.showBadgeText !== undefined ? result.showBadgeText : true;

    // Show or hide the badge text based on the showBadgeText value
    const badgeText = showBadgeText ? (isOn ? 'ON' : 'OFF') : '';
    chrome.action.setBadgeText({ text: badgeText });
  });
}

// Example: Execute CSS based on extension status and tab URL changes
function executeCss(tabId) {
  const cssDetails = {
    target: { url: matches },
    files: ['./css/block.css'],
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

console.log('Extension loaded');
