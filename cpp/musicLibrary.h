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
        // c/d - tor
        MusicLibrary(const char* dir);
        ~MusicLibrary();


        void addAlbum(const Album& a);
        vector<Album> getAllAlbums();
        vector<Album> findByArtist(const string& artist);
};

