
#include <allocate/reducers.hpp>

#include <algorithm>

data::Model data::reduce( data::Model other, actions::Init action )
{
  return other;
}

data::Model data::reduce( data::Model other, actions::AddAccount action )
{
  data::Model model = other;
  model.Accounts.push_back( { action.Name, action.AccountNumber } );
  return model;
}

data::Model data::reduce( data::Model other, actions::UpdatedAccount a )
{
  data::Model model = other;
  auto i = std::find_if( model.Accounts.begin(), model.Accounts.end(), [a](data::Account& o) { return (a.Name == o.Name); });
  if ( i != model.Accounts.end() ) {
    (*i).AccountNumber = a.AccountNumber;
  }
  return model;
}
