
#include <allocate/application.hpp>

#include <allocate/actions.hpp>
#include <allocate/widgets.hpp>
#include <terminal/components/component.hpp>
#include <foundation/logger.hpp>
#include <foundation/string_helper.hpp>

#include <assert.h>
#include <exception>


#define SAFE_DELETE(p) if ((p) != NULL) { delete (p); (p) = NULL; }



namespace data
{
  data::Model reduce( data::Model other, actions::AddAccount action )
  {
    Log( 0, "AddAccount reducer\n" );

    data::Model model = other;
    model.Accounts.push_back( { action.Name, action.AccountNumber } );
    return model;
  }

  data::Model reduce( data::Model other, actions::RefreshAccounts action )
  {
    Log( 0, "RefreshAccounts reducer\n" );

    data::Model model = other;
    model.Accounts = action.accounts;
    return model;
  }
}


Application::Application() :
  database(nullptr),
  store(nullptr),
  quit(false)
{}

Application::~Application()
{
  SAFE_DELETE(database);
  SAFE_DELETE(store);
}

void Application::setup()
{
  initModel();
  initDatabase();
  initDispatcher();
  initTerminal();
}

void Application::renderSingleFrame( data::Model const& model )
{
  Log( 0, "renderSingleFrame\n" );

  std::string next = ui::show(model).render(100).toString();

  next += '\n' + output + '\n';
  next += "\n\nPlease enter a command:\n>>";  //< Add in the temporary cli prompt.

  // Show the current state.
  terminal = terminal.flip( next );
}

void Application::processCmd( std::string& cmd, std::vector<std::string >& args )
{
  dispatcher.process( cmd, args );
}

void Application::run()
{
    Log( 0, "Starting main loop.\n" );

    std::string line;
    std::vector<std::string > args;

    while (!quit)
    {
        //renderSingleFrame();
        output = ""; //< clear out the output from the last iteration so its not repeated.

        getline( std::cin, line );                  // Grab the next operation from the command line.
        //std::cin.ignore();

        output += "Received Command: ";
        output += line;
        output += "\n";
        Log( 0, output );

        //terminal = terminal.append( line + '\n' );  // Add it to the current terminal state.

        args = foundation::split( line, " " );      // Parse; Pre-process command, splitting out all the args
        processCmd( args[0], args );
    }
}

void Application::initDatabase()
{
  try
  {
    // Open a database file in create/write mode
    database = new SQLite::Database( "test.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE );
    //std::cout << "SQLite database file '" << database->getFilename().c_str() << "' opened successfully\n";

    // Create a new table with an explicit "id" column aliasing the underlying rowid
    database->exec( "CREATE TABLE IF NOT EXISTS Accounts (id INTEGER PRIMARY KEY, Name VARCHAR(255), AccountNumber VARCHAR(18))" );
  }
  catch ( std::exception& e )
  {
      Log( 0, std::string("SQLite exception: ") + e.what() + "\n" );
      //return EXIT_FAILURE; // unexpected error : exit the example program
  }

  store->dispatch( actions::refreshAccounts( database ) );
}

void Application::initDispatcher()
{
  auto quit_fn = [this](const std::vector<std::string >& args)
  {
      Log( 0, "Quiting..." );
      quit = true;
  };

  // Database Functions...

  auto insert_fn = [this](const std::vector<std::string >& args)
  {
    assert( args.size() >= 3 );
    store->dispatch( actions::addAccount( database, args[1], args[2] ) );
  };

  auto update_fn = [this](const std::vector<std::string >& args)
  {
      try
      {
        database->exec("UPDATE Accounts SET value=\"second-updated\" WHERE id='2'");
      }
      catch ( std::exception& e )
      {
        Log( 0, "failed to update to database entry.\n" );  // something bad!
      }
  };

  auto query_fn = [this](const std::vector<std::string >& args)
  {
    try
    {
      SQLite::Statement query( *database, "SELECT * FROM Accounts" );
      output += "SELECT * FROM Accounts :\n";

      while ( query.executeStep() )
      {
        const std::string id = query.getColumn(0);
        const std::string name = query.getColumn(1);
        const std::string accountNumber = query.getColumn(2);
        output += std::string("row (") + id + ", " + name + ", " + accountNumber + ")\n";
      }
    }
    catch ( std::exception& e )
    {
      Log( 0, "query failed.\n" );  // something bad!
    }
  };

  dispatcher = CommandDispatcher<std::string, void (const std::vector<std::string >& ) > {{
      {"quit", quit_fn},
      {"insert", insert_fn},
      {"update", update_fn},
      {"query", query_fn}
  }};
}

void Application::initModel()
{
  Log( 0, "Init model.\n" );

  struct Listener : public data::Listener
  {
    data::Store<data::Model >* store;
    Application* app;

    virtual void onStateChanged()
    {
      Log( 0, "onStateChanged callback.\n" );
      data::Model state = store->getState();
      app->renderSingleFrame(state);
    }
  };

  store = new data::Store<data::Model >( {} );

  Log( 0, "Adding main application listener.\n" );
  static Listener listener;
  listener.store = store;
  listener.app = this;
  store->addListener( &listener );
  Log( 0, "Listener added.\n" );
}

void Application::initTerminal()
{}
