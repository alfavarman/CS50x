// listen webRequest: to edit or cancell them

function webListener (details) {
    // if switch
    chrome.storage.sync.get('switch', function (data) {
    if (data.switch) {
        // load block_list
        chrome.storage.sync.get('blockList', function (data) {
        var blockList = data.blockList;

        // check for url in the list
        for (let i = 0; i < blockList.length; i++) {
            var url = blockList[i].url;
            //
            if (details.url.indexOf(url) !== -1) {
            // inform url is currently blcock
            chrome.notifications.create({
                type: 'basic',
                title: 'Productivity bloacker',
                message: 'Access to ' + url + ' has been blocked.',
            });
            // cancel request
            return { cancel: true };
            }
        }
        });
    }
    });
}

export { webListener };