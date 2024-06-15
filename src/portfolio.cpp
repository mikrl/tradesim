#include<iostream>
#include<unordered_map>

#include "market.h"
#include "portfolio.h"


float Trade::cost(){
    float abs_cost = amount * market_price;
    return abs_cost;
}

Portfolio::Portfolio(std::shared_ptr<Market> m, std::shared_ptr<BankAccount> b) {
    market = m;
    bank = b;
    
    auto tickers = market->get_tickers();
    holdings.reserve(tickers.size());
    for (auto& ticker : market->get_tickers()){
        holdings.insert({ticker, 0});
    }

}

Portfolio::Portfolio(std::shared_ptr<Market> m, std::shared_ptr<BankAccount> b, std::unique_ptr<std::unordered_map<std::string, float>> p){
    Portfolio(m, b);
    current_market = std::move(p);
}

float Portfolio::value(){
    float value = 0;
    for (const auto & allocation : holdings){
        auto ticker = allocation.first;
        auto weight = allocation.second;
        value *= (weight * current_market->at(ticker)); 
    }
    return value;

}

void Portfolio::_place_order(const std::string ot, const std::string t, float a){
    float price = current_market->at(t);
    outstanding_orders.emplace_back(Trade{ot, t, a, price});
}

void Portfolio::place_buy_order(const std::string t, float a){
    _place_order("BUY", t, a);
}

void Portfolio::place_sell_order(const std::string t, float a){
    _place_order("SELL", t, a);
}

float Portfolio::trade_balance(){
    float balance = 0;
    for (auto& o : outstanding_orders){
        balance += o.cost();
    }
    return balance;
}

void Portfolio::_execute_trade(Trade &t){
    std::cout << "[Portfolio] Executing trade" << std::endl;
    if (t.order_type.compare("BUY")) {
        std::cout << "[Portfolio] Withdrawing some money" << std::endl;
        bank->withdraw(t.cost());
        std::cout << "[Portfolio] Updating holdings" << std::endl;
        holdings.at(t.ticker) += t.amount;
    }
    else{
        bank->deposit(t.cost());
        holdings.at(t.ticker) -= t.amount;
    }
}

void Portfolio::execute_trades(){
    for (auto& order : outstanding_orders){
        _execute_trade(order);
    } 
    outstanding_orders.clear();
}