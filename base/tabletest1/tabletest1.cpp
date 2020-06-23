#include <eosio/eosio.hpp>

using eosio::contract;
using eosio::name;
using eosio::print;
using eosio::multi_index;
using eosio::check;
using std::string;


class [[eosio::contract]] tabletest1 : public contract {
public:
	using contract::contract;

	// create & modify
	[[eosio::action]]
	void creatify( name person_ac, string first_name, string last_name, string state ) {
		require_auth(person_ac);
		address_index addresses_db(get_self(), get_first_receiver().value); 

		auto it = addresses_db.find(person_ac.value);

		if(it == addresses_db.end()) {
			addresses_db.emplace(person_ac, [&](auto& row) {
				row.person_ac = person_ac;
				row.first_name = first_name;
				row.last_name = last_name;
				row.state = state;
			});
		}
		else {
			// check if the data is same
			check((it-> first_name != first_name) && (it-> last_name != last_name) && (it-> state != state), "Sorry! All info same as stored");

			// modify the table
			addresses_db.modify(it, person_ac, [&](auto& row) {
				row.person_ac = person_ac;
				row.first_name = first_name;
				row.last_name = last_name;
				row.state = state;

			});
		}

	}

	// erase
	[[eosio::action]]
	void erase(name person_ac) {
		require_auth(person_ac);

		address_index addressesdb(get_self(), get_first_receiver().value);

		auto it = addressesdb.find(person_ac.value);
		check(it != addressesdb.end(), "Record doesn't exist");
		// erase the table
		addressesdb.erase(it);
	}


private:

	struct [[eosio::table]] person {
		name person_ac;
		string first_name;
		string last_name;
		string state;

		auto primary_key() const { return person_ac.value; }
		// auto secondary_key() const {}
	};

	// eosio name of the multi_index is "people". Link it with the struct data row structure
	using address_index = multi_index< "people"_n, person>;

};