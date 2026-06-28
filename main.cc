

#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <format>

#include "musicLibrary.h"
#include "album.h"


using namespace std;
namespace fs = std::filesystem;


void listFiles(string dir);
void listFilesRecur(string dir);
bool confirm(const string& message);
void removeAll(string dir);
void copyInsides(string from, string to, string folder);
void loadUSB(MusicLibrary ml, fs::path loc);



int main(int argc, char* argv[])
{
    cout << "\n\n ~~~ MUSIC MACHINE PROGRAM RUNNING! ~~~" << endl;

    // 
    std::time_t t = std::time(0);   // Get the time now
    std::tm* now = std::localtime(&t);
    std::cout << "Today: " << (now->tm_year + 1900) << '-'
        << (now->tm_mon + 1) << '-'
        <<  now->tm_mday
        << "\n";
    // Source - https://stackoverflow.com/a/997988
    // Posted by anon, modified by community. See post 'Timeline' for change history
    // Retrieved 2026-06-28, License - CC BY-SA 4.0
    cout << endl;
    
    fs::path musicMachine = "/Volumes/NO NAME/music"; 
    fs::path musicStore = "/Volumes/sadbunnymus/Music"; 
    cout << "testing music library constructor" << endl;
    string storeDB = "./musicStore.db";
    string playDB = "./musicPlayer.db";
    MusicLibrary store = MusicLibrary(storeDB);
    MusicLibrary play = MusicLibrary(playDB);
    cout << store << endl;
    cout << play << endl;
    if (confirm("load " + musicStore.string() + " into its database? "))
        store.loadAlbums(musicStore);
    if (confirm("load " + musicMachine.string() + " into its database? "))
        play.loadAlbums(musicMachine);
    cout << endl;
}


void listFilesRecur(string dir)
{
    try 
    {
        if (!fs::exists(dir)) 
        {
            cout << "Files not found at: " << dir << endl;
            return;
        }

        cout << "Listing files in "<< dir  << endl;

        for (const auto& entry : fs::recursive_directory_iterator(dir)) 
        {
            cout << entry.path() << endl;
        }
    } 
    catch (fs::filesystem_error& e) 
    {
        cout << e.what() << '\n';
    }
}
void listFiles(string dir)
{
    try 
    {
        if (!fs::exists(dir)) 
        {
            cout << "Files not found at: " << dir << endl;
            return;
        }

        cout << "Listing files in "<< dir  << endl;

        for (const auto& entry : fs::directory_iterator(dir)) 
        {
            cout << entry.path() << endl;
        }
    } 
    catch (fs::filesystem_error& e) 
    {
        cout << e.what() << '\n';
    }
}

bool confirm(const string& message)  
{
    string input;
    cout << message << " (type 'yes' to confirm): ";
    getline(std::cin, input);
    return input == "yes";
}

void removeAll(string dir) 
{
    string msg = "Delete ALL things in " + dir + " EVRERYTHINGGG YOU CANT UNDO";

    if (!fs::exists(dir)) 
    {
        cout << "files not found at: " << dir << endl;
        return;
    }

    if (!confirm(msg)) 
    {
        cout << "Aborted" << endl;
        return;
    }

    fs::remove_all(dir);
    std::cout << "Deleted" << endl;
}

void copyInsides(string from, string to, string folder) 
{
    string msg = "Coping files inside " + from+folder + " to inside this folder" + to+folder;

    if (!fs::exists((from+folder)))
    {
        cout << "files not found at: " << from << endl;
        return;
    }

    if (!confirm(msg)) 
    {
        cout << "Aborted" << endl;
        return;
    }

    fs::copy(from+folder, to+folder);
    std::cout << "Copied" << endl;
}

void loadUSB(MusicLibrary ml, fs::path loc)
{

}