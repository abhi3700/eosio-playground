#include <eosio/eosio.hpp>
#include <string>

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
using eosio::same_payer;

CONTRACT people : public contract {
public:
	using contract::contract;

	ACTION upsert(
		const name& user, 
		const string& firstname, 
		const string& lastname, 
		const name& job,
		const string& employee_id,
		const name& country 
		) {
		require_auth(user);

		// print("get_self(): ", get_self(), " | ");	// for debugging
		// print("get_first_receiver(): ", get_first_receiver(), " | ");	// for debugging
		// print("get_first_receiver() value: ", get_first_receiver().value, " |");	// for debugging

		people_index people_table(get_self(), get_self().value);
		auto it = people_table.find(user.value);

		if(it == people_table.end()) {
			people_table.emplace(user, [&](auto& row) {
				row.user = user;
				row.firstname = firstname;
				row.lastname = lastname;
				row.job = job;
				row.employee_id = employee_id;
				row.country = country;
			});

		}
		else {
			// check whether either of the new data is different
			check((it->firstname != firstname) || (it->lastname != lastname) || (it->job != job) 
				|| (it->employee_id != employee_id) || (it->country != country), "At least one of all data must be different.");
			// print((it->first_name != first_name), " |");	// for debugging
			// print((it->last_name != last_name), " |");	// for debugging
			// print((it->age != age), " |");	// for debugging
			// print((it->street != street), " |");	// for debugging
			// print((it->city != city), " |");	// for debugging
			// print((it->state != state), " |");	// for debugging

			// Now, modify the new data
			people_table.modify(it, user, [&](auto& row) {
				row.firstname = firstname;
				row.lastname = lastname;
				row.job = job;
				row.employee_id = employee_id;
				row.country = country;
			});
		}
	}



	ACTION erase(const name& user) {
		require_auth(user);

		people_index people_table(get_self(), get_self().value);
		auto it = people_table.find(user.value);
		check(it != people_table.end(), "Record doesn't exist!");
		people_table.erase(it);		
	}


	// Read `addressbook` table
	ACTION readjobcntry(const name& job, const name& country) {
		require_auth(get_self());

		people_index people_table(get_self(), get_self().value);
		auto job_idx = people_table.get_index<"byjobcountry"_n>();
		auto job_country_id = combine_ids(job.value, country.value);
		auto it = job_idx.find(job_country_id);

		check(it != job_idx.end(), "the table row doesn't exist for the parsed job, country");		// M-1

		auto size = std::distance(job_idx.cbegin(), job_idx.cend());
		print("table's size: ", size, " | ");

		auto job_country_it = job_idx.lower_bound(combine_ids(job.value, country.value));
		// auto job_country_it = job_idx.upper_bound(combine_ids(job.value, country.value));
		check(job_country_it != job_idx.end(), "there is no row found for the parsed job, country");		// M-2

		print("it found person\'s firstname, lastname: ", it->firstname, ", ", it->lastname ," | ");							// M-1
		print("found person\'s firstname, lastname: ", job_country_it->firstname, ", ", job_country_it->lastname ," | ");		// M-2


		// M-1: print all the rows as per priority
		// while(it != job_idx.end()) {
		// 	print("The row is: ", it->user, ",", it->firstname, ",", it->lastname, ",", it->job, ",", it->employee_id, ",", it->country, " | ");
		// 	++it;
		// }

		// M-2: print those rows with "engineer" & "india" values only
		while((it != job_idx.end()) && (it->job == job) && (it->country == country)) {			// prints only those rows
		// while((it != job_idx.end())/* && (it->job == job) && (it->country == country)*/) {			// prints all 
			print("The row is: ", it->user, ",", it->firstname, ",", it->lastname, ",", it->job, ",", it->employee_id, ",", it->country, " | ");
			++it;
		}

	}

private:
	TABLE person
	{
		name user;
		string firstname;
		string lastname;
		name job;
		string employee_id;
		name country;

		auto primary_key() const {return user.value;}
		uint128_t get_secondary_1_job_country() const { return combine_ids(job.value, country.value); }

	};

	using people_index = eosio::multi_index<"people"_n, person,
							indexed_by<"byjobcountry"_n, const_mem_fun<person, uint128_t, &person::get_secondary_1_job_country>>
							>;


	// concatenation of ids
	static uint128_t combine_ids(const uint64_t &x, const uint64_t &y) {
	    return (uint128_t{x} << 64) | y;
	}
};
