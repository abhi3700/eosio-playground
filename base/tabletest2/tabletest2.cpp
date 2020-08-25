// #pragma once
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <string>
// #include <eosio/asset>
#include <eosio/transaction.hpp>
#include <vector>
#include <algorithm>
// #include <iterator>

using eosio::contract;
using eosio::name;
using eosio::checksum256;
using eosio::multi_index;
// using eosio::const_mem_fun;
// using eosio::indexed_by;
using eosio::check;
using eosio::sha256;
using eosio::transaction_size;
using eosio::read_transaction;


using std::string;
using std::vector;
using std::pair;
using pair_t = pair<string, vector<string>>;

CONTRACT tabletest2 : public contract {
public:
	using contract::contract;

	ACTION creatify(const name& commuter, name& ride_action) {
		require_auth(commuter);

		ridetable_index ridetable(get_self(), get_self().value);
		auto ridetable_it = ridetable.find(commuter.value);

		if(ridetable_it == ridetable.end()) {
			ridetable.emplace(get_self(), [&](auto& row) {
				row.commuter = commuter;
				row.ride_action = ride_action;
				creatify_vector_pair(row.txn_vector, ride_action.to_string(), get_trxid_str());

			});
		} else {
			ridetable.modify(ridetable_it, get_self(), [&](auto& row) {
				row.ride_action = ride_action;
				creatify_vector_pair(row.txn_vector, ride_action.to_string(), get_trxid_str());

			});
		}
	}

	// NOTE: vector arg can't be const as emplace_back is non-const method
	inline void creatify_vector_pair( vector<pair_t>& v, const string& s, const string& val ) {
		auto s_it = std::find_if(v.begin(), v.end(), [&](auto& vs){ return vs.first == s; });
		if(s_it != v.end()) {		// key found
			s_it->second.emplace_back(val);
		}
		else {						// key NOT found
			v.emplace_back(make_pair(s, vector<string>{val}));
		}
	}


private:
	TABLE ridetable {
		name commuter;
		name ride_action;
		vector<pair_t> txn_vector;

		auto primary_key() const { return commuter.value; }
	};

	using ridetable_index = multi_index<"ridetable"_n, ridetable>;
	// ----------------------------------------------------------------------------------
	inline string get_trxid_str() {
		auto trxsize = transaction_size();
		char trxbuf[trxsize];
		uint32_t trxread = read_transaction( trxbuf, trxsize );
		check( trxsize == trxread, "read_transaction failed");
		auto hash_digest = sha256(trxbuf, trxsize);
		return hex_to_str(&hash_digest, sizeof(hash_digest));
	}

	template<typename CharT>
	static string hex_to_str(const CharT* d, uint32_t s) {
	  std::string r;
	  const char* to_hex="0123456789abcdef";
	  uint8_t* c = (uint8_t*)d;
	  for( uint32_t i = 0; i < s; ++i ) {
	    (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
	  }
	  return r;
	}

};