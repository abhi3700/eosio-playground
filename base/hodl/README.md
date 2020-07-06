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
* `ram_payer`: the contract i.e. `"bhub1111hodl"`.

> NOTE: Making `hodler` as ram_payer, means you are trying to charge someone RAM through an action that isn't specific to your contract.
> The user wants to just send money, and they wouldn't expect that they would be charged RAM for a transfer. So somewhere in your code you use multi_index::emplace, and you set the payer argument to the user's account. This is fine if the code is called by an action in the contract, but not from an external action that involves the contract such as transfer. If you must do an emplace in a transfer, then you will have to pay for it yourself [Source](https://eosio.stackexchange.com/questions/3429/how-to-solve-error-details-cannot-charge-ram-to-other-accounts-during-notify-on)

* `scope`: hodler i.e. whoever the holds the money.
* `primary_key`: find the symbol e.g. `"EOS"` which is a part of `asset`

## Actions
> NOTE: Annotating an action with an on_notify attribute ensures any incoming notification is forwarded to the annotated action if and only if the notification is dispatched from a specified contract and from a specified action.

* `deposit`:
	- It is not an action, rather utility/helper function like `send_summary()`, `increment_counter()` in the EOSIO developer Getting started Series. 
	- In this case, the `on_notify` attribute ensures the incoming notification is forward to the deposit action only if the notification comes from the `eosio.token` contract and is from the `eosio.token`'s `transfer` action.
	- This is also why we don't need to check if the hodler actually has the appropriate amount of tokens he or she claimed, as the `eosio.token` contract would have done this check prior to the transfer notification reaching the `hodl` `deposit` helper function.
	- Here, `hodler` is using `eosio.token`'s `transfer` action on `deposit` helper function to deposit money by transferring the money from user account to the contract account after checking necessary conditions.
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
### Test Deposit
* Use `eosio.token::transfer` action to deposit fund money & store info. into `hodl`'s `balance` table
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "0.0010 EOS", "hodl!"]' -p cabeos1user1@active
executed transaction: 28618352c2923b2040803182753e02e4d40fb0133a4e0b145391886c434fa80a  136 bytes  1071 us
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
#  cabeos1user1 <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
#  bhub1111hodl <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Add more fund money
```console
$ cleost push action eosio.token transfer '["cabeos1user1", "bhub1111hodl", "0.0010 EOS", "hodl!"]' -p cabeos1user1@active
executed transaction: f74ae910d38a2574adeee7d4b7a516deb9dc628c2e0e4cbbd26104ac85c51792  136 bytes  769 us
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
#  cabeos1user1 <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
#  bhub1111hodl <= eosio.token::transfer        {"from":"cabeos1user1","to":"bhub1111hodl","quantity":"0.0010 EOS","memo":"hodl!"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Test Withdraw
* trying to withdraw money before the maturity period has arrived
```
$ cleost push action bhub1111hodl party '["cabeos1user1"]' -p cabeos1user1@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: Hold your horses.
pending console output:
```
* In order to execute the withdrawal make the date as already passed, so that the maturity period is over.
```cpp
	// static const uint32_t the_party = 1645568542;	// UTC timestamp for "Tuesday, February 22, 2022 10:22:22 PM"
	static const uint32_t the_party = 1592829600;	// for withdrawal testing purpose. UTC timestamp for "06/22/2020 @ 12:40pm (UTC)"
```
* Now, withdraw the money successfully
```console
$ cleost push action bhub1111hodl party '["cabeos1user1"]' -p cabeos1user1@active
executed transaction: 46f37e80e9bcf825ba5eeaf42a38801b9e381ef7ec3abba5b662e9eaac54fd62  104 bytes  334 us
#  bhub1111hodl <= bhub1111hodl::party          {"hodler":"cabeos1user1"}
#   eosio.token <= eosio.token::transfer        {"from":"bhub1111hodl","to":"cabeos1user1","quantity":"0.0020 EOS","memo":"Party! Your hodl is free....
#  bhub1111hodl <= eosio.token::transfer        {"from":"bhub1111hodl","to":"cabeos1user1","quantity":"0.0020 EOS","memo":"Party! Your hodl is free....
>> These are not the droids you are looking for.
#  cabeos1user1 <= eosio.token::transfer        {"from":"bhub1111hodl","to":"cabeos1user1","quantity":"0.0020 EOS","memo":"Party! Your hodl is free....
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
* Show the table after 2 times depositing money ("0.0010 EOS" twice)
```console
$ cleost get table bhub1111hodl cabeos1user1 balance --show-payer
{
  "rows": [{
      "data": {
        "funds": "0.0020 EOS"
      },
      "payer": "bhub1111hodl"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the table after successful withdrawal
```console
$ cleost get table bhub1111hodl cabeos1user1 balance --show-payer
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```

## References
* [Payable actions](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/payable_actions)