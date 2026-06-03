

#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
int main() 
{
    string usbPath = "/Volumes/NO NAME/music"; 

    try 
    {
        if (!fs::exists(usbPath)) 
        {
            cout << "USB not found at: " << usbPath << "\n";
            return 1;
        }

        cout << "Listing files in USB:\n";

        for (const auto& entry : fs::recursive_directory_iterator(usbPath)) 
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
