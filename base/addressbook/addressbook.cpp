#include <eosio/eosio.hpp>
#include <string>
#include "abcounter.cpp"

using eosio::contract;
using eosio::print;
using eosio::multi_index;
using eosio::indexed_by;
using eosio::const_mem_fun;
using eosio::name;
using std::string;
using eosio::check;
using eosio::checksum256;
// using eosio::time_point_sec;
// using eosio::time_point_sec::operator;
using eosio::permission_level;
using eosio::action;

class [[eosio::contract]] addressbook : public contract
{
public:
	using contract::contract;

	[[eosio::action]]
	void upsert(
		name user, string first_name, string last_name, uint64_t age, string street, string city,
		string state ) {
		require_auth(user);

		// print("get_self(): ", get_self(), " | ");	// for debugging
		// print("get_first_receiver(): ", get_first_receiver(), " | ");	// for debugging
		// print("get_first_receiver() value: ", get_first_receiver().value, " |");	// for debugging

		address_index addresses(get_first_receiver(), get_first_receiver().value);
		auto it = addresses.find(user.value);

		if(it == addresses.end()) {
			addresses.emplace(user, [&](auto& row) {
				row.key = user;
				row.first_name = first_name;
				row.last_name = last_name;
				row.age = age;
				row.street = street;
				row.city = city;
				row.state = state;
			});

			send_summary(user, " successfully emplaced record to addressbook");
			increment_counter(user, "emplace");
		}
		else {
			// check whether either of the new data is different
			check((it->first_name != first_name) || (it->last_name != last_name) || (it->age != age) || (it->street != street) || (it->city != city) || (it->state != state), "At least one of all data must be different.");
			// print((it->first_name != first_name), " |");	// for debugging
			// print((it->last_name != last_name), " |");	// for debugging
			// print((it->age != age), " |");	// for debugging
			// print((it->street != street), " |");	// for debugging
			// print((it->city != city), " |");	// for debugging
			// print((it->state != state), " |");	// for debugging

			// Now, modify the new data
			string changes = "";
			addresses.modify(it, user, [&]( auto& row ) {

				if (row.first_name != first_name){				
					row.first_name = first_name;
					changes += "first name ";
				}				
				if(row.last_name != last_name) {
					row.last_name = last_name;
					changes += "last name ";
				}
				if(row.age != age) {
					row.age = age;
					changes += "age ";
				}
				if(row.street != street) {
					row.street = street;
					changes += "street ";
				}
				if(row.city != city) {
					row.city = city;
					changes += "city ";
				};
				if(row.state != state) {
					row.state = state;
					changes += "state ";
				}
			});
			if(!changes.empty()) {
				send_summary(user, " successfully modified record to addressbook. Fields changed: " + changes);
				increment_counter(user, "modify");
			} else {
				/*
					check((it->first_name != first_name) || (it->last_name != last_name) || (it->age != age) || (it->street != street) || (it->city != city) || (it->state != state), "At least one of all data must be different.");
				*/
				// NOTE: although this code line is not required, because there is already a check in the beginning of the modify like above:
				send_summary(user, " called upsert, but request resulted in no changes.");
			}
		}
	}


	[[eosio::action]]
	void erase(name user) {
		require_auth(user);

		address_index addresses(get_first_receiver(), get_first_receiver().value);
		auto it = addresses.find(user.value);
		check(it != addresses.end(), "Record doesn't exist!");
		addresses.erase(it);
		
		send_summary(user, " successfully erased record to addressbook");
		increment_counter(user, "erase");
	}

	template<typename T>
	void eraseall(T& table) {
	  auto itr = table.begin();
	  while(itr != table.end()) {
		itr = table.erase(itr);
	  }
	}

	ACTION deleteall() {
		require_auth(get_self());

		address_index addresses(get_self(), get_first_receiver().value);
		// auto it = addresses.begin();
		// while(it != addresses.end()) {
		//     addresses.erase(it);
		// }
		eraseall(addresses);
	}

// 	ACTION deleteallper(uint64_t pLimit, uint128_t pLastId){
// 		// block or it will run forever
// 		if(pLimit > 0){
// 			address_index addresses(get_self(), get_first_receiver().value);
// 			uint64_t count = 0;

// 			// iterate over first index 
// 			for(auto itr = addresses.begin(); itr != addresses.end() && count!=pLimit;) {
// 				// delete element and update iterator reference
// 				itr = addresses.erase(itr);
// 				count++;
// 			}

// /*			// iterate over second index 
// 			testIndex2 test2(get_self(), get_self()); // code, scope
// 			count = 0;
// 			for(auto itr = test2.begin(); itr != test2.end() && count!=pLimit;) {
// 				// delete element and update iterator reference
// 				itr = test2.erase(itr);
// 				count++;
// 			}
// */
// 			// are elements left in one of the indices?
// 			if(addresses.begin() != addresses.end()/* || test2.begin() != test2.end()*/){
// 					// build new transactions which will call the same function
// 					uint64_t time = time_point_sec::time_point_sec();
// 					checksum256 calc_hash; // fc::sha256
// 					uint128_t toHash, id2;


// 					toHash = ((uint128_t(get_self()) << 64) | uint128_t(time));
// 					// If not the first call use the pLastId to generate unique 
// 					if(pLastId != 0){
// 						toHash = toHash | pLastId;
// 					}

// 					// Build a Hash so the transaction ids get distinct
// 					sha256(reinterpret_cast<char *>(&toHash), 128, &calc_hash); 
// 					id2 = *reinterpret_cast<uint128_t *>(&calc_hash);

// 					// First Transaction with unhashed id and passed id as input
// 					transaction out;
// 					out.actions.emplace_back(permission_level{get_self(), N(active)}, get_self(), N(dtseq), std::make_tuple(pLimit, toHash));
// 					out.send(toHash, get_self());

// 					// Second Transction with hashed id and passed id as input
// 					transaction out2;

// 					out2.actions.emplace_back(permission_level{get_self(), N(active)}, get_self(), N(dtseq), std::make_tuple(pLimit, id2));
// 					out2.send(id2, get_self());
// 			}
// 		}
// 	}


	ACTION notify(name user, string msg) {
		require_auth(get_self());
		require_recipient(user);
	}

private:
	struct [[eosio::table("people")]] person
	{
		name key;
		string first_name;
		string last_name;
		uint64_t age;
		string street;
		string city;
		string state;

		uint64_t primary_key() const {return key.value;}
		uint64_t get_secondary_1() const { return age; }
	};

	using address_index = eosio::multi_index<"people"_n, person,
							indexed_by<"byage"_n, const_mem_fun<person, uint64_t, &person::get_secondary_1>>
							>;

	// Adding inline action to an action - "notify" in the same contract
	void send_summary(name user, string msg) {
		action(
			permission_level(get_self(), "active"_n), 
			get_self(),
			"notify"_n,
			std::make_tuple(user, name{user}.to_string() + msg)
			).send();
	}

	// Adding inline action to an action - "count" in the another contract - "abcounter"
	void increment_counter(name user, string type) {
		abcounter::count_action count("bhub1counter"_n, {get_self(), "active"_n});
		count.send(user, type);
	}
};
