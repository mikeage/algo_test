#include "quote.h"
#include "log.h"
#include "arbitrage.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(void) {

	INFO("Starting");

	ifstream ifs("quotes_for_test.txt");
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
