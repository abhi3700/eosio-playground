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

## Debugging contracts
Basically, try to see the values of local variables defined in the action
* So, try to see the variables like this:
	- Here, in the console, the 3 vars output can be seen.
```cpp
		print("get_self(): ", get_self(), " | ");	// for debugging
		print("get_first_receiver(): ", get_first_receiver(), " | ");	// for debugging
		print("get_first_receiver() value: ", get_first_receiver().value, " |");	// for debugging
```

```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 71b204a40f008a24779a3f739af718a48299562b97837cc805be284f858ce319  152 bytes  257 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
>> get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
