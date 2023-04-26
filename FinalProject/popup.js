// // Get the extension on/off switch element
// var toggleSwitch = document.getElementById('toggleSwitch');

// // Get the current state of the extension on/off switch
// chrome.storage.local.get('extensionOn', function(result) {
//   toggleSwitch.checked = result.extensionOn;
// });

// // Add an event listener to the extension on/off switch
// toggleSwitch.addEventListener('change', function() {
//   // Send a message to the background script to toggle the extension on/off switch
//   chrome.runtime.sendMessage({ toggleSwitch: true });
// });
