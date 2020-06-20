## Compiler
* Using `eosio-cpp`: `$ eosio-cpp -I=/usr/local/include -I=/usr/include/c++/7.5.0 -l=/usr/local/lib/libhl++.a otp.cpp -o otp.wasm`
	- Here, 2 paths have been given with `-I` flag
	- & `-l` flag is used to link with a library file.
	- For more, see this: `$ eosio-cpp -help`  


## Contract
* `CONTRACT` is equal to `class [[eosio::contract]]`


## Action
* `ACTION` is equal to `[[eosio::action]] void`  
* limit an action to the contract creator only: use `require_auth( get_self() );` inside an action function.
* For every action, please do monitor the __"ram payer"__ & __"the permission authority"__ for executing the action.
	- __ram_payer__ is defined inside the multi-index table var i.e. e.g. 
	- __permission authority__ is defined at `require_auth()`.

## Table
* `TABLE` is equal to `struct [[eosio::table]]`  


## Multi-index
* [How to Guide](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/index/)
* max. no. of columns: `uint32_t` i.e. 4 billion (approx.).
* primary index: mandatory to define.
* secondary index type: optional (max 16).
* secondary index data_types: `uint64_t`, `uint128_t`, `uint256_t`, `double` or `long double`.
* [ ] the table can't be updated, unless all the data is removed
* Each row is a struct which has different fields. So, __row__ --> `struct`
	- this can be found using `get` method like this:
```cpp
accounts accountstable(token_contract_account, owner.value);
const auto& ac = accountstable.get(sym_code.raw());	// get that row which contains the symbol
return ac.balance;							// now, return member i.e. 'supply' of struct 'st'
```

* In `addressbook` example, this code line - `using address_index = multi_index<"people"_n, person>;` indicates: 
	- Here, "__people__" is the name (with EOSIO name type i.e. 12 chars a-z1-5) of the table that will be used while showing table data using this: `$ cleos get table cabeos1test2 cabeos1test2 people`
	- & __person__ is the name of the struct defined to indicate a single row data structure.
* When declared inside action, `address_index addressestable()` indicates
	- `address_index` --> typedef 
	- `addressestable` --> variable name
* Real-world use cases:
	- [ ] Zomato App multi-index table
		+ a restaurant can have orders:
			- from different customers &
			- by different valets. 
		+ a valet can have orders: 
			- from different customers, 
			- to different restaurants
		+ a customer can have multiple orders:
			- to different restaurants
			- by different valets. 

> NOTE: 

> - Basically, it is not one to one like in Cab industry (driver <--> commuter)

> - With a restaurant name, many rows can be found in RAM table

> - With a customer name, many rows can be found in RAM table

> - With a valet name, many rows can be found in RAM table
