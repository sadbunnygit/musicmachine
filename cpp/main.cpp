// Source - https://stackoverflow.com/a/48614612
// Posted by Philipp Claßen, modified by community. See post 'Timeline' for change history
// Retrieved 2026-06-02, License - CC BY-SA 3.0

#ifndef __INTELLISENSE__
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
        scout << e.what() << '\n';
    }
    return 0;
}
