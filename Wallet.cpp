#include "Wallet.h"


Wallet::Wallet(const char *owner, const double balance) {
    this->owner = owner;
    this->balance = balance;
    this->elapsed = 0;
    this->decayed = time(nullptr);
    this->created = time(nullptr);
}

double Wallet::getBalance() {
    return this->decay();
}

bool Wallet::deposit(const double amount) {
    this->balance += amount;
    return this->decay() >= 0;
}

bool Wallet::withdraw(const double amount) {
    this->balance -= amount;
    return this->decay() >= 0;
}

double Wallet::decay() {
    if (const double time_elapsed =  difftime(this->created, this->decayed); time_elapsed > 0) {
        const double decay_factor = exp(-DECAY_RATE * time_elapsed);
        this->decayed = time(nullptr);
        return this->balance * decay_factor;
    }
    return this->balance;
}
