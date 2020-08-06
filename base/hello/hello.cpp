#include <eosio/eosio.hpp>
#include <string>
#include <eosio/asset.hpp>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;
using eosio::symbol;
using eosio::datastream;
using eosio::asset;



CONTRACT hello : public contract {
private:
	const symbol token_symbol;
public:
	using contract::contract;

	hello(name receiver, name code, datastream<const char*> ds) : 
								contract(receiver, code, ds), 
								token_symbol("TOE", 4) {}

	ACTION hiany(string a) {
		print("Hello, ", a);
	}

	ACTION hiname(name user) {
		require_auth(user);
		print("Hello, your EOS name is, ", user);
	}

	ACTION getsymbol() {
		print(token_symbol.code().raw(), " | ");	// only symbol part 'TOE' encoded as integer.
		print(token_symbol.raw(), " | ");					// entire - symbol & precision, encoded as integer.
		print(token_symbol.code().to_string());		// TOE
	}

	ACTION compareasset(const asset& a1, const asset& a2) {
		if(a1 < a2) {
			print("a1 is less than a2");
		}
		else if (a1 > a2){
			print("a1 is more than a2");
		} else {
			print("a1 is equal to a2");
		}
	}
};



// deprecated in eosio.cdt v1.7.0
// EOSIO_DISPATCH(hello, (hiany) (hiname))