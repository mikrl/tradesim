#pragma once

#include <chrono>
#include <vector>

struct OHLCData{
    float open;
    float close;
    float high;
    float low;
    long int volume;
};
struct Transaction{
    float price;
    long int volume;
    long int tick;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};


class TradingDay {
    
    private:
    long int total_volume;
    long int tick = 0;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
    std::vector<Transaction> transaction_ledger;

    public:
  
    TradingDay();
    TradingDay(std::vector<Transaction> transactions) : transaction_ledger(transactions) {}
    
    void add_transaction(float price, long int volume = 1, std::chrono::time_point<std::chrono::system_clock> timestamp = std::chrono::system_clock::now());
    
    long int get_tick() const {return tick;}
    std::vector<Transaction> get_transactions() const;

    OHLCData get_daily_data() const;
    std::vector<OHLCData> get_data_by_tick(long int n_ticks) const;
    std::vector<OHLCData> get_data_by_volume(long int n_volume) const;
    std::vector<OHLCData> get_hourly_data() const;
};