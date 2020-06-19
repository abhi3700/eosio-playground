#include <eosio/eosio.hpp>
#include <string>

using std::string;
using eosio::contract;
using eosio::print;

class [[eosio::contract]] valset : public contract
{
public:
	using contract::contract;

	[[eosio::action]]
	void putval(int num, string str) {
		print("The num is ", num, " & the string is ", str);
	}	
};

EOSIO_DISPATCH(valset, (putval))