#include <eosio/eosio.hpp>
#include <string>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>
#include <eosio/system.hpp>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;
using eosio::symbol;
using eosio::datastream;
using eosio::asset;
using eosio::check;
using eosio::checksum256;
using eosio::sha256;
using eosio::current_time_point;




CONTRACT hello : public contract {
private:
	const symbol token_symbol;
	const asset token_balance = asset(158000, symbol("TOE", 4));
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
			print("a1 is less than a2 by ", (a1 - a2).to_string());
		}
		else if (a1 > a2){
			print("a1 is more than a2 by ", (a1 - a2).to_string());
		} else {
			print("a1 is equal to a2");
		}
	}

	ACTION checklowbal( const asset& a1 ) {
		check(a1 < token_balance, "amount is greater than token_balance");
	}

	ACTION getsha25six(const name& commuter_ac ) {
		string data_str_cpp = commuter_ac.to_string() + std::to_string(now());
		const char * data_str_c = data_str_cpp.c_str(); 

		auto hash_digest = sha256(data_str_c, strlen(data_str_c));
		print("The C string, timestamp: ", data_str_c, " , ", now(), " | ");
		print("The hash digest is: ", hash_digest);
	}

private:
	// get the current timestamp
	inline uint32_t now() const {
		return current_time_point().sec_since_epoch();
	}
};



// deprecated in eosio.cdt v1.7.0
// EOSIO_DISPATCH(hello, (hiany) (hiname))