#include <gtest/gtest.h>
#include "banking/Transaction.hpp"
#include "banking/Account.hpp"

TEST(TransactionTest, ExecuteTransfersMoney) {
    Account from("A1");
    Account to("B1");
    from.deposit(500.0);
    
    Transaction tx(&from, &to, 200.0);
    tx.execute();
    
    EXPECT_DOUBLE_EQ(300.0, from.getBalance());
    EXPECT_DOUBLE_EQ(200.0, to.getBalance());
    EXPECT_TRUE(tx.isCompleted());
}

TEST(TransactionTest, DoubleExecuteThrows) {
    Account from("A1");
    Account to("B1");
    from.deposit(500.0);
    
    Transaction tx(&from, &to, 200.0);
    tx.execute();
    EXPECT_THROW(tx.execute(), std::runtime_error);
}

TEST(TransactionTest, RollbackRestoresBalances) {
    Account from("A1");
    Account to("B1");
    from.deposit(500.0);
    
    Transaction tx(&from, &to, 200.0);
    tx.execute();
    tx.rollback();
    
    EXPECT_DOUBLE_EQ(500.0, from.getBalance());
    EXPECT_DOUBLE_EQ(0.0, to.getBalance());
    EXPECT_FALSE(tx.isCompleted());
}

TEST(TransactionTest, RollbackWithoutExecuteThrows) {
    Account from("A1");
    Account to("B1");
    Transaction tx(&from, &to, 200.0);
    EXPECT_THROW(tx.rollback(), std::runtime_error);
}
