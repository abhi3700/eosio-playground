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
Skipping set abi because the new abi is the same as the existing abi
Publishing contract...
executed transaction: 03786ad57bdefa0fc58b10cce0befd391d75e4da7e3904d4ee7e0958e912c5a8  2120 bytes  1534 us
#         eosio <= eosio::setcode               {"account":"cabeos1test1","vmtype":0,"vmversion":0,"code":"0061736d010000000163126000006000017f60027...
warn  2020-06-19T13:12:37.250 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```

## Push
* `hiany`: Push the action
	- Here, you need the permission of any account
```console
....../base/hello
$ cleost push action cabeos1test1 hiany '["\"dalvath3700@gmail.com\""]' -p cabeos1user1@active
executed transaction: 5174e79bb3701024157a76e881f3bcb13d83c3c094e7043ee3d41d598f9d8a8f  120 bytes  505 us
#  cabeos1test1 <= cabeos1test1::hiany          {"a":"\"dalvath3700@gmail.com\""}
>> Hello, "dalvath3700@gmail.com"
warn  2020-06-19T13:14:42.052 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
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
executed transaction: 34bd98ff1b4f052dd01dfa5cd019633e48d190351660804c572057e3eeef2142  104 bytes  545 us
#  cabeos1test1 <= cabeos1test1::hiname         {"user":"cabeos1test1"}
>> Hello, your EOS name is, cabeos1test1
warn  2020-06-19T13:15:53.356 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```

* `getsymbol`
```
$ cleost push action cabeos1test1 getsymbol '[]' -p cabeos1test1@active
executed transaction: 3c32b1073972de6dad2582e40bfd35fbcfa3e4ab1202bca9fd6209ff0ca064de  96 bytes  617 us
#  cabeos1test1 <= cabeos1test1::getsymbol      ""
>> 4542292 | 1162826756 | TOE
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `compareasset`
	- test-1
```console
$ cleost push action cabeos1test1 compareasset '["15.8000 TOE", "15.8000 TOE"]' -p cabeos1test1@active
executed transaction: 44b74d13ede37c9c50ac1a3b3db24d34456a30b9daaca628a9d5a408e7723fb3  128 bytes  211 us
#  cabeos1test1 <= cabeos1test1::compareasset   {"a1":"15.8000 TOE","a2":"15.8000 TOE"}
>> a1 is equal to a2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-2
```console
$ cleost push action cabeos1test1 compareasset '["15.8000 TOE", "16.8000 TOE"]' -p cabeos1test1@activ
e
executed transaction: 2762ac1bf432df9281a97ca01aff0a7486e0d25a144bed793dc1d3e9f2350bcb  128 bytes  655 us
#  cabeos1test1 <= cabeos1test1::compareasset   {"a1":"15.8000 TOE","a2":"16.8000 TOE"}
>> a1 is less than a2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-3
```console
$ cleost push action cabeos1test1 compareasset '["16.8000 TOE", "15.8000 TOE"]' -p cabeos1test1@activ
e
executed transaction: ca0308dda55db4474e51ffc1687a0846e8ba47b2428bd6e278b67dab03f6f592  128 bytes  574 us
#  cabeos1test1 <= cabeos1test1::compareasset   {"a1":"16.8000 TOE","a2":"15.8000 TOE"}
>> a1 is more than a2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `checklowbal`
	- test-1
```console
$ cleost push action cabeos1test1 checklowbal '["14.8000 TOE"]' -p cabeos1test1@active
executed transaction: a3d2029e705d3c49aa2c46ef1841486cc4a5bf23843b239f60beead9cc9c0e3d  112 bytes  528 us
#  cabeos1test1 <= cabeos1test1::checklowbal    {"a1":"14.8000 TOE"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-2
```console
$ cleost push action cabeos1test1 checklowbal '["16.8000 TOE"]' -p cabeos1test1@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: amount is greater than token_balance
pending console output:
```