#include <eosio/eosio.hpp>
#include <eosio/print.hpp>
#include <eosio/system.hpp>
#include <eosio/asset.hpp>

// using namespace eosio;
using eosio::contract;
using eosio::name;
using eosio::check;
using eosio::print;
using eosio::symbol;
using eosio::multi_index;
using eosio::asset;
using eosio::same_payer;
using eosio::permission_level;
using eosio::datastream;
using eosio::current_time_point;
using eosio::action;

using std::string;

class [[eosio::contract]] hodl : public contract
{
private:
	// static const uint32_t the_party = 1645568542;	// UTC timestamp for "Tuesday, February 22, 2022 10:22:22 PM"
	static const uint32_t the_party = 1592829600;	// for withdrawal testing purpose. UTC timestamp for "06/22/2020 @ 12:40pm (UTC)"

	const symbol hodl_symbol;

public:
	using contract::contract;

	hodl(name receiver, name code, datastream<const char*> ds) : contract(code, receiver, ds), hodl_symbol("EOS", 4) {}

	[[eosio::on_notify("eosio.token::transfer")]]
	void deposit(const name& hodler, const name& to, const asset& quantity, const string& memo) {
		if(hodler == get_self() || to != get_self()) {
			print("These are not the droids you are looking for.");
			return;
		}

		// check for the conditions
		check(now() < the_party, "you are way late");
		check(quantity.amount > 0, "when pigs fly!");
		check(quantity.symbol == hodl_symbol, "These are not the droids you are looking for.");

		balance_index balance_table(get_self(), hodler.value);	// scope: person holding money
		auto hodl_it = balance_table.find(hodl_symbol.raw());

		if(hodl_it == balance_table.end()) {
			balance_table.emplace(hodler, [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			balance_table.modify(hodl_it, same_payer, [&](auto& row) {
				row.funds += quantity;
			});
		}


	}

	[[eosio::action]]
	void party(name hodler) {
		require_auth(hodler);

		// check the current time has passed the party time
		check(now() > the_party, "Hold your horses.");

		balance_index balance_table(get_self(), hodler.value);

		auto hodl_it = balance_table.find(hodl_symbol.raw());

		// Make sure the holder is in the table
		check(hodl_it != balance_table.end(), "You are not allowed to party.");

		action(
			permission_level{get_self(), "active"_n},		// permission of `hodl` account i.e. active permission of "bhub1111hodl" is used here.
			"eosio.token"_n,					// `code` of the callee action ("transfer") deployed: since the action called is in another contract - `eosio.token`
			"transfer"_n,
			std::make_tuple(get_self(), hodler, hodl_it->funds, std::string("Party! Your hodl is free."))
		).send();

		balance_table.erase(hodl_it);

	}

	inline uint32_t now() const {
		return current_time_point().sec_since_epoch();
	}

private:
	TABLE balance
	{
		asset funds;

		auto primary_key() const { return funds.symbol.raw(); }
	};

	using balance_index = multi_index<"balance"_n, balance>;
};