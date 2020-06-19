# compile the *.cpp code just by changing the folder, file name
# contract_name=set
# cpp_file_type=.cpp
# eosio-cpp ./$contract_name/$contract_name$cpp_file_type -o ./$contract_name/$contract_name.wasm
eosio-cpp ./test/test.cpp -o test/test.wasm