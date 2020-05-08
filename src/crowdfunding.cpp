#include <crowdfunding.hpp>

ACTION crowdfunding::hi(name nm) {}

void crowdfunding::handle_deposit(name from, name to, asset quantity, string memo)
{
   if (from == _self || to != _self)
      return;

   if (from == name("eosio.ram") || from == name("eosio.rex") || from == name("eosio.stake"))
      return;

   check(memo == "HYK swap", "invalid memo");
   check(eos_symbol == quantity.symbol, "only accept EOS");
   check(quantity.amount >= 10000, "less than 1 EOS");

   asset hyk_quantity = asset(quantity.amount * 10, hyk_symbol);
   action(
       permission_level{get_self(), "active"_n},
       name("jindaotokens"),
       name("transfer"),
       make_tuple(get_self(), from, hyk_quantity, string("HYK swap success. Thank you for your support.")))
       .send();
}

struct transfer_args
{
   name from;
   name to;
   asset quantity;
   string memo;
};

extern "C"
{
   void apply(uint64_t receiver, uint64_t code, uint64_t action)
   {
      auto self = receiver;

      if (code != self)
      {
         if (action == name("transfer").value && code == name("eosio.token").value)
         {
            crowdfunding instance(name(receiver), name(code), datastream<const char *>(nullptr, 0));
            const auto t = unpack_action_data<transfer_args>();
            instance.handle_deposit(t.from, t.to, t.quantity, t.memo);
         }
      }
   }
}