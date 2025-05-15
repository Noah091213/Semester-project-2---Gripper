#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

void setPinInput(unsigned int name);    // Function to set up an input GPIO pin
void setPinOutput(unsigned int name);   // Function to set up an output GPIO pin
void runTest(int toTest);               // Function to test pins due to the lack of error messages from library

//Database functions:
int displayData(void *placeholder, int totalColumns, char **values, char **columnName); //Internal function to display the data. Used internally in displayTable.
void openDatabase();                                                                    //Opens the database.
void createTable();                                                                     //Creates a table if it does not already exist.
void insertData(bool succesfullGrip)                                                    //Inserts data into table.
void displayTable();                                                                    //Displayes the table.
void closeDatabase();                                                                   //Closes the database.

#endif
