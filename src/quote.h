#ifndef QUOTE_H
#define QUOTE_H

using namespace std;
#include <stdint.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include <string.h>

class Quote {
	private:
		string m_bank;
		double m_price;
		uint64_t m_time;
		uint32_t m_volume;
		bool m_is_bid_or_ask;
	public:
		Quote(string, double , uint64_t, uint32_t, bool);
		void dump(void);
		double GetPrice(void) const { return m_price; };
		string GetBank(void) const { return m_bank; };
		uint32_t GetVolume(void) const { return m_volume; };
		uint64_t GetTime(void) const { return m_time; };
};

typedef bool (*pQuotesCallback)(class Quotes *);

class Quotes {
	private:
		vector<pQuotesCallback> m_cb;
		// OPTIMIZE: is the use of vectors efficient?	
		// OPTIMIZE: this should be an array of pointers, not objects, but I'm not 100% sure how to do that...
		vector<Quote> m_history; 
		// Cache a copy of the current, valid, orders
		vector<Quote> m_asks;
		vector<Quote> m_bids;
	public:
		bool AddQuote(string line);
		int GetByName(string bank, vector<Quote> vect); //OPTIMIZE: there's no way this can be good, even if it works. There must be a better way to return a pointer or something to the element to update
		Quote * GetLowestAsk(void) {return &m_asks[0]; }; //TODO: we might not need this. More precisely, we might need all open asks
		Quote * GetHighestBid(void) {return &m_bids[0]; };
		vector<Quote> GetAsks(void) {return m_asks; };
		vector<Quote> GetBids(void) {return m_bids; };
		bool RegisterCallback(pQuotesCallback cb);
		bool DeregisterCallback(pQuotesCallback cb);
		// Debugging only
		void dumpAsks(void);
		void dumpBids(void);
		void dumpHistory(void);
};

#endif /* QUOTE_H */

