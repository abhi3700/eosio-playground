# `addressbook` contract
## Account details:
* Network: "Jungle Testnet"
* Contract account: "cabeos1test2"
* Contract name: "addressbook"
* [addressbook.cpp](./addressbook.cpp)
* [addressbook.wasm](./addressbook.wasm)
* [addressbook.abi](./addressbook.abi)

## Layers
* A. Write an `addressbook` contract:
	- __primary_key__ in __multi_index table__.
* B. Modify the `addressbook` contract:
	- __primary_key__ in __multi_index table__.
	- __secondary_key__ in __multi_index table__.
* C. Modify the `addressbook` contract:
	- __primary_key__ in __multi_index table__.
	- __secondary_key__ in __multi_index table__.
	- add inline action - `send_summary()` to action - `notify()`
* D. Modify the `addressbook` contract:
	- __primary_key__ in __multi_index table__.
	- __secondary_key__ in __multi_index table__.
	- add inline action - `send_summary()` [in `addressbook` contract] to action - `notify()` [in `addressbook` contract]
	- add inline action - `increment_counter()` [in `addressbook` contract] to external action - `count()` [in `abcounter` contract]


## RAM table
* Here, the table is found in the contract (obviously as it is deployed there)
* Who pays for each row?
	- Here, each person pays for its own piece of data
* Where do you define that?
	- in the emplace, modify method of multi-index table
```cpp
addresses.emplace(user, [&]( auto& row ) {
      row.key = user;
      row.first_name = first_name;
      row.last_name = last_name;
			row.age = age;
      row.city = city;
      row.state = state;
    });
...
...
addresses.modify(iterator, user, [&]( auto& row ) {
      row.key = user;
      row.first_name = first_name;
      row.last_name = last_name;
			row.age = age;
      row.street = street;
      row.city = city;
      row.state = state;
    });
```
* Security bug: Here, on pushing the same action with same data, the CPU, NET consumption was getting increased.
	- Around `NET: 152 bytes, CPU: 412 bytes` are getting increased, after 2nd time pushed with the same data.

	> NOTE: No change in RAM although.

```console
abhi3700@Abhijit:/mnt/f/Coding/github_repos/eosio-playground/base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: e36af3551be882e3e6edd66e210ac12613a95652ad446a6ece282b54e066cc73  152 bytes  667 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
>> get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
abhi3700@Abhijit:/mnt/f/Coding/github_repos/eosio-playground/base/addressbook$ cleost get account cabeos1user1
created: 2020-06-18T21:21:46.500
permissions:
     owner     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
        active     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
memory:
     quota:     5.365 KiB    used:     3.643 KiB

net bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               306 bytes
     available:        62.45 KiB
     limit:            62.74 KiB

cpu bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               360 us
     available:        5.588 ms
     limit:            5.948 ms

EOS balances:
     liquid:           20.0000 EOS
     staked:            2.0000 EOS
     unstaking:         0.0000 EOS
     total:            22.0000 EOS

producers:     <not voted>

abhi3700@Abhijit:/mnt/f/Coding/github_repos/eosio-playground/base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 591701344a80f582f7bcb48750684d04a72942602dcfcacb4c6c2c9c4136c5a2  152 bytes  531 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
>> get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
abhi3700@Abhijit:/mnt/f/Coding/github_repos/eosio-playground/base/addressbook$ cleost get account cabeos1user1
created: 2020-06-18T21:21:46.500
permissions:
     owner     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
        active     1:    1 EOS7L5cABCRbkk9XSPY9qiTzUV5jMoPWWmehe29fW23qK5j3M6Se9
memory:
     quota:     5.365 KiB    used:     3.643 KiB

net bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               458 bytes
     available:         62.3 KiB
     limit:            62.74 KiB

cpu bandwidth:
     staked:          1.0000 EOS           (total stake delegated from account to self)
     delegated:       0.0000 EOS           (total staked delegated to account from others)
     used:               772 us
     available:        5.493 ms
     limit:            6.265 ms

EOS balances:
     liquid:           20.0000 EOS
     staked:            2.0000 EOS
     unstaking:         0.0000 EOS
     total:            22.0000 EOS

producers:     <not voted>
```
	- So, there is a security glitch, which can be exploited by repetitive pushing & consuming all the NET & CPU Bandwidths of the user.
	- Therefore, check for all the params & only then the transaction will be pushed successfully.
	- previously, the contract code was:
