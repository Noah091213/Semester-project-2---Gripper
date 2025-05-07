//1. Install sqlite3 & developement library: 
	//Linux terminal: "sudo apt install sqlite3"; "sudo apt install libsqlite3-dev" (most likely not needed)
	//Windows: Download from the official page, the link and instructions is in the devlog. (most likely not needed)
	//Raspberry pi terminal: "sudo apt-get update"; "sudo apt-get install sqlite3 libsqlite3-dev" (most likely needed)

//2. Add a database (.db file) to the project in the terminal: "sqlite3 gripperdata.db". Enter ".exit" to exit the database again before continuing with the next step.

//4. This header file needs to be included:
#include <sqlite3.h>
#include <iostream>

//5. Global pointer to an sqlite3 database object:
sqlite3 *gripperDatabase;

//6. Order of execution of the functions:
	//1. openDatabase 
	//2. createTable()
	//3. insertData()
	//4. displayData()
	//5. closeDatabase()
	
//7. Compilation with cmake: Example of a CMakeLists.txt file that can handle a sqlite3 db on raspberry pi.
	//cmake_minimum_required(VERSION 3.5)
	//project(ProjectTest LANGUAGES CXX)
	//set(CMAKE_CXX_STANDARD 17)
	//set(CMAKE_CXX_STANDARD_REQUIRED ON)
	//include_directories(/usr/include)
	//link_directories(/usr/lib)
	//target_link_libraries(ProjectTest sqlite3)
	//add_executable(ProjectTest databaseFunctions.cpp sqlite3.c) 	

//Internal function to display the data. Used internally in displayTable.
int displayData(void *placeholder, int totalColumns, char **values, char **columnName)
{
	//For loop for all columns of the table:
	for(int i = 0; i < totalColumns; ++i)
	{
		//Printing the values in the columns.
		if(values[i])
		{
			std::cout << columnName[i] << ": " << values[i] << "| ";
		}
		
		//Printing no data if it is empty.
		else
		{
			std::cout << columnName[i] << ": No Data!| ";
		}
	}
	std::cout << std::endl;
	return 0;
}

//Opens the database.
void openDatabase()
{	
	//Attempts to open the database. "sqlite3_open()" returns 0 when successful and other values when not successful.
	int error = sqlite3_open("gripperdata.db", &gripperDatabase);
	
	//When the database cannot be opened an error gets printed.
	if(error)
	{
		std::cerr << "Failed to open database!" << sqlite3_errmsg(gripperDatabase) << std::endl;
	}
}

//Creates a table if it does not already exist.
void createTable()
{
	//Sends the command to make a table to the database. "sqlite3_exec()" returns 0 when successful and other values when not successful.
	//"GripNumber" is the primary key (has to be unique) and it will automatically insert the data. So it will not be used in the insertData() function.
	const char *makeNewTable = "CREATE TABLE IF NOT EXISTS gripperdata (GripNumber INTEGER PRIMARY KEY, Succesfull INTEGER);";
    	
    	//Error Message pointer.
    	char *errorMessage = 0;
    	
    	int error = sqlite3_exec(gripperDatabase, makeNewTable, nullptr, nullptr, &errorMessage);
    	
	if(error)
	{
		//Printing the error message and clearing the memory.
		std::cerr << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
}

//Inserts data into table.
void insertData(bool succesfullGrip)
{
	//Sends the command to insert values to the database. "sqlite3_exec()" returns 0 when successful and other values when not successful.
	const char *insertSuccessulfulGrip = "INSERT INTO gripperdata (Succesfull) VALUES (1);"; //Succesful grip enters 1 into the succesfullGrip column.
	const char *insertFailedGrip = "INSERT INTO gripperdata (Succesfull) VALUES (0);"; //Failed grip enters 0 into the succesfullGrip column.
    
    	int error;
    	
    	//Error Message pointer.
    	char *errorMessage = 0;
    	
    	//Entering a successful grip.
    	if(succesfullGrip)
    	{
    		error = sqlite3_exec(gripperDatabase, insertSuccessulfulGrip, nullptr, nullptr, &errorMessage);
	}
	
	//Entering a failed grip.
	else
	{
    		error = sqlite3_exec(gripperDatabase, insertFailedGrip, nullptr, nullptr, &errorMessage);
	}
	
	if(error)
	{
		//Printing the error message and clearing the memory.
		std::cerr << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
}

//Displayes the table.
void displayTable()
{
	//Sends the command to display the table to the database. "sqlite3_exec()" returns 0 when successful and other values when not successful.
	const char *getTable = "SELECT * FROM gripperdata;";
    	
    	//Error Message pointer.
    	char *errorMessage = 0;
    	
        int error = sqlite3_exec(gripperDatabase, getTable, displayData, 0, &errorMessage);
	
	if(error)
	{
		///Printing the error message and clearing the memory.
		std::cerr << errorMessage << std::endl;
		sqlite3_free(errorMessage);
	}
}

//Closes the database.
void closeDatabase()
{
    	sqlite3_close(gripperDatabase);
}

int main()
{
	//Testing the functions:
	bool test;
	openDatabase();

	test = true;
	createTable();
	insertData(test);
	
	test = false;
	createTable();
	insertData(test);
	
	displayTable();
	closeDatabase();
	
	return 0;
}
