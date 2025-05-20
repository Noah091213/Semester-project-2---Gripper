#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <sqlite3.h>
#include "Gripper.hpp"
#include "functions.hpp"

//Global pointer to an sqlite3 database object:
sqlite3 *gripperDatabase;

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

int main() // Main loop for the whole program
{
    //Opening the database
    openDatabase();
    
    // Initializing GPIO library, this makes the GPIO pins available, if the runTest does not return a success, GPIO pins will not work
    std::cout << "Initializing GPIO library" << std::endl;
    int test = gpioInitialise();    // This is done in main because multiple parts of the program need this initialized, thus it wouldnt work together with starting other pins
    runTest(test);

    int currentCase = 1;        // Int used to control state machine for testing
    int userInput   = 0;        // Input for calling commands for testing, only call ints

    Gripper mainGripper(12, 13, 26, 0, 1);  // Creating an instance of the gripper class, the first 2 numbers are back and forward, 3rd pin is diable and the last 2 are for buttons

    mainGripper.pinInit();      // Method does all the necessary setup for the pins to make sure they work

    while (true) {              // Main work loop
        switch(currentCase) {   // currentCase is used to call the methods of the gripper from terminal, will change to modbus commands

            case 1: // Default case

                std::cout << "Case 1\n" << std::endl;   // Print for debugging and to show where in the code the program currently is
                
                // Sets all the pins to default
                mainGripper.setOffPinState(1);
                mainGripper.setForwardPinState(0);
                mainGripper.setBackwardPinState(0);

                std::cout << " Type 1 to close gripper \n Type 2 to open gripper \n Type 3 to get the current status \n " << std::endl;
                std::cin >> userInput;  // Takes userinput and sets the next case/command to call

                if (userInput == 1) {       // Calls command to close the gripper
                    currentCase = 2;

                } else if (userInput == 2) {// Calls command to open gripper
                    currentCase = 3;

                } else if (userInput == 3) { 
                    currentCase = 4;

                } else {
                    std::cout << "Please enter a valid option.\n\n" << std::endl;   // If input does not match an option, this will catch it and not throw an error
                }

                break;

            case 2: // Close gripper case

                mainGripper.closeGripper(); // Call closeGripper on the gripper
                currentCase = 1;
                break;

            case 3: // Open gripper case

                mainGripper.openGripper();  // Call openGripper on the gripper
                currentCase = 1;            // Resets the 
                break;

            case 4: // Get the current state of the grippers success
                
                if (mainGripper.wasSuccesfulGrip() == 1) {  // Calls the method on the gripper to see if it is holding something. If the gripper closed and did not reach 170 steps, it must be holding something, because the button stopped it and not the max steps
                    std::cout << "The gripper is holding something" << std::endl;
                    //Inserting succesful grip into the database
                    bool succesfulGrip = true;
                    createTable();
	                insertData(succesfulGrip);
                    displayTable(); //Showing the table in the terminal.
                } else {
                    std::cout << "The gripper is not holding something" << std::endl;
                    //Inserting failed grip into the database
                    bool succesfulGrip = false;
                    createTable();
	                insertData(succesfulGrip);
                    displayTable(); //Showing the table in the terminal.
                }
                
                currentCase = 1;
                break;
        }
    }
    //Closing the database
    closeDatabase();
    return 0;
}