```cpp
		else {
			// Now, modify the new data
			addresses.modify(it, user, [&]( auto& row ) {
				row.key = user;
				row.first_name = first_name;
				row.last_name = last_name;
				row.street = street;
				row.city = city;
				row.state = state;
			});
		}
```
	- the updated code is
```cpp
		else {
			// check whether the new data is same as stored
			check((it->first_name != first_name) && (it->last_name != last_name) && (it->street != street) && (it->city != city) && (it->state != state), "All data is same as stored");

			// Now, modify the new data
			addresses.modify(it, user, [&]( auto& row ) {
				row.key = user;
				row.first_name = first_name;
				row.last_name = last_name;
				row.street = street;
				row.city = city;
				row.state = state;
			});
		}

```
	- Now, pushing the same data gives this output
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: first_name must be different than stored one.
pending console output: get_self(): cabeos1test2 | get_first_receiver(): cabeos1test2 | get_first_receiver() value: 4723900389413761568 |
```

## Compile
* [Part A, B, C] Compile the contract
```console
....../base/addressbook
$ eosio-cpp addressbook.cpp -o addressbook.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <upsert> does not have a ricardian contract
Warning, action <erase> does not have a ricardian contract
```

* [Part D] Compile the contract
	- `abcounter`
```console
$ eosio-cpp abcounter.cpp -o abcounter.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <count> does not have a ricardian contract
```
	- `addressbook`
```console
$ eosio-cpp addressbook.cpp -o addressbook.wasm -I ../abcounter
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <upsert> does not have a ricardian contract
Warning, action <erase> does not have a ricardian contract
Warning, action <deleteall> does not have a ricardian contract
Warning, action <notify> does not have a ricardian contract
```

## Deploy
* Deploy the contract
	- Here, you always need the permission of contract account
```console
....../base/addressbook
$ cleost set contract cabeos1test2 ./ -p cabeos1test2@active
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/addressbook/addressbook.wasm...
Publishing contract...
executed transaction: df6f24adf93e7368109c9b8b5793bd40ae22318cf22dd0323e4806e33ec1ff6f  5208 bytes  2254 us
#         eosio <= eosio::setcode               {"account":"cabeos1test2","vmtype":0,"vmversion":0,"code":"0061736d01000000019b01196000006000017f600...
#         eosio <= eosio::setabi                {"account":"cabeos1test2","abi":"0e656f73696f3a3a6162692f312e31000305657261736500010475736572046e616...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Push
* `upsert`: Push the action
	- Here, you always need the permission of user's (person, whose details will be updated) account
	- write user's (`cabeos1user1`) address
```console
....../base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 7de992eacf4844b205d6fb768bd25869b7fc383f4e2bb21cea068970b5712c83  152 bytes  1209 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- look at the account info - `cabeos1test2` (contract) before pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```

	- look at the account info - `cabeos1user2` (user) before pushing the action
```console
$ cleost get account cabeos1user2
created: 2020-06-18T21:23:02.000
permissions:
	 owner     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
		active     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
memory:
	 quota:     5.365 KiB    used:     3.365 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 bytes
	 available:        62.74 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 us
	 available:        58.99 ms
	 limit:            58.99 ms

producers:     <not voted>
```

	- write user's (`cabeos1user2`) address
```console
....../base/addressbook
$ cleost push action cabeos1test2 upsert '["cabeos1user2", "ramesh", "bhattacharya", 34, "2-lane park street", "Kolkata", "West Bengal"]' -p cabeos1user2@active
executed transaction: 7de992eacf4844b205d6fb768bd25869b7fc383f4e2bb21cea068970b5712c83  152 bytes  1209 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","street":"r79, (top floor) \n Sec-74...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

	- look at the account info - `cabeos1test2` (contract) after pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```	

	- look at the account info - `cabeos1user2` (user) after pushing the action
```console
$ cleost get account cabeos1user2
created: 2020-06-18T21:23:02.000
permissions:
	 owner     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
		active     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
memory:
	 quota:     5.365 KiB    used:      3.54 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               161 bytes
	 available:        62.59 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               288 us
	 available:         58.7 ms
	 limit:            58.99 ms

producers:     <not voted>
```

