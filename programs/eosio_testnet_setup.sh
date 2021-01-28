# open bash file
nano ~/.bashrc
# calling cleos -u .... as cleost for EOS testnet
alias cleost='cleos -u http://jungle3.cryptolions.io:80'

# call source by executing
source ~/.bashrc

# check wax network
cleost get info