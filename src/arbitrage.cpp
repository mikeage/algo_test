#include "quote.h"
#include "log.h"
#include "arbitrage.h"

bool CheckArbitrage(Quotes * quotes)
{
	Quote * lowest_ask = quotes->GetLowestAsk();
	Quote * highest_bid = quotes->GetHighestBid();

	// TODO: identify multiple arbitrate opportunities (if we can buy from two banks and sell to one, etc)
	if (lowest_ask && highest_bid && lowest_ask->GetPrice() < highest_bid->GetPrice()) {
		uint64_t avail_time;
		uint32_t volume;
		if (lowest_ask->GetTime() >  highest_bid->GetTime()) {
			avail_time = lowest_ask->GetTime();
		} else { 
			avail_time = highest_bid->GetTime();
		}
		if (lowest_ask->GetVolume() < highest_bid->GetVolume()) {
			volume = lowest_ask->GetVolume();
		} else { 
			volume = highest_bid->GetVolume();
		}
		cout << avail_time << "," << lowest_ask->GetBank() << "," << highest_bid->GetBank() << endl;
		INFO("At %lld, buy %ld from %s at %f and sell to %s at %f", avail_time, volume, lowest_ask->GetBank().c_str(), lowest_ask->GetPrice(), highest_bid->GetBank().c_str(), highest_bid->GetPrice());
		return true;
	}
	return false;
}

bool CheckAllArbitrage(Quotes * quotes)
{
	bool found = false;
	vector<Quote> asks = quotes->GetAsks();
	vector<Quote> bids = quotes->GetBids();
	std::vector<Quote>::iterator ask;
	std::vector<Quote>::iterator bid;
	for( ask = asks.begin(); ask != asks.end(); ++ask )
	{
		for( bid = bids.begin(); bid != bids.end(); ++bid) {
			if (ask->GetPrice() < bid->GetPrice()) {
				uint64_t avail_time;
				uint32_t volume;
				if (ask->GetTime() >  bid->GetTime()) {
					avail_time = ask->GetTime();
				} else { 
					avail_time = bid->GetTime();
				}
				if (ask->GetVolume() < bid->GetVolume()) {
					volume = ask->GetVolume();
				} else { 
					volume = bid->GetVolume();
				}
				cout << avail_time << "," << ask->GetBank() << "," << bid->GetBank() << endl;
				INFO("At %lld, buy %ld from %s at %f and sell to %s at %f", avail_time, volume, ask->GetBank().c_str(), ask->GetPrice(), bid->GetBank().c_str(), bid->GetPrice());
				found = true;
			} else {
				break;
			}
		}
	}
	return found;
}
