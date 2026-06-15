#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "album.h"

using namespace std;
namespace fs = std::filesystem;

class MusicLibrary
{
    sqlite3* DB;
    const string dir;

    public:
        // ctor
        MusicLibrary(const string dir);

        void addAlbum(const Album& a);
        vector<Album> getAllAlbums();
        vector<Album> findByArtist(const string& artist);

    friend std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml );
};