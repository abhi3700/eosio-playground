#include <eosio/eosio.hpp>
#include <string>
#include <eosio/asset.hpp>
#include <eosio/crypto.hpp>
#include <eosio/system.hpp>
#include <eosio/transaction.hpp>
#include <cmath>
#include <vector>

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
using eosio::transaction_size;
using eosio::read_transaction;
using std::pow;
using std::vector;




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
		print(token_symbol.code().raw(), " | ");			// only symbol part 'TOE' encoded as integer.
		print(token_symbol.raw(), " | ");					// entire - symbol & precision, encoded as integer.
		print(token_symbol.code().to_string(), " | ");		// TOE
		print(token_symbol.precision());					// 4
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

	ACTION assetcalc(const asset& a1) {
		auto new_asset = asset(0, symbol("DUMMY", 4));
		new_asset.amount = a1.amount *30;

		print("New asset: ", new_asset.to_string(), " | ");
		print("New asset amount: ", new_asset.amount);
	}

	ACTION assetmul(const asset& a1, const asset& rate) {
		auto new_asset = asset(0, symbol("DUMMY", 4));
		// new_asset.amount = a1.amount * rate.amount/10^(rate.symbol.precision());
		new_asset.amount = a1.amount * rate.amount/pow(10, rate.symbol.precision());

		print("New asset: ", new_asset.to_string(), " | ");
		print("New asset amount: ", new_asset.amount, " | ");
		print("rate precision: ", rate.symbol.precision());
	}

	ACTION getsha25six(const name& commuter_ac ) {
		string data_str_cpp = commuter_ac.to_string() + std::to_string(now());
		const char * data_str_c = data_str_cpp.c_str(); 

		auto hash_digest = sha256(data_str_c, strlen(data_str_c));
		print("The C string, timestamp: ", data_str_c, " , ", now(), " | ");
		print("The hash digest is: ", hash_digest);
	}

	ACTION hexstr(const string& s) {
		const char * data_str_c = s.c_str(); 

		auto hash_digest = sha256(data_str_c, strlen(data_str_c));

		print("checksum256 to string: ", s, " whose checksum is: ", to_hex(&hash_digest, sizeof(hash_digest)));
	}

	// ACTION extintfrmstr(const string& s) {
	// 	print(ext_int_string(s));
	// }

	ACTION gettxnid() {
		print("txn id is: ", get_trxid());
	}

	ACTION gengameid() {
		uint64_t game_id = 10000123456789 + (uint64_t)now();
		print(game_id);
	}

	ACTION genrandindex(const vector<name> v) {
		//cast the random_value to a smaller number
	    uint64_t max_value = v.size()-1;
	    uint64_t min_value = 1;

	    auto t = hash_digest_256(get_trxid(), now());	
	    auto byte_array = t.extract_as_byte_array();

	    uint64_t random_int = 0;
	    for (int i = 0; i < 8; i++) {
	        random_int <<= 8;
	        random_int |= (uint64_t)byte_array[i];
	    }
	    
	    uint64_t num1 = min_value + ( random_int % ( max_value - min_value + 1 ) );			// in range from `min` to `max` (including `min` & `max`)
	    print(num1);
	}

	ACTION genrandbin() {
	    auto t = hash_digest_256(get_trxid(), now());	
	    auto byte_array = t.extract_as_byte_array();

	    uint64_t random_int = 0;
	    for (int i = 0; i < 8; i++) {
	        random_int <<= 8;
	        random_int |= (uint64_t)byte_array[i];
	    }
	    
	    uint64_t num1 = random_int % 2;				// either 0 or 1
	    print(num1);
	}

private:
	// get the current timestamp
	inline uint32_t now() const {
		return current_time_point().sec_since_epoch();
	}

	template<typename CharT>
	static std::string to_hex(const CharT* d, uint32_t s) {
	  std::string r;
	  const char* to_hex="0123456789abcdef";
	  uint8_t* c = (uint8_t*)d;
	  for( uint32_t i = 0; i < s; ++i ) {
	    (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
	  }
	  return r;
	}

/*	// extract integers from string
	inline uint256_t ext_int_string(const string& s ) const {
	    // string input = "1ee5ad0d074cfffbaa1598f0d236c09537d9c28b3b85aff206e20398f5e032dd";//I added some more extra characters to prove my point.
	    string numbers = "0123456789";
	    std::size_t found = s.find_first_of(numbers.c_str());
	    string output_str = "";

	    while (found != string::npos) {
	        output_str += s[found];
	        found = s.find_first_of(numbers.c_str(), found+1);
	    }

	    // std::cout << output_str << "\n";
	    // std::cout << "length" << output_str.size() << "\n";
	    uint256_t output_int = = (uint256_t)output_str;
	    // std::cout << output_int << "\n";

	    return output_int;
	}
*/
	// get the sha256 hash digest/checksum from (txn_id, timestamp)
	inline checksum256 hash_digest_256(const checksum256& txn_id,
										uint32_t timestamp) const {
		string data_str_cpp = to_hex(&txn_id, sizeof(txn_id)) + std::to_string(timestamp);
		const char * data_str_c = data_str_cpp.c_str(); 

		auto hash_digest = sha256(data_str_c, strlen(data_str_c));

		return hash_digest;
	}

	inline checksum256 get_trxid()
	{
	  auto trxsize = transaction_size();
	  char trxbuf[trxsize];
	  uint32_t trxread = read_transaction( trxbuf, trxsize );
	  check( trxsize == trxread, "read_transaction failed");
	  return sha256(trxbuf, trxsize);
	}
};



// deprecated in eosio.cdt v1.7.0
// EOSIO_DISPATCH(hello, (hiany) (hiname))