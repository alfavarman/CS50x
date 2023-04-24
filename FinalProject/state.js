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

  export { updateExtensionState };