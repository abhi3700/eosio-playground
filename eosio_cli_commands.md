## Version
* Client version:
```console
❯ cleos version client
v2.1.0
```
* Full version:
```console
❯ cleos version full
v2.1.0-26a4d285d0be1052d962149e431eb81500782991
```

## Wallet
* Create a wallet with password display in console
```console
❯ cleos wallet create -n ndwax --to-console                                   ⏎
Creating wallet: ndwax
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5JA4Mv9oaoNveyFhDyXwtxwMqTU22x8tu9z9KcgACBqAHMDEdvi"
```

## Contract
* Set the contract
```console
$ cleosw set contract gpkbatescrow ./
Reading WASM from /mnt/f/Coding/github_repos/eosio_gpkbattles_contracts/gpkbatescrow/gpkbatescrow.wasm...
Publishing contract...
executed transaction: 7410d224760874729dc7c3edb04b552c379edeae07d286a8372c6593f160ce87  47592 bytes  6237 us
#         eosio <= eosio::setcode               {"account":"gpkbatescrow","vmtype":0,"vmversion":0,"code":"0061736d0100000001af022c60000060037f7f7f0...
#         eosio <= eosio::setabi                {"account":"gpkbatescrow","abi":"0e656f73696f3a3a6162692f312e3100050a6361726477616c6c657400030763617...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Clear the contract
```console
$ cleosw set contract gpkbattlesco --clear
Publishing contract...
executed transaction: 093828df3da647e066cbc9e4c89326a06a410fec5d2702d93c2d33ad10f56d33  112 bytes  510 us
#         eosio <= eosio::setcode               {"account":"gpkbattlesco","vmtype":0,"vmversion":0,"code":""}
#         eosio <= eosio::setabi                {"account":"gpkbattlesco","abi":""}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Account
* Buy RAM for self account
```console
$ cleost system buyram cabeos1test2 cabeos1test2 "1 EOS"
executed transaction: 90c50348098c9155d57364acbfac2ce117efaba8717104e51f6b34f88629c138  128 bytes  1571 us
#         eosio <= eosio::buyram                {"payer":"cabeos1test2","receiver":"cabeos1test2","quant":"1.0000 EOS"}
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ram","quantity":"0.9950 EOS","memo":"buy ram"}
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ramfee","quantity":"0.0050 EOS","memo":"ram fee"}
#   eosio.token <= eosio.token::transfer        {"from":"eosio.ramfee","to":"eosio.rex","quantity":"0.0050 EOS","memo":"transfer from eosio.ramfee t...
#  cabeos1test2 <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ram","quantity":"0.9950 EOS","memo":"buy ram"}
#     eosio.ram <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ram","quantity":"0.9950 EOS","memo":"buy ram"}
#  cabeos1test2 <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ramfee","quantity":"0.0050 EOS","memo":"ram fee"}
#  eosio.ramfee <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.ramfee","quantity":"0.0050 EOS","memo":"ram fee"}
#  eosio.ramfee <= eosio.token::transfer        {"from":"eosio.ramfee","to":"eosio.rex","quantity":"0.0050 EOS","memo":"transfer from eosio.ramfee t...
#     eosio.rex <= eosio.token::transfer        {"from":"eosio.ramfee","to":"eosio.rex","quantity":"0.0050 EOS","memo":"transfer from eosio.ramfee t...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Delegate NET for self account
```console
$ cleost system delegatebw cabeos1test2 cabeos1test2 "1 EOS" "0 EOS"
executed transaction: e175d740d35f7955245c9c9e7afd6b7c3f6ee187b8bf53597d4a7381c67d4074  144 bytes  380 us
#         eosio <= eosio::delegatebw            {"from":"cabeos1test2","receiver":"cabeos1test2","stake_net_quantity":"1.0000 EOS","stake_cpu_quanti...
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"1.0000 EOS","memo":"stake bandwidth"}
#  cabeos1test2 <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"1.0000 EOS","memo":"stake bandwidth"}
#   eosio.stake <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"1.0000 EOS","memo":"stake bandwidth"}
```
* Delegate CPU for self account
```console
$ cleost system delegatebw cabeos1test2 cabeos1test2 "0 EOS" "2 EOS"
executed transaction: 2d0cd04f91acd118883244d35d41ba44cf11042ab53c859edbd88040b8f951bf  144 bytes  966 us
#         eosio <= eosio::delegatebw            {"from":"cabeos1test2","receiver":"cabeos1test2","stake_net_quantity":"0.0000 EOS","stake_cpu_quanti...
#   eosio.token <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"2.0000 EOS","memo":"stake bandwidth"}
#  cabeos1test2 <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"2.0000 EOS","memo":"stake bandwidth"}
#   eosio.stake <= eosio.token::transfer        {"from":"cabeos1test2","to":"eosio.stake","quantity":"2.0000 EOS","memo":"stake bandwidth"}
```
* Add code permission to the contract account
```console
$ cleost set account permission toe1111ridex active --add-code
executed transaction: e518946f5afdef0a6c8943fa3ddb231f102a5dd1d9ed328b4292d6cff9ceb634  184 bytes  434 us
#         eosio <= eosio::updateauth            {"account":"toe1111ridex","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Remove code permission to the contract account
```console
$ cleost set account permission bhubtoeindia active --remove-code
executed transaction: 3e366d4ee020335a4c5730a154ef1376293973eb2bf1728a175b6d03e3985c0c  160 bytes  471 us
#         eosio <= eosio::updateauth            {"account":"bhubtoeindia","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Compile
## Deploy
## Push
* broadcast transaction to the network
```console
....../base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 7de992eacf4844b205d6fb768bd25869b7fc383f4e2bb21cea068970b5712c83  152 bytes  1209 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Don't broadcast transaction to the network
```console
....../base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active -d
OR
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active -d -j
{
	"expiration": "2020-06-21T23:48:51",
	"ref_block_num": 56098,
	"ref_block_prefix": 4270078558,
	"max_net_usage_words": 0,
	"max_cpu_usage_ms": 0,
	"delay_sec": 0,
	"context_free_actions": [],
	"actions": [{
			"account": "cabeos1test2",
			"name": "upsert",
			"authorization": [{
					"actor": "cabeos1user1",
					"permission": "active"
				}
			],
			"data": "10aec23a60aa8e4107616268696a697403726f79197237392c2028746f7020666c6f6f7229200a205365632d3734064d6f68616c690650756e6a6162"
		}
	],
	"transaction_extensions": [],
	"signatures": [
		"SIG_K1_KYy1bWty81kCEFP3PpTnJ5B25yvA7rnT3oGTWmxoVvSrwUpx7VkemgN1yoBv6Qf7jwViwpYy4Wdth283QCwRdiU6YYmXwM"
	],
	"context_free_data": []
}
```
* Print result as JSON
```console
....../base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active -j
{
	"transaction_id": "c3219ffa2f99708e6be3037cc72e4b5f627000863c48b665c3dd9e25017c87e5",
	"processed": {
		"id": "c3219ffa2f99708e6be3037cc72e4b5f627000863c48b665c3dd9e25017c87e5",
		"block_num": 97901897,
		"block_time": "2020-06-21T23:50:11.000",
		"producer_block_id": null,
		"receipt": {
			"status": "executed",
			"cpu_usage_us": 263,
			"net_usage_words": 19
		},
		"elapsed": 263,
		"net_usage": 152,
		"scheduled": false,
		"action_traces": [{
				"action_ordinal": 1,
				"creator_action_ordinal": 0,
				"closest_unnotified_ancestor_action_ordinal": 0,
				"receipt": {
					"receiver": "cabeos1test2",
					"act_digest": "61c09356bcfe26c3be3ed675a50e5c75f92ed8f1e69f9ed489be92c0e05708bc",
					"global_sequence": 604458598,
					"recv_sequence": 17,
					"auth_sequence": [[
							"cabeos1user1",
							16
						]
					],
					"code_sequence": 7,
					"abi_sequence": 1
				},
				"receiver": "cabeos1test2",
				"act": {
					"account": "cabeos1test2",
					"name": "upsert",
					"authorization": [{
							"actor": "cabeos1user1",
							"permission": "active"
						}
					],
					"data": {
						"user": "cabeos1user1",
						"first_name": "abhijit",
						"last_name": "roy",
						"street": "r79, (top floor) \n Sec-74",
						"city": "Mohali",
						"state": "Punjab"
					},
					"hex_data": "10aec23a60aa8e4107616268696a697403726f79197237392c2028746f7020666c6f6f7229200a205365632d3734064d6f68616c690650756e6a6162"
				},
				"context_free": false,
				"elapsed": 73,
				"console": "get_self(): cabeos1test2...get_first_receiver(): cabeos1test2...get_first_receiver() value: 4723900389413761568...",
				"trx_id": "c3219ffa2f99708e6be3037cc72e4b5f627000863c48b665c3dd9e25017c87e5",
				"block_num": 97901897,
				"block_time": "2020-06-21T23:50:11.000",
				"producer_block_id": null,
				"account_ram_deltas": [],
				"except": null,
				"error_code": null
			}
		],
		"account_ram_delta": null,
		"except": null,
		"error_code": null
	}
}
```

