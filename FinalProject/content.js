chrome.storage.local.get('extensionOn', function(result) {
    if (result.extensionOn) {
        chrome.storage.local.get('blockList', function(result) {
            var blockList = result.blockList || [];
            if (blockList.length > 0) {
              var currentUrl = window.location.href;
              for (var i = 0; i < blockList.length; i++) {
                if (currentUrl.includes(blockList[i])) {
                  alert('This website is blocked by Productivity Blocker!');
                  break;
                }
              }
            }
          });
    }});