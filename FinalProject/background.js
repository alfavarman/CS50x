// load cvs file
fetch(chrome.runtime.getURL('block_list.csv'))
  .then(response => response.text())
  .then(text => {

    // phrase is to array blockList
    const blockList = [];
    const rows = text.split('\n');

    // iterare row by row
    for (let i = 0; i < rows.length; i++) {
      const [url, category] = rows[i].split(',');
      blockList.push({ url, category });
    }

    // store it in chome storage
    chrome.storage.local.set({ blockList }, () => {
      console.log('Block list loaded');
    });
  });



// set extenstion state

// set icon acording to state

// if state is on

    //listen the request

    // check if reurst is BlockList

        // create notifiction f url: {url} blocked by oriductivityBlocker

        // cancel request
