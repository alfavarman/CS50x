// Listen for changes to the blocked URLs list in storage
chrome.storage.onChanged.addListener(({ blockedUrls }) => {
  if (blockedUrls) {
    // Get the updated list of blocked URLs
    const urls = blockedUrls.newValue || [];

    // Build the new blocking rule list
    const rules = urls.map(url => {
      return {
        id: url,
        priority: 1,
        action: {
          type: 'block'
        },
        condition: {
          urlFilter: url
        }
      };
    });

    // Update the blocking rules
    chrome.declarativeNetRequest.updateDynamicRules({
      addRules: rules.map(rule => ({ rule })),
      removeRuleIds: urls.map(url => ({ id: url }))
    });
  }
});

// Initialize the blocking rules based on the current list of blocked URLs in storage
chrome.storage.local.get('blockedUrls', ({ blockedUrls }) => {
  const urls = blockedUrls || [];
  const rules = urls.map(url => {
    return {
      id: url,
      priority: 1,
      action: {
        type: 'block'
      },
      condition: {
        urlFilter: url
      }
    };
  });

  chrome.declarativeNetRequest.updateDynamicRules({
    addRules: rules.map(rule => ({ rule }))
  });
});
