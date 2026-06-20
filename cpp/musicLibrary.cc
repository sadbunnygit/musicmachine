

// sql stuff inspired and from : https://github.com/RobertoChapa/C-SQLite_Demo

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <sqlite3.h>

#include "musicLibrary.h"
#include "album.h"


using namespace std;
namespace fs = std::filesystem;


MusicLibrary::MusicLibrary(const string dbFile) : DB(nullptr), dbFile(dbFile)
{
    int rc = sqlite3_open(dbFile.c_str(), &DB); // rc meaning return code
    if (rc != SQLITE_OK)
    {
        cerr << "\e[0;31m" <<"Cannot open DB: " << sqlite3_errmsg(DB)  << "\e[0m" << endl;
        sqlite3_close(DB);
        DB = nullptr;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS Albums("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "artist TEXT, "
        "path TEXT UNIQUE NOT NULL, "
        "size_mb INTEGER NOT NULL, "
        "download_count INTEGER DEFAULT 0, "
        "last_downloaded TEXT"
        ");";

    char* errMsg = nullptr;
    rc = sqlite3_exec(DB, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        std::cerr << "\e[0;31m" << "Table creation failed: " << errMsg  << "\e[0m" << std::endl;
        sqlite3_free(errMsg);
    }
}
MusicLibrary::~MusicLibrary()
{
    if (DB)
    {
        sqlite3_close(DB);
        DB = nullptr;
    }
}


void MusicLibrary::addAlbum(const Album& a)
{
	cerr << endl;
    char* errMsg;

    cerr << "Trying to add " << a << " into " << *this <<endl;
    string sql =
        "INSERT OR IGNORE INTO Albums "
        "(title, artist, path, size_mb, download_count, last_downloaded) "
        "VALUES ('"
        + a.title + "','"
        + a.artist + "','"
        + a.path.string() + "','"
        + to_string(a.sizeMB) + "','"
        + to_string(a.downloadCount) + "', 'placeholder');"
        ;

    int rc = sqlite3_open(dbFile.c_str(), &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	rc = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errMsg);
	if (rc != SQLITE_OK) 
    {
		cerr << "\e[0;31m" << "Error in addAlbum function: " << errMsg << "\e[0m" << endl;
		sqlite3_free(errMsg);
	}
	else
		cerr << "\e[0;32m" << "Album inserted Successfully!" << "\e[0m" << endl;
}
void MusicLibrary::loadAlbums(fs::path loc)
{
    try 
    {
        if (!fs::exists(loc)) 
        {
            cerr << "\e[0;31m" << "Files not found at: " << loc << "\e[0m" << endl;
            return;
        }

        for (const auto& entry : fs::directory_iterator(loc)) 
        {
            auto name = entry.path().filename().string();
            if (name[0]=='.' && name[1]=='_')
                continue;
            addAlbum(Album(entry.path())); 
        }
    } 
    catch (fs::filesystem_error& e) 
    {
        cerr << "\e[0;31m" << e.what() << "\e[0m" <<endl;
    }
}

int MusicLibrary::selectData()
{
	char* errMsg;

	string sql = "SELECT * FROM Albums;";

	int rc = sqlite3_open(dbFile.c_str(), &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	rc = sqlite3_exec(DB, sql.c_str(), callback, NULL, &errMsg);

	if (rc != SQLITE_OK) 
    {
		cerr << "Error in selectData function." << endl;
		sqlite3_free(errMsg);
	}
	else
		cout << "Records selected Successfully!" << endl;

	return 0;
}
// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
int MusicLibrary::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) 
    {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

	cout << endl;

	return 0;
}

// non-member operator overload
std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml ) 
{
    out << "dbFile: " << ml.dbFile;
    return out;
} // operator<<