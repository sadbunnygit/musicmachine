
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
// string lastDownloaded;

Album::Album(fs::path path) : path(path), title(path.filename()), artist("unknown") 
{
    cout << "Album ctor (path version) called: ";
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
Album::Album(fs::path p, string t, string a, int s, int dc, string ld) : path(p), title(t), artist(a), sizeMB(s), downloadCount(dc), lastDownloaded(ld) 
{
    cout << "Album ctor (full parameters version - prolly from database info) called: " << *this << endl;
}


// non-member operator overload
std::ostream & operator<<( std::ostream & out, const Album & a ) 
{
    out << a.title << " - " << a.artist 
        << ", path: " << a.path << ", mb = " << a.sizeMB 
        << ", download count: " << a.downloadCount << ", last_download: " << a.lastDownloaded;
    return out;
} // operator<<


