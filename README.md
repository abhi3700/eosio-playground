# EOSIO Playground
This is my playground for **EOS.IO software on EOS Blockchain.**

Dependency repositories: 
* [x] [eos](https://github.com/EOSIO/eos) - `cleos`, `nodeos`, `keosd`
* [x] [eosio.cdt](https://github.com/EOSIO/eosio.cdt) - `eosio-cpp`,...
* [x] [eosio.contracts](https://github.com/EOSIO/eosio.contracts) - `eosio.bios`, `eosio.msig`, `eosio.system`, `eosio.token`, `eosio.wrap`
* [x] [Oraclize EOS API header](https://github.com/oraclize/eos-api)

## Installation
### System: 
* Linux
* WSL
* Mac

#### Follow the steps [for Compiler i.e. eosio-cpp, ....]
* M-1 (from setup file)
  - download latest (stable) version of `.deb` file from [here](https://github.com/EOSIO/eosio.cdt/releases).
  - in the bash terminal
  ```
  $ wget https://github.com/eosio/eosio.cdt/releases/download/v1.5.0/eosio.cdt-1.5.0-1_amd64.deb
  $ sudo apt install ./eosio.cdt-1.5.0-1_amd64.deb
  ```
* M-2 (from scratch)
  - in the bash terminal
  ```
  $ git clone --recursive https://github.com/eosio/eosio.cdt
  $ cd eosio.cdt
  $ ./build.sh
  $ sudo ./install.sh
  ```

## Setup for Dependency Libraries
Follow the steps:

### Part A: EOSIO libraries
* Repository: [eosio.cdt](https://github.com/EOSIO/eosio.cdt)
*	copy and paste the following folders from 
	Source: `eosio.cdt` repo:-
	goto the "libraries" folder:
	- boost 
	- eosiolib
	Destination: `eosio-playground`
* Commands for creating folder:
	- boost: `svn checkout https://github.com/EOSIO/eosio.cdt/trunk/libraries/boost/include/boost`
	- eosiolib: `svn checkout https://github.com/EOSIO/eosio.cdt/trunk/libraries/eosiolib`
* Commands for updating folder:
	- boost: 
		+ `cd boost`
		+ `svn update`
	- eosiolib:
		+ `cd eosiolib`
		+ `svn update`

### Part B: EOSIO system contracts
* Repository: [eosio.contracts](https://github.com/EOSIO/eosio.contracts)
* copy and paste the following folders from 
	Source: `eosio.contracts` git repo:-
	goto the "libraries" folder:
	- eosio.bios
	- eosio.msig
	- eosio.system
	- eosio.token
	- eosio.wrap
* Commands for creating folder:
	- eosio.bios: `svn checkout https://github.com/EOSIO/eosio.contracts/trunk/eosio.bios`
	- eosio.msig: `svn checkout https://github.com/EOSIO/eosio.contracts/trunk/eosio.msig`
	- eosio.system: `svn checkout https://github.com/EOSIO/eosio.contracts/trunk/eosio.system`
	- eosio.token: `svn checkout https://github.com/EOSIO/eosio.contracts/trunk/eosio.token`
	- eosio.wrap: `svn checkout https://github.com/EOSIO/eosio.contracts/trunk/eosio.wrap`
* Commands for updating folder:
	- eosio.bios: 
		+ `cd eosio.bios`
		+ `svn update`
	- eosio.msig:
		+ `cd eosio.msig`
		+ `svn update`
	- eosio.system:
		+ `cd eosio.system`
		+ `svn update`
	- eosio.token:
		+ `cd eosio.token`
		+ `svn update`
	- eosio.wrap:
		+ `cd eosio.wrap`
		+ `svn update`

### Part C: EOS API Header
* Repository: [eos-api](https://github.com/oraclize/eos-api)
* create folder inside `eosio-playground` cloned repo.: `git submodule add https://github.com/oraclize/eos-api.git eos-api`
* update the repo. inside `eosio-playground` cloned repo.: 
  - M-1: `git submodule update`
  - M-2:
    + `cd eos-api`
    + `git pull`

##### NOTE: Make a bash file for all the `git` & `svn` operations - [setup.sh](https://github.com/abhi3700/eosio-playground/blob/master/setup.sh)

## Contracts
* [x] [Quickstart](./quickstart.md)
* [x] [**Hello**](https://github.com/abhi3700/eosio-playground/tree/master/hello)
* [ ] **CRUD**
* [ ] **Todo**
* [ ] **Messenger**
* [ ] **FoodApp**
* [ ] **ShoppingApp**
* [ ] **StakeForMe**: both CPU & NET
* [ ] **Timestamp**
  - https://github.com/sim31/timeos
* **TweetBot**
  - https://github.com/kesar/twitbot
* **OLX**
  - https://github.com/digital-scarcity/equiprental, [YouTube Video](https://www.youtube.com/watch?v=J0SYv-GC3R0)
* **Voting**
  - https://github.com/JackDiSalvatore/shared_contracts/tree/master/contracts/ballot
  - https://github.com/EOSMore/eos-contracts/tree/dev/more.voting [Read first](https://github.com/EOSMore/eos-contracts/blob/dev/README.md)
  - https://github.com/sim31/polleos
* **OTP**
  - https://github.com/eoshackathon/eos_dapp_development_cn/blob/master/docs/randomization.md
  - https://github.com/OracleChain/EOSDACRandom
* **Lottery**
  - https://github.com/jsonsnow/lottery
  - https://github.com/trentlotteryteam/trentLotteryContract
  - https://github.com/lottery100/lottery100/
* **BP Info.**
  - https://github.com/greymass/producerjson

## Commands
* `cleos`: [How to guides](https://developers.eos.io/manuals/eos/latest/cleos/how-to-guides/index)

## EOSIO DApp Tools
* EOSIO SDK for Java - https://github.com/EOSIO/eosio-java
* EOSIO SDK for C++ - https://github.com/EOSIO/eos/blob/master/programs/cleos/main.cpp

## Deploy a contract [on Testnet]
* Ensure you have a wallet created locally
* Create an EOS account with public keys (owner & active)
* Now, link this EOS account with your wallet created by importing the public key using private key (secret to you)
* Now, deploy contract (`.wasm`) to your testnet from wallet by setting e.g. `cabeos1test1@active`