#include <iostream>
#include <fstream>
#include <ctime>
#include "router.h"
#include "cmdline.h"



void ParserCommand(int argc, char* argv[]);

using std::cout, std::endl;
using std::string;

bool DEBUG_STATUS = false;
bool INFO_STATUS = true;
cmdline::parser cmdParser;

int main(int argc, char* argv[])
{
	ParserCommand(argc, argv);

	// Router should receive following parameters
		// ruleFile
		// dataFile
		// algorithmName

	hicuts_router router;

	// If benchmark mode on
		// Parse the list file.
		// Updata outputfile name every time read a file.

	// Initialize router
		// Build the router tree
	router.Init();
	router.Match();

	// Show the info & Exit program
		// Destroy the router properly
	if (INFO_STATUS)
	{
		cout.precision(3);
		cout << "INFO || Exiting the router, show info now..." << "\n"
			 << "---------------------" << "\n"
			 << "Time: " << router.time() << "\n"
			 << "Rule: " << router.rulenum() << "\n"
			 << "Memory: " << router.memory() / 1000.0 << "KB" << "\n"
			 ;
			
		cout << endl;
	}
	return 0;
}


void ParserCommand(int argc, char* argv[])
{
	// Define command arguments
	cmdParser.add<string>("open", 'o', "Output File\t - assign an output file <list file> (overwrite existed file).", false, "ans");
	cmdParser.add<string>("benchmark", 'b', "Benchmark Mode\t - run router as the assigned <list file>.", false, "list.dat");
	cmdParser.add("debug", 'd', "Debug Mode\t\t - run router in debug mode.");
	cmdParser.add("info", 'i', "Show info\t\t - show info, including time and memory info.");
	cmdParser.footer("<rule file> <data file>");

	cmdParser.parse_check(argc, argv);


	// INFO_STATUS = cmdParser.exist("info") ? true : false;
	// if (cmdParser.exist("debug"))
	// {
	// 	DEBUG_STATUS = true;
	// 	INFO_STATUS = true;
	// }

	// Arguments debug info
	if (DEBUG_STATUS)
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


void Exit(void)
{
	// Do some cleaning
	
	return;
}