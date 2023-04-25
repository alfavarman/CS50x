import { webListener } from './web-listener.js';
import { updateExtensionState, toggleSwitch } from './state.js';
import { createContextMenus } from './context-menu.js';

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

// listen webRequest: to edit or cancel them
chrome.webRequest.onBeforeRequest.addListener(
  webListener,
  { urls: ['<all_urls>'] },
  ['blocking']
);

// load csv file
fetch(chrome.runtime.getURL('block_list.csv'))
  .then((response) => response.text())
  .then((text) => {
    // parse it into array blockList
    const blockList = [];
    const rows = text.split('\n');

    // include all rows
    for (let i = 0; i < rows.length; i++) {
      const [url, category] = rows[i].split(',');
      blockList.push({ url, category });
    }

    chrome.storage.local.set({ blockList }, () => {
      console.log('Block list loaded');
    });
  });

// context menu
import { createContextMenus } from './context-menu.js';

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
    onclick: showMessage.bind(null, 'This is Final Project of CS50X')
  }
];

createContextMenus(contextMenuItems);

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
