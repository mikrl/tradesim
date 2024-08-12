#pragma once

#include <memory>
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
};


class TradingDay {
    
    private:
    long int total_volume;
    std::vector<Transaction> transaction_ledger;

    public:
  
    TradingDay();
    TradingDay(std::vector<Transaction> transactions) : transaction_ledger(transactions) {}
    
    void add_transaction(float price, long int volume = 1);
    std::vector<Transaction> get_transactions() const;
    OHLCData get_daily_data() const;
    std::vector<OHLCData> get_hourly_data() const;
};