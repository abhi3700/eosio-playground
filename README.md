# EOSIO Playground
This is my playground for **EOS.IO software on EOS Blockchain.**

Dependency repositories: 
* [x] [eos](https://github.com/EOSIO/eos) - `cleos`, `nodeos`, `keosd`
* [x] [eosio.cdt](https://github.com/EOSIO/eosio.cdt) - `eosio-cpp`,...
* [x] [eosio.contracts](https://github.com/EOSIO/eosio.contracts) - `eosio.bios`, `eosio.msig`, `eosio.system`, `eosio.token`, `eosio.wrap`
* [x] [Oraclize EOS API header](https://github.com/oraclize/eos-api)

## Installation
* System (EOSIO tools & SC toolkit): 
	- Linux (using WSL)
	- Mac
* Editor (ST3 or VSC)

Below is the details for installing both on Linux & Mac OS.

### Linux
#### Follow the steps for EOSIO components - cleos, nodeos, keosd
* M-1 (from setup file)
  - download latest (stable) version of `.deb` file from [here](https://github.com/EOSIO/eosio/releases).
  - Install
	```console
	$ wget https://github.com/eosio/eos/releases/download/v2.0.9/eosio_2.0.9-1-ubuntu-18.04_amd64.deb
	$ sudo apt install ./eosio_2.0.9-1-ubuntu-18.04_amd64.deb
	```
  - Uninstall
```console
$ sudo apt remove eosio
```

* M-2 (from scratch)
  - Install
	```console
	$ git clone --recursive https://github.com/eosio/eos
	$ cd eosio
	$ ./scripts/eosio_build.sh
	$ sudo ./scripts/eosio_install.sh
	```
  - Uninstall
	```console
	$ cd eosio
	$ ./scripts/eosio_build.sh
	$ sudo ./scripts/eosio_install.sh
	```

#### Follow the steps [for Compiler i.e. eosio-cpp, ....]
* M-1 (from setup file)
  - download latest (stable) version of `.deb` file from [here](https://github.com/EOSIO/eosio.cdt/releases).
  - in the bash terminal
	```console
	$ wget https://github.com/eosio/eosio.cdt/releases/download/v1.7.0/eosio.cdt_1.7.0-1-ubuntu-18.04_amd64.deb
	$ sudo apt install ./eosio.cdt_1.7.0-1-ubuntu-18.04_amd64.deb
	```
  - Uninstall
	```console
	$ sudo apt remove eosio.cdt
	```
* M-2 (from scratch)
  - in the bash terminal
	```console
	$ git clone --recursive https://github.com/eosio/eosio.cdt
	$ cd eosio.cdt
	$ ./scripts/eosiocdt_build.sh
	$ sudo ./scripts/eosiocdt_install.sh
	```
  - Uninstall
	```console
	$ cd eosio.cdt
	$ ./scripts/eosiocdt_build.sh
	$ sudo ./scripts/eosiocdt_install.sh
	```

### Mac
#### Follow the steps for EOSIO components - cleos, nodeos, keosd
* [Source](https://github.com/EOSIO/eos#mac-os-x)
* Steps:
	- pre-requisite: Cover [this](https://github.com/abhi3700/my_coding_toolkit/blob/master/mac_for_win.md#3-unable-to-use-software-requiring-x86_64-architecture-on-m1-macbook) first.
	- `ibrew tap eosio/eosio`
	- `ibrew install eosio`

#### Follow the steps [for Compiler i.e. eosio-cpp, ....]
* [Source](https://github.com/EOSIO/eosio.cdt#mac-os-x-brew-install)
* Steps:
	- pre-requisite: Cover [this](https://github.com/abhi3700/my_coding_toolkit/blob/master/mac_for_win.md#3-unable-to-use-software-requiring-x86_64-architecture-on-m1-macbook) first.
	- `ibrew tap eosio/eosio.cdt`
	- `ibrew install eosio.cdt`

#### Editor
* VSC
	- Install the packages:
		+ [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
		```
		M-1
		1. Create a cpp config file named "c_cpp_properties.json" inside ".vscode" in the workspace/repository by clicking on the 'C++' in bottom menu in the editor. Get this file [here](./.vscode/c_cpp_properties.json)

		2. Add this folder for EOSIO enabling:
		"/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/"

		NOTE: update the eosio.cdt version. Also, confirm the directory path exists via `$ find / -type d -name "*eosio.cdt*"` in terminal.


		OR

		M-2 [RECOMMENDED]
		1. Add this to "settings.json" in vscode. <kbd>cmd+shift+p</kbd> >> "Preferences: Open Settings (JSON)"
		
		"C_Cpp.default.includePath": [
        "${workspaceFolder}/**",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/libc",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/libcxx",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/eosiolib/capi",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/eosiolib/contracts",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/eosiolib/core",
        "/usr/local/Cellar/eosio.cdt/1.8.1/opt/eosio.cdt/include/eosiolib/native"
    	],
		```
		+ [TabNine](https://marketplace.visualstudio.com/items?itemName=TabNine.tabnine-vscode)
* ST
	- Install the tabnine package

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
