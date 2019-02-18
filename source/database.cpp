
#include <allocate/database.hpp>
#include <foundation/logger/logger.hpp>

#include <SQLiteCpp/VariadicBind.h>

Database::Database() :
  database_(nullptr)
{
  init();
}

Database::~Database()
{
  if (database_) {
    delete database_;
  }
}

void
Database::init()
{
  try
  {
    // Open a database file in create/write mode
    database_ = new SQLite::Database( "test.db3",
      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE );
    Log( 0, "SQLite database file '%s' opened successfully\n",
      database_->getFilename().c_str() );

    // Create Accounts table if it doesnt already exist.
    database_->exec(
      "CREATE TABLE IF NOT EXISTS Accounts (id INTEGER PRIMARY KEY,            \
       Name VARCHAR(255), AccountNumber VARCHAR(18))" );

    // Create Transaction table if it doesnt already exist.
    database_->exec(
      "CREATE TABLE IF NOT EXISTS Transactions (id INTEGER PRIMARY KEY,        \
       Name VARCHAR(255), Amount DECIMAL(8,2), Frequency VARCHAR32),           \
       StartDate TIMESTAMP )" );
  }
  catch ( std::exception& e )
  {
    Log( 0, "SQLite exception: '%s'\n", e.what() );
    // unexpected error: exit the program?  Not sure how/if we should recover
  }
}

void
Database::addAccount( data::Account const& account )
{
  try
  {
    SQLite::Statement query( *database_,
      "INSERT INTO Accounts(Name, AccountNumber) VALUES (?, ?)" );
    SQLite::bind( query, account.Name, account.AccountNumber );
    int nb = query.exec();
    //return { name, number };
  }
  catch ( std::exception& e )
  {
    Log( 0, "failed to insert to database.\n" );          // something bad!
  }
}

void
Database::updateAccount( data::Account const& account )
{
  try
  {
    int id = 1; //< how should we associate id's?

    int nb;
    SQLite::Statement query( *database_,
      "UPDATE Accounts SET ?=? WHERE id=?" );
    SQLite::bind( query, "Name", account.Name, id );
    nb = query.exec();
    SQLite::bind( query, "AccountNumber", account.AccountNumber, id );
    nb = query.exec();
  }
  catch ( std::exception& e )
  {
    Log( 0, "failed to update to database entry.\n" );  // something bad!
  }
}
