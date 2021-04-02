from aioeos import EosJsonRpc, EosTransaction
from aioeos.contracts import eosio_token


rpc = EosJsonRpc(url='http://jungle3.cryptolions.io:80')
block = await rpc.get_head_block()

account = EosAccount(name="toecom111111", private_key='5HxdvNEnvQvDFZdKzZmXDj6YpVRV3GJzN9mVV627usbcr5m5zS5')

transaction = EosTransaction(
   ref_block_num=block['block_num'] & 65535,
   ref_block_prefix=block['ref_block_prefix'],
   actions=[
      eosio_token.transfer(
         from_addr=account.name,
         to_addr='toecom11112',
         quantity='1.0000 EOS',
         authorization=[account.authorization('active')]
      )
   ]
)
await rpc.sign_and_push_transaction(transaction, keys=[account.key])