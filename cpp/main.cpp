

#ifdef __INTELLISENSE__
#include <iostream>
#include <filesystem>
#else
import iostream;
import filesystem;
#endif
using namespace std;

int main() 
{
    try 
    {
        rename("from.txt", "to.txt");
    } 
    catch (filesystem::filesystem_error& e) 
    {
        cout << e.what() << '\n';
    }
    return 0;
}
