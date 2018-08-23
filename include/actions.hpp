#ifndef ALLOCATE_ACTIONS_HPP__
#define ALLOCATE_ACTIONS_HPP__

#include <allocate/model.hpp>
#include <foundation/logger.hpp>
#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <vector>


namespace actions {

struct RefreshAccounts
{
  std::vector<data::Account > accounts;
};

RefreshAccounts refreshAccounts( SQLite::Database* database );


using AddAccount = data::Account;
//struct AddAccount : public data::Account {};

AddAccount addAccount( SQLite::Database* database, std::string const& name, std::string const& number );

}

#endif // ALLOCATE_ACTIONS_HPP__
