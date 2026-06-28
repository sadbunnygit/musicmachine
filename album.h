#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>


using namespace std;
namespace fs = std::filesystem;


class Album
{
    public:
        const fs::path path;
        string title;
        string artist;
        int sizeMB;
        int downloadCount = 0;
        string lastDownloaded; // using string to represent date bc easier w/ sql stuff i think

        // Different CTORs
        Album(fs::path);
        Album(string title);
        Album(fs::path path, string title, string artist, int sizeMB, int downloadCount, string lastDownloaded);
};

// Non - member functions
std::ostream & operator<<( std::ostream & out, const Album & a );