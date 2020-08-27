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
				// row.txn_vector.emplace_back(make_pair(ride_action.to_string(), get_trxid_str()));
				creatify_vector_pair(row.txn_vector, ride_action.to_string(), get_trxid());

			});
		} else {
			ridetable.modify(ridetable_it, get_self(), [&](auto& row) {
				row.ride_action = ride_action;
				// row.txn_vector.emplace_back(make_pair(ride_action.to_string(), get_trxid_str()));
				creatify_vector_pair(row.txn_vector, ride_action.to_string(), get_trxid());

			});
		}
	}

	ACTION del(const name& commuter) {
		require_auth(get_self());

		ridetable_index ridetable(get_self(), get_self().value);
		auto ridetable_it = ridetable.find(commuter.value);

		check(ridetable_it != ridetable.end(), "Commuter info exists in the table.");
		ridetable.erase(ridetable_it);

	}


	// NOTE: vector arg can't be const as emplace_back is non-const method
	inline void creatify_vector_pair( vector<pair<string, checksum256>>& v, const string& s, const checksum256& val ) {
		auto s_it = std::find_if(v.begin(), v.end(), [&](auto& vs){ return vs.first == s; });
		if(s_it != v.end()) {		// key found
			s_it->second = val;
		}
		else {						// key NOT found
			v.emplace_back(make_pair(s, val));
		}
	}
	
private:
	TABLE ridetable {
		name commuter;
		name ride_action;
		// vector<pair_t> txn_vector;
		vector<pair<string, checksum256>> txn_vector;

		auto primary_key() const { return commuter.value; }
	};

	using ridetable_index = multi_index<"ridetable"_n, ridetable>;
	// ----------------------------------------------------------------------------------
	inline checksum256 get_trxid()
	{
	  auto trxsize = transaction_size();
	  char trxbuf[trxsize];
	  uint32_t trxread = read_transaction( trxbuf, trxsize );
	  check( trxsize == trxread, "read_transaction failed");
	  return sha256(trxbuf, trxsize);
	}


};