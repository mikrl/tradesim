#pragma once

#include <memory>
#include <unordered_map>
#include<vector>

#include "bank.h"
#include "market.h"

struct Trade{
    const std::string order_type;
    const std::string ticker;
    float amount;
    float market_price;

    Trade(const std::string ot, const std::string t, float a, float mp) : order_type(ot), ticker(t), amount(a), market_price(mp) {};
    float cost();
};

class Portfolio {

    std::shared_ptr<Market> market;
    std::shared_ptr<BankAccount> bank;
    std::vector<Trade> outstanding_orders;
    std::unordered_map<std::string, float> holdings;
    std::unique_ptr<std::unordered_map<std::string, float>> current_market;
    
    void _place_order(const std::string order_type, const std::string ticker, float amount);
    void _execute_trade(Trade &trade);
  
    public:
    Portfolio() = delete;
    Portfolio(std::shared_ptr<Market> m, std::shared_ptr<BankAccount> b);
    Portfolio(std::shared_ptr<Market> m, std::shared_ptr<BankAccount> b, std::unique_ptr<std::unordered_map<std::string, float>> p);


    float value();
    void place_buy_order(const std::string ticker, float amount);
    void place_sell_order(const std::string ticker, float amount);
    float trade_balance();
    void execute_trades();


};