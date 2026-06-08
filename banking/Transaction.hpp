#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include "Account.hpp"

class Transaction {
private:
    Account* from;
    Account* to;
    double amount;
    bool completed;

public:
    Transaction(Account* fromAcc, Account* toAcc, double amt);
    void execute();
    void rollback();
    bool isCompleted() const;
};

#endif
