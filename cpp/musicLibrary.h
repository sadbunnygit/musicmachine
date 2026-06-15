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
    const char* dir = "./test.db";

    public:
        // ctor
        MusicLibrary(const char* dir);

        void addAlbum(const Album& a);
        vector<Album> getAllAlbums();
        vector<Album> findByArtist(const string& artist);
};

