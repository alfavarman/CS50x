// Define variables for DOM elements
const urlInput = document.getElementById('url-input');
const addUrlButton = document.getElementById('add-url-btn');
const clearUrlButton = document.getElementById('clear-url-btn');
const urlList = document.getElementById('url-list');

// Define variables for storage keys
const blockedUrlsKey = 'blockedUrls';

// Initialize the URL list on the options page
chrome.storage.local.get(blockedUrlsKey, data => {
  const urls = data[blockedUrlsKey] || [];
  urls.forEach(url => addUrlToList(url));
});

// Add event listener for add URL button
addUrlButton.addEventListener('click', event => {
  event.preventDefault();
  const url = urlInput.value.trim();
  if (url) {
    chrome.storage.local.get(blockedUrlsKey, data => {
      const urls = data[blockedUrlsKey] || [];
      const filterIndex = urls.length + 1;
      urls.push({ url, filterIndex });
      chrome.storage.local.set({ [blockedUrlsKey]: urls }, () => {
        addUrlToList({ url, filterIndex });
        urlInput.value = '';
      });
    });
  }
});

// Add event listener for clear URL button
clearUrlButton.addEventListener('click', () => {
  chrome.storage.local.set({ [blockedUrlsKey]: [] }, () => {
    urlList.innerHTML = '';
  });
});

// Add an item to the URL list
function addUrlToList({ url, filterIndex }) {
  const listItem = document.createElement('li');
  listItem.innerHTML = `${url} <button class="remove-url-btn" data-filter-index="${filterIndex}">Remove</button>`;
  urlList.appendChild(listItem);
}

// Add event listener for remove URL buttons
urlList.addEventListener('click', event => {
  if (event.target.classList.contains('remove-url-btn')) {
    const filterIndex = parseInt(event.target.getAttribute('data-filter-index'));
    chrome.storage.local.get(blockedUrlsKey, data => {
      const urls = data[blockedUrlsKey] || [];
      const filteredUrls = urls.filter(urlObj => urlObj.filterIndex !== filterIndex);
      chrome.storage.local.set({ [blockedUrlsKey]: filteredUrls }, () => {
        event.target.parentNode.remove();
      });
    });
  }
});
