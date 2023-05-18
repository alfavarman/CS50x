document.addEventListener("DOMContentLoaded", function () {
    const toggleSwitch = document.getElementById("toggle-switch");
  
    // Load switch state from storage
    chrome.storage.local.get("showBadgeText", function (result) {
      if (result.showBadgeText !== undefined) {
        toggleSwitch.checked = result.showBadgeText;
      }
    });
  
    toggleSwitch.addEventListener("input", function () {
      const isOn = toggleSwitch.checked;
  
      // Save switch state to storage
      chrome.storage.local.set({ showBadgeText: isOn });
    });
  });
  