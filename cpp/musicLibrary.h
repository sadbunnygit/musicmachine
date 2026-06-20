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
    const string dbFile;

    public:
        // ctor
        MusicLibrary(const string dbFile);
        // dtor
        ~MusicLibrary();

        void addAlbum(const Album& a);
        void loadAlbums(fs::path loc);
        vector<Album> getAllAlbums();

        static string toSQLdateTime(const std::chrono::system_clock::time_point tp);

        int selectData();
        static int callback(void* NotUsed, int argc, char** argv, char** azColName);

    friend std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml );
};