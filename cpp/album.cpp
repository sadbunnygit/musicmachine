
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

Album::Album(fs::path path) : path(path), title(path.filename()) {}
Album::Album(string title) : path("/Volumes/sadbunnymus/Music/"+title), title(title) {}