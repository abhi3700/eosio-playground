## Compile
* Compile the contract
```console
....../base/addressbook
$ eosio-cpp addressbook.cpp -o addressbook.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <upsert> does not have a ricardian contract
Warning, action <erase> does not have a ricardian contract
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
$ cleost push action cabeos1test2 upsert '["cabeos1user2", "ramesh", "bhattacharya", "2-lane park street", "Kolkata", "West Bengal"]' -p cabeos1user2@active
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



