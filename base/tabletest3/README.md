# `tabletest3` contract
## Account details:
* Network: "Jungle 3 Testnet"
* Contract account: "bhubtabtes13"
* Contract name: "tabletest3"
* [tabletest3.cpp](./tabletest3.cpp)
* [tabletest3.wasm](./tabletest3.wasm)
* [tabletest3.abi](./tabletest3.abi)

## Compile
```console
$ eosio-cpp tabletest3.cpp -o tabletest3.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <creatify> does not have a ricardian contract
Warning, action <readtable> does not have a ricardian contract
Warning, action <del> does not have a ricardian contract
```

## Deploy
* deploy contract (ABI & WASM)
```console
$ cleost set contract bhubtabtes13 ./
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/tabletest3/tabletest3.wasm...
Publishing contract...
executed transaction: d486532bfe857ce994929339b6d68d2ec0fb0f583ffef35b76c180d60435695c  6936 bytes  638 us
#         eosio <= eosio::setcode               {"account":"bhubtabtes13","vmtype":0,"vmversion":0,"code":"0061736d0100000001aa011c6000006000017f600...
#         eosio <= eosio::setabi                {"account":"bhubtabtes13","abi":"0e656f73696f3a3a6162692f312e310005086372656174696679000208636f6d6d7...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Adding eosio.code to permissions (for inline actions)
```
$ cleost set account permission bhubtabtes13 active --add-code
executed transaction: 8238ee37d0f94406a13511c2dae1da78756d23f62555371ef8262e420c788760  184 bytes  157 us
#         eosio <= eosio::updateauth            {"account":"bhubtabtes13","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Testing
### Action - `creatify`
* creatify with "create" ride action.
```console
$ cleost push action bhubtabtes13 creatify '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: a9d4d4b006cf93df95d5b90349bc0fcab6f68709647492380fd4943f1b1a3da5  112 bytes  268 us
#  bhubtabtes13 <= bhubtabtes13::creatify       {"commuter":"cabeos1user1","ride_action":"create"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after emplace (table) & "create" key
```console
$ cleost get table bhubtabtes13 bhubtabtes13 ridetable
{
	"rows": [{
			"commuter": "cabeos1user1",
			"ride_action": "create",
			"txn_vector": [{
					"first": "create",
					"second": "a9d4d4b006cf93df95d5b90349bc0fcab6f68709647492380fd4943f1b1a3da5"
				}
			]
		}
	],
	"more": false,
	"next_key": ""
}
```
* creatify with "create" ride action again with key - "create"
```console
$ cleost push action bhubtabtes13 creatify '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: 71de7e876a08569f9c75a0e9c2a3011e873d031b290b5c503a9fb576e87f0031  112 bytes  183 us
#  bhubtabtes13 <= bhubtabtes13::creatify       {"commuter":"cabeos1user1","ride_action":"create"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after modify (table) & same key
```console
$ cleost get table bhubtabtes13 bhubtabtes13 ridetable
{
	"rows": [{
			"commuter": "cabeos1user1",
			"ride_action": "create",
			"txn_vector": [{
					"first": "create",
					"second": "a9d4d4b006cf93df95d5b90349bc0fcab6f68709647492380fd4943f1b1a3da5"
				},{
					"first": "create",
					"second": "71de7e876a08569f9c75a0e9c2a3011e873d031b290b5c503a9fb576e87f0031"
				}
			]
		}
	],
	"more": false,
	"next_key": ""
}
```
	- Observation:
		+ total 2 items gets inserted into the __txn_vector__ with same key from back side
* creatify with "create" ride action again with key - "create"
```console
$ cleost push action bhubtabtes13 creatify '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: c72b772e89d2145b4f464d3cad3ce4f0fee4d1826503ebb833f9302a644e3f60  112 bytes  177 us
#  bhubtabtes13 <= bhubtabtes13::creatify       {"commuter":"cabeos1user1","ride_action":"create"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after modify (table) & same key
```console
$ cleost get table bhubtabtes13 bhubtabtes13 ridetable
{
	"rows": [{
			"commuter": "cabeos1user1",
			"ride_action": "create",
			"txn_vector": [{
					"first": "create",
					"second": "a9d4d4b006cf93df95d5b90349bc0fcab6f68709647492380fd4943f1b1a3da5"
				},{
					"first": "create",
					"second": "71de7e876a08569f9c75a0e9c2a3011e873d031b290b5c503a9fb576e87f0031"
				},{
					"first": "create",
					"second": "c72b772e89d2145b4f464d3cad3ce4f0fee4d1826503ebb833f9302a644e3f60"
				}
			]
		}
	],
	"more": false,
	"next_key": ""
}
```
	- Observation:
		+ total 3 items gets inserted into the __txn_vector__ with same key from back side


### Action - `readtable`
* read table for action_type "create"
```console
$ cleost push action bhubtabtes13 readtable '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: ca2dbf0696d6e8aa78e3e3b024ddad2f0a3a751cd78a563b8fb159f84b3ddaf5  112 bytes  197 us
#  bhubtabtes13 <= bhubtabtes13::readtable      {"commuter":"cabeos1user1","search_key":"create"}
>> The value(s): a9d4d4b006cf93df95d5b90349bc0fcab6f68709647492380fd4943f1b1a3da5 | 71de7e876a08569f9c75a0e9c2a3011e873d031b290b5c503a9fb576e87f0031 | c72b772e89d2145b4f464d3cad3ce4f0fee4d1826503ebb833f9302a644e3f60 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Action - `del`
* erase the commuter's data "cabeos1user1" with contract's authority
```console
$ cleost push action bhubtabtes13 del '["cabeos1user1"]' -p bhubtabtes13@active
executed transaction: 470bd359eef76a03d6d2827e0bb645ce9ea825fcb853fdca67e28cf57a3dd2ad  104 bytes  244 us
#  bhubtabtes13 <= bhubtabtes13::del            {"commuter":"cabeos1user1"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table so as to check the data doesn't exist anymore
```console
$ cleost get table bhubtabtes13 bhubtabtes13 ridetable
{
	"rows": [],
	"more": false,
	"next_key": ""
}
```

## NOTES
* Here, 2 types of finding is happening:
	- Here, the multi-index table finds for commuter.
	- The vector finds for action_type as key in the vector of pairs.