#include "Wallet.h"

using namespace Ephemeral;

Wallet::Wallet(std::string owner, const double balance)
    : m_balance(balance),
      m_owner(std::move(owner)),
      m_last_activity_timestamp(time(nullptr)) {}

void Wallet::update_balance_to_now() {
    const time_t current_time = time(nullptr);
    const double time_elapsed = difftime(current_time, m_last_activity_timestamp);

    if (time_elapsed > 0) {
        const double decay_factor = exp(-DECAY_RATE * time_elapsed);
        m_balance *= decay_factor;
        m_last_activity_timestamp = current_time;
    }
}

double Wallet::getBalance() const {
    const double time_elapsed = difftime(time(nullptr), m_last_activity_timestamp);
    if (time_elapsed > 0) {
        const double decay_factor = exp(-DECAY_RATE * time_elapsed);
        return m_balance * decay_factor;
    }
    return m_balance;
}

void Wallet::deposit(const double amount) {
    update_balance_to_now();
    m_balance += amount;
}

bool Wallet::withdraw(const double amount) {
    update_balance_to_now();
    if (m_balance >= amount) {
        m_balance -= amount;
        return true;
    }
    return false;
}
