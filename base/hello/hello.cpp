#include <eosio/eosio.hpp>
#include <string>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;

class [[eosio::contract]] hello : public contract {
public:
	using contract::contract;

	[[eosio::action("hiany")]]
	void hi_any(string a) {
		print("Hello, ", a);
	}

	[[eosio::action("hiname")]]
	void hi_name(name user) {
		require_auth(user);
		print("Hello, your EOS name is, ", user);
	}
};



// deprecated in eosio.cdt v1.7.0
// EOSIO_DISPATCH(hello, (hiany) (hiname))