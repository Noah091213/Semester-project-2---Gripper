#include <pigpio.h>
#include <iostream>


// Check if pigpio errors occur, must be used because runtime errors have no checks in library
void runTest(int toTest) {
    if (toTest == PI_INIT_FAILED) {
        std::cout << "ERROR" << toTest << std::endl;
    } else {
        std::cout << "Pin passed test" << std::endl;
    }
}

// Define a pin as input
void setPinInput(unsigned int name) {
    int gpioTest = 0;
    gpioTest = gpioSetMode(name, PI_INPUT);
    runTest(gpioTest);  // Checking if the pin was set up correctly
}

// Define a pin as output
void setPinOutput(unsigned int name) {
    int gpioTest = 0;
    gpioTest = gpioSetMode(name, PI_OUTPUT);
    runTest(gpioTest);  // Checking if the pin was set up correctly
}

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
	int error = sqlite3_open("../gripperdata.db", &gripperDatabase);
	
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


