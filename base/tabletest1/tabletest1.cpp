#include <eosio/eosio.hpp>

using eosio::name;
using eosio::print;
using eosio::multi_index;
using std::string;

class [[eosio::contract("bhubtabtes11")]] tabletest1 : public contract {
public:
	using contract::contract;

	// create & modify
	[[eosio::action]]
	void creatify( name person_ac, string first_name, string last_name, string state ) {
		require_auth(person_ac);
		address_index addresses_db(person_ac, ) 

	}

private:

	[[eosio::table]]
	struct person {
		name person_ac;
		string first_name;
		string last_name;
		string state;

		auto primary_key() const { return person_ac.value; }
		auto first_name
	};

	// eosio name of the multi_index is "people". Link it with the struct data row structure
	using address_index = multi_index< "people"_n, person>;

}