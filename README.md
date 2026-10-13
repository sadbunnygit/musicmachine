# Music Machine 🎵

A personal music-library manager for organizing albums and selecting music to transfer to an MP3 player.

The goal is to make an app that would allow users to pick new songs to upload by different categories: Artist, Album, Genre, LastUploaded, LeastUploaded. The app has a database that would keep track of how often and the last time a song or album or artist was uploaded to the MP3.

## Features

- **Album library management** - Scan a music directory and record its albums in a SQLite database.
- **Download history** - Track how many times an album has been selected and when it was last downloaded.
- **Album selection** - Query the library for albums with low download counts.
- **File transfer** - Copy selected albums to a destination directory and update their download history.

## Tech Stack

| Technology | Purpose |
| --- | --- |
| C++20 | Core application and filesystem operations |
| SQLite | Album data and download history |
| Make | Build automation |
| React | User interface |

