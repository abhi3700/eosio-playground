'''
    About
    =====
    - cabeos1user1 transfer token to cabeos1uer2
    - show the txn_id of the successful transaction
  
'''

# import sys
import json
import binascii
import requests as r
from getpass import getpass
from datetime import datetime, timedelta
from ueosio import sign_tx, DataStream, get_expiration, get_tapos_info, build_push_transaction_body

chain_api_url = "https://jungle3.cryptolions.io:443"

### example tx
tx = {"delay_sec":0,"max_cpu_usage_ms":0,"actions":[{"account":"eosio.token","name":"transfer","data":{"from":"cabeos1user1","to":"cabeos1user2","quantity":"0.0001 EOS","memo":" This tx was sent using µEOSIO"},"authorization":[{"actor":"cabeos1user1","permission":"active"}]}]}

# Get chain info from a working api node
info = r.get(f'{chain_api_url}/v1/chain/get_info').json()
ref_block_num, ref_block_prefix = get_tapos_info(info['last_irreversible_block_id'])
chain_id = info['chain_id']

# package transaction
data = tx['actions'][0]['data']
ds = DataStream()
ds.pack_name(data['from'])
ds.pack_name(data['to'])
ds.pack_asset(data['quantity'])
ds.pack_string(data['memo'])

tx['actions'][0]['data'] = binascii.hexlify(ds.getvalue()).decode('utf-8')

tx.update({
    "expiration": get_expiration(datetime.utcnow(), timedelta(minutes=15).total_seconds()),
    "ref_block_num": ref_block_num,
    "ref_block_prefix": ref_block_prefix,
    "max_net_usage_words": 0,
    "max_cpu_usage_ms": 0,
    "delay_sec": 0,
    "context_free_actions": [],
    "transaction_extensions": [],
    "context_free_data": []
})

# enter private key of the account
# auth = tx['actions'][0]['authorization'][0]
# private_key = getpass("Enter private key for %s@%s: " % (auth['actor'], auth['permission']))
private_key = "5JWe3zbNL1JJocbUZ67ta6iwXV7mKs7w5chPENfJzVgfVRiU9nm"

# Sign transaction
tx_id, tx = sign_tx(
   chain_id,
   tx,
   private_key
)
ds = DataStream()
ds.pack_transaction(tx)
packed_trx = binascii.hexlify(ds.getvalue()).decode('utf-8')
tx = build_push_transaction_body(tx['signatures'][0], packed_trx)

# Push transaction
res = r.post(f'{chain_api_url}/v1/chain/push_transaction', json=tx)
res_json = res.json()

print(res.status_code)

if(res.status_code == 202):       # successfully posted for POST method
  print(res_json['transaction_id'])
else:                             # code: 500, Internal Server Error
  # print(res_json)
  print(res_json['error']['details'][0]['message'])
