## EOSIO Table Test - 4

## About
* multi-index table with this data structure
```cpp
	TABLE account
	{
		uint64_t owner;		// telegram_id, e.g. 452435325.

		/*
			[ 
				{ "key": { "symbol": "4,SOV", "contract": "sovmintofeos" }, "value": 30000 }, 
				{ "key": { "symbol": "4,FROG", "contract": "frogfrogcoin" }, "value": 3500000 }, 
				{ "key": { "symbol": "4,PEOS", "contract": "thepeostoken" }, "value": 100000 }, 
				{ "key": { "symbol": "4,KROWN", "contract": "krowndactokn" }, "value": 7169 } 
			]
			
			Here, quantity amount is 30000/10^4 = 3 i.e. asset is "3.0000 SOV"
		*/
		map<extended_symbol, uint64_t> balances; // map with extended_symbol, uint64_t

		auto primary_key() const { return owner; }
	};

	using account_index = multi_index<"accounts"_n, account>;

```