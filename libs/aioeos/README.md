## Installation
### Using pip
* `pip install aioeos`

## Coding
* [Submitting your first transaction](https://aioeos.readthedocs.io/en/latest/introduction.html#submitting-your-first-transaction)

## Troubleshooting
### 1. No valid JSON response
* Console output
```console
# no balances for corresponding quantity symbol pair
- `/withdrawmemo tipuser11111 0.0001 TLOS pay_bill`
- /withdrawmemo tipuser11111 0.00001 EOS pay_bill
{"code": 3050003, "name": "eosio_assert_message_exception", "what": "eosio_assert_message assertion failure"
, "details": [{"message": "assertion failure with message: there is no balances available corresponding to t
he parsed quantity symbol for the given from_id.", "file": "cf_system.cpp", "line_number": 14, "method": "eo
sio_assert"}, {"message": "pending console output: ", "file": "apply_context.cpp", "line_number": 143, "meth
od": "exec_one"}]} 

- /withdrawmemo tipuser11117 0.0001 EOS pay_bill
{"code": 3010001, "name": "name_type_exception", "what": "Invalid name", "details": [{"message": "Name conta
ins invalid character: (7) ", "file": "name.hpp", "line_number": 26, "method": "char_to_symbol"}, {"message"
: "", "file": "abi_serializer.cpp", "line_number": 570, "method": "_variant_to_binary"}, {"message": "", "fi
le": "abi_serializer.cpp", "line_number": 570, "method": "_variant_to_binary"}, {"message": "", "file": "abi
_serializer.cpp", "line_number": 584, "method": "_variant_to_binary"}, {"message": "\"{"from_id":410894301,"
from_username":"abhi3700","to_ac":"tipuser11117","quantity":"0.0001 EOS","memo":"pay_bill"}\" is invalid arg
s for action \"withdraw\" code \"tippertipper\". expected \"[{"name":"from_id","type":"uint64"},{"name":"fro
m_username","type":"string"},{"name":"to_ac","type":"name"},{"name":"quantity","type":"asset"},{"name":"memo
","type":"string"}]\"", "file": "chain_plugin.cpp", "line_number": 3396, "method": "abi_json_to_bin"}, {"mes
sage": "code: tippertipper, action: withdraw, args: {"from_id":410894301,"from_username":"abhi3700","to_ac":
"tipuser11117","quantity":"0.0001 EOS","memo":"pay_bill"}", "file": "chain_plugin.cpp", "line_number": 3402,
 "method": "abi_json_to_bin"}]}
```
* Solution:
```python
		try:
			# push txn
			asyncio.get_event_loop().run_until_complete(tip(chat.id, args[0], message.sender.username, "optional", args[1] + " " + args[2], args[3], chat))
		except EosRpcException as e:
			e = str(e).replace("\'", "\"")
			code_idx = e.find('code')
			code_val = int(e[code_idx+7:(code_idx+14)])
			# print(code_idx)
			# print(code_val)
			# print(type(code_val))
			if code_idx != -1:			# found "code" key
				if code_val == 3010001:						# Case-1: invalid name
					chat.send("Sorry! Your EOSIO account name doesn\'t exist on this chain.")
				elif code_val == 3050003:					# Case-1: incorrect quantity or symbol
					chat.send("Sorry! Your EOSIO account doesn\'t have any balances corresponding to parsed quantity symbol pair on this chain.")
				else:
					chat.send("Sorry! Some other Exception occured. Please contact the Bot owner {bot.owner}.")
			else:						# NOT found "code" key
				chat.send("Sorry! No code no. is present in the error. Please contact the Bot owner {bot.owner}.")
```

## References
* Github - https://github.com/ulamlabs/aioeos
* pip - https://pypi.org/project/aioeos/
* Documentation - https://aioeos.readthedocs.io/en/latest/index.html