#include "quote.h"

// Check for basic arbitage opportunities. It will print the most recent, highest value, arbitrage available. If the opportunity remains available, it will be printed on each subsequent invocation (can be filtered from the command line by passing through 'uniq')
bool CheckArbitrage(Quotes * quotes);
