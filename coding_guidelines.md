## Compiler
* Using `eosio-cpp`: `$ eosio-cpp -I=/usr/local/include -I=/usr/include/c++/7.5.0 -l=/usr/local/lib/libhl++.a otp.cpp -o otp.wasm`
	- Here, 2 paths have been given with `-I` flag
	- & `-l` flag is used to link with a library file.
	- For more, see this: `$ eosio-cpp -help`	 



## Action
* limit an action to the contract creator only: use `require_auth( get_self() );` inside an action function.

## Multi-index
* [How to Guide](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/index/)
* max. no. of columns: `uint32_t` i.e. 4 billion (approx.).
* primary index: mandatory to define.
* secondary index type: optional (max 16).
* secondary index data_types: `uint64_t`, `uint128_t`, `uint256_t`, `double` or `long double`.
* [ ] the table can't be updated, unless all the data is removed
