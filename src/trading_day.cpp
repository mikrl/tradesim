#include <algorithm>
#include <cmath>
#include <vector>

#include "trading_day.h"




OHLCData TradingDay::get_daily_data() const{
    /* Turns a vector of floats representing stock transactions for some period into a vector of OHLC data.*/
    
    std::vector<Transaction> tr = get_transactions();
    auto t_open = tr.front();
    auto t_close = tr.back();
    
    float open = t_open.price;
    float close = t_close.price;
    // Get the maximum value of transaction.price from the vector
    float high = std::max_element(tr.begin(), tr.end(), [](Transaction a, Transaction b){return a.price < b.price;})->price;
    float low = std::min_element(tr.begin(), tr.end(), [](Transaction a, Transaction b){return a.price < b.price;})->price;

    long int volume = 0;
    for (auto & transaction : tr){
        volume += transaction.volume;
    }
    
    return {open, close, high, low , volume};
}

TradingDay::TradingDay(){
    total_volume = 0;
    transaction_ledger = std::vector<Transaction>();
}

void TradingDay::add_transaction(float price, long int volume){
    /* Adds a transaction to the trading day.*/
    transaction_ledger.push_back({price, volume});
    total_volume += volume;
}

std::vector<Transaction> TradingDay::get_transactions() const{
    return transaction_ledger;
}

// std::unique_ptr<std::vector<OHLCData>> TradingDay::_generate_hourly_data(const std::vector<float> &ph){
//     /* Returns a vector of OHLC data for each hour of the trading day.*/
//     float hours_per_trading_day = 6.5; // 9:30am - 4:00pm
//     float trades_per_trading_day = ph.size();
//     float trades_per_hour = trades_per_trading_day / hours_per_trading_day;

//     std::unique_ptr<std::vector<OHLCData>> hourly_data = std::make_unique<std::vector<OHLCData>>();
    
//     hourly_data->reserve(std::ceil(hours_per_trading_day));

//     int trades_this_hour = std::floor(trades_per_hour);
//     for (int processed_trades = 0; processed_trades < trades_per_trading_day; processed_trades += trades_this_hour){
//         std::vector<float> hourly_window;

//         if (processed_trades + trades_this_hour > trades_per_trading_day){
//             /* If the last hour of trading is not a full hour, we need to handle this case.*/
//             hourly_window = std::vector<float>(ph.begin() + processed_trades, ph.end());
//         } else {
//             hourly_window = std::vector<float>(ph.begin() + processed_trades, ph.begin() + processed_trades + trades_this_hour);
//         }
        
//         auto start = ph.begin() + processed_trades;
//         auto end = ph.begin() + processed_trades + trades_this_hour;
//         std::vector<float> prices_this_hour(start, end);
//         hourly_data->push_back(_generate_OHLC_from_price_history(prices_this_hour));
//     }


//     return hourly_data;
// }