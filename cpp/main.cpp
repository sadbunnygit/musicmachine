

#include <iostream>
#include <filesystem>
using namespace std;

int main() 
{
    try 
    {
        rename("from.txt", "to.txt");
        cout << "trying" << endl;
    } 
    catch (filesystem::filesystem_error& e) 
    {
        cout << e.what() << '\n';
    }
    return 0;
}
