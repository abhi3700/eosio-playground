'''
		About
		=====
		- fetch table info from eosio - `producers`
		- Table Result
#	
owner (key) total_votes	producer_key	is_active	url	unpaid_blocks	last_claim_time	location	producer_authority
1	alohaeostest	33076211163130298368.00000000000000000	EOS8JTznQrfvYcoFskidgKeKsmPsx3JBMpTo1jsEG2y1Ho6sQhFuL	1	https://www.alohaeos.com/	6684	2021-06-11T20:00:48.000	840	[ "block_signing_authority_v0", { "threshold": 1, "keys": [ { "key": "EOS8JTznQrfvYcoFskidgKeKsmPsx3JBMpTo1jsEG2y1Ho6sQhFuL", "weight": 1 } ] } ]
'''
from ueosio.rpc import Api
import requests as r
import requests as r2

# ===============================================
# EOS Testnet | Jungle
chain_api_url = "https://jungle3.cryptolions.io:443"

chain_info = r.get(f'{chain_api_url}/v1/chain/get_info')
node = Api(f"{chain_api_url}")
if chain_info.status_code == 200: 
	print("producers table in Jungle Testnet-->")

	for r in node.v1.chain.get_table_rows( code="eosio", scope="eosio", table="producers",
		key_type="float64", index_position="2", limit=10, json=True)["rows"]:
		print(r['owner'])
else:
	print("connection error")

# ===============================================
# EOS Mainnet
chain_api_url_2 = "https://api.eosnewyork.io"

chain_info_2 = r2.get(f'{chain_api_url_2}/v1/chain/get_info', verify=False)
# print(chain_info_2.status_code)
node_2 = Api(f"{chain_api_url_2}")
if chain_info_2.status_code == 200: 
	print("producers table in EOS Mainnet-->")

	for r in node_2.v1.chain.get_table_rows( code="eosio", scope="eosio", table="producers",
		key_type="float64", index_position="2", limit=10, json=True)["rows"]:
		print(r['owner'])
else:
	print("connection error")