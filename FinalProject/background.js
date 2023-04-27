// Initialize filter index
let filterIndex = 1;

// Listen for changes to the blocked URLs list in storage
chrome.storage.onChanged.addListener(({ blockedUrls }) => {
  if (blockedUrls) {
    // Get the updated list of blocked URLs
    const urls = blockedUrls.newValue || [];

    filterIndex++;
    // Build the new blocking rule list
    const rules = urls.map(url => {
      return {
        id: filterIndex,
        priority: 1,
        action: {
          type: 'block'
        },
        condition: {
          urlFilter: url.url // Use the url property instead of the whole object
        }
      };
    });
    // Update the blocking rules
    chrome.declarativeNetRequest.updateDynamicRules({ addRules: rules }, () => {});
  }
});

// Initialize the blocking rules based on the current list of blocked URLs in storage
chrome.storage.local.get('blockedUrls', ({ blockedUrls }) => {
  const urls = blockedUrls || [];

  filterIndex++;
  const rules = urls.map(({ url, filterIndex }) => {
    return {
      id: filterIndex,
      priority: 1,
      action: {
        type: 'block'
      },
      condition: {
        urlFilter: url // Use the url property instead of the whole object
      }
    };
  });

  chrome.declarativeNetRequest.updateDynamicRules({ addRules: rules }, () => {});
});
