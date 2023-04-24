// menu func
function createContextMenus(contextMenuItems) {
    // create menu items
    for (const item of contextMenuItems) {
      chrome.contextMenus.create({
        id: item.id,
        title: item.title,
        contexts: ['browser_action'],
        onclick: item.onclick
      });
    }
  }

export { createContextMenus };
