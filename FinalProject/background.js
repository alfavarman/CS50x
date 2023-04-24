// load cvs file
fetch(chrome.runtime.getURL('block_list.csv'))
  .then(response => response.text())
  .then(text => {

    // phrase is to array blockList
    const blockList = [];
    const rows = text.split('\n');

    // iterare row by row
    for (let i = 0; i < rows.length; i++) {
      const [url, category] = rows[i].split(',');
      blockList.push({ url, category });
    }

    // store it in chome storage
    chrome.storage.local.set({ blockList }, () => {
      console.log('Block list loaded');
    });
  });

// load blockList
chrome.storage.sync.get('blockList');

// set extenstion state
  // listen for action
chrome.browserAction.onClicked.addListener(function(tab) {
// set icon acording to state:
  // get 'switch'
  chrome.storage.sync.get('switch', function(data) {
   // define new switch and overwight it
    var newState = !data.switch;
    chrome.storage.sync.set({ switch: newState }); 
    // set icon based on state
    var iconPath = newState ? 'active128.png' : 'inactive128.png';
    var title = newState ? 'Focus ON' : 'Focus OFF';

    // check all tabs in all windows:
    // Send a message to the content script to update its state

    chrome.tabs.query({ active: true}, function(tabs) {          // { active: true, currentWindow: true } !SETTING OPTION!
      chrome.tabs.sendMessage(tabs[0].id, { switch: newState });
    });
  });
});

// listen webRequest: to edit or cancell them
chrome.webRequest.onBeforeRequest.addListener(
  function(details) {
    // if switch
    chrome.storage.sync.get('switch', function(data) {
      if (data.switch) {
        // load block_list
        chrome.storage.sync.get('blockList', function(data) {
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

//menu 
let isOn = true;

chrome.browserAction.onClicked.addListener(function(tab) {
  // differ clicked button on extensiton icone
  // left click (0ledt 1middle 2right)
  if (tab.button === 0) { 
    // Toggle the state of the extension
    isOn = !isOn;

    // Update the icon based on the new state
    const iconPath = isOn ? 'on_icon.png' : 'off_icon.png';
    chrome.browserAction.setIcon({ path: iconPath });

    // Send a message to the content script to update its state
    chrome.tabs.query({ active: true, currentWindow: true }, function(tabs) {
      chrome.tabs.sendMessage(tabs[0].id, { switch: isOn });
    });
  }
});

// Create the context menu
chrome.contextMenus.create({
  title: 'My Extension',
  contexts: ['browser_action'],
  onclick: function() {
    // Do something when the menu item is clicked
  }
});