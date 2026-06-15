
#include <iostream>
#include <filesystem>
#include <string>
#include "album.h"


using namespace std;
namespace fs = std::filesystem;

Album::Album(fs::path path) : path(path), title(path.filename()) {}
Album::Album(string title) : path("/Volumes/sadbunnymus/Music/"+title), title(title) {}


// non-member operator overload
std::ostream & operator<<( std::ostream & out, const Album & a ) 
{
    out << a.title << " - " << a.artist << ", path: " << a.path;
    return out;
} // operator<<