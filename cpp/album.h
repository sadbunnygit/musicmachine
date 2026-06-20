#pragma once

#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>


using namespace std;
namespace fs = std::filesystem;
using timepoint = std::chrono::system_clock::time_point;


class Album
{
    public:
        const fs::path path;
        string title;
        string artist;
        int downloadCount;
        timepoint lastDownloaded;
        timepoint lastUploaded;

        // Different CTORs
        Album(fs::path);
        Album(string title);
};

// Non - member functions
std::ostream & operator<<( std::ostream & out, const Album & a );