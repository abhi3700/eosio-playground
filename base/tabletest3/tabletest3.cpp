// #pragma once
#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>
#include <string>
// #include <eosio/asset>
#include <eosio/transaction.hpp>
#include <vector>
#include <algorithm>

using eosio::print;
using eosio::contract;
using eosio::name;
using eosio::checksum256;
using eosio::multi_index;
using eosio::check;
using eosio::sha256;
using eosio::transaction_size;
using eosio::read_transaction;


using std::string;
using std::vector;
using std::pair;

CONTRACT tabletest3 : public contract {
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
				row.txn_vector.emplace_back(make_pair(ride_action.to_string(), get_trxid()));

			});
		} else {
			ridetable.modify(ridetable_it, get_self(), [&](auto& row) {
				row.ride_action = ride_action;
				row.txn_vector.emplace_back(make_pair(ride_action.to_string(), get_trxid()));

			});
		}
	}

	ACTION readtable(const name& commuter, const string& search_key) {
		ridetable_index ridetable(get_self(), get_self().value);
		auto ridetable_it = ridetable.find(commuter.value);

		check(ridetable_it != ridetable.end(), "Commuter info exists in the table.");

		read_vector_pair(ridetable_it->txn_vector, search_key);
	}

	ACTION del(const name& commuter) {
		require_auth(get_self());

		ridetable_index ridetable(get_self(), get_self().value);
		auto ridetable_it = ridetable.find(commuter.value);

		check(ridetable_it != ridetable.end(), "Commuter info exists in the table.");
		ridetable.erase(ridetable_it);

	}


	inline void read_vector_pair( const vector<pair<string, checksum256>>& v, const string& s ) {
		auto s_it = std::find_if(v.begin(), v.end(), [&](auto& vs){ return vs.first == s; });

		if(s_it != v.end()) {			// key found
			print("The value(s): ");

			while(s_it != v.end()) {
				print(s_it->second, " | ");
				++s_it;
			}
		} else {						// key NOT found
			print("No item found with this key");
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
