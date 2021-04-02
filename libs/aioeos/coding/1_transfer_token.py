'''
	M-1: Using Python -> Transfer EOS tokens from 'toecom111111' to `toecom111112`
	M-2: Using cleos -> cleost push action eosio.token transfer '["toecom111111", "toecom111112", "1.0000 EOS", "for fun"]' -p toecom111111@active
'''

import asyncio

from aioeos import EosAccount, EosJsonRpc, EosTransaction
from aioeos.contracts import eosio_token
from aioeos.exceptions import EosAssertMessageException

import json

async def example():
	test_account = EosAccount(
	  name='toecom111111',
	  private_key='5JNc3LPSq5hsb8tgi8NPyktQKitUjyZE9UBpaSmTyGDDBVr6h1p'
	)

	action = eosio_token.transfer(
	  from_addr=test_account.name,
	  to_addr='toecom111112',
	  quantity='0.0001 EOS',
	  memo='for fun',
	  authorization=[test_account.authorization('active')]
	)

	rpc = EosJsonRpc(url='http://jungle3.cryptolions.io:80')
	block = await rpc.get_head_block()

	transaction = EosTransaction(
	  ref_block_num=block['block_num'] & 65535,
	  ref_block_prefix=block['ref_block_prefix'],
	  actions=[action]
	)

	response = await rpc.sign_and_push_transaction(
	  transaction, keys=[test_account.key]
	)
	print(response)				# print the full response after SUCCESS
	
	response = str(response).replace("\'", "\"")            # replace single quotes (') with double quotes (") to make it as valid JSON & then extract the 'message' value.
	# print(response)				# print the full response after replacing single with double quotes
	'''
		Here, as the response o/p is not a valid JSON giving error like this:
		Error:
			Parse error on line 1:
			...producer_block_id": None, "receipt": {"s
			-----------------------^
			Expecting 'STRING', 'NUMBER', 'NULL', 'TRUE', 'FALSE', '{', '[', got 'undefined'

		So, capture txn_id by char no. i.e. {"transaction_id": "14e310c6e296560202ec808139d7e1b06901616f35b5c4a36ee0a4f065ec72a6"
	'''
	print(f"\nthe txn_id is: {response[20:84]}")          # print the txn_id for successful transaction

# SUCCESS
try:
	asyncio.get_event_loop().run_until_complete(example())

# FAIL: to check this, parse "1.000 EOS" instead of "1.0000 EOS" i.e. precision error.
except EosAssertMessageException as e:
	e = str(e).replace("\'", "\"")            # replace single quotes (') with double quotes (") to make it as valid JSON & then extract the 'message' value.
	# print(f'{e}')      # print full error dict
	print(f"{json.loads(e)['details'][0]['message']}")          # print the message


