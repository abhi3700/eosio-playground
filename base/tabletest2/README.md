# `tabletest2` contract
## Account details:
* Network: "Jungle 3 Testnet"
* Contract account: "bhubtabtes12"
* Contract name: "tabletest2"
* [tabletest2.cpp](./tabletest2.cpp)
* [tabletest2.wasm](./tabletest2.wasm)
* [tabletest2.abi](./tabletest2.abi)

## Compile
```console
$ eosio-cpp tabletest2.cpp -o tabletest2.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <creatify> does not have a ricardian contract
Warning, action <del> does not have a ricardian contract
```

## Deploy
* deploy contract (ABI & WASM)
```console
$ cleost set contract bhubadrbook1 ./
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/tabletest2/tabletest2.wasm...
Publishing contract...
executed transaction: f2caed50909e2f84e7f336133382675945649c6286d969ae264139e431f5d97b  12304 bytes  1049 us
#         eosio <= eosio::setcode               {"account":"bhubadrbook1","vmtype":0,"vmversion":0,"code":"0061736d0100000001ed012260000060047f7f7f7...
#         eosio <= eosio::setabi                {"account":"bhubadrbook1","abi":"0e656f73696f3a3a6162692f312e3100070964656c657465616c6c0000056572617...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Adding eosio.code to permissions (for inline actions)
```
$ cleost set account permission bhubadrbook1 active --add-code
executed transaction: 6b1b5e87de2f8d1d8ef9ba8a6e30beef776bdf64d0db1ca2ac07c92b1e75f631  184 bytes  215 us
#         eosio <= eosio::updateauth            {"account":"toe1userauth","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Testing
### Action - `creatify`
* creatify with "create" ride action.
```console
$ cleost push action bhubtabtes12 creatify '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: 7f84faaf403634e3adf62d1abf8363fb2509d45a159e7b5e16b471464e5c5384  112 bytes  293 us
#  bhubtabtes12 <= bhubtabtes12::creatify       {"commuter":"cabeos1user1","ride_action":"create"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after emplace (table) & "create" key
```console
$ cleost get table bhubtabtes12 bhubtabtes12 ridetable
{
  "rows": [{
      "commuter": "cabeos1user1",
      "ride_action": "create",
      "txn_vector": [{
          "first": "create",
          "second": "568da4bc3bbe8adfec0c306406756d6fbf11b9a47d4549876467e5ae0f431898"
        }
      ]
    }
  ],
  "more": false,
  "next_key": ""
}
```
* creatify with "create" ride action again to test whether modifying existing key - "create"
```console
$ cleost push action bhubtabtes12 creatify '["cabeos1user1", "create"]' -p cabeos1user1@active
executed transaction: 568da4bc3bbe8adfec0c306406756d6fbf11b9a47d4549876467e5ae0f431898  112 bytes  141 us
#  bhubtabtes12 <= bhubtabtes12::creatify       {"commuter":"cabeos1user1","ride_action":"create"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after modify (table) & same key
```console
$ cleost get table bhubtabtes12 bhubtabtes12 ridetable
{
  "rows": [{
      "commuter": "cabeos1user1",
      "ride_action": "create",
      "txn_vector": [{
          "first": "create",
          "second": "568da4bc3bbe8adfec0c306406756d6fbf11b9a47d4549876467e5ae0f431898"
        }
      ]
    }
  ],
  "more": false,
  "next_key": ""
}
```
* creatify with "assign" ride action again to test whether modifying existing key - "assign"
```console
$ cleost push action bhubtabtes12 creatify '["cabeos1user1", "assign"]' -p cabeos1user1@active
executed transaction: e89408c578ee6b50a3407b18f14c1e5acf728cb0ef71adddef57c1f9dad17126  112 bytes  140 us
#  bhubtabtes12 <= bhubtabtes12::creatify       {"commuter":"cabeos1user1","ride_action":"assign"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after modify (table) & "assign" key
```console
$ cleost get table bhubtabtes12 bhubtabtes12 ridetable
{
  "rows": [{
      "commuter": "cabeos1user1",
      "ride_action": "assign",
      "txn_vector": [{
          "first": "create",
          "second": "568da4bc3bbe8adfec0c306406756d6fbf11b9a47d4549876467e5ae0f431898"
        },{
          "first": "modify",
          "second": "9df3d6bee7e8c13284ba76b700080868e026617da117c949cf7054d21a5618f4"
        },{
          "first": "assign",
          "second": "e89408c578ee6b50a3407b18f14c1e5acf728cb0ef71adddef57c1f9dad17126"
        }
      ]
    }
  ],
  "more": false,
  "next_key": ""
}
```
* creatify with "assign" ride action again to test whether modifying existing key - "assign" again
```console
$ cleost push action bhubtabtes12 creatify '["cabeos1user1", "assign"]' -p cabeos1user1@active
executed transaction: d271277d73414870321850bf0a08ad23d108c179f0a9468db9812dce9d1fa1d8  112 bytes  168 us
#  bhubtabtes12 <= bhubtabtes12::creatify       {"commuter":"cabeos1user1","ride_action":"assign"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table after modify (table) & same "assign" key
```console
$ cleost get table bhubtabtes12 bhubtabtes12 ridetable
{
  "rows": [{
      "commuter": "cabeos1user1",
      "ride_action": "assign",
      "txn_vector": [{
          "first": "create",
          "second": "568da4bc3bbe8adfec0c306406756d6fbf11b9a47d4549876467e5ae0f431898"
        },{
          "first": "modify",
          "second": "9df3d6bee7e8c13284ba76b700080868e026617da117c949cf7054d21a5618f4"
        },{
          "first": "assign",
          "second": "d271277d73414870321850bf0a08ad23d108c179f0a9468db9812dce9d1fa1d8"
        }
      ]
    }
  ],
  "more": false,
  "next_key": ""
}
```

### Action - `del`
* erase the commuter's data "cabeos1user1" with contract's authority
```console
$ cleost push action bhubtabtes12 del '["cabeos1user1"]' -p bhubtabtes12@active
executed transaction: 470bd359eef76a03d6d2827e0bb645ce9ea825fcb853fdca67e28cf57a3dd2ad  104 bytes  244 us
#  bhubtabtes12 <= bhubtabtes12::del            {"commuter":"cabeos1user1"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- view the table so as to check the data doesn't exist anymore
```console
$ cleost get table bhubtabtes12 bhubtabtes12 ridetable
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```