> NOTE:
> - Here, 2 rows of 2 users (`cabeos1user1`, `cabeos1user2`) has been entered.
> - Here, the user (person) who gives the details of the address, is the payer of RAM. Also, the CPU, NET is also consumed, as the permission was taken by the user & not the contract.
> - And this can be set (the RAM payer), while configuring the multi-index table.

* Check for: A user is not able to add other user's data
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user2", "ramesh", "bhattacharya", "2-lane park street", "Kolkata", "West Bengal"]' -p cabeos1user1@active
Error 3090004: Missing required authority
Ensure that you have the related authority inside your transaction!;
If you are currently using 'cleos push action' command, try to add the relevant authority using -p option.
Error Details:
missing authority of cabeos1user2
pending console output:
``` 

* `erase`: Push the action
	- Here, you always need the permission of user's (person, whose details will be erased) account
	- #### EXAMPLE-1: Here, erase the user's data, whose address is not present in the table
	- look at the account info - `cabeos1test2` (contract) before pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```

	- look at the account info - `cabeos1user3` (user) before pushing the action
```console
$ cleost get account cabeos1user3
created: 2020-06-18T21:28:00.500
permissions:
	 owner     1:    1 EOS4yCYGzJAo5sTGPtL8mGS2TgfLagykrodBWGaDApNRY8KWfHJ75
		active     1:    1 EOS4yCYGzJAo5sTGPtL8mGS2TgfLagykrodBWGaDApNRY8KWfHJ75
memory:
	 quota:     5.365 KiB    used:     3.365 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 bytes
	 available:        62.74 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 us
	 available:        58.99 ms
	 limit:            58.99 ms

producers:     <not voted>
```

	- Now, push the action. So, there is an Error!, as the record doesn't exist.
```console
....../base/addressbook
$ cleost push action cabeos1test2 erase '["cabeos1user3"]' -p cabeos1user3@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: Record doesn't exist!
pending console output:         ]
```

	- look at the account info - `cabeos1test2` (contract) after pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```	

	- look at the account info - `cabeos1user3` (user) after pushing the action
```console
$ cleost get account cabeos1user3
created: 2020-06-18T21:28:00.500
permissions:
	 owner     1:    1 EOS4yCYGzJAo5sTGPtL8mGS2TgfLagykrodBWGaDApNRY8KWfHJ75
		active     1:    1 EOS4yCYGzJAo5sTGPtL8mGS2TgfLagykrodBWGaDApNRY8KWfHJ75
memory:
	 quota:     5.365 KiB    used:     3.365 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 bytes
	 available:        62.74 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:                 0 us
	 available:        58.99 ms
	 limit:            58.99 ms

producers:     <not voted>
```
	- #### EXAMPLE-2: Here, erase the user's data, whose address is present in the table
	- look at the account info - `cabeos1test2` (contract) before pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```

	- look at the account info - `cabeos1user2` (user) before pushing the action
```console
$ cleost get account cabeos1user2
created: 2020-06-18T21:23:02.000
permissions:
	 owner     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
		active     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
memory:
	 quota:     5.365 KiB    used:      3.54 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               161 bytes
	 available:        62.59 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               288 us
	 available:         58.7 ms
	 limit:            58.99 ms

producers:     <not voted>
```

	- Now, push the action. So, it's successful! and the user's (`cabeos1user2`) data is erased.
```console
....../base/addressbook
$ cleost push action cabeos1test2 erase '["cabeos1user2"]' -p cabeos1user2@active
executed transaction: 8970839905b5ebb7a464978563dc212d293b1815006a51539698b6097c1199dd  104 bytes  218 us
#  cabeos1test2 <= cabeos1test2::erase          {"user":"cabeos1user2"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

	- look at the account info - `cabeos1test2` (contract) after pushing the action
```console
$ cleost get account cabeos1test2
created: 2020-06-19T23:32:38.000
permissions:
	 owner     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
		active     1:    1 EOS6RfC8G85q8ZYeota1g8Fb4YpJ2vBxaKBoByzLZEG1qQQCPwvp6
memory:
	 quota:     173.4 KiB    used:     114.7 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:             5.211 KiB
	 available:        57.53 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               739 us
	 available:        58.25 ms
	 limit:            58.99 ms

EOS balances:
	 liquid:           80.0000 EOS
	 staked:            2.0000 EOS
	 unstaking:         0.0000 EOS
	 total:            82.0000 EOS

