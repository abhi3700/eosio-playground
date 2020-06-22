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