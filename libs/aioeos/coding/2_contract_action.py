'''
    M-1: Using Python -> User-A (with telegram_id) tips EOSIO tokens (EOS, FUTBOL,...) to User-B (with telegram_id) from balances maintained in tippertipper contract ac
    M-2: Using cleos -> cleost push action tippertipper tip '["145624324", "768743431", "ali67", "ali68", "0.0001 FUTBOL", "tip for enjoy"]' -p tippertipper@active

    References: https://github.com/ulamlabs/aioeos/blob/master/aioeos/contracts/eosio_token.py
'''

import asyncio

from aioeos import EosAccount, EosJsonRpc, EosTransaction
from aioeos.contracts import eosio_token
from aioeos.exceptions import EosAssertMessageException
from aioeos import types

import json

async def tip():
    contract_account = EosAccount(
      name='tippertipper',
      private_key='5KUbt8wFoadvmCc1zu3Q2VgKNKBxWKNyJYnmpBb4W3AVp5EDx6s'
    )

    action = types.EosAction(
        account='tippertipper',
        name='tip',
        authorization=[contract_account.authorization('active')],
        data={
            'from_id': '145624324',
            'to_id': '768743431',
            'from_username': 'ali67',
            'to_username': 'ali68',
            'quantity': '0.0001 FUTBOL',
            'memo': 'tip for enjoy'
        }
    )

    rpc = EosJsonRpc(url='http://jungle3.cryptolions.io:80')
    block = await rpc.get_head_block()

    transaction = EosTransaction(
      ref_block_num=block['block_num'] & 65535,
      ref_block_prefix=block['ref_block_prefix'],
      actions=[action]
    )

    response = await rpc.sign_and_push_transaction(
      transaction, keys=[contract_account.key]
    )
    print(response)             # print the full response after SUCCESS
    
    response = str(response).replace("\'", "\"")            # replace single quotes (') with double quotes (") to make it as valid JSON & then extract the 'message' value.
    # print(response)               # print the full response after replacing single with double quotes
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
    asyncio.get_event_loop().run_until_complete(tip())

# FAIL: to check this, parse "0.001 FUTBOL" instead of "0.0001 FUTBOL" i.e. precision error.
except EosAssertMessageException as e:
    e = str(e).replace("\'", "\"")            # replace single quotes (') with double quotes (") to make it as valid JSON & then extract the 'message' value.
    # print(f'{e}')      # print full error dict
    print(f"{json.loads(e)['details'][0]['message']}")          # print the message


