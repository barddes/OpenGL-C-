#include "iostream"
#include "stdlib.h"
#include "sqlite3.h"
#include "sstream"

void create_world_db(sqlite3*& db);

void gen_world_chunk(sqlite3* db, int a, int b);

int main(){
	sqlite3* db;

	create_world_db(db);

	int n=-20,
		m=20;
	for(int i=n; i<=m; i++){
		for(int j=n; j<=m; j++){
			gen_world_chunk(db, i, j);
		}
	}

	sqlite3_close(db);
}

void create_world_db(sqlite3*& db){
	if(sqlite3_open("database.db", &db) != SQLITE_OK){
			std::cout << "Error: Unable to open or create database" << std::endl;
			exit(-1);
		}

		int status;

		status = sqlite3_exec(
			db,                                  /* An open database */
			"CREATE TABLE IF NOT EXISTS World( \
					`Chunk X` INTEGER NOT NULL, \
					`Chunk Y` INTEGER NOT NULL, \
					`x` INTEGER NOT NULL, \
					`y` INTEGER NOT NULL, \
					`z` INTEGER NOT NULL, \
					`ID` INTEGER NOT NULL, \
					`State` INTEGER, \
					PRIMARY KEY(`x`, `y`, `z`) \
			)",     /* SQL to be evaluated */
			NULL,  								 /* Callback function */
			NULL,                                /* 1st argument to callback */
			NULL                              	 /* Error msg written here */
		);

		if(status != SQLITE_OK){
			std::cout << "Algo de errado nao esta certo" << std::endl;
			exit(21);
		}
}

void gen_world_chunk(sqlite3* db, int a, int b){
	int x[16][16], y[16][16], z[16][16];

	std::string str;
	std::stringstream ss;

	ss << "INSERT INTO World VALUES ";
	for(int i=0; i<16; i++){
		for(int j=0; j<16; j++){
			x[i][j] = i+16*a;
			z[i][j] = j+16*b;
			y[i][j] = (x[i][j]*x[i][j] - z[i][j]*z[i][j])/500;

			ss << "(" << a << ", " << b << ", " << x[i][j] << ", " << y[i][j] << ", " << z[i][j] << ", 2, NULL)";

			if(i==15 && j==15) ss << ";";
			else ss << ",\n";
		}
	}					

	str = ss.str();
	int status;
	status = sqlite3_exec(
					db,
					str.c_str(),
					NULL,
					NULL,
					NULL
	);

	if(status != SQLITE_OK){
		std::cout << "Ops " << str << std::endl;
	}
	else{
		std::cout << "Chunk Added at ("<<a<<", "<<b<<")" << std::endl;
	}
}