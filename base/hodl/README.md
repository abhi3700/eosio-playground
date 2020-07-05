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

## Compile

## Deploy

## Push

## Table
