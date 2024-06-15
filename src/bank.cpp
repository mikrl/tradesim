#include <cmath>
#include <iostream>

#include "bank.h"

void BankAccount::apply_interest(float timestep){
    // Assume deposit rate and borrow rate is the same
    float multiplier = std::exp(rate * timestep);
    asset_balance *= multiplier;
    liability_balance *= multiplier;
}

void BankAccount::borrow(float amount){
    liability_balance += amount;
    asset_balance += amount;
    
}

void BankAccount::pay_back(float amount){
    liability_balance -= amount;
    asset_balance -= amount;
}

void BankAccount::withdraw(float amount){
    if (amount > asset_balance){
        float difference = amount - asset_balance;
        std::cout << "Borrowing " << difference << std::endl;
        borrow(difference);
    }
    asset_balance -= amount;

}

void BankAccount::deposit(float amount){
    asset_balance += amount;
}

float BankAccount::get_balance(){
    return asset_balance - liability_balance;
}