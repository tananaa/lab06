#include <gtest/gtest.h>
#include "banking/Account.hpp"

TEST(AccountTest, InitialBalanceIsZero) {
    Account acc("12345");
    EXPECT_DOUBLE_EQ(0.0, acc.getBalance());
    EXPECT_EQ("12345", acc.getNumber());
}

TEST(AccountTest, DepositIncreasesBalance) {
    Account acc("12345");
    acc.deposit(100.0);
    EXPECT_DOUBLE_EQ(100.0, acc.getBalance());
}

TEST(AccountTest, DepositNegativeThrows) {
    Account acc("12345");
    EXPECT_THROW(acc.deposit(-50.0), std::invalid_argument);
}

TEST(AccountTest, WithdrawDecreasesBalance) {
    Account acc("12345");
    acc.deposit(200.0);
    acc.withdraw(50.0);
    EXPECT_DOUBLE_EQ(150.0, acc.getBalance());
}

TEST(AccountTest, WithdrawMoreThanBalanceThrows) {
    Account acc("12345");
    acc.deposit(100.0);
    EXPECT_THROW(acc.withdraw(200.0), std::runtime_error);
}
