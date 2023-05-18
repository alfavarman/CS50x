// options.js

document.addEventListener("DOMContentLoaded", function () {
    const toggleSwitch = document.getElementById("toggle-switch");
    const blockedUrlsList = document.getElementById("blocked-urls-list");
    const newUrlInput = document.getElementById("new-url-input");
    const addUrlButton = document.getElementById("add-url-button");
  
    // Load switch state from storage
    chrome.storage.local.get("showBadgeText", function (result) {
      if (result.showBadgeText !== undefined) {
        toggleSwitch.checked = result.showBadgeText;
      }
    });
  
    // Load blocked URLs from storage
    chrome.storage.local.get("matches", function (result) {
      if (result.matches !== undefined) {
        const urls = result.matches;
        displayBlockedUrls(urls);
      }
    });
  
    function displayBlockedUrls(urls) {
      blockedUrlsList.innerHTML = "";
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
      chrome.storage.local.get("matches", function (result) {
        if (result.matches !== undefined) {
          const urls = result.matches;
          const index = urls.indexOf(url);
          if (index !== -1) {
            urls.splice(index, 1);
            chrome.storage.local.set({ matches: urls }, function () {
              displayBlockedUrls(urls);
            });
          }
        }
      });
    }
  
    addUrlButton.addEventListener("click", function () {
      const newUrl = newUrlInput.value.trim();
      if (newUrl !== "") {
        chrome.storage.local.get("matches", function (result) {
          if (result.matches !== undefined) {
            const urls = result.matches;
            urls.push(newUrl);
            chrome.storage.local.set({ matches: urls }, function () {
              displayBlockedUrls(urls);
              newUrlInput.value = "";
            });
          }
        });
      }
    });
  });
  