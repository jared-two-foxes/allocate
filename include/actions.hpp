#ifndef ALLOCATE_ACTIONS_HPP__
#define ALLOCATE_ACTIONS_HPP__

#include <allocate/model.hpp>
#include <string>
#include <vector>


namespace actions {

//
// Lifecycle actions.
//

struct Init {
  std::vector<data::Account > accounts;
  std::vector<data::Transaction > transactions;
};

Init initState();
Init initState( data::Account* accounts, std::size_t accountCount );


//
// Account actions
//

struct AddAccount {
  std::string Name;
  std::string AccountNumber;
};

struct UpdatedAccount {
  std::string Name;
  std::string AccountNumber;
};

AddAccount addAccount( std::string const& name, std::string const& number );

UpdatedAccount updateAccount( std::string const& name, std::string const& number );

}

#endif // ALLOCATE_ACTIONS_HPP__
