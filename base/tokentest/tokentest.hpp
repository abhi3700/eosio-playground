#include <eosio/eosio.hpp>

using eosio::contract;
using eosio::multi_index;
using eosio::

class [[eosio::contract]] tokentest : public contract {
public:
	using contract::contract;

private:
	struct [[eosio::table]] currency_stats
	{
		asset supply;
		asset maximum_supply;
		name issuer;

		auto primary_key() const { return supply.symbol.code().raw(); }
	};

	struct [[eosio::table]] account {
		asset balance;

		auto primary_key() const { return balance.value; }
	}

	using stats_index = multi_index< "stats"_n, currency_stats >;
	using account_index = multi_index< "accounts", account >;
};