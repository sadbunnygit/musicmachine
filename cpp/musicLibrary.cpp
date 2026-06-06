

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "album.cpp"

using namespace std;
namespace fs = std::filesystem;

class MusicLibrary
{
    public:
        fs::path root;
        vector<Album> albums;
};