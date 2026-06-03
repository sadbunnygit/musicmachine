

#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
int main() 
{
    string musicMachine = "/Volumes/NO NAME/music"; 
    string musicStore = "/Volumes/sadbunnymus"; 

    try 
    {
        if (!fs::exists(musicStore)) 
        {
            cout << "USB not found at: " << musicStore << "\n";
            return 1;
        }

        cout << "Listing files in musicStore:\n";

        for (const auto& entry : fs::recursive_directory_iterator(musicStore)) 
        {
            cout << entry.path() << "\n";
        }
    } 
    catch (fs::filesystem_error& e) 
    {
        cout << e.what() << '\n';
    }
    return 0;
}
