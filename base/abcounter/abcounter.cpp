#include <eosio/eosio.hpp>
#include <string>

using eosio::contract;
using std::string;
using eosio::multi_index;
using eosio::name;
using eosio::same_payer;

class [[eosio::contract]] abcounter : public contract {
public:
	using contract::contract;

	[[eosio::action]] 
	void count ( name user, string type ) {
		require_auth("cabeos1test2"_n);

		counter_index countstable(get_first_receiver(), get_first_receiver().value);
		auto it = countstable.find(user.value);
		if (it == countstable.end()) {
			countstable.emplace("cabeos1test2"_n, [&] (auto& row) {
				row.key = user;
				row.emplaced = (type == "emplace") ? 1 : 0;
				row.modified = (type == "modify") ? 1 : 0;
				row.erased = (type == "erase") ? 1 : 0;

			});
		} else {
			countstable.modify(it, "cabeos1test2"_n, [&] (auto& row) {
				if(type == "emplace") { row.emplaced += 1; }
				if(type == "modify") { row.modified +=1 ; }
				if(type == "erase") { row.erased += 1; }
			});
		}
	}

	using count_action = eosio::action_wrapper<"count"_n, &abcounter::count>;

private:
	struct [[eosio::table]] counter {
		name key;
		uint64_t emplaced;
		uint64_t modified;
		uint64_t erased;

		auto primary_key() const { return key.value; }
	};

	using counter_index = multi_index<"counts"_n, counter>;

};