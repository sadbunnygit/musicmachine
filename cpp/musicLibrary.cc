

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


MusicLibrary::MusicLibrary(const char* dir) : DB(nullptr)
{

    //createDB
    int exit = 0;
	exit = sqlite3_open(dir, &DB);
	sqlite3_close(DB);

    //createTable
    char* messageError;

    const char* sql =
        "CREATE TABLE IF NOT EXISTS albums ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "artist TEXT NOT NULL, "
        "path TEXT, "
        "year INTEGER"
        ");";


    try
	{
		int exitTB = 0;
		exitTB = sqlite3_open(dir, &DB);
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
    char* messageError;

    string sql =
        "INSERT INTO albums (title, artist, path, year) VALUES ('" 
        +
            a.title + "','" + a.artist + "','" + (a.path).string() + "'"
        + ");";

    sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, nullptr);

    int exit = sqlite3_open(dir, &DB);

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