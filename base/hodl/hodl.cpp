#include <eosio/eosio.hpp>

using eosio::contract;
using eosio::check;
using std::string;
using eosio::symbol;
using eosio::multi_index;
using eosio::asset;
using eosio::same_payer;

class [[eosio::contract]] hodl : public contract
{
private:
	static const uint32_t the_party = 1645568542;	// UTC timestamp for "Tuesday, February 22, 2022 10:22:22 PM"
	const symbol hodl_symbol;
public:
	using contract::contract;

	hodl(name receiver, name code, datastream<const char*> ds) : contract(code, receiver, ds), hodl_symbol("SYS", 4) {}

	[[eosio::on_notify("eosio.token::transfer")]]
	void deposit(const name& hodler, const name& to, const asset& quantity, const string& memo) {
		if(hodler == get_self() || to != get_self()) {
			print("These are not the droids you are looking for.");
			return;
		}

		// check for the conditions
		check(now() < the_party, "you are way late");
		check(quantity.amount > 0, "when pigs fly!");
		check(quantity.symbol() == hodl_symbol, "These are not the droids you are looking for.");

		hodl_index hodl_table(get_self(), hodler.value);	// scope: person holding money
		auto hodl_it = hodl_table.find(hodl_symbol.raw());

		if(hodl_it == hodl_table.end()) {
			hodl_table.emplace(hodler, [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			hodl_table.modify(hodl_it, same_payer, [&](auto& row) {
				row.funds += quantity;
			});
		}


	}

	inline uint32_t now() const {
		return current_time_point().sec_since_epoch();
	}

private:
	TABLE hodl
	{
		asset funds;

		auto primary_key() const { return funds.symbol.raw(); }
	};

	using hodl_index = multi_index<"hodl"_n, hodl>;
};