## History API
* [History API Endpoints list](https://hyperion.docs.eosrio.io/endpoint/)
* Get actions via
	- eg-1: `https://junglehistory.cryptolions.io/v2/history/get_actions?account=cabeos1user3`
```json
{
	"query_time_ms":15.779,
	"cached":false,"lib":0,
	"total":{"value":7,"relation":"eq"},
	"actions":[
		{
			"@timestamp":"2020-07-01T23:27:18.000",
			"timestamp":"2020-07-01T23:27:18.000",
			"block_num":99626648,
			"trx_id":"442eea8e8528695df51af5ac9300a1509737cc5de0387c8f1be4c57e22ec37b8",
			"act":{
				"account":"cabeos1test2",
				"name":"notify",
				"authorization":[{"actor":"cabeos1test2","permission":"active"}],
				"data":{
					"user":"cabeos1user3",
					"msg":"cabeos1user3 successfully emplaced record to addressbook"}
			},
			"notified":["cabeos1test2","cabeos1user3"],
			"global_sequence":606820038,
			"producer":"junglemorpho",
			"action_ordinal":2,
			"creator_action_ordinal":1
		},
		{
			"@timestamp":"2020-07-01T23:27:18.000",
			"timestamp":"2020-07-01T23:27:18.000",
			"block_num":99626648,
			"trx_id":"442eea8e8528695df51af5ac9300a1509737cc5de0387c8f1be4c57e22ec37b8",
			"act":{
				"account":"cabeos1test2",
				"name":"upsert",
				"authorization":[{"actor":"cabeos1user3","permission":"active"}],
				"data":{
					"user":"cabeos1user3",
					"first_name":"Gurvinder",
					"last_name":"Dhillon",
					"age":"54",
					"street":"Dwarka, Sec-12",
					"city":"Delhi",
					"state":"Delhi"
				}
			},
			"notified":["cabeos1test2"],
			"cpu_usage_us":936,
			"net_usage_words":20,
			"account_ram_deltas":[{"account":"cabeos1user3","delta":301}],
			"global_sequence":606820037,
			"producer":"junglemorpho",
			"action_ordinal":1,
			"creator_action_ordinal":0
		}
	]
}
```

## Troubleshooting
* Sometimes it might happen like this that "Wallet doesn't exist"
```console
$ cleos wallet list
"/usr/opt/eosio/2.0.5/bin/keosd" launched
cWallets:
[]
```
	- To verify, whether your wallet actually exists
```console
$ ls /home/abhi3700/eosio-wallet/
cabeos.wallet  config.ini  keosd.sock  wallet.lock
```
	- Just unlock the wallet using password:
```console
$ cleos wallet unlock -n cabeos
password: Unlocked: cabeos
```
	- Then, you find your wallet
```console
$ cleos wallet list
Wallets:
[
	"cabeos *"
]
```