producers:     <not voted>
```	

	- look at the account info - `cabeos1user2` (user) after pushing the action
```console
$ cleost get account cabeos1user2
created: 2020-06-18T21:23:02.000
permissions:
	 owner     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
		active     1:    1 EOS5oU8s1CX9fRBsqM1PHiuf1L4s1H8BdTxP2Vx1WP5bhoUbWXByu
memory:
	 quota:     5.365 KiB    used:     3.365 KiB

net bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               260 bytes
	 available:        62.49 KiB
	 limit:            62.74 KiB

cpu bandwidth:
	 staked:          1.0000 EOS           (total stake delegated from account to self)
	 delegated:       0.0000 EOS           (total staked delegated to account from others)
	 used:               371 us
	 available:        58.62 ms
	 limit:            58.99 ms

producers:     <not voted>
```

## Table
### Part A: Primary key
* Show the table till now
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
	  "key": "cabeos1user1",
	  "first_name": "abhijit",
	  "last_name": "roy",
	  "street": "r79, (top floor) \n Sec-74",
	  "city": "Mohali",
	  "state": "Punjab"
	},{
	  "key": "cabeos1user2",
	  "first_name": "ramesh",
	  "last_name": "bhattacharya",
	  "street": "2-lane park street",
	  "city": "Kolkata",
	  "state": "West Bengal"
	}
  ],
  "more": false,
  "next_key": ""
}
```
* Now, see the entire table with the ram_payer
```console
$ cleost get table cabeos1test2 cabeos1test2 people --show-payer
{
  "rows": [{
	  "data": {
		"key": "cabeos1user1",
		"first_name": "abhijit",
		"last_name": "roy",
		"street": "r79, (top floor) \n Sec-74",
		"city": "Mohali",
		"state": "Punjab"
	  },
	  "payer": "cabeos1user1"
	},{
	  "data": {
		"key": "cabeos1user2",
		"first_name": "ramesh",
		"last_name": "bhattacharya",
		"street": "2-lane park street",
		"city": "Kolkata",
		"state": "West Bengal"
	  },
	  "payer": "cabeos1user2"
	}
  ],
  "more": false,
  "next_key": ""
}
```
* Show the data of `cabeos1user1` in the table,
```console
$ cleost get table cabeos1test2 cabeos1test2 people --lower cabeos1user1
{
  "rows": [{
	  "key": "cabeos1user1",
	  "first_name": "abhijit",
	  "last_name": "roy",
	  "street": "r79, (top floor) \n Sec-74",
	  "city": "Mohali",
	  "state": "Punjab"
	}
  ],
  "more": false,
  "next_key": ""
}
```
* Show the data in reverse order
```console
$ cleost get table cabeos1test2 cabeos1test2 people -r
{
  "rows": [{
      "key": "cabeos1user2",
      "first_name": "ramesh",
      "last_name": "bhattacharya",
      "street": "2-lane park street",
      "city": "Kolkata",
      "state": "West Bengal"
    },{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "street": "r79, (top floor) \n Sec-74",
      "city": "Mohali",
      "state": "Punjab"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the table till now. Here, one user's data is erased.
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
	  "key": "cabeos1user1",
	  "first_name": "abhijit",
	  "last_name": "roy",
	  "street": "r79, (top floor) \n Sec-74",
	  "city": "Mohali",
	  "state": "Punjab"
	}
  ],
  "more": false,
  "next_key": ""
}
```
* Show the data of `cabeos1user2` in the table,
```console
$ cleost get table cabeos1test2 cabeos1test2 people --lower cabeos1user2
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```
* Show the table data in JSON binary
```console
$ cleost get table cabeos1test2 cabeos1test2 people --binary
{
  "rows": [
    "10aec23a60aa8e4107616268696a697403726f79197237392c2028746f7020666c6f6f7229200a205365632d3734064d6f68616c690650756e6a6162",
    "20aec23a60aa8e410672616d6573680c62686174746163686172796112322d6c616e65207061726b20737472656574074b6f6c6b6174610b576573742042656e67616c"
  ],
  "more": false,
  "next_key": ""
}
```

