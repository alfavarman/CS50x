# Productivity Blocker Chrome Extension

A Chrome extension that allows users to block access to certain URLs based on a predefined list.

## Features

- Toggle the extension on/off with a single click.
- Blocks access to specific URLs (e.g., Facebook and Netflix) when the extension is active.
- Updates the extension icon and badge text to reflect the current status.

## Installation

1. Clone or download the repository to your local machine.
2. Open Google Chrome and go to `chrome://extensions`.
3. Enable the **Developer mode** toggle switch (top right corner).
4. Click on the **Load unpacked** button.
5. Select the folder where you cloned/downloaded the extension.

## Usage

1. Once installed, you'll see the extension icon in the Chrome toolbar.
2. Click on the extension icon to toggle it on or off.
3. When the extension is active (icon color is active), it will block access to specific URLs (e.g., Facebook and Netflix).
4. When the extension is inactive (icon color is inactive), access to the blocked URLs will be allowed.
5. The extension icon and badge text will reflect the current status (ON/OFF).

## Customization

You can customize the list of blocked URLs by modifying the `matches` array in the `executeCss()` function within the `background.js` file. Update the URLs to match your desired blocked websites.

```javascript
const matches = [
  'https://www.facebook.com/*',
  'https://www.netflix.com/*'
];

## Features

- Block access to specific URLs.
- Works in the background, so you can focus on your work without distractions.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial License. See the LICENSE file for details.

## Acknowledgements

- This extension was created using the Chrome extension API.
