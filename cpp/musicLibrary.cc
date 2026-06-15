

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "musicLibrary.h"
#include "album.h"


using namespace std;
namespace fs = std::filesystem;


MusicLibrary::MusicLibrary(fs::path root) : root(root), albums(loadAlbums()) {}

vector<Album> MusicLibrary::loadAlbums()
{
    vector<Album> a;
    try 
    {
        if (!fs::exists(root)) 
        {
            cout << "Files not found at: " << root << endl;
            return a;
        }

        cout << "Listing Albums in "<< root  << endl;

        for (const auto& entry : fs::directory_iterator(root)) 
        {
            //cout << entry.path().filename() << endl;
            a.emplace_back(Album(entry.path()));
        }

        return a;
    } 
    catch (fs::filesystem_error& e) 
    {
        cout << e.what() << '\n';
        return a;
    }
}

void MusicLibrary::printAlbums()
{
    for (const auto& a : albums) 
    {
        cout << a << endl;
    }
}