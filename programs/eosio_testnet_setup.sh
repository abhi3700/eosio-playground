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


# Powerup your eosio account on Jungle
# M-1:
#  - visit here: https://monitor3.jungletestnet.io/#powerup
#  - enter your account & powerup

# M-2:
#  - visit here: hhttps://jungle.bloks.io/
#  - login/add account using Anchor wallet (PC- desktop, Mobile)
#  - Then, visit here: https://jungle3.bloks.io/wallet/powerup
#  - give the amount of CPU or NET or both & then authorize on Anchor wallet & then the account is powered up.