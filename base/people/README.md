# `people` contract
## Account details:
* Network: "Jungle Testnet"
* Contract account: "bhubpeople11"
* Contract name: "people"
* [people.cpp](./people.cpp)
* [people.wasm](./people.wasm)
* [people.abi](./people.abi)

## Compile
```
$ eosio-cpp people.cpp -o people.wasm
Warning, empty ricardian clause file
Warning, empty ricardian clause file
Warning, action <upsert> does not have a ricardian contract
Warning, action <erase> does not have a ricardian contract
Warning, action <readjobctry> does not have a ricardian contract
```

## Deploy
* deploy contract (ABI & WASM)
```console
$ cleost set contract bhubpeople11 ./
Reading WASM from /mnt/f/Coding/github_repos/eosio-playground/base/people/people.wasm...
Publishing contract...
executed transaction: b8aceffa882c85f1d52bc96a421eb7115fd4ab3b668f846181a67a544ee98490  8136 bytes  740 us
#         eosio <= eosio::setcode               {"account":"bhubpeople11","vmtype":0,"vmversion":0,"code":"0061736d0100000001da012060000060047f7f7f7...
#         eosio <= eosio::setabi                {"account":"bhubpeople11","abi":"0e656f73696f3a3a6162692f312e31000405657261736500010475736572046e616...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* Adding eosio.code to permissions (for inline actions)
```
$ cleost set account permission bhubpeople11 active --add-code
executed transaction: 6d3c03dc5fc1d5adce035363216520135740fd270d8525a5b7a515ed9cf1f04a  184 bytes  162 us
#         eosio <= eosio::updateauth            {"account":"bhubpeople11","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[{"key...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

## Testing
### Action - `upsert`
* `cabeos1user1` adds info
```console
$ cleost push action bhubpeople11 upsert '["cabeos1user1", "abhijit", "roy", "engineer", "CL0010234", "india"]' -p cabeos1user1@active
executed transaction: ebd19041c6c92206a226718e095d146cd7afbe2da3072402d963cee9be63f9ef  144 bytes  246 us
#  bhubpeople11 <= bhubpeople11::upsert         {"user":"cabeos1user1","firstname":"abhijit","lastname":"roy","job":"engineer","employee_id":"CL0010...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- View the table
```console
$ cleost get table bhubpeople11 bhubpeople11 people
{
  "rows": [{
      "user": "cabeos1user1",
      "firstname": "abhijit",
      "lastname": "roy",
      "job": "engineer",
      "employee_id": "CL0010234",
      "country": "india"
    }
  ],
  "more": false,
  "next_key": ""
}
```
* `cabeos1user2` adds info
```console
$ cleost push action bhubpeople11 upsert '["cabeos1user2", "abhijit", "bhattacharyya", "engineer", "CL005432", "ukraine"]' -p cabeos1user2@active
executed transaction: 97a99a1a7c48ec4da48616a20db685c37b0a7e1ef91fb7b737bc314404965724  152 bytes  216 us
#  bhubpeople11 <= bhubpeople11::upsert         {"user":"cabeos1user2","firstname":"abhijit","lastname":"bhattacharyya","job":"engineer","employee_i...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `cabeos1user3` adds info
```console
$ cleost push action bhubpeople11 upsert '["cabeos1user3", "deep", "roy", "scientist", "CL005432", "indonesia"]' -p cabeos1user3@active
executed transaction: fd78842862a20e571f8520e07caf0c32418e60ee6d774cb71f6d9d9e79960edd  136 bytes  260 us
#  bhubpeople11 <= bhubpeople11::upsert         {"user":"cabeos1user3","firstname":"deep","lastname":"roy","job":"scientist","employee_id":"CL005432...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `cabeos1user4` adds info
```console
$ cleost push action bhubpeople11 upsert '["cabeos1user4", "sandilya", "chatterjee", "scientist", "CL23545", "india"]' -p cabeos1user4@active
executed transaction: c2d73821d8b4bc81a0405d070bf906ca387508eac0eb7684b8104686cd4f40fb  144 bytes  201 us
#  bhubpeople11 <= bhubpeople11::upsert         {"user":"cabeos1user4","firstname":"sandilya","lastname":"chatterjee","job":"scientist","employee_id...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
* `cabeos1user5` adds info
```console
$ cleost push action bhubpeople11 upsert '["cabeos1user5", "somendra", "mukherjee", "engineer", "CL3545", "india"]' -p cabeos1user5@active
executed transaction: 9c7ffc02bc1701afbcd8fc0bb9a7ec29dd3bde6f7bf129f64df4d10198646f8d  144 bytes  207 us
#  bhubpeople11 <= bhubpeople11::upsert         {"user":"cabeos1user5","firstname":"somendra","lastname":"mukherjee","job":"engineer","employee_id":...
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```

### Action - `readjobctry`
* read all the rows:
```console
$ cleost push action bhubpeople11 readjobcntry '["engineer", "india"]' -p bhubpeople11@active
executed transaction: 9dfe20bdc7335ec3de3997a19bbc282cf701a01b53dbefdee4640c1e6f73538b  112 bytes  276 us
#  bhubpeople11 <= bhubpeople11::readjobcntry   {"job":"engineer","country":"india"}
>> table's size: 5 | The row is: cabeos1user1,abhijit,roy,engineer,CL0010234,india | The row is: cabeos1user5,somendra,mukherjee,engineer,CL3545,india | The row is: cabeos1user2,abhijit,bhattacharyya,engineer,CL005432,ukraine | The row is: cabeos1user4,sandilya,chatterjee,scientist,CL23545,india | The row is: cabeos1user3,deep,roy,scientist,CL005432,indonesia |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- The code snippet used:
```cpp
// M-1: print all the rows as per priority
while(it != job_idx.end()) {
	print("The row is: ", it->user, ",", it->firstname, ",", it->lastname, ",", it->job, ",", it->employee_id, ",", it->country, " | ");
	++it;
}
```

* read table by 2 filters: job, country
```console
$ cleost push action bhubpeople11 readjobcntry '["engineer", "india"]' -p bhubpeople11@active
executed transaction: 162f3bb1d0b67bb9e08604428c242aa0bc7f4c8763c7c6de47976fba6289b215  112 bytes  164 us
#  bhubpeople11 <= bhubpeople11::readjobcntry   {"job":"engineer","country":"india"}
>> table's size: 5 | The row is: cabeos1user1,abhijit,roy,engineer,CL0010234,india | The row is: cabeos1user5,somendra,mukherjee,engineer,CL3545,india |
warning: transaction executed locally, but may not be confirmed by the network yet         ]
```
	- The code snippet used:
```cpp
// M-2: print those rows with "engineer" & "india" values only
while((it != job_idx.end()) && (it->job == "engineer"_n) && (it->country == "india"_n)) {
	print("The row is: ", it->user, ",", it->firstname, ",", it->lastname, ",", it->job, ",", it->employee_id, ",", it->country, " | ");
	++it;
}
```