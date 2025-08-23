#pragma once
#include <ctime>
#include <cmath>
#include <string>

class Wallet {
public:
    // Utiliser std::string pour la sécurité de la mémoire
    Wallet(std::string owner, double balance);

    // Cette fonction ne doit pas modifier l'état, on la marque 'const'
    [[nodiscard]] double getBalance() const;

    // Ces fonctions modifient l'état
    void deposit(double amount);
    bool withdraw(double amount);

private:
    // Méthode privée pour la logique centrale : mettre à jour le solde à l'instant T
    void update_balance_to_now();

    // static constexpr est mieux pour une constante de classe
    static constexpr double DECAY_RATE = 0.000008;

    double m_balance; // Préfixer les membres privés (convention courante)
    std::string m_owner;
    time_t m_last_activity_timestamp;
};