## RAM table
* Here, the table is found in the contract (obviously as it is deployed there)
* Who pays for each row?
	- Here, each person pays for its own piece of data
* Below is shown `eosio.token` tables data in Jungle Testnet
* Table-1 ("stat"_n): This stores `supply`, `max_supply`, `issuer`
	- stat of "EOS" token in Jungle testnet
```console
$ cleost get table eosio.token EOS stat --show-payer
{
  "rows": [{
      "data": {
        "supply": "10780618644.8810 EOS",
        "max_supply": "100000000000.0000 EOS",
        "issuer": "eosio"
      },
      "payer": "eosio.token"
    }
  ],
  "more": false,
  "next_key": ""
}
```
  - stat of "SYS" token in Jungle testnet.
```console
$ cleost get table eosio.token SYS stat --show-payer
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```

> NOTE: this token doesn't exist. Basically, it doesn't give Error. Please, note that the symbol is a part of `asset` which is the actual data in the cells. 

  - stat of "JUNGLE" token in Jungle testnet
```console
$ cleost get table eosio.token JUNGLE stat --show-payer
{
  "rows": [{
      "data": {
        "supply": "10000020000.0000 JUNGLE",
        "max_supply": "100000000000.0000 JUNGLE",
        "issuer": "eosio"
      },
      "payer": "eosio.token"
    }
  ],
  "more": false,
  "next_key": ""
}
```


* Table-2 ("accounts"_n): This stores `balance`
	- balance of "cabeos1test1" account in Jungle testnet
```console
$ cleost get table eosio.token cabeos1test1 accounts --show-payer
{
  "rows": [{
      "data": {
        "balance": "60.0000 EOS"
      },
      "payer": "cabeos1test1"
    },{
      "data": {
        "balance": "100.0000 JUNGLE"
      },
      "payer": "junglefaucet"
    }
  ],
  "more": false,
  "next_key": ""
}
```
