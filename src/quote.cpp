#include "quote.h"
#include "log.h"
using namespace std;
#include <algorithm>
#include <float.h>

/* Sort functions for the bid and ask caches */
static const bool sort_by_price_desc(const Quote& q1, const Quote& q2)
{
	return q1.GetPrice() < q2.GetPrice();
}
static const bool sort_by_price_asc(const Quote& q1, const Quote& q2)
{
	return q1.GetPrice() > q2.GetPrice();
}

Quote::Quote(string bank, double price, uint64_t time , uint32_t volume, bool is_bid_or_ask) {
	m_bank = bank;
	m_price = price;
	m_time = time;
	m_volume = volume;
	m_is_bid_or_ask = is_bid_or_ask;
}

// Debugging
void Quote::dump(void) {
	cout << m_bank << "\t" << (m_is_bid_or_ask ? "BID\t" : "ASK\t") << m_time << "\t" << m_volume << "\t" << m_price << endl;
}

// Get an index for the bank matching 'bank' in a specific vector, or -1 if it wasn't found.
int Quotes::GetByName(string bank, vector<Quote> vect)
{
	std::vector<Quote>::iterator i;
	for( i = vect.begin(); i != vect.end(); ++i )
	{
		if( i->GetBank() == bank )
			return i - vect.begin();
	}
	return -1;
}

bool Quotes::AddQuote(string line) {
	// OPTIMIZE: reimplement using C++ native types for both performance and memory efficiency. 
	char *dup = NULL;
	char *token = NULL;

	string bank;
	double price;
	uint64_t time;
	uint32_t volume;

	dup = strdup(line.c_str());
	if (dup) {
		// The first field applies to both sections
		token = strtok(dup, ",");
		bank = token;

		// The bid
		token = strtok(NULL, ",");
		price = strtod(token, NULL);
		token = strtok(NULL, ",");
		time = strtoll(token, NULL, 10);
		token = strtok(NULL, ",");
		// delivery_counter
		token = strtok(NULL, ",");
		volume = strtol(token, NULL, 10);
		Quote bid(bank, price, time, volume, true);
#if 0
		bid.dump();
#endif
		m_history.push_back(bid);

		// Save a copy of the most recent bid for this bank (sorted by price)
		int stored_bid_idx = GetByName(bank, m_bids);
		if (stored_bid_idx != -1) {
			INFO("Found %s at %d", bank.c_str(), stored_bid_idx);
			if (price > DBL_EPSILON) {
				// TODO: what are 0 values supposed to represent? i'm assuming it means they're not selling, so we won't cache it, and will remove any existing offers
				m_bids[stored_bid_idx] = bid;
			} else {
				m_bids.erase(m_bids.begin() + stored_bid_idx);
			}
		} else  {
			INFO("Didn't find %s", bank.c_str());
			if (price > DBL_EPSILON) {
				m_bids.push_back(bid);
			}
		}
		sort(m_bids.begin(), m_bids.end(), sort_by_price_asc);
#if 0
		dumpBids();
#endif

		// The ask (using the same bank as before)
		token = strtok(NULL, ",");
		price = strtod(token, NULL);
		token = strtok(NULL, ",");
		time = strtoll(token, NULL, 10);
		token = strtok(NULL, ",");
		// delivery_counter
		token = strtok(NULL, ",");
		volume = strtol(token, NULL, 10);
		Quote ask(bank, price, time, volume, false);
#if 0
		ask.dump();
#endif
		m_history.push_back(ask);

		// Save a copy of the most recent ask for this bank (sorted by price)
		int stored_ask_idx = GetByName(bank, m_asks);
		if (stored_ask_idx != -1) {
			INFO("Found %s at %d", bank.c_str(), stored_ask_idx);
			if (price > DBL_EPSILON) {
				m_asks[stored_ask_idx] = ask;
			} else {
				m_asks.erase(m_asks.begin() + stored_ask_idx);
			}
		} else  {
			INFO("Didn't find %s", bank.c_str());
			if (price > DBL_EPSILON) {
				m_asks.push_back(ask);
			}
		}
		sort(m_asks.begin(), m_asks.end(), sort_by_price_desc);
#if 0
		dumpAsks();
#endif

		/* Run any analysis callbacks */
		for (vector<pQuotesCallback>::iterator iter = m_cb.begin(); iter != m_cb.end(); ++iter)
		{
			(*iter)(this);
		}

	}
	free(dup);
	return true;
}

// Register a function for analysis (real time)
bool Quotes::RegisterCallback(pQuotesCallback cb) {
	if (cb) {
		m_cb.push_back(cb);
		return true;
	}
	return false;
}

bool Quotes::DeregisterCallback(pQuotesCallback cb) {
	if (cb) {
		std::vector<pQuotesCallback>::iterator position = std::find(m_cb.begin(), m_cb.end(), cb);
		if (position != m_cb.end()) {
			m_cb.erase(position);
			return true;
		}
	}
	return false;
}

void Quotes::dumpAsks(void)
{
	for (vector<Quote>::iterator iter = m_asks.begin(); iter != m_asks.end(); ++iter)
	{
		iter->dump();
	}
}

void Quotes::dumpHistory(void)
{
	for (vector<Quote>::iterator iter = m_history.begin(); iter != m_history.end(); ++iter)
	{
		iter->dump();
	}
}

void Quotes::dumpBids(void)
{
	for (vector<Quote>::iterator iter = m_bids.begin(); iter != m_bids.end(); ++iter)
	{
		iter->dump();
	}
}

