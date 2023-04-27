
# Productivity Blocker

Productivity Blocker Light is a Chrome extension that allows users to block access to certain URLs defined in manifest (hardcoded). This can help users stay focused on their work and avoid distractions. Blocker Light use only manifest.json and css. It is the simplest blocker solution rather for educational purpouses.

## Installation

1. Clone the repository or download the source code as a ZIP file.
2. Edit manifest.json and edit value of matches key (list of urls comma separated values)
3. Open Google Chrome and go to chrome://extensions/.
4. Enable "Developer mode" in the top right corner.
5. Click "Load unpacked" and select the folder containing the extension files.

## Usage

1. Open Google Chrome and go to chrome://extensions/ and set extenstion active
2. While active all urls defined in manifest won't be accessible
3. To unblock a URL go to chrome://extensions/ and set extenstion inactive

## Features

- Block access to specific URLs.
- Works in the background, so you can focus on your work without distractions.

## License

This project is licensed under the Creative Commons Attribution-NonCommercial License. See the LICENSE file for details.

## Acknowledgements

- This extension was created using the Chrome extension API.
