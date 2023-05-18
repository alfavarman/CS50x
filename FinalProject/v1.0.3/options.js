document.addEventListener("DOMContentLoaded", function () {
    const toggleSwitch = document.getElementById("toggle-switch");
    const blockedUrlsList = document.getElementById("blocked-urls-list");
  
    // Load switch state from storage
    chrome.storage.local.get("showBadgeText", function (result) {
      if (result.showBadgeText !== undefined) {
        toggleSwitch.checked = result.showBadgeText;
      }
    });
  
    toggleSwitch.addEventListener("change", function () {
      const isOn = toggleSwitch.checked;
  
      // Save switch state to storage
      chrome.storage.local.set({ showBadgeText: isOn });
    });
  
  // Load blocked URLs from storage
  chrome.storage.local.get("matches", function (result) {
    if (result.matches !== undefined) {
      result.matches.forEach(function (url) {
        const li = document.createElement("li");
        li.textContent = url;
        blockedUrlsList.appendChild(li);
      });
    }
  });
});


  