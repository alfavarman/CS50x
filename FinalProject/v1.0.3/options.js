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
    function displayBlockedUrls(urls) {
        urls.forEach(function (url) {
          const listItem = document.createElement("li");
          listItem.textContent = url;
          const deleteIcon = document.createElement("span");
          deleteIcon.classList.add("delete-icon");
          deleteIcon.innerHTML = "&#10006;";
          deleteIcon.addEventListener("click", function () {
            deleteUrl(url);
          });
          listItem.appendChild(deleteIcon);
          blockedUrlsList.appendChild(listItem);
        });
      }
    
      function deleteUrl(url) {
        chrome.storage.local.get("blockedUrls", function (result) {
          if (result.blockedUrls !== undefined) {
            const urls = result.blockedUrls;
            const index = urls.indexOf(url);
            if (index !== -1) {
              urls.splice(index, 1);
              chrome.storage.local.set({ blockedUrls: urls }, function () {
                blockedUrlsList.innerHTML = "";
                displayBlockedUrls(urls);
              });
            }
          }
        });
      }
    
      addUrlButton.addEventListener("click", function () {
        const newUrl = newUrlInput.value.trim();
        if (newUrl !== "") {
          chrome.storage.local.get("blockedUrls", function (result) {
            if (result.blockedUrls !== undefined) {
              const urls = result.blockedUrls;
              urls.push(newUrl);
              chrome.storage.local.set({ blockedUrls: urls }, function () {
                blockedUrlsList.innerHTML = "";
                displayBlockedUrls(urls);
                newUrlInput.value = "";
              });
            }
          });
        }
      });
    });
  