#!/bin/bash
##########################################################################
# This sets up the dependency libraries from different github repositories.
# NOTE: in case of any unexpected error, try to use `dos2unix <shell-script-file-name.sh>`
##########################################################################
# -----------------------------------------------------------------
# eosiolib
cd libs/
if [[ -d "eosiolib" ]]; then
	# echo "eosiolib folder exist"
	cd eosiolib
	svn update
	cd ../../
else
	# echo "eosiolib folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.cdt/trunk/libraries/eosiolib
	cd ../
fi
# -----------------------------------------------------------------
# eosio.bios
cd libs/contracts/
if [[ -d "eosio.bios" ]]; then
	# echo "eosio.bios folder exist"
	cd eosio.bios
	svn update
	cd ../../../
else
	# echo "eosio.bios folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.contracts/trunk/contracts/eosio.bios
	cd ../../
fi
# -----------------------------------------------------------------
# eosio.msig
cd libs/contracts/
if [[ -d "eosio.msig" ]]; then
	# echo "eosio.msig folder exist"
	cd eosio.msig
	svn update
	cd ../../../
else
	# echo "eosio.bios folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.contracts/trunk/contracts/eosio.msig
	cd ../../
fi
# -----------------------------------------------------------------
# eosio.system
cd libs/contracts/
if [[ -d "eosio.system" ]]; then
	# echo "eosio.system folder exist"
	cd eosio.system
	svn update
	cd ../../../
else
	# echo "eosio.system folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.contracts/trunk/contracts/eosio.system
	cd ../../
fi
# -----------------------------------------------------------------
# eosio.token
cd libs/contracts/
if [[ -d "eosio.token" ]]; then
	# echo "eosio.token folder exist"
	cd eosio.token
	svn update
	cd ../../../
else
	# echo "eosio.token folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.contracts/trunk/contracts/eosio.token
	cd ../../
fi
# -----------------------------------------------------------------
# eosio.wrap
cd libs/contracts/
if [[ -d "eosio.wrap" ]]; then
	# echo "eosio.wrap folder exist"
	cd eosio.wrap
	svn update
	cd ../../../
else
	# echo "eosio.wrap folder NOT exist"
	svn checkout https://github.com/EOSIO/eosio.contracts/trunk/contracts/eosio.wrap
	cd ../../
fi
# -----------------------------------------------------------------
# eos-api
cd libs/
if [[ -d "eos-api" ]]; then
	# echo "eos-api folder exist"
	cd eos-api
	git pull
	cd ../../
else
	# echo "eos-api folder NOT exist"
	git submodule add https://github.com/provable-things/eos-api.git eos-api
	cd ../
fi



