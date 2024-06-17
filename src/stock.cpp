#include "stock.h"

float Stock::price(float timestep){
    return price_process->next(timestep);
}

void Stock::update(float drift, float volatility, float price){
    price_process->update(drift, volatility, price);
}
