## Compile
* Compile the contract
```console
....../base/hello
$ eosio-cpp hello.cpp -o hello.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <hiany> does not have a ricardian contract
Warning, action <hiname> does not have a ricardian contract
Warning, action <getsymbol> does not have a ricardian contract
Warning, action <compareasset> does not have a ricardian contract
Warning, action <checklowbal> does not have a ricardian contract
Warning, action <getsha25six> does not have a ricardian contract
Warning, action <hexstr> does not have a ricardian contract
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
executed transaction: 0e1e7f2048261a90904390cac74a5ccbc86eb9d01421de30a6b400faaf92b900  96 bytes  111 us
#  cabeos1test1 <= cabeos1test1::getsymbol      ""
>> 4542292 | 1162826756 | TOE | 4
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
* `assetcalc`
```console
$ cleost push action cabeos1test1 assetcalc '["40.0000 EOS"]' -p cabeos1test1@active
executed transaction: d1acba87b1ad2f138d84108b20a1e3a9b18c73df315eec4e27c55c15e437ecbd  112 bytes  209 us
#  cabeos1test1 <= cabeos1test1::assetcalc      {"a1":"40.0000 EOS"}
>> New asset: 1200.0000 DUMMY
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `assetmul`
```console
$ cleost push action cabeos1test1 assetmul '["3.0000 EOS", "40.0000 TRPM"]' -p cabeos1test1@active
executed transaction: 58ddf7e461692699c119fee0071d3fb348f1ef44f68af932bdbed12093b1a611  128 bytes  183 us
#  cabeos1test1 <= cabeos1test1::assetmul       {"a1":"3.0000 EOS","rate":"40.0000 TRPM"}
>> New asset: 120.0000 DUMMY | New asset amount: 1200000 | rate precision: 4
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
* `getsha25six`
```console
$ cleost push action cabeos1test1 getsha25six '["toecom111111"]' -p cabeos1test1@active
executed transaction: 16c3e8de65cb2aa176ac528addbefb6dd604b8ea5e3e17e3977ba932f1a89b7f  104 bytes  188 us
#  cabeos1test1 <= cabeos1test1::getsha25six    {"commuter_ac":"toecom111111"}
>> The C string, timestamp: toecom1111111597434665 , 1597434665 | The hash digest is: f478ec901f2231819ce7e489f9cab04aee0a92e551dd9990081c0ab2bae0b8b4
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `hexstr`
```console
$ cleost push action cabeos1test1 hexstr '["abhijit"]' -p cabeos1test1@active
executed transaction: cf815e352e9b32ea93ef8b8b1b0e19b8434aef04618f9fa86b00209295dcf383  104 bytes  223 us
#  cabeos1test1 <= cabeos1test1::hexstr         {"s":"abhijit"}
>> checksum256 to string: abhijit whose checksum is: 654c62962bdf81fd478d259e82e6349e66dfcbfb47573c3f02155588ecc472b8
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `getgameid`
```console
$ cleost push action cabeos1test1 gengameid '[]' -p cabeos1test1@active
executed transaction: 738712a2d7008489be48056e756082c1a1539f90f3fc9ea49ffd71a04f7c7653  96 bytes  158 us
#  cabeos1test1 <= cabeos1test1::gengameid      ""
>> 10001723663692
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `getrandindex`
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: ad588836e016615da0f6bb2cb1032d855ff8264eccfb065e708886bbc96c64d8  136 bytes  142 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 3
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-2
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: f760e77553a4da487fee501b52741d67564db346c15d416bb5b2b86c65e9dc62  136 bytes  166 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: dec7386d841e3accc602e4f7561cbd25931a74378c763ea62fbc37366ebaee25  136 bytes  142 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: 087c6358866a59cd62f5ea9ba873f4ec4022fd0cf7480e8941f32289ec1d7a22  136 bytes  142 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 3
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: 30b34bad44de6c53e6efed6751f14a202a61bd3d0e3ce93fdd5c74b3bf28041c  136 bytes  135 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 3
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: 41348095f90ed02c252f4ee42e0bff071e55a917de6e5a5ddb048215ec6877b9  136 bytes  120 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 2
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: bf141da53d8e4c0c2074197eed169995d23fd1e3565586434c9154d585c1b891  136 bytes  152 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 1
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- test-1
```console
$ cleost push action cabeos1test1 genrandindex '{"v": ["gbuser111111", "gbuser111112", "gbuser111113", "gbuser111114", "gbuser111115"]}' -p cabeos1test1@active
executed transaction: edbbb98235b3bd98bd9c8fda346f1359969bee4ac784db8f6cf3bba8fe683fe6  136 bytes  210 us
#  cabeos1test1 <= cabeos1test1::genrandindex   {"v":["gbuser111111","gbuser111112","gbuser111113","gbuser111114","gbuser111115"]}
>> 4
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- So, it generates random no. in range 1 to 4 (including 1 and 4)
	- For creating either 0 or 1, use `uint64_t num1 = random_int % 2;`
	- For more details, refer [here](https://www.bitdegree.org/learn/random-number-generator-cpp)


## TODO
* [ ] multi-index table with data having same primary_key e.g. driver having more than 1 ride in case of following cases:
	- pool ride
	- commuter didn't rate & the ride will be erased after 'x' hrs. So, driver should not wait for 'x' hrs for the ride to get erased.