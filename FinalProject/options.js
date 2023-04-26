// Get references to the UI elements
const blockedUrlsList = document.getElementById('blocked-urls');
const urlInput = document.getElementById('url-input');
const addButton = document.getElementById('add-button');
const clearButton = document.getElementById('clear-button');

// Load the blocked URLs from storage and display them in the UI
chrome.storage.local.get('blockedUrls', ({ blockedUrls }) => {
  if (blockedUrls && blockedUrls.length) {
    blockedUrls.forEach(url => {
      const li = document.createElement('li');
      li.textContent = url;
      blockedUrlsList.appendChild(li);
    });
  }
});

// Add event listeners for the UI elements
addButton.addEventListener('click', () => {
  const url = urlInput.value.trim();
  if (url) {
    // Add the URL to the blocked URLs list
    const li = document.createElement('li');
    li.textContent = url;
    blockedUrlsList.appendChild(li);

    // Save the updated list of blocked URLs to storage
    chrome.storage.local.get('blockedUrls', ({ blockedUrls }) => {
      const updatedUrls = blockedUrls ? [...blockedUrls, url] : [url];
      chrome.storage.local.set({ blockedUrls: updatedUrls });
    });

    // Clear the URL input field
    urlInput.value = '';
  }
});

clearButton.addEventListener('click', () => {
  // Clear the blocked URLs list in the UI
  blockedUrlsList.innerHTML = '';

  // Clear the list of blocked URLs in storage
  chrome.storage.local.set({ blockedUrls: [] });
});
