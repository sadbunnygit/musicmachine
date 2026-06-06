

#include <iostream>
#include <filesystem>
#include <string>

#include "musicLibrary.cpp"

using namespace std;
namespace fs = std::filesystem;


void listFiles(string dir);
void listFilesRecur(string dir);
bool confirm(const string& message);
void removeAll(string dir);
void copyInsides(string from, string to, string folder);

int main(int argc, char* argv[])
{
    fs::path musicMachine = "/Volumes/NO NAME/music"; 
    fs::path musicStore = "/Volumes/sadbunnymus/Music"; 

    cout << "testing music library constructor" << endl;
    MusicLibrary mlib = MusicLibrary(musicStore);
    mlib.printAlbums();
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

