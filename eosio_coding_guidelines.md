## Compiler
* Using `eosio-cpp`: `$ eosio-cpp -I=/usr/local/include -I=/usr/include/c++/7.5.0 -l=/usr/local/lib/libhl++.a otp.cpp -o otp.wasm`
	- Here, 2 paths have been given with `-I` flag
	- & `-l` flag is used to link with a library file.
	- For more, see this: `$ eosio-cpp -help`  


## Contract
* `CONTRACT` is equal to `class [[eosio::contract]]`
* “Pushing an action to a contract requires the authorization of at least one account. Further accounts and permissions can be required depending on contract complexity. An account can be made of a single, or many, individuals set up in a permission based configuration. Smart contracts can only be run by a single account, and a single account can only have a single smart contract. It is best practice to give both the account and contract the same (lowercase) name.” [Source](https://link.medium.com/1G4zitL6t7)
* Every EOSIO smart contract is set to a single EOSIO account. A contract is basically an object that other accounts can interact with. An account cannot have more than 1 contract. [Source](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)

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


## Table
* `TABLE` is equal to `struct [[eosio::table]]`
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
* To ensure table, one param should e
* In EOSIO, we have multi-index table insprired from Boost Multi-index library. For more, look at the next section below.

### Multi-index
* [How to Guide](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/index/)
* Each smart contract using multi index table reserves a partition of the RAM cache, which is controlled using table name, code and scope. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index tables provide a fast access to data storage and can be accessed by smart contract. Therefore, the Dapps are required to store application data in the Multi index Tables, and the blockchain records the transactions by interacting with the smart contact. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index Tables support using multiple indexes on the data. The primary index type must be unit64_t and must be unique, but the secondary indexes can have duplicates. If you want to index on a string you will need to convert this to an integer type and store the results in a field that you then index. Up to 16 indexes are allowed.
* max. no. of columns: `uint32_t` i.e. 4 billion (approx.). [Source](https://t.me/c/1139062279/226525)
* primary index: mandatory to define. & must be `uint64_t` & must be unique.
	- if `name` data type is defined as primary_index, then the get_func will return `n.value`
* secondary index type: optional (max 16) & can have duplicates like a valet in Zomato linked linked to multiple orders i.e. rows in table.
* secondary index data_types: `uint64_t`, `uint128_t`, `uint256_t`, `double` or `long double`.

> NOTE: If you want to index on a `string` you will need to convert this to an `integer` type and store the results in a field that you then index. 

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
	- `find`: for querying an entry
```cpp
...
address_index addresses(get_self(), get_first_receiver().value);
auto it = addresses.find(user.value);
...
...
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



## References
* [EOSIO Developer Portal](https://developers.eos.io/)
* [Understanding The eosio.token Contract](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* [The Dispatcher – First Line Of Defense In Any EOS Smart Contract](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)
* [[CODEOS] Essential knowledge in EOS contract development](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* [How to estimate RAM/CPU/NET cost for your EOS DApp](https://medium.com/leclevietnam/eos-resource-allocation-98bb6cb84497)
* [Modifying data structure in EOS contract is not an easy thing](https://medium.com/@cc32d9/modifying-data-structure-in-eos-contract-is-not-an-easy-thing-594f596c9995)
	- [delete all the data at once](#create-an-action-to-delete-all-the-table-data-at-once)