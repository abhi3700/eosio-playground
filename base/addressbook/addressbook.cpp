#include <eosio/eosio.hpp>
#include <string>

using eosio::contract;
using eosio::print;
using eosio::multi_index;
using eosio::name;
using std::string;
using eosio::check;

class [[eosio::contract]] addressbook : public contract
{
public:
	using contract::contract;

	[[eosio::action]]
	void upsert(
		name user, string first_name, string last_name, string street, string city,
		string state ) {
		require_auth(user);


		print("get_code(): ", get_code(), " | ");	// for debugging
		print("get_self(): ", get_self(), " | ");	// for debugging
		print("get_first_receiver(): ", get_first_receiver(), " | ");	// for debugging
		print("get_first_receiver() value: ", get_first_receiver().value, " |");	// for debugging

		address_index addresses(get_self(), get_first_receiver().value);
		auto it = addresses.find(user.value);

		if(it == addresses.end()) {
			addresses.emplace(user, [&](auto& row) {
				row.key = user;
				row.first_name = first_name;
				row.last_name = last_name;
				row.street = street;
				row.city = city;
				row.state = state;
			});
		}
		else {
			addresses.modify(it, user, [&]( auto& row ) {
				row.key = user;
				row.first_name = first_name;
				row.last_name = last_name;
				row.street = street;
				row.city = city;
				row.state = state;
			});
		}
	}


	[[eosio::action]]
	void erase(name user) {
		require_auth(user);

		address_index addresses(get_self(), get_first_receiver().value);
		auto it = addresses.find(user.value);
		check(it != addresses.end(), "Record doesn't exist!");
		addresses.erase(it);
	}

private:
	struct [[eosio::table]] person
	{
		name key;
		string first_name;
		string last_name;
		string street;
		string city;
		string state;

		uint64_t primary_key() const {return key.value;}
	};

	using address_index = multi_index<"people"_n, person>;


	
};
