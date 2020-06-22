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
* Monitor 

## Table
* `TABLE` is equal to `struct [[eosio::table]]`  


## Multi-index
* [How to Guide](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/index/)
* Each smart contract using multi index table reserves a partition of the RAM cache, which is controlled using table name, code and scope. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index tables provide a fast access to data storage and can be accessed by smart contract. Therefore, the Dapps are required to store application data in the Multi index Tables, and the blockchain records the transactions by interacting with the smart contact. [Source](https://medium.com/@moonxfamily/multi-index-table-ram-infrastructure-of-eos-9e78fb5fed13)
* Multi Index Tables support using multiple indexes on the data. The primary index type must be unit64_t and must be unique, but the secondary indexes can have duplicates. If you want to index on a string you will need to convert this to an integer type and store the results in a field that you then index. Up to 16 indexes are allowed.
* max. no. of columns: `uint32_t` i.e. 4 billion (approx.).
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
* Multi-index DB table storage: Take the [addressbook example](./base/addressbook/addressbook.cpp)
	- Case-1: [tabletest1](./base/tabletest1)
		+ action permission: user
		+ action ram_payer: user
```cpp
void create(name user, string first_name) {
	require_auth(user);



}
```

```console
$ cleost push action cabeos1test2 create '["cabeos1user1", "Abhijit"]' -p cabeos1test2
```
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


## Permission
* Multisig

## Notification
* “A notification is a function to deliver success action to designated user once the action is successfully completed.” [Source](https://link.medium.com/flTeJNKdw7)
* When using inline action, you need to add permission ‘contract@eosio.code’, to user’s account. However, it’s not easy to apply to service because most of users are reluctant to add it to their own account. So notification function is used mainly in service instead of adding permission. [Source](https://link.medium.com/flTeJNKdw7)
* A notification is a function to deliver success action to designated user once the action is successfully completed.
	- E.g. - When actions are made within contracts or using external contracts, there is very helpful way of checking if its properly done or not is by getting notification. `eosio.token` is a good instance to understand how a transfer actions are made and how the notification is made.

## Coding syntax
### Data types
* `name` - [Source](https://developers.eos.io/manuals/eosio.cdt/latest/structeosio_1_1name)
	- e.g `name.value`

### print [All](https://developers.eos.io/manuals/eosio.cdt/v1.7/best-practices/debugging_a_smart_contract/#print)
* `print`
```cpp
print("Name, ", nm);
```

* `print_f`:
```cpp
print_f("Name : %\n", nm);
```

### Contracts
* `get_self()` - gives the contract account name
* `get_first_receiver()`
* code vs receiver [Source]()
	-

### Permission
* `require_auth( account name )`
This action explains that the transfer function requires the authorization of the account holder from where the tokens are transferred.
* `require_recipient( account name )`
This action helps in getting notification to the account. This explains that the current action to be delivered to the account name.



## References
* [EOSIO Developer Portal](https://developers.eos.io/)
* [Understanding The eosio.token Contract](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)
* [The Dispatcher – First Line Of Defense In Any EOS Smart Contract](https://chainsecurity.com/the-dispatcher-first-line-of-defense-in-any-eos-smart-contract/)
* [[CODEOS] Essential knowledge in EOS contract development](https://medium.com/eoseoul/codeos-essential-knowledge-in-eos-contact-development-9c9b1bf26d0c)