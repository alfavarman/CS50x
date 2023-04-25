// set extenstion state
let isOn = true;

function updateExtensionState(isOn) {
  // set extension on/off icon
  const iconPath = isOn ? 'on_icon.png' : 'off_icon.png';
  chrome.browserAction.setIcon({ path: iconPath });

  // 
  chrome.tabs.query({ active: true, currentWindow: true }, function (tabs) {
    chrome.tabs.sendMessage(tabs[0].id, { switch: isOn });
  });

  // save new stage
  chrome.storage.sync.set({ switch: isOn });
}

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
