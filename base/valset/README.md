## Compile
* Compile the contract
```console
....../base/valset
$ eosio-cpp valset.cpp -o valset.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <putval> does not have a ricardian contract
```

## Deploy
* Deploy the contract
	- Here, you always need the permission of contract account
```console
....../base/valset
$ cleost set contract cabeos1test1 ./ -p cabeos1test1@active
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/valset/valset.wasm...
Publishing contract...
executed transaction: 72ae5bad7ec2e394b97c8da72eff31dae635a1c7fea5ebdad133f7c69f0b6bc8  2376 bytes  1401 us
#         eosio <= eosio::setcode               {"account":"cabeos1test1","vmtype":0,"vmversion":0,"code":"0061736d0100000001701460000060037f7f7f006...
#         eosio <= eosio::setabi                {"account":"cabeos1test1","abi":"0e656f73696f3a3a6162692f312e3100010670757476616c0002036e756d05696e7...
warn  2020-06-19T10:46:29.229 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```

## Push
* `putval`: Push the action
	- Here, you need the permission of any account as no `require_auth()` in the code.
```console
....../base/valset
$ cleost push action cabeos1test1 putval '["3700", "\"dalvath3700@gmail.com\""]' -p cabeos1test1@active
executed transaction: 23bae0b76086007ecad219f2b56cdca25d729b38b6e7f5993e2e391daac3f2f0  120 bytes  644 us
#  cabeos1test1 <= cabeos1test1::putval         {"num":3700,"str":"\"dalvath3700@gmail.com\""}
>> The num is 3700 & the string is "dalvath3700@gmail.com"
warn  2020-06-19T10:52:42.910 cleos     main.cpp:506                  print_result   warning: transaction executed locally, but may not be confirmed by the network yet
```


