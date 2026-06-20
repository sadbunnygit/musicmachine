

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

    //createDB
    int exit = sqlite3_open(dbFile.c_str(), &DB);
	sqlite3_close(DB);

    //createTable
    char* messageError;

    const char* sql =
        "CREATE TABLE IF NOT EXISTS albums ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "artist TEXT, "
        "path TEXT, "
        "song_count INTEGER, "
        "download_count INTEGER DEFAULT 0, "
        "last_downloaded TEXT, "
        "last_uploaded TEXT, "
        "UNIQUE(title, artist)"
        ");";


    try
	{
		int exitTB = 0;
		exitTB = sqlite3_open(dbFile.c_str(), &DB);
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exitTB = sqlite3_exec(DB, sql, NULL, 0, &messageError);
		if (exitTB != SQLITE_OK) 
        {
			cerr << "Error in createTable function." << endl;
			sqlite3_free(messageError);
		}
		else
			cout << "Table created Successfully" << endl;
		sqlite3_close(DB);
	}
	catch (const exception& e)
	{
		cerr << e.what();
	}
}


void MusicLibrary::addAlbum(const Album& a)
{
	cerr << endl;
    char* messageError;

    cerr << "Trying to add " << a << " into " << *this <<endl;
    string sql =
        "INSERT OR IGNORE INTO albums "
        "(title, artist, path, download_count, last_downloaded, last_uploaded) "
        "VALUES ('"
        + a.title + "','"
        + a.artist + "','"
        + a.path.string() + "',"
        + std::to_string(a.downloadCount) + ",'"
        + toSqlDateTime(a.lastDownloaded) + "','"
        + toSqlDateTime(a.lastUploaded) + "');";

    int exit = sqlite3_open(dbFile.c_str(), &DB);

	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) 
    {
		cerr << "\e[0;31m" << "Error in insertData function. :" << messageError << "\e[0m" << endl;
		sqlite3_free(messageError);
	}
	else
		cerr << "\e[0;32m" << "Records inserted Successfully!" << "\e[0m" << endl;
}
void MusicLibrary::loadAlbums(fs::path loc)
{
    vector<Album> a;
    try 
    {
        if (!fs::exists(loc)) 
        {
            cerr << "\e[0;31m" << "Files not found at: " << loc << "\e[0m" << endl;
            return;
        }

        for (const auto& entry : fs::directory_iterator(loc)) 
        {
            addAlbum(Album(entry.path())); 
        }
    } 
    catch (fs::filesystem_error& e) 
    {
        cerr << "\e[0;31m" << e.what() << "\e[0m" <<endl;
    }
}

static string toSQLdateTime(const std::chrono::system_clock::time_point tp)
{
    
}


// non-member operator overload
std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml ) 
{
    out << "dbFile: " << ml.dbFile;
    return out;
} // operator<<