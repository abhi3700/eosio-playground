'''
    Shows a balance(s) i.e. multiple tokens from a contract's table
'''
import json

import asyncio
from aioeos import EosAccount, EosJsonRpc, EosTransaction
from aioeos import types

from aioeos.exceptions import EosAccountDoesntExistException
from aioeos.exceptions import EosAssertMessageException
from aioeos.exceptions import EosDeadlineException
from aioeos.exceptions import EosRamUsageExceededException
from aioeos.exceptions import EosTxCpuUsageExceededException
from aioeos.exceptions import EosTxNetUsageExceededException

from input import *

# def validate(j):
#     try:
#         return json.load(j) # put JSON-data to a variable
#     except json.decoder.JSONDecodeError:
#         print("Invalid JSON") # in case json is invalid
#     else:
#         print("Valid JSON") # in case json is valid

async def balance(
        from_id,
        # chat
    ):
    rpc = EosJsonRpc(url=Chain_URL)
    table_response = await rpc.get_table_rows(
                            code=tip_eosio_ac,
                            scope= tip_eosio_ac, 
                            table=tip_table, 
                            lower_bound= from_id, 
                            upper_bound= from_id
                        )
    
    table_response = str(table_response).replace("\'", "\"")
    table_response = table_response.replace("False", "false")       # As False is invalid in JSON, so replace with false
    # print(table_response)
    
    for r in json.loads(table_response)['rows'][0]["balances"]:
        prec, sym_name = r["key"]["sym"].split(",")
        # print(f'token precision: {prec}')                 # precision
        # print(f'token sym_name: {sym_name}')              # symbol name
        # print(f'val: {r["value"]/10**int(prec)}\n\n')     # exact value
        print(f'{r["value"]/10**int(prec)} {sym_name}')     # result e.g. 2.0 EOS

if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(balance(410894301))