

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;


void listFiles(string dir);
bool confirm(const string& message);
void removeAll(string dir);
void copy(string from, string to);

int main(int argc, char* argv[])
{
    string musicMachine = "/Volumes/NO NAME/music"; 
    string musicStore = "/Volumes/sadbunnymus"; 

    listFiles(musicMachine);

    removeAll("");
    copy("/Volumes/sadbunnymus/Music/St Elizabeth", "/Volumes/NO NAME/music/testfile/");
}


void listFiles(string dir)
{
    try 
    {
        if (!fs::exists(dir)) 
        {
            cout << "USB not found at: " << dir << endl;
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

void copy(string from, string to) 
{
    string msg = "Coping files inside " + from + "to inside this folderS" + to;

    if (!fs::exists(from)) 
    {
        cout << "files not found at: " << from << endl;
        return;
    }

    if (!confirm(msg)) 
    {
        cout << "Aborted" << endl;
        return;
    }

    fs::copy(from, to);
    std::cout << "Copied" << endl;
}