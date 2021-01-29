# =================================================================
# Setup your local DApp development environment sin CLI
# =================================================================
# open bash file
nano ~/.bashrc

# -----------------------------------------------------------------
# Refer RPI API for different networks 
# source: https://github.com/abhi3700/My_Learning_EOS/blob/master/README.md
# EOS Mainnet
alias cleosm='cleos -u https://eos.greymass.com'

# EOS Testnet | Jungle3                                                                                                                                                     
alias cleost='cleos -u http://jungle3.cryptolions.io:80'

# WAX Mainnet
alias cleoswm='cleos -u https://chain.wax.io/'                                                                                                                              

# WAX Testnet
alias cleoswt='cleos -u https://api.waxtest.greeneosio.com/'
# -----------------------------------------------------------------
# call source by executing
source ~/.bashrc

# check wax network
cleoswt get info