### Part B: Secondary key
* Show the table after introducing the secondary key
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "age": 27,
      "street": "r79, (top floor) \n Sec-74",
      "city": "Mohali",
      "state": "Punjab"
    },{
      "key": "cabeos1user2",
      "first_name": "ramesh",
      "last_name": "bhattacharya",
      "age": 37,
      "street": "2-lane park street",
      "city": "Kolkata",
      "state": "West Bengal"
    }
  ],
  "more": false,
  "next_key": ""
}
```

* Show the table with max. age = 30. Here, `--index 2` indicates the secondary index
```console
$ cleost get table cabeos1test2 cabeos1test2 people --upper 30 --key-type i64 --index 2
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "age": 27,
      "street": "r79, (top floor) \n Sec-74",
      "city": "Mohali",
      "state": "Punjab"
    }
  ],
  "more": false,
  "next_key": ""
}
```

* Show the table with max. age = 37 (includes). Here, it includes the row with age == 37. Basically, it means "37 & below"
```console
$ cleost get table cabeos1test2 cabeos1test2 people --upper 37 --key-type i64 --index 2
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "age": 27,
      "street": "r79, (top floor) \n Sec-74",
      "city": "Mohali",
      "state": "Punjab"
    },{
      "key": "cabeos1user2",
      "first_name": "ramesh",
      "last_name": "bhattacharya",
      "age": 37,
      "street": "2-lane park street",
      "city": "Kolkata",
      "state": "West Bengal"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Push action `modifybyage` to modify the record by age:
	- Show the table before any modification
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "age": 27,
      "street": "Khandwala road",
      "city": "Ludhiana",
      "state": "Punjab"
    }
  ],
  "more": false,
  "next_key": ""
}
```
	- Error-1: w/o permission.
```console
$ cleost push action cabeos1test2 modifybyage '[27, "Jalandhar"]'
Error 3040003: Transaction should have at least one required authority
Error Details:
transaction must have at least one authorization
```

	> NOTE: Even if `require_auth()` not added in the code, still the user's permission has to be provided during modification

	- Modify the table
```console
$ cleost push action cabeos1test2 modifybyage '[27, "Bhatinda"]' -p cabeos1user1@active
executed transaction: 74ecea86cddb240d387a86fa4fac010cc28378e71beb8d05ff1aa80114a660e4  112 bytes  867 us
#  cabeos1test2 <= cabeos1test2::modifybyage    {"age":27,"city":"Bhatinda"}
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully modified record to addressbook. Fields chang...
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user1","type":"modify"}
#  cabeos1user1 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully modified record to addressbook. Fields chang...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- Show the table after modification
```console
$ cleost get table cabeos1test2 cabeos1test2 people
{
  "rows": [{
      "key": "cabeos1user1",
      "first_name": "abhijit",
      "last_name": "roy",
      "age": 27,
      "street": "Khandwala road",
      "city": "Bhatinda",
      "state": "Punjab"
    }
  ],
  "more": false,
  "next_key": ""
}
```


## Inline actions to action in same contract
* Added an inline action `send_summary` to the user as a transaction receipt
```cpp
	void send_summary(name user, string msg) {
		action(
			permission_level(get_self(), "active"_n), 
			get_self(),
			"notify"_n,
			std::make_tuple(user, name{user}.to_string() + msg)
			).send();
	}
```
	- define `ACTION notify()` & `send_summary()` with the same params
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user3", "Gurvinder", "Dhillon", 54, "Dwarka, Sec-12", "Delhi", "Delhi"]' -p cabeos1user3@active
executed transaction: 442eea8e8528695df51af5ac9300a1509737cc5de0387c8f1be4c57e22ec37b8  160 bytes  701 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user3","first_name":"Gurvinder","last_name":"Dhillon","age":54,"street":"Dwarka, Sec...
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user3","msg":"cabeos1user3 successfully emplaced record to addressbook"}
#  cabeos1user3 <= cabeos1test2::notify         {"user":"cabeos1user3","msg":"cabeos1user3 successfully emplaced record to addressbook"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* You can check the action by entering in the browser `https://junglehistory.cryptolions.io/v2/history/get_actions?account=cabeos1user3`
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
- Observations in actions response
	+ actions are sorted by latest added
	+ Here, 2 actions are recorded, 1st - upsert action, 2nd - notify action
	+ The timestamp is same in both the case.
	+ Also, the Block no. is same.
	+ Also, the transaction id is same.  

