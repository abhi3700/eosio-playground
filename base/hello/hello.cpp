#include <eosio/eosio.hpp>
#include <string>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;

class [[eosio::contract]] hello : public contract {
public:
	using contract::contract;

	[[eosio::action]]
	void hi(string a) {
		print("Hello, ", a);
	}
};

EOSIO_DISPATCH(hello, (hi))