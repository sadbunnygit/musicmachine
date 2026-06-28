

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
        + to_string(a.downloadCount) + "','" 
        + a.lastDownloaded + ");"
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
    cout << "--- LOADING ALBUMS FROM " << loc << " START ---" <<endl;
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
    cout << "--- LOADED ALBUMS FROM " << loc << " END ---" <<endl;
}
void MusicLibrary::updateData()
{
	char* errMsg;

	string sql("UPDATE GRADES SET GRADE = 'A' WHERE LNAME = 'Cooper'"); // this obv wont work

	int rc = sqlite3_open(dbFile.c_str(), &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	rc = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errMsg);
	if (rc != SQLITE_OK) 
    {
		cerr << "\e[0;31m" << "Error in updateData function: " << errMsg << "\e[0m" <<endl;
		sqlite3_free(errMsg);
	}
	else
		cerr << "\e[0;32m" << "Records updated Successfully!" << endl;
}
void MusicLibrary::selectData()
{
	char* errMsg;

	string sql = "SELECT * FROM Albums;";

	int rc = sqlite3_open(dbFile.c_str(), &DB);
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	rc = sqlite3_exec(DB, sql.c_str(), callback, NULL, &errMsg);

	if (rc != SQLITE_OK) 
    {
		cerr << "\e[0;31m" "Error in selectData function: " << errMsg << "\e[0m" <<endl;
		sqlite3_free(errMsg);
	}
	else
		cerr << "\e[0;32m"  << "Records selected Successfully!" << "\e[0m" <<endl;
}
vector<Album> MusicLibrary::selectLeastDownloaded() // want to return vector<album>
{
	char* errMsg;

	string sql = "SELECT path, title, artist, size_mb, download_count,last_downloaded FROM Albums WHERE download_count == 0 LIMIT 10;"; // instead of limit 10 should be until size exceeds max
    
	int rc = sqlite3_open(dbFile.c_str(), &DB);
    vector<Album> albums;   // Stores the albums returned by the query

    // Pass a pointer to the vector so the callback can add Album objects to it.
    
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	rc = sqlite3_exec(DB, sql.c_str(), callback2, &albums, &errMsg);

	if (rc != SQLITE_OK) 
    {
		cerr << "\e[0;31m" "Error in selectData function: " << errMsg << "\e[0m" <<endl;
		sqlite3_free(errMsg);
	}
	else
		cerr << "\e[0;32m"  << "Records selected Successfully!" << "\e[0m" <<endl;

    return albums;
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
int MusicLibrary::callback2(void* data, int argc, char** argv, char** azColName)
{
    // Recover the vector<Album> that was passed to sqlite3_exec()
    auto* albums = static_cast<vector<Album>*>(data);

    // Create an Album from the current row and add it to the vector.
    // argv[i] contains the value of the ith selected column.
    for (int i = 0; i < argc; i++) 
    {
		// column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}

    albums->emplace_back(
        argv[0],           // path
        argv[1],           // title
        argv[2],           // artist
        stoi(argv[3]),     // size (convert string to int)
        stoi(argv[4]),     // download_count (convert string to int)
        argv[5]            // last_downloaded
    );

    // Returning 0 tells SQLite to continue processing rows.
    return 0;
}

// non-member operator overload
std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml ) 
{
    out << "dbFile: " << ml.dbFile;
    return out;
} // operator<<