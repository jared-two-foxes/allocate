#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>
#include <vector>

//typedef int uuid; //< make uuid just an int for now.

namespace data
{

struct Account {
    std::string Name;          // Varchar(255)
    std::string AccountNumber; // Varchar(18)
};

struct Transaction {
    std::string Name;         // VARCHAR(255)
    float Amount;             // DECIMAL (8,2)
    std::string Frequency;    // VARCHAR(32)
    std::string StartDate;    // TIMESTAMP
};

struct Model {
    std::vector<Account > Accounts;
    std::vector<Transaction > Transactions;
};

}

#endif // __MODEL_HPP__
