#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

void setPinInput(unsigned int name);    // Function to set up an input GPIO pin
void setPinOutput(unsigned int name);   // Function to set up an output GPIO pin
void runTest(int toTest);               // Function to test pins due to the lack of error messages from library

#endif
