#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>
using namespace eosio;
using namespace std;

CONTRACT crowdfunding : public contract
{
public:
   using contract::contract;
   static constexpr symbol eos_symbol = symbol(symbol_code("EOS"), 4);
   static constexpr symbol hyk_symbol = symbol(symbol_code("HYK"), 4);
   ACTION hi(name nm);
   void handle_deposit(name from, name to, asset quantity, string memo);
};