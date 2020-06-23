## RAM Table
* The table looks like this
| person_ac | first_name | last_name | state |
|---|---|---|---|
|cabeos1user1|Abhijit|Roy|Punjab|
|cabeos1user2|Abhijit|Bhattacharyya|West Bengal|
|cabeos1user3|Abhijit|Bhattacharyya|Karnataka|
|cabeos1user4|Ramesh|Bhattacharyya|West Bengal|
* Here, No 2 or more users can enter the same info. (`first_name`, `last_name`, `state`).


## Compile
```console
$ eosio-cpp tabletest1.cpp -o tabletest1.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <creatify> does not have a ricardian contract
Warning, action <erase> does not have a ricardian contract
```

## Deploy
```console
$ cleost set contract bhubtabtes11 ./ -p bhubtabtes11@active
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/tabletest1/tabletest1.wasm...
Publishing contract...
executed transaction: f98cf60fc1e3d3079f75861ed6ac6e6807b6138ab458fd6d63c581c27d8fc270  5176 bytes  674 us
#         eosio <= eosio::setcode               {"account":"bhubtabtes11","vmtype":0,"vmversion":0,"code":"0061736d01000000019901196000006000017f600...
#         eosio <= eosio::setabi                {"account":"bhubtabtes11","abi":"0e656f73696f3a3a6162692f312e310003086372656174696679000409706572736...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Push
* user1
```console
$ cleost push action bhubtabtes11 creatify '["cabeos1user1", "Abhijit", "Roy", "Punjab"]' -p cabeos1user1@active
executed transaction: b98336cbbfcdd37939de3434142ccc5f6d09b436276fa34ec38127a94347f0c4  120 bytes  268 us
#  bhubtabtes11 <= bhubtabtes11::creatify       {"person_ac":"cabeos1user1","first_name":"Abhijit","last_name":"Roy","state":"Punjab"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* user2
	- 1st time
```console
$ cleost push action bhubtabtes11 creatify '["cabeos1user2", "Abhijit", "Bhattacharyya", "West Bengal"]' -p cabeos1user2@active
executed transaction: 0b2fcf42a35d9d654267093c0a59d2ff6e5b68f63dc99ada26bdbaddaadc7df8  136 bytes  249 us
#  bhubtabtes11 <= bhubtabtes11::creatify       {"person_ac":"cabeos1user2","first_name":"Abhijit","last_name":"Bhattacharyya","state":"West Bengal"...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- 2nd time
```console
$ cleost push action bhubtabtes11 creatify '["cabeos1user2", "Abhijit", "Bhattacharyya", "West Bengal"]' -p cabeos1user2@active
Error 3050003: eosio_assert_message assertion failure
Error Details:
assertion failure with message: Sorry! All info same as stored
pending console output:
```
* user3
```console
$ cleost push action bhubtabtes11 creatify '["cabeos1user3", "Abhijit", "Bhattacharyya", "Karnataka"]' -p cabeos1user3@active
executed transaction: 4feeda4360f8c22f074068c30f5ad00d30cc4ab22e6f2923789f22c17fb27ace  136 bytes  647 us
#  bhubtabtes11 <= bhubtabtes11::creatify       {"person_ac":"cabeos1user3","first_name":"Abhijit","last_name":"Bhattacharyya","state":"Karnataka"}
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Table
* Show all data stored with ram_payer
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --show-payer
{
  "rows": [{
      "data": {
        "person_ac": "cabeos1user1",
        "first_name": "Abhijit",
        "last_name": "Roy",
        "state": "Punjab"
      },
      "payer": "cabeos1user1"
    },{
      "data": {
        "person_ac": "cabeos1user2",
        "first_name": "Abhijit",
        "last_name": "Bhattacharyya",
        "state": "West Bengal"
      },
      "payer": "cabeos1user2"
    },{
      "data": {
        "person_ac": "cabeos1user3",
        "first_name": "Abhijit",
        "last_name": "Bhattacharyya",
        "state": "Karnataka"
      },
      "payer": "cabeos1user3"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the data in reverse order of pushing data
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people -r
{
  "rows": [{
      "person_ac": "cabeos1user3",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "Karnataka"
    },{
      "person_ac": "cabeos1user2",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "West Bengal"
    },{
      "person_ac": "cabeos1user1",
      "first_name": "Abhijit",
      "last_name": "Roy",
      "state": "Punjab"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the record of `cabeos1user1` & below (pushed after). Here, limit 3 bcoz, max. no. of rows (or records) inserted is 3 here.
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --lower cabeos1user1 --limit 3
{
  "rows": [{
      "person_ac": "cabeos1user1",
      "first_name": "Abhijit",
      "last_name": "Roy",
      "state": "Punjab"
    },{
      "person_ac": "cabeos1user2",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "West Bengal"
    },{
      "person_ac": "cabeos1user3",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "Karnataka"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the record of `cabeos1user2` & below (pushed after)
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --lower cabeos1user2 --limit 3
{
  "rows": [{
      "person_ac": "cabeos1user2",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "West Bengal"
    },{
      "person_ac": "cabeos1user3",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "Karnataka"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the record of `cabeos1user2` & above (pushed before)
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --upper cabeos1user2 --limit 3
{
  "rows": [{
      "person_ac": "cabeos1user1",
      "first_name": "Abhijit",
      "last_name": "Roy",
      "state": "Punjab"
    },{
      "person_ac": "cabeos1user2",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "West Bengal"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the record of `cabeos1user3` & below (pushed after)
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --lower cabeos1user3 --limit 3
{
  "rows": [{
      "person_ac": "cabeos1user3",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "Karnataka"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* Show the record of `cabeos1user3` & above (pushed before)
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --upper cabeos1user3 --limit 3
{
  "rows": [{
      "person_ac": "cabeos1user1",
      "first_name": "Abhijit",
      "last_name": "Roy",
      "state": "Punjab"
    },{
      "person_ac": "cabeos1user2",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "West Bengal"
    },{
      "person_ac": "cabeos1user3",
      "first_name": "Abhijit",
      "last_name": "Bhattacharyya",
      "state": "Karnataka"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* 1st row of the record of `cabeos1user3` & above (pushed before)
```console
$ cleost get table bhubtabtes11 bhubtabtes11 people --upper cabeos1user3 --limit 1
{
  "rows": [{
      "person_ac": "cabeos1user1",
      "first_name": "Abhijit",
      "last_name": "Roy",
      "state": "Punjab"
    }
  ],
  "more": true,
  "next_key": "4723900389437648416"
}
```