## Inline actions to action in different contract
* The action_wrapper is written like. This is defined in `abcounter.cpp`
```cpp
...
...
using count_action = action_wrapper<"count"_n, &abcounter::count>;
...
...
```
* The action constructor is like this:
```cpp
void increment_counter(name user, string type) {
	abcounter::count_action count("bhub1counter"_n, {get_self(), "active"_n});
	count.send();
}
```
* Instead this can also be written like this w/o action_wrapper:
```cpp
void increment_counter(name user, string type) {
	action(
			permission_level{get_self(), "active"_n},
			"bhub1counter"_n,
			"count"_n,
			std::make_tuple(user, type)
		).send();
}
```
* Compile & deploy the `abcounter` contract to `bhub1counter` account.
* Recompile & redeploy the `addressbook` contract to `cabeos1test2` account
	- `$ eosio-cpp addressbook.cpp -o addressbook.wasm -I ../abcounter/`
* View the `counts` table before pushing any data
```console
$ cleost get table bhub1counter bhub1counter counts
{
  "rows": [],
  "more": false,
  "next_key": ""
}
```
* Push these 2 data by `cabeos1user1` & `cabeos1user2`
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user2", "ramesh", "bhattacharya", 34, "2-lane park street", "Kolkata", "West Bengal"]' -p cabeos1user2@active
executed transaction: 3a429f36d44aae767150aca466d7e7daaa04512f3dd7478baf65ffef7f323297  168 bytes  434 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user2","first_name":"ramesh","last_name":"bhattacharya","age":34,"street":"2-lane pa...
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully emplaced record to addressbook"}
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user2","type":"emplace"}
#  cabeos1user2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully emplaced record to addressbook"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
abhi3700@Abhijit:/mnt/f/Coding/github_repos/eosio-playground/base/addressbook$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "r79, (top floor) \n Sec-74", "Mohali", "Punjab"]' -p cabeos1user1@active
executed transaction: 75872f7d2a2da209def540f1c382ff7c2597ef7311188d6c0272633ef7cbb515  160 bytes  1104 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","age":27,"street":"r79, (top floor) ...
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully emplaced record to addressbook"}
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user1","type":"emplace"}
#  cabeos1user1 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully emplaced record to addressbook"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* View the `counts` table after pushing the data
```console
$ cleost get table bhub1counter bhub1counter counts --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "emplaced": 1,
        "modified": 0,
        "erased": 0
      },
      "payer": "cabeos1test2"
    },{
      "data": {
        "key": "cabeos1user2",
        "emplaced": 1,
        "modified": 0,
        "erased": 0
      },
      "payer": "cabeos1test2"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Push 1 data to just modify the `cabeos1user2` 's age from __"34 -> 35"__
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user2", "ramesh", "bhattacharya", 35, "2-lane park street", "Kolkata", "West Bengal
"]' -p cabeos1user2@active
executed transaction: 82620d9dbb054a691dd7978f773003f784e1af80d0608b7dbfc2aeb32d006654  168 bytes  784 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user2","first_name":"ramesh","last_name":"bhattacharya","age":35,"street":"2-lane pa...
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully modified record to addressbook"}
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user2","type":"modify"}
#  cabeos1user2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully modified record to addressbook"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Now, view the `counts` table after modiying the age of the user
```console
$ cleost get table bhub1counter bhub1counter counts --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "emplaced": 1,
        "modified": 0,
        "erased": 0
      },
      "payer": "cabeos1test2"
    },{
      "data": {
        "key": "cabeos1user2",
        "emplaced": 1,
        "modified": 1,
        "erased": 0
      },
      "payer": "cabeos1test2"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Erase the user (`cabeos1user2`) data:
```console
$ cleost push action cabeos1test2 erase '["cabeos1user2"]' -p cabeos1user2@active
executed transaction: d19b2b6518bf72f6ad897780504078458ba79ac2d3aaa77e61b70fcacbf8221a  104 bytes  279 us
#  cabeos1test2 <= cabeos1test2::erase          {"user":"cabeos1user2"}
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully erased record to addressbook"}
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user2","type":"erase"}
#  cabeos1user2 <= cabeos1test2::notify         {"user":"cabeos1user2","msg":"cabeos1user2 successfully erased record to addressbook"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Now, view the `counts` table after erasing the user (`cabeos1user2`) data:
```console
$ cleost get table bhub1counter bhub1counter counts --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "emplaced": 1,
        "modified": 0,
        "erased": 0
      },
      "payer": "cabeos1test2"
    },{
      "data": {
        "key": "cabeos1user2",
        "emplaced": 1,
        "modified": 1,
        "erased": 1
      },
      "payer": "cabeos1test2"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Now, let's try to push the `count` action otherwise. You will find that it would give error saying `"missing authority of cabeos1test2"`
```console
$ cleost push action bhub1counter count '["cabeos1user1", "modify"]' -p cabeos1user1@active
Error 3090004: Missing required authority
Ensure that you have the related authority inside your transaction!;
If you are currently using 'cleos push action' command, try to add the relevant authority using -p option.
Error Details:
missing authority of cabeos1test2
pending console output:
```
	- Wonderful! Since we require_auth for name("cabeos1test2"), only the addressbook contract can successfully execute this action, the call by `cabeos1user1` to fudge the numbers had no affect on the table.
* You can also view the actions forwarded as receipt to the respective users who pushes the action `cabeos1user1`, `cabeos1user2`, `cabeos1user3`
* Now, add a feature to see the field changes in the actions memo. E.g if `street`, `city` are changed, then in the action of the user, these field changes should be visible in the message.
	- add this code snippet
```cpp
			string changes = "";
			addresses.modify(it, user, [&]( auto& row ) {

				if (row.first_name != first_name){				
					row.first_name = first_name;
					changes += "first name ";
				}				
				if(row.last_name != last_name) {
					row.last_name = last_name;
					changes += "last name ";
				}
				if(row.age != age) {
					row.age = age;
					changes += "age ";
				}
				if(row.street != street) {
					row.street = street;
					changes += "street ";
				}
				if(row.city != city) {
					row.city = city;
					changes += "city ";
				};
				if(row.state != state) {
					row.state = state;
					changes += "state ";
				}
			});
			if(!changes.empty()) {
				send_summary(user, " successfully modified record to addressbook. Fields changed: " + changes);
				increment_counter(user, "modify");
			} else {
				/*
					check((it->first_name != first_name) || (it->last_name != last_name) || (it->age != age) || (it->street != street) || (it->city != city) || (it->state != state), "At least one of all data must be different.");
				*/
				// NOTE: although this code line is not required, because there is already a check in the beginning of the modify like above:
				send_summary(user, " called upsert, but request resulted in no changes.");
			}
```
	- push changes in `street`, `city` of user - `cabeos1user1`
```console
$ cleost push action cabeos1test2 upsert '["cabeos1user1", "abhijit", "roy", 27, "Khandwala road", "Ludhiana", "Punjab"]' -p cabeos1user1@active
executed transaction: a96b4c0d53f0e3f060862175475ba22c1b198057e969bd3e2f49f25fce3564da  152 bytes  264 us
#  cabeos1test2 <= cabeos1test2::upsert         {"user":"cabeos1user1","first_name":"abhijit","last_name":"roy","age":27,"street":"Khandwala road","...
#  cabeos1test2 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully modified record to addressbook. Fields chang...
#  bhub1counter <= bhub1counter::count          {"user":"cabeos1user1","type":"modify"}
#  cabeos1user1 <= cabeos1test2::notify         {"user":"cabeos1user1","msg":"cabeos1user1 successfully modified record to addressbook. Fields chang...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- View the `people` table to see modified data
```console
$ cleost get table cabeos1test2 cabeos1test2 people --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "first_name": "abhijit",
        "last_name": "roy",
        "age": 27,
        "street": "Khandwala road",
        "city": "Ludhiana",
        "state": "Punjab"
      },
      "payer": "cabeos1user1"
    }
  ],
  "more": false,
  "next_key": ""
}
```
	- View the `counts` table to see modify no.
```console
$ cleost get table bhub1counter bhub1counter counts --show-payer
{
  "rows": [{
      "data": {
        "key": "cabeos1user1",
        "emplaced": 1,
        "modified": 1,
        "erased": 0
      },
      "payer": "cabeos1test2"
    },{
      "data": {
        "key": "cabeos1user2",
        "emplaced": 1,
        "modified": 1,
        "erased": 1
      },
      "payer": "cabeos1test2"
    }
  ],
  "more": false,
  "next_key": ""
}
```
## References
* [Part A](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/data-persistence/)
* [Part B](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/secondary-indices)
* [Part C](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/adding-inline-actions)
* [Part D](https://developers.eos.io/welcome/latest/getting-started/smart-contract-development/inline-action-to-external-contract)