#pragma once
#include <ctime>
#include <cmath>
#include <string>

namespace Ephemeral {
    /**
     *
     * @class Wallet
     *
     * @brief Ephemeral wallet whose balance decays over time.
     *
     * This wallet models a "melting" value system:
     * - Balance decreases continuously as time passes (entropy of money).
     * - Any deposit or withdrawal first updates the balance to the current time,
     *   then applies the requested operation.
     *
     * Conceptual purpose:
     * - Encourage circulation: value loses strength if it is left unused.
     * - Embed the flow of time directly into the monetary object.
     */
    class Wallet {
    public:
        /**
         *
         * @brief Construct a wallet with an owner and initial balance.
         *
         * @param owner   Identifier of the wallet owner (safe string).
         * @param balance Initial balance at creation time.
         *
         * Records the current timestamp for decay tracking.
         *
         */
        Wallet(std::string owner, double balance);

        /**
         *
         * @brief Get the current balance (read-only).
         *
         * @return Balance adjusted for decay up to now.
         *
         * @note This does not modify the internal state permanently.
         *       It queries the effective balance at the instant of the call.
         */
        [[nodiscard]] double getBalance() const;

        /**
         *
         * @brief Deposit funds into the wallet.
         *
         * @param amount Positive amount to add.
         *
         * Internally updates balance according to time decay since the last activity,
         * then applies the deposit, and resets last_activity_timestamp.
         *
         * @throws std::invalid_argument if amount < 0.
         *
         */
        void deposit(double amount);

        /**
         *
         * @brief Attempt to withdraw funds from the wallet.
         *
         * @param amount Positive amount requested.
         *
         * @return True if withdrawal succeeded, false if insufficient balance.
         *
         * Internally updates balance with time decay, then checks availability.
         * If enough, subtracts and updates last_activity_timestamp.
         *
         */
        bool withdraw(double amount);

    private:
        /**
         *
         * @brief Update m_balance to reflect decay since the last activity.
         *
         * Formula:
         *  new_balance = m_balance * exp(-DECAY_RATE * Δt)
         * where Δt is the elapsed time in seconds since m_last_activity_timestamp.
         *
         * @note Called internally before any state-changing operation.
         *
         */
        void update_balance_to_now();

        /// Continuous decay rate (per second).
        static constexpr double DECAY_RATE = 0.000008;
        ///< Current balance (decayed to last update).
        double m_balance;
        ///< Owner identifier (immutable after construction).
        std::string m_owner;
        ///< Last time the state was updated.
        time_t m_last_activity_timestamp;
    };
}
