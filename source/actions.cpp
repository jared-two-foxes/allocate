
#include <allocate/actions.hpp>

namespace actions {

RefreshAccounts refreshAccounts( SQLite::Database* database )
{
  Log( 0, "refreshAccounts.\n" );

  // This is obviously is going to need to get handled like redux-pack so that
  // we can better handle fail cases.
  RefreshAccounts action;// = {};

  try
  {
    Log( 0, "creating statement.\n" );
    SQLite::Statement query( *database, "SELECT * FROM Accounts" );
    Log( 0, "statement created.\n" );

    Log( 0, "begin execution.\n" );
    while ( query.executeStep() )
    {
      Log( 0, "adding account to action.\n" );

      //const std::string id = query.getColumn(0);
      const std::string name = query.getColumn(1);
      const std::string accountNumber = query.getColumn(2);
      action.accounts.push_back( { name, accountNumber } );
    }
  }
  catch ( std::exception& e )
  {
    Log( 0, "query failed.\n" );  // something bad!
  }

  Log( 0, "returning action.\n" );
  return action;
}

AddAccount addAccount( SQLite::Database* database, std::string const& name, std::string const& number )
{
  // This is obviously is going to need to get handled like redux-pack so that
  // we can better handle fail cases.

  try
  {
    SQLite::Statement query( *database, "INSERT INTO Accounts(Name, AccountNumber) VALUES (?, ?)" );
    SQLite::bind( query, name, number );
    int nb = query.exec();
    return { name, number };
  }
  catch ( std::exception& e )
  {
    Log( 0,  "failed to insert to database.\n" );          // something bad!
  }

  return {};
}

}
