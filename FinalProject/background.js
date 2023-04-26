// Fetch the block list file and save it to storage
fetch(chrome.runtime.getURL('block_list.csv'))
  .then(response => response.text())
  .then(text => {
    var lines = text.split('\n').filter(line => line.trim() !== '');
    var blockList = lines.map(line => line.split(',')[0].trim());
    chrome.storage.local.set({ 'blockList': blockList });
  })
  .catch(error => console.error('Error fetching block list file:', error));
  console.log('list fetched');

// Set the extension on/off switch to off by default
chrome.storage.local.get('extensionOn', function(result) {
  if (!result.extensionOn) {
    chrome.storage.local.set({ 'extensionOn': false });
  }
  console.log('extensionOn', result.extensionOn);
});

// Fetch the block list file and save it to storage
fetch(chrome.runtime.getURL('block_list.csv'))
  .then(response => response.text())
  .then(text => {
    var lines = text.split('\n').filter(line => line.trim() !== '');
    var blockList = lines.map(line => line.split(',')[0].trim());
    chrome.storage.local.set({ 'blockList': blockList });
    console.log('list fetched');
  })
  .catch(error => console.error('Error fetching block list file:', error));

// Set the extension on/off switch to off by default
chrome.storage.local.get('extensionOn', function(result) {
  if (!result.extensionOn) {
    chrome.storage.local.set({ 'extensionOn': false });
  }
  console.log('extensionOn', result.extensionOn);
});

// Listen for the extension icon click event
chrome.browserAction.onClicked.addListener(function(tab) {
  // Update the extension on/off switch
  chrome.storage.local.get('extensionOn', function(result) {
    var extensionOn = !result.extensionOn;
    chrome.storage.local.set({ 'extensionOn': extensionOn });

    // Update the extension icon based on the switch state
    if (extensionOn) {
      chrome.browserAction.setIcon({ path: {
        "16": "./icons/active16.png",
        "32": "./icons/active32.png",
        "48": "./icons/active48.png",
        "128": "./icons/active128.png"
      }});
      console.log('extensionOn', extensionOn);
    } else {
      chrome.browserAction.setIcon({ path: {
        "16": "./icons/inactive16.png",
        "32": "./icons/inactive32.png",
        "48": "./icons/inactive48.png",
        "128": "./icons/inactive128.png"
      }});
      console.log('extensionOn', extensionOn);
    }
  });
});


chrome.webRequest.onBeforeRequest.addListener(
  function(details) {
    // Check if the extension is on
    return new Promise(resolve => {
      chrome.storage.local.get('extensionOn', function(result) {
        if (result.extensionOn) {
          // Check if the requested URL is in the block list
          chrome.storage.local.get('blockList', function(result) {
            var blockList = result.blockList || [];
            if (blockList.length > 0) {
              console.log('block list not empty')
            };
            if (blockList.includes(details.url)) {
              // Block the request
              resolve({redirectUrl:"javascript:"});
            } else {
              // Don't block the request
              resolve({});
            }
          })
        } else {
          // Don't block the request
          resolve({});
        }
      });
    });
  },
  { urls: ["<all_urls>"]}, 
  ["blocking"]
);

