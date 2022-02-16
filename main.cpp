#include <iostream>
#include <fstream>
#include <ctime>
#include "router.h"
#include "cmdline.h"

void ParserCommand(int argc, char* argv[]);

using std::cout, std::endl;
using std::string;

bool isDebug;
cmdline::parser cmdParser;

int main(int argc, char* argv[])
{
	ParserCommand(argc, argv);
	
	// Router should receive following parameters
		// ruleFile
		// dataFile
		// algorithmName

	base_router router;

	// If benchmark mode on
		// Parse the list file.

	// Initialize router
		// Build the router tree
	
	router.Init();
	router.BuildTree();
	router.Match();

	// Read the dataset

	// Destroy the router properly


	// Show the info & Exit program
	if (cmdParser.exist("info") || cmdParser.exist("debug"))
	{
		cout << "INFO || Exiting the router, show info now..." << "\n"
			 << "Time: " << router.time() << "\n"
			 << "Memory: " << router.memory() << "\n"
			 ;
			
		cout << endl;
	}
	return 0;
}


void ParserCommand(int argc, char* argv[])
{
	// Define command arguments
	cmdParser.add<string>("benchmark", 'b', "Benchmark Mode\t - run router as the assigned <list file>.", false, "list.dat");
	cmdParser.add("debug", 'd', "Debug Mode\t\t - run router in debug mode.");
	cmdParser.add("info", 'i', "Show info\t\t - show info, including time and memory info.");
	cmdParser.footer("<rule file> <data file>");

	cmdParser.parse_check(argc, argv);
	
	// Write to a global variable
	// May UNuseless?? consider del it!
	isDebug = cmdParser.exist("debug") ? true : false;

	// Arguments debug info
	if (isDebug)
	{
		cout << "DEBUG || Received arguments\n"
			 << "Benchmark status: \t" << cmdParser.exist("benchmark") << "\n"
			 << "Benchmark argument: \t" << cmdParser.get<string>("benchmark") << "\n"
			 << "Debug status: \t\t" << cmdParser.exist("debug") << "\n"

			 << "---------------------" << "\n"
			 << "Rest arguments:" << "\n"
			 ;

			for (auto i : cmdParser.rest())
			{
				cout << i << "\n";
			}

			cout << "---------------------";
			cout << endl;
	}
}
