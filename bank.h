#pragma once

class BankAccount {
    float rate;
    float asset_balance;
    float liability_balance;

    public:
    BankAccount(float r, float ib) : rate(r), asset_balance(ib), liability_balance(0) {};
    BankAccount(float r) : BankAccount(r, 0.0f) {};
    BankAccount() : BankAccount(0.0f) {};
    
    void apply_interest(float timestep);
    void borrow(float amount);
    void pay_back(float amount);
    void withdraw(float amount);
    void deposit(float amount);
    float get_balance();
};