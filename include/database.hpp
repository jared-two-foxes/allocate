#ifndef ALLOCATE_DATABASE_HPP__
#define ALLOCATE_DATABASE_HPP__

#include <allocate/model.hpp>
#include <SQLiteCpp/Database.h>

class Database {
private:
  SQLite::Database* database_;

public:
  Database();
  ~Database();

  void addAccount( data::Account const & account );
  void updateAccount( data::Account const & account );
  data::Account fetchAccount( std::string const & name );

private:
  void init();

};

#endif // ALLOCATE_DATABASE_HPP__
