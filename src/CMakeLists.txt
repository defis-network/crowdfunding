project(crowdfunding)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( crowdfunding crowdfunding crowdfunding.cpp )
target_include_directories( crowdfunding PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( crowdfunding ${CMAKE_SOURCE_DIR}/../ricardian )