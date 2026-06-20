
#include <iostream>
#include <filesystem>
#include <string>
#include <sqlite3.h>

#include "album.h"


using namespace std;
namespace fs = std::filesystem;


// const fs::path path;
// string title;
// string artist;
// int sizeMB;
// int downloadCount;
// timepoint lastDownloaded;
// timepoint lastUploaded;

Album::Album(fs::path path) : path(path), title(path.filename()), artist("unknown") 
{
    cout << "path ctor called" << endl;
    uintmax_t totalSize = 0;

    for (const auto& entry : fs::recursive_directory_iterator(path)) 
    {
        auto name = entry.path().filename().string();
        if (name[0]=='.' && name[1]=='_')
            continue;
        
        if (entry.is_regular_file()) 
        {
            totalSize += entry.file_size();
        }
    }

    sizeMB = totalSize / (1024.0 * 1024.0);

    cout << *this << endl;
}
Album::Album(string title) : path("/Volumes/sadbunnymus/Music/"+title), title(title), artist("unknown") {}


// non-member operator overload
std::ostream & operator<<( std::ostream & out, const Album & a ) 
{
    out << a.title << " - " << a.artist << ", path: " << a.path << ", mb = " << a.sizeMB;
    return out;
} // operator<<