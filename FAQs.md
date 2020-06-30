# EOSIO SC FAQs
Here, the FAQs are mostly related to EOSIO Smart contract.

1. ##### Who is the account holding the Smart contract?
	- The account which is used for deploying the contract.
	- And this can be set using this - `$ cleost set contract cabeos1test2 ./ -p cabeos1test2@active`

1. ##### Can anyone upgrade the Smart contract onto that used account during deploy?
	- Only one, who holds the private key of that already used contract account during deploy.

1. ##### Who pays for the RAM table row? How to set that?
	- During instantiation, the `code` param declared (depending on actions, utility functions). The options are listed as below:
		+ using `get_self()`
		+ using `user`		// declared as param in function

	- [How to instantiate a multi index table](https://developers.eos.io/manuals/eosio.cdt/v1.7/how-to-guides/multi-index/how-to-instantiate-a-multi-index-table)

1. ##### Can an EOSIO contract action have any return type?
	- No
	- They can be of any type, but their return value is ignored.
	- Just make them `void`

1. ##### How to connect an EOSIO contract action with a function?
	- use a private function for that
	- your public functions can call private functions directly
	- [Source](https://t.me/c/1139062279/227631)

1. ##### Is it possible to push data to database API using contract's action?
	- No
	- but the contract can change a state on the blockchain, so that an external oracle reads it and performs what is needed. [Source](https://t.me/c/1139062279/227648)