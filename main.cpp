#include <iostream>
#include "cmdline.h"

using std::cout, std::endl;
using std::string;

int main(int argc, char* argv[])
{
	cmdline::parser cmdParser;
	cmdParser.add<string>("benchmark", 'b', "Running the benchmark, according to the preset file \"list.dat\"(default).", false, "list.dat");
	cmdParser.add("debug", 'd', "Run router in debug mode.");
	cmdParser.footer("<rule file> <data file>");

	// std::cout << cmdParser.rest()[0] << std::endl;

	cmdParser.parse_check(argc, argv);

	cout << cmdParser.exist("debug") << endl;

	if (cmdParser.exist("debug"))
	{
		cout << "DEBUG: arguments received:\n"
			 << "benchmark arguments: " << cmdParser.get<string>("benchmark") << "\n"
			 << "debug status: " << cmdParser.exist("debug") << "\n"

			 << "rest arguments: " << "\n"
			 << endl;

			for (auto i : cmdParser.rest())
			{
				cout << i << endl;
			}
	}

	// std::cout << "Hello, world!\n";

	return 0;
}
