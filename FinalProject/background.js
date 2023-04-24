// set extenstion state
// listen for action
let isOn = true;
chrome.browserAction.onClicked.addListener(function (tab) {
  // differ clicked button on extensiton icone
  // left click (0ledt 1middle 2right)
  if (tab.button === 0) {
    // Toggle the state of the extension
    isOn = !isOn;
    updateExtensionState(isOn);
  }
});

function updateExtensionState(isOn) {
  // Update the icon based on the new state
  const iconPath = isOn ? 'on_icon.png' : 'off_icon.png';
  chrome.browserAction.setIcon({ path: iconPath });

  // Send a message to the content script to update its state
  chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
    chrome.tabs.sendMessage(tabs[0].id, { switch: isOn });
  });

  // Store the new state in Chrome storage
  chrome.storage.sync.set({ switch: isOn });
}

// listen webRequest: to edit or cancell them
chrome.webRequest.onBeforeRequest.addListener(
  function (details) {
    // if switch
    chrome.storage.sync.get('switch', function (data) {
      if (data.switch) {
        // load block_list
        chrome.storage.sync.get('blockList', function (data) {
          var blockList = data.blockList;

          // check for url in the list
          for (let i = 0; i < blockList.length; i++) {
            var url = blockList[i].url;
            //
            if (details.url.indexOf(url) !== -1) {
              // inform url is currently blcock
              chrome.notifications.create({
                type: 'basic',
                title: 'Productivity bloacker',
                message: 'Access to ' + url + ' has been blocked.',
              });
              // cancel request
              return { cancel: true };
            }
          }
        });
      }
    });
  },
  // for all urls
  { urls: ['<all_urls>'] },
  // array of action
  ['blocking']
);

// load cvs file
fetch(chrome.runtime.getURL('block_list.csv'))
  .then((response) => response.text())
  .then((text) => {
    // phrase is to array blockList
    const blockList = [];
    const rows = text.split('\n');

    // read all rows
    for (let i = 0; i < rows.length; i++) {
      const [url, category] = rows[i].split(',');
      blockList.push({ url, category });
    }

    // store it
    chrome.storage.local.set({ blockList }, () => {
      console.log('Block list loaded');
    });
  });

// menu
// menu items
const contextMenuItems = [
  { 
    id: 'switch',
    title: 'Switch',
    onclick: toggleSwitch
  },
  { 
    id: 'blockList',
    title: 'Block Lists',
    onclick: openPage.bind(null, 'block_list.html')
  },
  { 
    id: 'timer',
    title: 'Timer',
    onclick: showTimer
  },
  { 
    id: 'settings',
    title: 'Settings',
    onclick: openPage.bind(null, 'settings.html')
  },
  { 
    id: 'about',
    title: 'About',
    onclick: showMessage.bind(null, 'This is the about page.')
  }
];

// Create the context menu
for (const item of contextMenuItems) {
  chrome.contextMenus.create({
    id: item.id,
    title: item.title,
    contexts: ['browser_action'],
    onclick: item.onclick
  });
}

// Define the onclick handlers for the context menu items
function toggleSwitch() {
  chrome.storage.sync.get('switch', function(data) {
    const newState = !data.switch;
    chrome.storage.sync.set({ switch: newState }); 

    const iconPath = newState ? 'active128.png' : 'inactive128.png';
    const title = newState ? 'Focus ON' : 'Focus OFF';

    chrome.browserAction.setIcon({ path: iconPath });
    chrome.browserAction.setTitle({ title: title });

    chrome.tabs.query({ active: true, currentWindow: true }, function(tabs) {
      chrome.tabs.sendMessage(tabs[0].id, { switch: newState });
    });
  });
}

function openBlockListPage() {
  chrome.tabs.create({ url: chrome.extension.getURL('block_list.html') });
}

function showTimer() {
  chrome.storage.sync.get('timer', function(data) {
    const minutes = data.timer || 0;
    alert(`Blockade is on for ${minutes} minutes.`);
  });
}

function openSettingsPage() {
  chrome.tabs.create({ url: chrome.extension.getURL('settings.html') });
}

function openAboutPage() {
  alert('This is the about page.');
}
