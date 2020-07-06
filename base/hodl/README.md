# `hodl` contract
## Account details:
* Network: "Jungle Testnet"
* Contract account: "bhub1111hodl"
* Contract name: "hodl"
* [hodl.cpp](./hodl.cpp)
* [hodl.wasm](./hodl.wasm)
* [hodl.abi](./hodl.abi)

## About
As for the logic of this smart contract, we're going to write a contract that accepts a particular token but will not allow the tokens to be withdrawn for a specific amount of time.

This contract needs to set up a few constraints:

* What symbol/token does this contract accept?
	- `"SYS"` token
* When is the hodl over?
	- `the_party` constant sets the hodl to end on `Tuesday, February 22, 2022 10:22:22 PM`.

## RAM Table
* The contract table is definitely stored in the contract account.
* `ram_payer`: the contract i.e. `"bhub1111hodl"`
* `scope`: hodler i.e. whoever the holds the money.
* `primary_key`: find the symbol e.g. `"EOS"` which is a part of `asset`

## Actions
> NOTE: Annotating an action with an on_notify attribute ensures any incoming notification is forwarded to the annotated action if and only if the notification is dispatched from a specified contract and from a specified action.

* `deposit`:
	- In this case, the `on_notify` attribute ensures the incoming notification is forward to the deposit action only if the notification comes from the `eosio.token` contract and is from the `eosio.token`'s `transfer` action.
	- This is also why we don't need to check if the hodler actually has the appropriate amount of tokens he or she claimed, as the `eosio.token` contract would have done this check prior to the transfer notification reaching the `hodl` `deposit` action.
	- Here, `hodler` is using `eosio.token`'s `transfer` action on `deposit` action to deposit money by transferring the money from user account to the contract account after checking necessary conditions.
	- Note that most of the conditions like (below) are checked in the `eosio.token::transfer` action.
		+ subtraction of amount from balance,
		+ addition of amount to balance
	- The `funds` record is updated in the table.
* `party`:
	- Here, `hodler` is using `party` action to withdraw the fund money by transferring the money from contract account to the user account by using inline action.
	- use action constructor to send the money using `eosio.token::transfer` action.
```cpp
action(
	permission_level{get_self(), "active"_n},
	"eosio.token"_n,
	"transfer"_n,
	std::make_tuple(get_self(), hodler, hold_it->funds, std::string("Party! Your hodl is free."))
	)
```
> NOTE: this constructor instead can also be written like this [this](../addressbook/README.md#inline-actions-to-action-in-different-contract)

## Compile
```console
$ eosio-cpp hodl.cpp -o hodl.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <party> does not have a ricardian contract
```

## Contract-to-contract communication permission
```console
$ cleost set account permission bhub1111hodl active --add-code
executed transaction: 77921b9b157999a616f5f2249a25032e66b0923e934195b934c50bfff433f084  184 bytes  647 us
#         eosio <= eosio::updateauth            {"account":"bhub1111hodl","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Deploy
```console
$ cleost set contract bhub1111hodl ./ -p bhub1111hodl@active
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/hodl/hodl.wasm...
Publishing contract...
executed transaction: 9c28b3c94e7b85fd8b8e7d690306a443d1826528834a7a030b18d4a77cbac01a  5304 bytes  2102 us
#         eosio <= eosio::setcode               {"account":"bhub1111hodl","vmtype":0,"vmversion":0,"code":"0061736d01000000019401196000006000017f600...
#         eosio <= eosio::setabi                {"account":"bhub1111hodl","abi":"0e656f73696f3a3a6162692f312e3100020762616c616e636500010566756e64730...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Push
* Use `eosio.token::transfer` action to store into `hodl`'s `balance` table
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "1.0000 EOS", "deposit fund"]' -p cabeos1user1@acti
ve
executed transaction: 9a4b97dc37ecdaa33993e1f1a44246296fa1489de517e74f2a9967caca8507dc  144 bytes  746 us
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"1.0000 EOS","memo":"deposit fund"}
#  cabeos1user1 <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"1.0000 EOS","memo":"deposit fund"}
#  bhub1111hodl <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"1.0000 EOS","memo":"deposit fund"}
>> These are not the droids you are looking for.
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Possible errors
* 1. wrong symbol
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "1.0000 SYS", "deposit fund"]' -p cabeos1user1@acti
ve
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: unable to find key
pending console output:
```
* 2. wrong precision
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "1 EOS", "deposit fund"]' -p cabeos1user1@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: symbol precision mismatch
pending console output:
```
* 3. account doesn't own this token
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "1.0000 JUNGLE", "deposit fund"]' -p cabeos1user1@a
ctive
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: no balance object found
pending console output:
```
* 4. Asset symbol is missing in '0.0020', rectified to --> '0.0020 EOS' 
```console
$ cleost transfer cabeos1user1 bhub1111hodl '0.0020' 'Hodl!' -p cabeos1user1@active
warn  2020-07-06T11:37:22.554 cleos     asset.cpp:75                  from_string          ] 3010011 asset_type_exception: Invalid asset
Asset's amount and symbol should be separated with space
    {}
    cleos  asset.cpp:38 from_string
warn  2020-07-06T11:37:22.555 cleos     asset.cpp:75                  from_string          ] from: 0.0020
Error 3010011: Invalid asset
Error Details:
Asset's amount and symbol should be separated with space
rethrow
```

## Table
* check `cabeos1user1`'s balance via `get account` method:
```console
$ cleost get account cabeos1user1
created: 2020-06-18T21:21:46.500
permissions:
     owner     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
        active     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
memory:
     quota:     5.365 KiB    used:     4.027 KiB

net bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               304 bytes
     available:        62.45 KiB
     limit:            62.74 KiB

cpu bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               398 us
     available:        58.59 ms
     limit:            58.99 ms

EOS balances:
     liquid:           18.0000 EOS
     staked:            2.0000 EOS
     unstaking:         0.0000 EOS
     total:            20.0000 EOS

producers:     <not voted>
```

* check `cabeos1user1`'s balance via table of `eosio.token`:
```console
$ cleost get table eosio.token cabeos1user1 accounts
{
  "rows": [{
      "balance": "18.0000 EOS"
    }
  ],
  "more": false,
  "next_key": ""
}
```

