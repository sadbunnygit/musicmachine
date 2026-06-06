

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

        

        // Different CTORs
        MusicLibrary(fs::path);

        // Member functions
        vector<Album> getAlbums();
};


MusicLibrary::MusicLibrary(fs::path root) : root(root), albums(getAlbums()) {}

vector<Album> MusicLibrary::getAlbums()
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
            cout << entry.path().filename() << endl;
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