

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


MusicLibrary::MusicLibrary(const string dir) : DB(nullptr), dir(dir)
{

    //createDB
    int exit = 0;
	exit = sqlite3_open(dir.c_str(), &DB);
	sqlite3_close(DB);

    //createTable
    char* messageError;

    const char* sql =
        "CREATE TABLE IF NOT EXISTS albums ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "artist TEXT, "
        "path TEXT"
        ");";


    try
	{
		int exitTB = 0;
		exitTB = sqlite3_open(dir.c_str(), &DB);
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
    cout << "ADD ALBUM CALLED" << endl;
    char* messageError;

    cout << "trying to add " << a << " into " << *this <<endl;
    string sql =
        "INSERT INTO albums (title, artist, path) VALUES ('" 
        +
            a.title + "','" + a.artist + "','" + (a.path).string() + "'"
        + ");";


    int exit = sqlite3_open(dir.c_str(), &DB);

	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) 
    {
		cerr << "Error in insertData function." << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Records inserted Successfully!" << endl;
}

// non-member operator overload
std::ostream & operator<<( std::ostream & out, const MusicLibrary & ml ) 
{
    out << "Dir: " << ml.dir;
    return out;
} // operator<<