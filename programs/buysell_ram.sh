# permission is payer_ac@active by default.
# cleos system buyram <payer_ac> <to_ac> <amount_in_EOS> -p <payer_ac>@<permission>
cleos system buyram gpkbattlesco gbuser111112 "0.1 EOS" -p gpkbattlesco@active

# cleos system buyram <payer_ac> <to_ac> -b <amount_in_bytes> -p <payer_ac>@<permission>
cleos system buyram hello1111111 hello1111111 -b 100 -p hello1111111@active

# cleos system buyram <payer_ac> <to_ac> -k <amount_in_kbytes> -p <payer_ac>@<permission>
cleos system buyram hello1111111 hello1111111 -k 10 -p hello1111111@active