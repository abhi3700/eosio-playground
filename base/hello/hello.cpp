#include <eosio/eosio.hpp>
#include <string>
#include <eosio/asset.hpp>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;
using eosio::symbol;


class [[eosio::contract]] hello : public contract {
private:
	static constexpr symbol token_symbol = symbol("TOE", 4);
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

	ACTION getsymbol() {
		print(token_symbol.code().raw(), " | ");
		print(token_symbol.raw());
	}
};



// deprecated in eosio.cdt v1.7.0
// EOSIO_DISPATCH(hello, (hiany) (hiname))