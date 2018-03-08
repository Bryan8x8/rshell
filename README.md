# assignment3

IMPORTANT: I have no idea why but throughout the controller_.cpp I have placed random conditionals that literally do NOTHING but for somereason the code refuses to funtion without them, I spent 4 days trying to figure out what was wrong until I noticed by chance that only after the use of these conditionals does the code work. 

In this assignment, please finish two things:

1 In "CS100_Assignment1.pdf", finish setting up your “Assignment” github repo, and writing an epic for assignment 2.

2 Finish everything mentioned in "CS100_Assignment2.pdf".

rshell Summary:

IMPORTANT: to end rshell session type 'terminate' command.

the functionality of this rshell is split into four classes
	
	- Package
	- Packager
	- Executer
	- Controller

Package Class: This class is design to act as a container of user input. It contains within it two vectors, one for holding input commands, and another for holding connectors. 

Packager Class: This class is designed to take an input string and parse through it and packaing the string into a set of packages. the parsing process involves two stages, the initial parse splits the input by semicolons. The second pass takes an individual command split by the previous parse and places the present commands and connectors into seperate vectors within a package, and then adds that package to a vector of packages.

Executer Class: This class receives a vector of packages from the Packager class and performs a final parse and clean up of the commands prior to execution. This final parse is crucial as it will identify whether the user has passed the terminate shell function. This class is also resposible for executing the user commands and determining whether or not commands should be executed based on the connectors that were passed.

Controller: Big changes have been made to this class, it now dictates the flow of information and handles nearly all of the parsing, package has become obsolete as our rshell now handles vectors.

rShell.cpp: this file creates a container and continously loops its receiveAndRun function until it returns a true value.

Bugs:

	- echo '\n' will result in a space in rshell, while if I run this command in the terminal I receive a \n
