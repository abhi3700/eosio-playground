'''
		About
		=====
		- fetch table info from oyanftmarket - `accounts`
		- Table Result
		#	owner (key)	balances
		1	1456243456	[ { "key": { "sym": "4,EOS", "contract": "eosio.token" }, "value": 20000 } ]

'''

from ueosio.rpc import Api
import requests as r

# ===============================================
# EOS Testnet | Jungle
chain_api_url = "https://jungle3.cryptolions.io:443"

chain_info = r.get(f'{chain_api_url}/v1/chain/get_info')
node = Api(f"{chain_api_url}")
if chain_info.status_code == 200: 
	print("Account owners & their balances:")
	for r in node.v1.chain.get_table_rows( code="oyanftmarket", scope="oyanftmarket", table="accounts",
		key_type="i64", index_position="1", limit=10, json=True)["rows"]:
		print(f"\towner: {r['owner']} & \n\tbalances:")
		for b in r['balances']:
			prec, sym_name = b["key"]["sym"].split(",")
			# print(f'token precision: {prec}')                 # precision
			# print(f'token sym_name: {sym_name}')              # symbol name
			# print(f'val: {r["value"]/10**int(prec)}\n\n')     # exact value
			print(f'\t\t{b["value"]/10**int(prec)} {sym_name}')     # result e.g. 2.0 EOS

else:
	print("connection error")

'''
Output:
```
Account owners & their balances:
        owner: 1456243456 &
        balances:
                2.0 EOS
```
'''