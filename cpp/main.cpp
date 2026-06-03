// Source - https://stackoverflow.com/a/48614612
// Posted by Philipp Claßen, modified by community. See post 'Timeline' for change history
// Retrieved 2026-06-02, License - CC BY-SA 3.0

import <iostream>;
import <filesystem>;

int main() 
{
    try 
    {
        std::filesystem::rename("from.txt", "to.txt");
    } 
    catch (std::filesystem::filesystem_error& e) 
    {
        std::cout << e.what() << '\n';
    }
    return 0;
}
