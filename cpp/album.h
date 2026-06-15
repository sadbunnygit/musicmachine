#pragma once

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;


class Album
{
    public:
        const fs::path path;
        string artist;
        string title;
        int songCount;

        // Different CTORs
        Album(fs::path);
        Album(string title);
};

// Non - member functions
std::ostream & operator<<( std::ostream & out, const Album & a );