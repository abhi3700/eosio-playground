# Quickstart
## Code
```cpp
#include <eosio/eosio.hpp>
#include <string>

using eosio::contract;
using eosio::print;
using eosio::name;
using std::string;

class [[eosio::contract]] hello : public contract {
public:
	using contract::contract;

	[[eosio::action]]
	void hi(string a) {
		print("Hello, ", a);
	}
};

EOSIO_DISPATCH(hello, (hi))
```

## Compile
* Compile the code
```console
$ eosio-cpp hello.cpp -o hello.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <hi> does not have a ricardian contract
```
* This creates this tree
```console
...../base/hello$ tree
.
├── hello.abi
├── hello.cpp
└── hello.wasm

0 directories, 3 files
```

## Wallet
* Open a bash (ubuntu) in any directory.
* Create a wallet locally using 
```console
$ cleos wallet create -n cabeos --to-console
Creating wallet: cabeos
Save password to use in the future to unlock this wallet.
Without password imported keys will not be retrievable.
"PW5KE5hRLHL4zHwFdokgiEn588GtJGuis4yvVZKsLPZxjXwSDRBJt"
```
* Please, note down the password to unlock the wallet later.
* To unlock the wallet use 
```console
$ cleos wallet unlock -n cabeos --password PW5KE5hRLHL4zHwFdokgiEn588GtJGuis4yvVZKsLPZxjXwSDRBJt
Unlocked: cabeos
```
* To see the list of wallets, where * means unlocked
```console
$ cleos wallet list
Wallets:
[
  "cabeos *"
]
```

## Network
* Get info
```console
$ cleos -u http://jungle2.cryptolions.io:80 get info
{
  "server_version": "c6a7ec0d",
  "chain_id": "e70aaab8997e1dfce58fbfac80cbbb8fecec7b99cf982a9444273cbc64c41473",
  "head_block_num": 97356532,
  "last_irreversible_block_num": 97356199,
  "last_irreversible_block_id": "05cd89a7665f33c7d8e6849cf71b50304f65959e84bfe8af7dbec9fa32f2baed",
  "head_block_id": "05cd8af4600263264249d50ef782acdae649f4fb08d5c3bf2fc013a397f0c4e6",
  "head_block_time": "2020-06-18T20:04:58.000",
  "head_block_producer": "eoscafeloons",
  "virtual_block_cpu_limit": 500000000,
  "virtual_block_net_limit": 524288000,
  "block_cpu_limit": 499990,
  "block_net_limit": 524288,
  "server_version_string": "v2.0.6",
  "fork_db_head_block_num": 97356532,
  "fork_db_head_block_id": "05cd8af4600263264249d50ef782acdae649f4fb08d5c3bf2fc013a397f0c4e6",
  "server_full_version_string": "v2.0.6-c6a7ec0dd816f98a6840f59dca9fed04efd9f7a5"
}
```

> NOTE: it's better to alias as __`cleost`__ for testnet,   

## Deploy a contract
* set contract, here `cleost` is aliased as `alias cleost='cleos -u http://jungle2.cryptolions.io:80'`
```console
$ cleost set contract cabeos1test1 ./hello -p cabeos1test1@active
Reading WASM from /mnt/f/Coding/github_repos/cabeos_contracts/base/hello/hello.wasm...
Publishing contract...
executed transaction: b54cb89774eb02f2b485440116fb60c5ce8d44fd71e97ab1cb6f12948745c92e  824 bytes  867 us
#         eosio <= eosio::setcode               {"account":"cabeos1test1","vmtype":0,"vmversion":0,"code":"0061736d01000000013e0c60027f7e0060027f7f0...
#         eosio <= eosio::setabi                {"account":"cabeos1test1","abi":"0e656f73696f3a3a6162692f312e31000102686900010475736572046e616d65010...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Push action
```console
$ cleost push action cabeos1test1 hi '["abhijit is a good boy"]' -p cabeos1user1@active
executed transaction: 0d6d9c3bf20c90b1e3982ff752d5e3287d135929116d2dcbd68eaacbed3c514f  120 bytes  1251 us
#  cabeos1test1 <= cabeos1test1::hi             {"a":"abhijit is a good boy"}
>> Hello, abhijit is a good boy
warning: transaction executed locally, but may not be confirmed by the network yet
```