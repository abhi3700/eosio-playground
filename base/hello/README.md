## Compile
* Compile the contract
```console
....../base/hello
$ eosio-cpp hello.cpp -o hello.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <putval> does not have a ricardian contract
```

## Deploy
* Deploy the contract
	- Here, you always need the permission of contract account
```console
....../base/hello
$ cleost set contract cabeos1test1 ./ -p cabeos1test1@active
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/hello/hello.wasm...
Publishing contract...
executed transaction: 7db1be427fa9d42e19b35b5fb8e32196eab83a360bc5adf90b9dc95041997962  2560 bytes  1415 us
#         eosio <= eosio::setcode               {"account":"cabeos1test1","vmtype":0,"vmversion":0,"code":"0061736d01000000016a1360000060027f7f00600...
#         eosio <= eosio::setabi                {"account":"cabeos1test1","abi":"0e656f73696f3a3a6162692f312e310002056869616e790001016106737472696e6...
warn  2020-06-19T11:15:15.445 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```

## Push
* `hiany`: Push the action
	- Here, you need the permission of any account
```console
....../base/hello
$ cleost push action cabeos1test1 hiany '["\"dalvath3700@gmail.com\""]' -p cabeos1user1@active
executed transaction: fb50c50c97c6094f3d6b97b5ee0512ab562973b8552895913f781fd58770d5df  120 bytes  176 us
#  cabeos1test1 <= cabeos1test1::hiany          {"a":"\"dalvath3700@gmail.com\""}
>> Hello, "dalvath3700@gmail.com"
warn  2020-06-19T11:27:36.453 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```
* `hiname`: Push the action
	- Here, you need the permission of contract as it includes require_auth(<eos-username>)
	
		+ Error!
```console
....../base/hello
$ cleost push action cabeos1test1 hiname '["cabeos1test1"]' -p cabeos1user1@active
Error 3090004: Missing required authority
Ensure that you have the related authority inside your transaction!;
If you are currently using 'cleos push action' command, try to add the relevant authority using -p option.
Error Details:
missing authority of cabeos1test1
pending console output:
```

		+ Ok!
```console
....../base/hello
$ cleost push action cabeos1test1 hiname '["cabeos1test1"]' -p cabeos1test1@active
executed transaction: cbcec3dfb4a0b14f3bfcae49ec9cc3ee48ea70fe7ffba7313407adc3f6cb6751  104 bytes  177 us
#  cabeos1test1 <= cabeos1test1::hiname         {"user":"cabeos1test1"}
>> Hello, your EOS name is, cabeos1test1
warn  2020-06-19T11:30:04.400 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```


