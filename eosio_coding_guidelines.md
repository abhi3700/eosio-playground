## Compiler
* Using `eosio-cpp`: `$ eosio-cpp -I=/usr/local/include -I=/usr/include/c++/7.5.0 -l=/usr/local/lib/libhl++.a otp.cpp -o otp.wasm`
	- Here, 2 paths have been given with `-I` flag
	- & `-l` flag is used to link with a library file.
	- For more, see this: `$ eosio-cpp -help`  

> NOTE: If only the sequence of actions in `*.cpp` contract code is altered, the `*.wasm` binary file changes.  

## Contract
* `CONTRACT` is equal to `class [[eosio::contract]]`
* “Pushing an action to a contract requires the authorization of at least one account. Further accounts and permissions can be required depending on contract complexity. An account can be made of a single, or many, individuals set up in a permission based configuration. Smart contracts can only be run by a single account, and a single account can only have a single smart contract. It is best practice to give both the account and contract the same (lowercase) name.” [Source](https://link.medium.com/1G4zitL6t7)
* Every EOSIO smart contract is set to a single EOSIO account. A contract is basically an object that other accounts can interact with. An account cannot have more than 1 contract. [Source](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* __Code v/s Receiver__
	- code is always the first receiver of the action, while receiver is the account currently executing the action. [Source](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)
	- By using code == receiver the dispatcher knows that this contract has been called by the action directly, while in the case of code != receiver the action was originally destined for another account, but this account has been notified about it. [Source](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)


### Understanding Token contract
* unique `issuer` [Source](https://medium.com/coinmonks/understanding-the-eosio-token-contract-87466b9fdca9)
* a token is of `asset type` i.e. 
* token --> "<number> <symbol>" e.g. "10000000.0000 EOS"
	- number: max (2^62-1), can go to 18 decimal.
	- symbol: 1-7 uppercase letters.



## Action
* `ACTION` is equal to `[[eosio::action]] void`  
* limit an action to the contract creator only: use `require_auth( get_self() );` inside an action function.
* For every action, please do monitor the __"ram payer"__ & __"the permission authority"__ for executing the action.
	- __ram_payer__ is defined inside the multi-index table var i.e. e.g. 
	- __permission authority__ is defined at `require_auth()`.
	- account, where the data gets stored. This account could be same as the permission authority or even ram_payer.
* types
	- External actions
	- Inline actions
		+ Type-1: action calls to another action within same contract
		+ Type-2: action of one contract calls to action of another contract.
* Actions can only be pushed if it's added in ABI. e.g. with [[eosio::on_notify]] attribute, doesn't add that function as action. Rather, that's a payable action mostly.
* Inline actions are the caller actions, but `on_notify` attributed functions are actually callee functions (utility) to update the table of contract called.
* `on_notify` function
	- `eosio.token::transfer` action is calling a helper function deposit to add the info (i.e. transferred money) to the contract (`hodl`)'s table.
  - `*::transfer` annotation means any contract with transfer ACTION can trigger this function of this contract
  - here, avoid using `eosio::check()`, because the `transfer` ACTION can fail & lead to no transfer of asset (token, card, etc.) to this contract ac. Instead use `if-else` logic like this:
```cpp
void tippertipper::deposit( const name& from_ac, 
                            const name& contract_ac, 
                            const asset& quantity,
                            const string& memo ) 
{
  ...
  ...
  // if there is no alphabets, just the telegram_id in memo.
  if(count_alpha(memo) == 0) {
    auto tg_id = memo;    // capture the telegram_id

    // instantiate the `account` table
    account_index account_table(get_self(), get_self().value);
    auto account_it = account_table.find(owner_id);

    // update (add/modify) the deposit_qty
    if(account_it == account_table.end()) {
      account_table.emplace(get_self(), [&](auto& row) {
        row.owner = tg_id;
        row.balances.emplace_back(
          make_pair("symbol_name", quantity.symbol.code()),
          make_pair("symbol_precision", quantity.symbol.precision()),
          make_pair("contract", get_first_receiver()),
          make_pair("value", quantity.amount)
        )
      });
    } else {
      account_table.modify(account_it, get_self(), [&](auto& row) {
        row.balances.emplace_back(
          make_pair("symbol_name", quantity.symbol.code()),
          make_pair("symbol_precision", quantity.symbol.precision()),
          make_pair("contract", get_first_receiver()),
          make_pair("value", quantity.amount)
        )
      });
    }

  }

```

## Transaction
* Deferred transaction are scheduled transaction & are deprecated now.
* [Is there a way for triggering an inline ACTION after sometime (say 180 secs) from within a contract's another ACTION?](https://t.me/c/1139062279/261193)
	- No, inline actions have to execute within the same transaction, and you only have 30ms for all [source](https://t.me/c/1139062279/261225)
	- But you can set a condition in a contract so that it allows executing a certain thing within a given period only [source](https://t.me/c/1139062279/261226)
	- Basically, you can apply a check condition like this:
```cpp
...
check(elapsed_time > 180, "the action is triggered before the exprity time i.e. 180 sec");
``` 

## Table
* `TABLE` is equal to `struct [[eosio::table]]`
* Get the size/length of multi-index table. NOTE: this method is applicable for few rows of multi-index table or else your action may time out scanning large tables.
```cpp
parkinfo_index parkinfo_table(get_self(), park_id);
auto size = std::distance(parkinfo_table.cbegin(),parkinfo_table.cend());
check(size > 0, "park id doesn\'t exist");
```
* The table data is sorted by default as per the primary key like this:
```console
$ cleoswt get table gpkbatescrow gbuser111111 cardwallet --show-payer
{
  "rows": [{
      "data": {
        "card_id": "100000000007690",
        "contract_ac": "simpleassets",
        "usage_status": "available"
      },
      "payer": "gpkbatescrow"
    },{
      "data": {
        "card_id": "100000000007693",
        "contract_ac": "simpleassets",
        "usage_status": "available"
      },
      "payer": "gpkbatescrow"
    },{
      "data": {
        "card_id": "100000000007709",
        "contract_ac": "simpleassets",
        "usage_status": "available"
      },
      "payer": "gpkbatescrow"
    }
  ],
  "more": false,
  "next_key": ""
}
```
	- Here, card_id is the primary key. So, the each row is sorted by card_id.
* 2 params
	- 1. `code`: specifies the owner of this table. 
		+ Here we use the `get_self()` function which will pass the name of this contract.
	- 2. `scope`: ensures the uniqueness of the table.
		+ Scopes were originally intended to separate table state in order to allow for parallel computation on the individual sub-tables. However, currently inter-blockchain communication has been prioritized over parallelism. Because of this, scopes are currently only used to logically separate the tables as in the case of eosio.token. [Source](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/data-persistence)
		+ In this case, since we only have one table we can use the value from `get_first_receiver()`. The value returned from the get_first_receiver function is the account name on which this contract is deployed to.
	- E.g. below to instantiate a table:
```cpp
address_index addresses(get_self(), get_first_receiver().value);
```
	- Also, based on the `code` & `scope` defined in the action for table, one can get the table data using `cleos` like this:
```console
$ cleost get table cabeos1test2 cabeos1test2 people --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "first_name": "abhijit",
        "last_name": "roy",
        "street": "r79, (top floor) \n Sec-74",
        "city": "Mohali",
        "state": "Punjab"
      },
      "payer": "cabeos1user1"
    },{
      "data": {
        "key": "cabeos1user2",
        "first_name": "ramesh",
        "last_name": "bhattacharya",
        "street": "2-lane park street",
        "city": "Kolkata",
        "state": "West Bengal"
      },
      "payer": "cabeos1user2"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* In EOSIO, we have multi-index table insprired from Boost Multi-index library. For more, look at the next section below.

### Using cleos
* fetch with (primary key, 0 limit)
```console
$ cleost get table tippertipper tipuser11111 fund --lower 1397703940 --limit 0
{
  "rows": [],
  "more": true,
  "next_key": "1397703940",
  "next_key_bytes": ""
}
```
* fetch with (primary key, 1 limit)
```console
$ cleost get table tippertipper tipuser11111 fund --lower 1397703940 --limit 1
{
  "rows": [{
      "token_id": 1397703940,
      "token_contract_ac": "eosio.token",
      "balance": "9.0000 EOS"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* fetch with (primary key, 1 limit, show payer)
```console
$ cleost get table tippertipper tipuser11111 fund --lower 1397703940 --limit 1 --show-payer
{
  "rows": [{
      "data": {
        "token_id": 1397703940,
        "token_contract_ac": "eosio.token",
        "balance": "9.0000 EOS"
      },
      "payer": "tippertipper"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* fetch with (secondary key, 1 limit)
```console
$ cleost get table tippertipper tipuser11111 fund --lower eosio.token --key-type name --index 2
{
  "rows": [{
      "token_id": 1397703940,
      "token_contract_ac": "eosio.token",
      "balance": "9.0000 EOS"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* fetch with (secondary key, 1 limit, show payer)
```console
$ cleost get table tippertipper tipuser11111 fund --lower eosio.token --key-type name --index 2 --show-payer
{
  "rows": [{
      "data": {
        "token_id": 1397703940,
        "token_contract_ac": "eosio.token",
        "balance": "9.0000 EOS"
      },
      "payer": "tippertipper"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```
* fetch with (secondary key, 1 limit)
```console
$ cleost get table tippertipper tipuser11111 fund --lower eosio.token --key-type name --index 2 --limit 1
{
  "rows": [{
      "token_id": 1397703940,
      "token_contract_ac": "eosio.token",
      "balance": "9.0000 EOS"
    }
  ],
  "more": true,
  "next_key": "14781000547611517456",
  "next_key_bytes": ""
}
```
* fetch with (secondary key, 1 limit, show payer)
```console
$ cleost get table tippertipper tipuser11111 fund --show-payer --lower eosio.token --key-type name --index 2 --limit 1
{
  "rows": [{
      "data": {
        "token_id": 1397703940,
        "token_contract_ac": "eosio.token",
        "balance": "9.0000 EOS"
      },
      "payer": "tippertipper"
    }
  ],
  "more": true,
  "next_key": "14781000547611517456",
  "next_key_bytes": ""
}
```
* fetch with (secondary key, show payer)
```console
$ cleost get table tippertipper tipuser11111 fund --show-payer --lower eosio.token --key-type name --index 2
{
  "rows": [{
      "data": {
        "token_id": 1397703940,
        "token_contract_ac": "eosio.token",
        "balance": "9.0000 EOS"
      },
      "payer": "tippertipper"
    },{
      "data": {
        "token_id": "21479244531320324",
        "token_contract_ac": "tokenfutbol1",
        "balance": "9.0000 FUTBOL"
      },
      "payer": "tippertipper"
    }
  ],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```

### Multi-index
* [How to Guide](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/index/)
* Each smart contract using multi index table reserves a partition of the RAM cache, which is controlled using table name, code and scope. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index tables provide a fast access to data storage and can be accessed by smart contract. Therefore, the Dapps are required to store application data in the Multi index Tables, and the blockchain records the transactions by interacting with the smart contact. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index Tables support using multiple indexes on the data. The primary index type must be unit64_t and must be unique, but the secondary indexes can have duplicates. If you want to index on a string you will need to convert this to an integer type and store the results in a field that you then index. Up to 16 indexes are allowed.
* max. no. of columns: `uint32_t` i.e. 4 billion (approx.). [Source](https://t.me/c/1139062279/226525)
* primary index: mandatory to define. & must be `uint64_t` & must be unique.
	- if `name` data type is defined as primary_index, then the get_func will return `n.value`
* secondary index type: optional (max 16) & can have duplicates like a valet in Zomato linked linked to multiple orders i.e. rows in table.
* Don't user `auto` as deduction-type for the get_function inside the struct table. But, one can use `auto` as deduction type in primary_key function.
```cpp
		auto primary_key() const { return commuter_ac.value; }
		uint64_t get_secondary_1() const { return driver_ac.value; }
		uint64_t get_secondary_2() const { return ride_status.value; }
```
* secondary index data_types: `uint64_t`, `uint128_t`, `uint256_t`, `double` or `long double`.

> NOTE: If you want to index on a `string` you will need to convert this to an `integer` type and store the results in a field that you then index. 

* [ ] the table can't be updated, unless all the data is removed.
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
* “According to the ‘eosio::multi_index’ definitions, `code` is the name of the account which has write permission and the `scope` is the account where the data gets stored.” [Source](https://link.medium.com/1G4zitL6t7)
* Steps to create a Multi-index table:
	- Struct
		+ Create a struct with name (as per EOSIO valid name)
		+ Name one of the getters as `primary_key()`
		+ If you choose to have a secondary index, then choose the getter for the field.
	- Create a type
		+ Use C++ `typedef`/`using` to define a type based on Multi Index Table Index, such as: tablename, the struct, additional indexes
	- Create Local Variables inside actions or functions
* Multi-index methods
	- `find`: for querying an entry via primary_index
```cpp
...
address_index addresses(get_self(), get_first_receiver().value);
auto it = addresses.find(user.value);
...
...
```
		+ for querying an entry via secondary index. Do same like primary key index:
```cpp
address_index addresses(get_self(), get_first_receiver().value);
age_idx = addresses.get_index<"byage"_n>;
auto it = age_idx.find(user.value);

```
		+ retrieving items, For retrieving a record by its primary key we simply run:
```cpp
auto itr = proposals.find(proposal_id)
```
		+ The iterator on itself can return the current object by object dereference or as object instance:
```cpp
print(eosioitr->property) // reference
print((*itr).property) // instance
Proposal proposal = *itr // get object instance
```
		+ Next & previous objects
```cpp
auto nextitr = itr++;
auto previtr = itr--;
```
	
		> NOTE: For me to understand a subject, it really helps for me to understand the underlying functionality, and it usually also reveals the simplicity of it. This is also the case with EOS, upon digging through code, the `.find()` method simply runs the `std::find_if` functionality that checks if the looped item has the correct primary key:
```cpp
ptr._item->primary_key() == input_primary
```

	- `emplace`: Create a record in the table. This method accepts 2 arguments: [Source](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/data-persistence)
		+ 1. the "payer" of the given record who pays the storage usage
		+ 2. callback function: the lambda function (to create a reference, i.e. capture all params by reference) which updates the field data in the particular row. This function is going to follow once it's predecessor job is done i.e. the payer RAM balance storage is deducted
		+ E.g. below:
```cpp
addresses.emplace(user, [&]( auto& row ) {
      row.key = user;
      row.first_name = first_name;
      row.last_name = last_name;
      row.street = street;
      row.city = city;
      row.state = state;
    });
``` 
	- `modify`: Update a record in the table. This method accepts 3 arguments: [Source](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/data-persistence)
		+ a. The iterator defined earlier, presently set to the user as declared when calling this action.
		+ b. The "payer", who will pay for the storage cost of this row, in this case, the user.
		+ c. The callback function that actually modifies the row.* Multi-index DB table storage: Take the [addressbook example](./base/addressbook/addressbook.cpp)
		+ E.g. below:
```cpp
addresses.modify(iterator, user, [&]( auto& row ) {
      row.key = user;
      row.first_name = first_name;
      row.last_name = last_name;
      row.street = street;
      row.city = city;
      row.state = state;
    });
```
		+ modify the table by secondary index. Basically, get the index via `get_index` & then add `find`, `modify` to it
```cpp
ACTION modifybyage(uint64_t age, const string& city) {
	address_index addresses(get_first_receiver(), get_first_receiver().value);
	auto age_idx = addresses.get_index<"byage"_n>();
	auto it = age_idx.find(age);

	check(it != age_idx.end(), "row with this age not found.");

	require_auth(it->key);			// Not needed necessarily, because anyway during modification, there has to be permission taken from the user.

	// modify
	age_idx.modify(it, same_payer, [&](auto& row){
		row.city = city;
	});

	send_summary(it->key, " successfully modified record to addressbook. Fields changed: " + city);
	increment_counter(it->key, "modify");
}
```
	- size of table
```cpp
people_index people_table(get_self(), get_self().value);
auto it = people_table.find(user.value);

check(it != people_table.end(), "Record doesn't exist!");

auto size = std::distance(people_table.cbegin(), people_table.cend());
print(size);
```
	- Case-1: [tabletest1](./base/tabletest1)
		+ action permission: user
```cpp
void create(name user, string first_name) {
	require_auth(user);
	...
	...
}
```
		+ action ram_payer: user

	- Case-2: [tabletest2](./base/tabletest2)
		+ action permission: user
		+ action ram_payer: contract ac


```console
$ cleost push action cabeos1test2 create '["cabeos1user1", "Abhijit"]' -p cabeos1test2
```

* ##### Create an action to delete all the Table data at once
	- __M-1:__ Mainly used (during development)
```cpp
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
```

		+ __NOTE:__ 
			- As mentioned by others, this will only work as long as the table contains a limited number of items as often during development. [Source](https://eosio.stackexchange.com/a/4995/167)
			- The fear is, that if the index is too large, the valid processing time will overrun and the action will get cancelled.
			- Problems: [Source](https://eosio.stackexchange.com/a/3857/167)

	- __M-2:__ Robust for any no. of rows. [Source](https://eosio.stackexchange.com/a/1432/167)

* ##### Whenever modify table is needed in series (sequentially), then always do it loops like this:
```cpp
			players_index players_table(get_self(), get_self().value);
			auto players_it = players_table.find(ongamestat_it->asset_contract_ac.value);

			check(players_it != players_table.end(), "players_list is not set.");

			// Now, erase p1, p2 from the `players` table's `players_list`
			std::vector<name> paired_players = {ongamestat_it->player_1, ongamestat_it->player_2};

			for(auto&& p : paired_players) {
				auto pl_search_it = std::find(players_it->players_list.begin(), players_it->players_list.end(), p);
				check(pl_search_it != players_it->players_list.end(), p.to_string() + " is not in the players_list.");
				players_table.modify(players_it, get_self(), [&](auto& row) {
					row.players_list.emplace_back(p);
					// send_alert(p, p.to_string() + " is erased from the players list");			// for debug
				});
			}

```

* Whenever, creating a table with having more than 1 party as users, then try not to use `same_payer` (or else, there will be confusion in finding, which party is the ram_payer) param inside `modify()` method of multi_index table.
* Applications:
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

* the list of possible key types
	- i64 (uint64_t)
	- i128 (uint128_t)
	- i256 (uint256_t)
	- float64 (double)
	- float128 (long double)
	- name (name)
	- sha256 (checksum256)
	- ripemd160 (checksum160)

* All possible combinations of Table params:
  - [ ] vector of maps like this: ```vector<map<string, string>> balances;```
  - [x] Map: 
    + [`map<extended_symbol, uint64_t> balances;` used in __eosio_tipuser_contracts__](https://github.com/abhi3700/eosio_tipuser_contracts)
  - [x] Vector
  - [x] Vector of pairs:
    + [`vector<pair<string, checksum256>> txn_vector;` used in __tabletest2__](./base/tabletest2)

## Account Permission
* Multisig

## Notification
* “A notification is a function to deliver success action to designated user once the action is successfully completed.” [Source](https://link.medium.com/flTeJNKdw7)
* When using inline action, you need to add permission ‘contract@eosio.code’, to user’s account. However, it’s not easy to apply to service because most of users are reluctant to add it to their own account. So notification function is used mainly in service instead of adding permission. [Source](https://link.medium.com/flTeJNKdw7)
	- Here, setting `eosio.code` permission to the contract account's active permission, so that the inline actions are sent from contract `addressbook` : [Source](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/adding-inline-actions/#step-1-adding-eosiocode-to-permissions)
```console
$ cleost set account permission cabeos1test2 active --add-code
executed transaction: 244cca344fc48d88fbed39b6a297e15e4c06ff5cacedbff15a36eb9325b9ef97  184 bytes  215 us
#         eosio <= eosio::updateauth            {"account":"cabeos1test2","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warn  2020-07-01T22:07:41.973 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```
* A notification is a function to deliver success action to designated user once the action is successfully completed.
	- E.g. - When actions are made within contracts or using external contracts, there is very helpful way of checking if its properly done or not is by getting notification. `eosio.token` is a good instance to understand how a transfer actions are made and how the notification is made.
* In `addressbook` example, adding the helper function `send_summary()` in private ensures safety, if the action (`notify()` here) is defined in the same contract.

## Coding syntax
### Data types
* `name` - [Source](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1name)
	- `name.value` - `uint64_t` part of `name`
* `asset` - [Source](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1asset)
	- e.g. "1000.0000 EOS"
	- `asset.symbol.raw()` - uint64_t part of `asset`
	- `asset.symbol` - `symbol` class type 
	- instantiate like this:
```cpp
int64_t fareamount_in_toe = (ride_it->fare_act)/375.00;		// convert 'INR' to 'TOE'
auto fare_toe = asset(fareamount_in_toe, symbol("TOE", 4));		// create a asset variable for converted fare (in TOE)

asset token_balance = asset(158000, symbol("TOE", 4));		// represents "15.8000 TOE"
```
	- get precision of asset: `current_price.symbol.precision()`

* `symbol`
	- initialize symbol like this:
```cpp
symbol sym{"TOE", 4};		// Ok or
symbol sym = symbol("TOE", 4);		// Ok
```
	- symbol encoded as integer. So, choose wisely during contracts.
```cpp
symbol sym = symbol("TOE", 4);

// only symbol part 'TOE'
sym.code()				// TOE

// only symbol part 'TOE' encoded as integer
sym.code().raw()	// 4542292

// both components - symbol & precision, encoded as integer
sym.raw() 				// 1162826756
```

### print [All](https://developers.eos.io/manuals/eosio.cdt/v1.7/best-practices/debugging_a_smart_contract/#print)
* `print`
```cpp
print("Name, ", nm);
```
	- The eosio.code authority is a pseudo authority implemented to:	[Source](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/adding-inline-actions/#step-1-adding-eosiocode-to-permissions)
		+ enhance security, and 
		+ enable contracts to execute inline actions.


* `print_f`:
```cpp
print_f("Name : %\n", nm);
```

### Contracts
* The "code" AKA "account where contract is deployed"
* `get_self()` - gives the contract account name
* `get_first_receiver()`
* code vs receiver [Source](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)
	- Self is where the action is executed, and first receiver is where the notification is originated [Source](https://t.me/c/1139062279/229432)
	- They are different in a notification context i.e. `[[eosio::on_notify("")]]` attributed function [Source](https://t.me/c/1139062279/229439)
	- it doesn't need to be a transfer. Contract A executes require_recipient(B), then B receives a notification that it can process somehow. Then in B's context, B will be self, and A will be the first receiver [Source](https://t.me/c/1139062279/229441)
	- "receiver" is the account that is currently processing the action. "code" is the account that authorized the contract.
		+ E.g. - to get the account of the caller within an action
		
### Permission
* `require_auth( account name )`
This action explains that the transfer function requires the authorization of the account holder from where the tokens are transferred.
* `require_recipient( account name )`
This action helps in getting notification to the account. This explains that the current action to be delivered to the account name.

## Debugging contracts
Basically, try to see the values of local variables defined in the action
* So, try to see the variables like this:
	- Here, in the console, the 3 vars output can be seen.
```cpp
		print("get_self(): ", get_self(), " | ");	// for debugging
		print("get_first_receiver(): ", get_first_receiver(), " | ");	// for debugging
		print("get_first_receiver() value: ", get_first_receiver().value, " |");	// for debugging
```

```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 71b204a40f008a24779a3f739af718a48299562b97837cc805be284f858ce319  152 bytes  257 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
>> get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```


## Troubleshooting
* See [these](https://developers.eos.io/manuals/eosio.cdt/v1.7/troubleshooting) on EOSIO developer portal.
* code assertion failure
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
Error 3050004: eosio_assert_code assertion failure
Error Details:
assertion failure with error code: 8000000000000000000
pending console output:
```
	- this means check for the this line
```cpp
class [[eosio::contract("cabeos1test2")]] addressbook : public contract
```
	- just remove this `("cabeos1test2")`, & you will see that, the output is in front of you like this:
```cpp
class [[eosio::contract]] addressbook : public contract
```
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: ceca02d079c4bb6709658ecf91f5a277f7e1019a464456a4093f150ae7929491  152 bytes  536 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
>> get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* message assertion failure
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: read
pending console output: get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
```
	- Please check for your table (if corrupted)
```console
$ cleost get table cabeos1test2 cabeos1test2 people
Error 3015013: Unpack data exception
Error Details:
Unable to unpack built-in type 'string' while processing 'person.street'
read datastream of length 56 over by -26
```
	- It looks like that the table is corrupted
	- So, try to go to the old struct (as defined previously) & erase all the data & confirm. [Source](https://medium.com/@cc32d9/modifying-data-structure-in-eos-contract-is-not-an-easy-thing-594f596c9995)
	- You can also add this C++ code as an action to delete all at once
```cpp
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
```
	- Now, maintaining the old struct code, get the table:
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "street": "27",
      "city": "r79, (top floor) \n Sec-74",
      "state": "Mohali"
    }
  ],
  "more": false,
  "next_key": ""
}
```
	- Here, you are getting the data which was hindering the new data to get parsed as per the new data structure.
	- Now, delete all the data at once
```console
$ cleost push action cabeos1test2 deleteall '[]' -p cabeos1test2@active
executed transaction: ce243867894cc652a0f1dcaf412e7a7074f47481f04eca98da0004e2ca95ae62  96 bytes  278 us
#  cabeos1test2 <= cabeos1test2::deleteall      ""
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- verify table, if any other data exists:
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```
	- DONE!

* Error during transfer of money & consuming extra RAM from user
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "0.0010 EOS", "hodl!"]' -p
 cabeos1user1@active
Error 3050010: Action attempts to increase RAM usage of account without authorization
Error Details:
unprivileged contract cannot increase RAM usage of another account within a notify context: cabeos1user1
pending console output:
```
	- Error details & reason: This error means you are trying to charge someone RAM through an action that isn't specific to your contract.

	The user wants to just send money, and they wouldn't expect that they would be charged RAM for a transfer. So somewhere in your code you use multi_index::emplace, and you set the payer argument to the user's account. This is fine if the code is called by an action in the contract, but not from an external action that involves the contract such as transfer. If you must do an emplace in a transfer, then you will have to pay for it yourself. [Source](https://eosio.stackexchange.com/questions/3429/how-to-solve-error-details-cannot-charge-ram-to-other-accounts-during-notify-on)

	- Solution: modify the ram_payer as the contract (being called) e.g. `eosio.token::transfer` calling `bhub1111hodl` using `deposit` helper function, where the table is defined. Modify like this (Before & After):
	- Before:
```cpp
		if(hodl_it == balance_table.end()) {
			balance_table.emplace(hodler, [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			balance_table.modify(hodl_it, hodler, [&](auto& row) {
				row.funds += quantity;
			});
		}
```
	- After:
```cpp
		if(hodl_it == balance_table.end()) {
			balance_table.emplace(get_self(), [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			balance_table.modify(hodl_it, get_self(), [&](auto& row) {
				row.funds += quantity;
			});
		}
```
	- Issue resolved!!!

* Keep this mind that, what could be the problems in using `same_payer`
```cpp
		if(hodl_it == balance_table.end()) {
			balance_table.emplace(hodler, [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			balance_table.modify(hodl_it, same_payer, [&](auto& row) {
				row.funds += quantity;
			});
		}
```
	- Let's say you upgrade the contract & replace the `user` as ram_payer to `contract` itself. Then during each modification, the user's RAM would be charged still then.
	- This is because, the last `ram_payer` was the `user` itself.
	- Solution: It's always better to use the same param in both the functions - `emplace` & `modify` like this:
```cpp
		if(hodl_it == balance_table.end()) {
			balance_table.emplace(hodler, [&](auto& row) {
				row.funds = quantity;
			});
		} else {
			balance_table.modify(hodl_it, hodler, [&](auto& row) {
				row.funds += quantity;
			});
		}
```
* Multi-index table secondary_index auto-deduction error
```console
...
./../include/toetaxiride.hpp:242:80: error: function 'get_secondary_1' with deduced return type cannot be used before it is defined
                                                                        indexed_by<"bydriver"_n, const_mem_fun<ridetaxi, uint64_t, &ridetaxi::get_secondary_1>>,

...
...                                                                                                                                              ^
```
	- Solution: remove the `auto` from the function defined inside struct table
```cpp
		uint64_t get_secondary_1() const { return driver_ac.value; }
```
* Sometimes during compile using `eosio-cpp`, actions might get repeated like this:
```console
cabeos_contracts/toeridetaxi$ eosio-cpp src/toeridetaxi.cpp -o toeridetaxi.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <addpay> does not have a ricardian contract
Warning, action <create> does not have a ricardian contract
Warning, action <assign> does not have a ricardian contract
Warning, action <cancelbycom> does not have a ricardian contract
Warning, action <cancelbydri> does not have a ricardian contract
Warning, action <changedes> does not have a ricardian contract
Warning, action <reachsrc> does not have a ricardian contract
Warning, action <start> does not have a ricardian contract
Warning, action <finish> does not have a ricardian contract
Warning, action <addfareact> does not have a ricardian contract
Warning, action <recvfare> does not have a ricardian contract
Warning, action <sendalert> does not have a ricardian contract
Warning, action <sendreceipt> does not have a ricardian contract
Warning, action <eraseride> does not have a ricardian contract
Warning, action <addpay> does not have a ricardian contract
Warning, action <create> does not have a ricardian contract
Warning, action <assign> does not have a ricardian contract
Warning, action <cancelbycom> does not have a ricardian contract
Warning, action <cancelbydri> does not have a ricardian contract
Warning, action <changedes> does not have a ricardian contract
Warning, action <reachsrc> does not have a ricardian contract
Warning, action <start> does not have a ricardian contract
Warning, action <finish> does not have a ricardian contract
Warning, action <addfareact> does not have a ricardian contract
Warning, action <recvfare> does not have a ricardian contract
Warning, action <sendalert> does not have a ricardian contract
Warning, action <sendreceipt> does not have a ricardian contract
Warning, action <eraseride> does not have a ricardian contract
```
	- Solution: 
		+ Don’t worry about actions being repeated [Source](https://t.me/c/1139062279/229890)
		+ Its likely using multiple jobs, so it prints multiple time [Source](https://t.me/c/1139062279/229892)

* Error during pushing data onto the table
```console
$ cleost push action toe1111token transfer '["toecom111111", "toe11rwallet" "0.0001 TOE", "transfer 0.0001 TOE to ride wallet"]' -p toecom111111@active
error 2020-08-04T21:27:10.040 cleos     main.cpp:4013                 main                 ] Failed with error: could not insert object, most likely a uniqueness constraint was violated (13)
could not insert object, most likely a uniqueness constraint was violated: pending console output:
```
	- The table looks like below, in this case: 
```console
$ cleost get table toe13rwallet toecom111111 ridewallet
{
  "rows": [{
      "balance": "0.0001 TOE"
    },{
      "balance": "15.8000 TOE"
    }
  ],
  "more": false,
  "next_key": ""
}
```
	- There is clear problem in the data structure in the table.
	- So, target the primary_key. Code before:
```cpp
	TABLE ridewallet
	{
		asset balance;

		auto primary_key() const { return balance.amount; }
	};

	using ridewallet_index = multi_index<"ridewallet"_n, ridewallet>;


```
	- <u>Solution:</u> Code after
```cpp
	TABLE ridewallet
	{
		asset balance;

		auto primary_key() const { return balance.symbol.raw(); }
	};

	using ridewallet_index = multi_index<"ridewallet"_n, ridewallet>;


```
* Error during action_wrapper for inline action to external contracts
```console
/mnt/f/Coding/github_repos/toe_contracts/toeridetaxi/src/toeridetaxi.cpp:648:2: error: type 'toeridewallet::disburse_action' (aka 'action_wrapper<operator""_n<char, 'd',
      'i', 's', 'b', 'u', 'r', 's', 'e'>(), &toeridewallet::disburse>') does not provide a call operator
        disburse(receiver_ac, wallet_holder, quantity, memo);
```
	- missing `send()`. So, the modified code is:
```cpp
	toeridewallet::disburse_action disburse(wallet_contract_ac, {get_self(), "active"_n});
	disburse.send(receiver_ac, wallet_holder, quantity, memo);
```
* `read` Error related to token transfer action
```console
$ cleost push action toe1111ridex initridex '["bhubtoeindia", "commuter", "1000000.0000 TOE", "1000000"]'
-p bhubtoeindia@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: read
pending console output:
```
	- __Before:__ the piece of code inside the `initridex` action was:

```cpp
...
...

	action(
		permission_level{get_self(), "active"_n},
		token_contract_ac,
		"transfer"_n,
		std::make_tuple(token_issuer, ridex_supply_ac, toe_qty, "transfer initial toe quantity")
	).send();

...
...
```
	- So, the problem was __The memo text in transfer looks suspicious. It's a char*, while the action expects "string" object__ [Source](https://t.me/c/1139062279/232669)
	- __After:__ the correct code is by adding `std::string()`
```cpp
...
...

	action(
		permission_level{get_self(), "active"_n},
		token_contract_ac,
		"transfer"_n,
		std::make_tuple(token_issuer, ridex_supply_ac, toe_qty, std::string("transfer initial toe quantity"))
	).send();

...
...
```

* Error related to transferring tokens via inline action inside a contract action
	- The error:
```console
$ cleost push action toe1111ridex initridex '["driver", "1000000.0000 TOE", "1000000"]' -p bhubtoeindia@active
Error 3090003: Provided keys, permissions, and delays do not satisfy declared authorizations
Ensure that you have the related private keys inside your wallet and your wallet is unlocked.
Error Details:
transaction declares authority '{"actor":"bhubtoeindia","permission":"active"}', but does not have signatures for it under a provided delay of 0 ms, provided permissions [{"actor":"toe1111ridex","permission":"eosio.code"}], provided keys [], and a delay max limit of 3888000000 ms
pending console output:
```

	- __Before:__ The source code used:
```cpp
void toeridex::initridex(
                     
                        const name& ride_type,
                        const asset& toe_qty,
                        uint64_t ride_qty ) 
{
    // require the authority of toe_owner ac - "bhubtoeindia"
    require_auth(token_issuer);
    // require_auth(get_self());
...
...
...
    action(
        permission_level{token_issuer, "active"_n},
        token_contract_ac,
        "transfer"_n,
        std::make_tuple(token_issuer, ridex_supply_ac, toe_qty, std::string("transfer initial toe quantity"))
    ).send();
...
...
...
}
``` 

	- The reason for the error is at code line: `action().send()`.
	- Key points:
		+ you cannot pass authorisation from the top level action to the inline action [Source](https://t.me/c/1139062279/232735)
		+ token_issuer would need to be satisfied by the contract@eosio.code [Source](https://t.me/c/1139062279/232736)
		+ M-1: `cleos set account permission --add-code token_issuer active contract owner` [Source](https://t.me/c/1139062279/232739)
		+ M-2: the tokens transferred should really be owned by the contract. So token_issuer sends them to contract_ac and then contract_ac sends to ridex_supply_ac [Source](https://t.me/c/1139062279/232743). This is achieved by:
```
action-1: via on_notify("token::transfer") token_issuer transfers to contract_ac

action-2: inside contract's action `initridex`
		action(
		    permission_level{get_self(), "active"_n},
		    token_contract_ac,
		    "transfer"_n,
		    std::make_tuple(get_self(), ridex_supply_ac, toe_qty, std::string("transfer initial toe quantity"))
		).send();
```

		+ Q. how come then `buyram` happens...bcoz there the token is transferred from `buyer` to `eosio.ram`? And there the contract is uploaded into eosio.system contract
			- A. eosio is priviledged [Source](https://t.me/c/1139062279/232746). Buyram is executed by eosio account, which has supervisor powers. It can initiate the payment from the user's account [Source](https://t.me/c/1139062279/232747)
		+ Q. So, basically, in order to make my account `bhubtoeindia` as supervisor for my set of contracts. I shall have to use give contract@eosio.code permission to `bhubtoeindia`. Right?
			- yes [Source](https://t.me/c/1139062279/232751)

* Error related to `get`:
```console
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: get
pending console output:
```
	- the error is due to some incorrect/missing parameter parsing
	- Here, the previous code:
```cpp
void vigorico::disburse_inline(const name& receiver_ac,
						const name& buyorsell_type,
						const name& phase_type,
						const asset& disburse_qty,
						const string& memo )
{
	action(
		permission_level{get_self(), "active"_n},
		get_self(),
		"disburse"_n,
		std::make_tuple(receiver_ac, phase_type, disburse_qty, memo)
	).send();
}
```
	- the correct code:
```cpp
void vigorico::disburse_inline(const name& receiver_ac,
						const name& buyorsell_type,
						const name& phase_type,
						const asset& disburse_qty,
						const string& memo )
{
	action(
		permission_level{get_self(), "active"_n},
		get_self(),
		"disburse"_n,
		std::make_tuple(receiver_ac, buyorsell_type, phase_type, disburse_qty, memo)
	).send();
}
```
	- here, `buyorsell_type` was missing as a param
* Unable to find key
```console
$ cleost push action eosio.token transfer '["trpmuser1111", "tropium11ico", "0.0001 EOS", "phase A"]' -p trpmuser1111@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: unable to find key
pending console output:
```
	- Here, the reason is that token needs to be created
	- step 1
```console
$ cleost push action trpm111token create '["trpiumissuer", "10000000.0000 TRPM"]' -p trpm111token@active
executed transaction: 36f0c0e1965e0b65d393fd59fd1a4200549049acbd1f2c7afa492a7454e27b5c  120 bytes  229 us
#  trpm111token <= trpm111token::create         {"issuer":"trpiumissuer","maximum_supply":"10000000.0000 TRPM"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- if not resolved, then follow this step 2
```console
$ cleost push action trpm111token issue '["trpiumissuer", "1000000.0000 TRPM", "issue 1M tokens"]' -p trpiumissuer@active
executed transaction: c79ae107a26e4593bad0a97f2d6d273ff56aad17c04f5ff195f77a49a6cd9fae  136 bytes  192 us
#  trpm111token <= trpm111token::issue          {"to":"trpiumissuer","quantity":"1000000.0000 TRPM","memo":"issue 1M tokens"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Runtime Error Processing WASM
```console
Error 3070002: Runtime Error Processing WASM
Error Details:
access violation
pending console output:
```
	- [Github issue link](https://github.com/EOSIO/eosio.cdt/issues/967)
	- Here, the list is going out of bound
	- I guess this is not a bug. U find in vector copy and got iterator to vector copy element after  u trying to erase from base vector but provide iterator to copy vector. This iterator point to different memory. [Source](https://t.me/c/1139062279/235682)
	- previous code of action:
```cpp
void tropiumstake::remadmin(const name& type, 
                    const name& admin) {
    require_auth(get_self());

    admin_index admin_table(get_self(), get_self().value);
    auto admin_it = admin_table.find(type.value);

    check(admin_it != admin_table.end(), "set admins list using action - \'setadmins\'.");
    check(admin_it->vector_admin.size() != 0, "empty admin list");
    
    auto vec = admin_it->vector_admin;
    auto vec_it = std::find(vec.begin(), vec.end(), admin);

    check(vec_it != vec.end(), "the parsed admin is not in the list."); 

    admin_table.modify(admin_it, get_self(), [&](auto& row){    // found & erase it
        row.vector_admin.erase(vec_it);
    });

}
```
	- So, a copy (`vec`) of the original vector is created & then trying to erase element of original vector (`admin_it->vector_admin`).
	- Rectify that by removing that copy. So, the modified code is:
```cpp
void tropiumstake::remadmin(const name& type, 
                    const name& admin) {
    require_auth(get_self());

    admin_index admin_table(get_self(), get_self().value);
    auto admin_it = admin_table.find(type.value);

    check(admin_it != admin_table.end(), "set admins list using action - \'setadmins\'.");
    check(admin_it->vector_admin.size() != 0, "empty admin list");
    
    auto vec_it = std::find(admin_it->vector_admin.begin(), admin_it->vector_admin.end(), admin);
    check(vec_it != admin_it->vector_admin.end(), "the parsed admin is not in the list."); 

    admin_table.modify(admin_it, get_self(), [&](auto& row){    // found & erase it
        row.vector_admin.erase(vec_it);
    });

}
```
* I am calling an external action from another contract.
using 2 methods:
	- M-1: like shown in EOSIO documentation
```cpp
add_ridequota("driver"_n, 1)`
```
	- M-2: like this:
```cpp
action(
    permission_level{get_self(), "active"_n},
    ridex_contract_ac,
    "addridequota"_n,
    std::make_tuple("driver"_n, 1)
).send();
```

In M-1, there is no error. But, In M-2,  I am facing this error:
```console
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: read
pending console output:
```
	- In this type of errors, always doubt the parameters parsed inside `make_tuple`. It could be due to incorrect (in terms of casting) or missing param.
	- Soln: Cast the `1` like this:
```cpp
action(
    permission_level{get_self(), "active"_n},
    ridex_contract_ac,
    "addridequota"_n,
    std::make_tuple("driver"_n, (uint64_t)1)
).send();
```
* Error like this:
```console
error: no member named 'symbol' in 'oyanftmarket::asset'
                                        make_pair(extended_symbol(qty.symbol, capture_contract_in_map( frm_account_it->balances, qty )), qty.amount)
                                                                  ~~~ ^
/mnt/f/Coding/github_repos/eosio_oya_contracts/oyanftmarket/oyanftmarket.hpp:981:107: error: no member named 'amount' in 'oyanftmarket::asset'
                                        make_pair(extended_symbol(qty.symbol, capture_contract_in_map( frm_account_it->balances, qty )), qty.amount)
                                                                                                                                         ~~~ ^
/mnt/f/Coding/github_repos/eosio_oya_contracts/oyanftmarket/oyanftmarket.hpp:1098:59: error: no member named 'symbol' in 'oyanftmarket::asset'
                                                        [&](auto& ms) {return ms.first.get_symbol() == qty.symbol;});
```
  - Problem: the eosio::asset is not getting recognized
  - there is a table with struct asset defined like this:
```cpp
  TABLE asset
  {
    uint64_t asset_id;
    uint64_t creator_id;      // creator telegram_id    
    string asset_name;        // asset name
    string asset_desc;        // asset description

    auto primary_key() const { return asset_id; }
    uint64_t by_creator() const { return creator_id; }
  };

  using asset_index = multi_index<"assets"_n, asset,
                indexed_by< "bycreator"_n, const_mem_fun<asset, uint64_t, &asset::by_creator>>
                >;

```
  - Solution: just rename asset (in TABLE asset) with some other name like 'oasset'
```cpp
  TABLE oasset
  {
    uint64_t asset_id;
    uint64_t creator_id;      // creator telegram_id    
    string asset_name;        // asset name
    string asset_desc;        // asset description

    auto primary_key() const { return asset_id; }
    uint64_t by_creator() const { return creator_id; }
  };

  using asset_index = multi_index<"assets"_n, oasset,
                indexed_by< "bycreator"_n, const_mem_fun<oasset, uint64_t, &oasset::by_creator>>
                >;

```

#### getting this error during fetching one of the table:
* Error
```console
$ cleost get table oyanftmarket oyanftmarket accounts
Error 3015004: The type defined in the ABI is invalid
Error Details:
bid_t
```

* Problem: defined the contract table like this:
```cpp
typedef struct {
  bool claimed_by_bidder;
  asset bid_crypto_price;
  float bid_fiat_price_usd;
} bid_t;

// scope: self i.e. oyanftmarket
TABLE auction
{
...

  map<uint64_t, bid_t> map_bidderid_info;
...
}
```
* ABI generated like this:
```json
{
  "name": "pair_uint64_bid_t",
  "base": "",
  "fields": [
      {
          "name": "key",
          "type": "uint64"
      },
      {
          "name": "value",
          "type": "bid_t"
      }
  ]
},
```
* Solution: tried `struct bid_t {…}` [Source](https://t.me/c/1139062279/276517)
```cpp
struct bid_t {
  bool claimed_by_bidder;
  asset bid_crypto_price;
  float bid_fiat_price_usd;
};
```
* Output:
```console
$ cleost get table oyanftmarket oyanftmarket accounts
{
  "rows": [],
  "more": false,
  "next_key": "",
  "next_key_bytes": ""
}
```

#### Error 3070003: Serialization Error Processing WASM
* During deploy of contract:
```
Publishing contract...
Error 3070003: Serialization Error Processing WASM
Error Details:
no mapping for imported function
pending console output:
```
* Problem:
  - `regex` lib is used hence, string processing has to be performed by the contract.
  - that's why the contract is to be free from heavy processing in EOSIO VM.
* Solution:
  - Do the processing outside of the contract
* More info:
  - [Here's how to find out: run the wasm through wasm2wat and grep for import. Look for anything which isn't an eosio intrinsic](https://t.me/c/1139062279/278714)
  - [It's not recommended to do any heavy string processing inside a contract](https://t.me/c/1139062279/278721)
  - [No, regex is not a part of C++, it's a lib](https://t.me/c/1139062279/278726)
  - [You have 30ms for everything, and RAM is quite expensive](https://t.me/c/1139062279/278728)
  - [The version of eosiolib which comes with the cdt includes a very hacked-up version of the C++ runtime library. It was made compatible with wasm in a rush. A lot of it was sacrificed.](https://t.me/c/1139062279/278732)
  - [Maybe there's a regexp library for microprocessors, but it's really a wrong place to do](https://t.me/c/1139062279/278732)
  - [clsdk uses the wasi-sdk,  a much more complete port of the RTL. But string processing is still a pretty heavy task for contracts.](https://t.me/c/1139062279/278734)

#### For more errors log, Click [here](https://www.dfuse.io/en/blog/common-errors-on-eosio-and-how-to-get-past-them)

## Miscellaneous
* let's say we deal with a table. Here, we set a value inside a table & then we want to read that value from inside the same ACTION, then the value is not going to be read becuase it hasn't been set yet until the transaction is made.
	- E.g. of code snippet inside an ACTION
```cpp
void gpkbattlesco::pairwplayer(const name& player_1, 
								const name& asset_contract_ac)
{
	...
	...
	ongamestat_table.emplace(get_self(), [&](auto& row){
		row.game_id = game_id;
		row.player_1 = p1;
		row.player_2 = p2;
		row.asset_contract_ac = asset_contract_ac;
		row.game_fee = computed_gfee_p1;
		row.player1_cards = card_ids_p1;
		row.player1_cards_combo = card_ids_type_p1;
		row.player2_cards = card_ids_p2;
		row.player2_cards_combo = card_ids_type_p2;
		row.status = "paired"_n;
	});

	...
	send_alert(player_1, "You have been paired with a player in game_id: " + std::to_string(game_id));
}
```
	- here, `ongamestat_it->player_2` can't be put inside the send_alert msg param, as it is not yet set in the table.
* giving error: "unable to find key"
	- parsed command
```console
$ cleost push action eosio.token transfer '["tipuser11111", "tippertipper", "1.0000 FUTBOL", "deposit for fund"]' -p tipuser11111@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: unable to find key
pending console output:
```
	- wrong token contract account name as `eosio.token` instead of `tokenfutbol1` So, the correct command is as follows:
```console
$ cleost push action tokenfutbol1 transfer '["tipuser11111", "tippertipper", "1.0000 FUTBOL", "deposit for fund"]' -p tipuser11111@active
executed transaction: 0c4c058cf212668b95e725f460160acf06137b3667c1fbc459c0f6b2d92deacc  144 bytes  180 us
#  tokenfutbol1 <= tokenfutbol1::transfer       {"from":"tipuser11111","to":"tippertipper","quantity":"1.0000 FUTBOL","memo":"deposit for fund"}
#  tipuser11111 <= tokenfutbol1::transfer       {"from":"tipuser11111","to":"tippertipper","quantity":"1.0000 FUTBOL","memo":"deposit for fund"}
#  tippertipper <= tokenfutbol1::transfer       {"from":"tipuser11111","to":"tippertipper","quantity":"1.0000 FUTBOL","memo":"deposit for fund"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Hash storage: `checksum256` better than `string`
* In order to use a hash as storage field in contract, always use `checksum256` instead of `string`.
* Cons: contract wasm size would be greater if `checksum256` is used.
* Pros: TABLE size would be relatively smaller as `checksum256` consumes 32 bytes of data, whereas `string` consumes 64+ bytes of data. 

### Table Storage
* Any data should be stored in the table, only if it's used in between the actions.
* Otherwise, store the data into the cloud, if not stored into the table.

## Error codes
* Error 3015004: The type defined in the ABI is invalid
* Error 3080004: Transaction exceeded the current CPU usage limit imposed on the transaction
* Error 3090003: Provided keys, permissions, and delays do not satisfy declared authorizations
* Error 3120002: Nonexistent wallet

## References
* [EOSIO Developer Portal](https://developers.eos.io/)
* [Best Practices](https://developers.eos.io/manuals/eosio.cdt/v1.8/best-practices/index)
* [EOSIO Contracts Guides](https://developers.eos.io/manuals/eosio.contracts/latest/guides/index)
* [Understanding The eosio.token Contract](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* [The Dispatcher – First Line Of Defense In Any EOS Smart Contract](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)
* [[CODEOS] Essential knowledge in EOS contract development](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* [How to estimate RAM/CPU/NET cost for your EOS DApp](https://medium.com/leclevietnam/eos-resource-allocation-98bb6cb84497)
* [Modifying data structure in EOS contract is not an easy thing](https://medium.com/@cc32d9/modifying-data-structure-in-eos-contract-is-not-an-easy-thing-594f596c9995)
	- [delete all the data at once](#create-an-action-to-delete-all-the-table-data-at-once)
* Glossary:
	- EOSIO Developer portal: https://developers.eos.io/welcome/latest/glossary/index
	- dfuse: https://www.eoscanada.com/en/abc-eos
* [Multiplication and division of assets with different symbols and precision on EOSIO](https://medium.com/@genesix/exchange-on-eosio-36e43a360398)
* [Common Errors on EOSIO and How to Get Past Them](https://www.dfuse.io/en/blog/common-errors-on-eosio-and-how-to-get-past-them)
* [Deferred transacitons by EOSIO Developer portal](https://developers.eos.io/manuals/eosio.cdt/v1.7/best-practices/deferred_transactions)
* [Deferred transacitons by CMitchel](https://cmichel.io/deferred-transactions-on-eos/)
* [How to fetch any secondary EOSIO table index using eosjs](https://cmichel.io/how-to-fetch-table-indexes-using-eosjs/)