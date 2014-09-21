#include "quote.h"
#include "log.h"
#include "arbitrage.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {

	INFO("Starting");

	// TODO: use getopt
	
	if (argc != 2) {
		ERROR("Please call %s <input_file_name>\n", argv[0]);
		exit(1);
	}

	INFO("Reading from %s\n", argv[1]);
	ifstream ifs(argv[1]);
	string line;

	Quotes quotes;
	int i=0;

	quotes.RegisterCallback(&CheckArbitrage);

	while(getline(ifs, line))
	{
		i++;
		if (false == quotes.AddQuote(line)) {
			WARNING("Error parsing line: %s", line.c_str());
		}
		/* Analysis is done inline */
	}

	INFO("Finished; parsed %d quotes", i);
	return 0;
}
