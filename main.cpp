#include <iostream>
#include <ctime>
#include "router.h"
#include "cmdline.h"

using std::cout, std::endl;
using std::string;

extern bool isDebug;

int main(int argc, char* argv[])
{
	// Define command arguments
	cmdline::parser cmdParser;
	cmdParser.add<string>("benchmark", 'b', "Running the benchmark as the assigned preset file", false);
	cmdParser.add("debug", 'd', "Run router in debug mode.");
	cmdParser.footer("<rule file> <data file>");

	cmdParser.parse_check(argc, argv);
	
	isDebug = cmdParser.exist("debug") ? true : false;

	// Arguments debug info
	if (isDebug)
	{
		cout << "DEBUG: arguments received:\n"
			 << "Benchmark status: \t" << cmdParser.exist("benchmark") << "\n"
			 << "Benchmark argument: \t" << cmdParser.get<string>("benchmark") << "\n"
			 << "Debug status: \t\t" << cmdParser.exist("debug") << "\n"

			 << "---------------------" << "\n"
			 << "Rest arguments:"
			 << endl;

			for (auto i : cmdParser.rest())
			{
				cout << i << "\n";
			}

			cout << "---------------------" << endl;
	}

	// Initialize router

	return 0;
}
