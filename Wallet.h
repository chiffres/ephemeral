#pragma once
#include <ctime>
#include <cmath>

class Wallet {
public:
    const double DECAY_RATE = 0.000008;

    Wallet(const char *owner, double balance);

    [[nodiscard]] double getBalance();

    bool deposit(double amount);

    bool withdraw(double amount);

    [[nodiscard]] double decay();

private:
    double balance;
    const char *owner;
    time_t created;
    double elapsed;
    time_t decayed;
};
