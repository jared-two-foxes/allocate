
#include <allocate/actions.hpp>

actions::Init actions::initState()
{
  //@todo: pull accounts and transactions from database?
  return {};
}

actions::Init actions::initState( data::Account* accounts, std::size_t accountCount )
{
  actions::Init action;
  action.accounts.assign( accounts, accounts + accountCount );
  return action;
}

actions::AddAccount actions::addAccount( std::string const& name, std::string const& number )
{
  return { name, number };
}

actions::UpdatedAccount actions::updateAccount( std::string const& name, std::string const& number )
{
  return { name, number };
}
