#include "router.h"

using std::getline;

int base_router::Init()
{
	cout << "This is a defination of initialization function" << endl;
	return 0;
}

unsigned int ConvertIPToInt(string ip)
{
	string strTemp;
	unsigned int IPTemp;

	std::istringstream ipStream(ip);
	unsigned int resultIP = 0;

	for (int i = 0; i < 4; i++)
	{
		getline(ipStream, strTemp, '.') >> IPTemp;
		// TO-DO
			// Stream error check

		resultIP += IPTemp << ((4 - i - 1) * 8);
	}

	return resultIP;
}

