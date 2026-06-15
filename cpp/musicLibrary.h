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
    public:
        fs::path root;
        vector<Album> albums;

        

        // Different CTORs
        MusicLibrary(fs::path);

        // Member functions
        vector<Album> loadAlbums();
        void printAlbums();
};

