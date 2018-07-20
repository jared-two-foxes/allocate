#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include <string>
#include <vector>
typedef uuid int; //< make uuid just an int for now.

struct accounts {
    std::string Name;          // Varchar(255)
    std::string AccountNumber; // Varchar(18)
};

struct transaction {
    std::string Name;
    float Amount;
    int Frequency;
    Date StartDate;
};

struct model {
    std::vector<accounts > Accounts;
    std::vector<transaction > Transactions;
};

#endif // __MODEL_HPP__
