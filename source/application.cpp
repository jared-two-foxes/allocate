
#include <allocate/application.hpp>
#include <allocate/actions.hpp>
#include <allocate/reducers.hpp>
#include <allocate/widgets.hpp>

#include <terminal/components/component.hpp>
#include <foundation/logger.hpp>
#include <foundation/strings/utils.hpp>

#include <assert.h>
#include <exception>


Application::Application() :
  store({}),
  quit(false)
{}

Application::~Application()
{}

void Application::setup()
{
  initStoreListener();
  initDispatcher();

  store.dispatch( actions::initState() );
}

void Application::renderSingleFrame( data::Model const& model )
{
  Log( 0, "renderSingleFrame\n" );

  framework::StackLayout<> layout {
    ui::show(model),
    framework::Text(" "),
    framework::Text("Please enter a command:")
  };

  std::string const next = layout.render(100).toString();
  std::string const prompt( ">> " );

  // Show the current state.
  terminal = terminal.flip( next + prompt );
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
    // Grab the next operation from the command line.
    getline( std::cin, line );

    terminal = terminal.append( line + '\n' );

    // Pre-process command, split commands and arguments, and send to the
    // command processor.
    args = foundation::split( line, " " );
    processCmd( args[0], args );
  }
}

void Application::initDispatcher()
{
  // Lifecycle functions.
  auto quit_fn = [this](const std::vector<std::string >& args) {
      Log( 0, "Quiting..." );
      quit = true;
  };

  // Account Functions.
  auto insert_account_fn = [this](const std::vector<std::string >& args ) {
    assert( args.size() >= 3 );
    store.dispatch( actions::addAccount( args[1], args[2] ) );
  };

  auto update_account_fn = [this](const std::vector<std::string >& args ) {
    assert( args.size() >= 3 );
    store.dispatch( actions::updateAccount( args[1], args[2] ) );
  };

  // Create the actual dispatcher
  dispatcher =
      CommandDispatcher<std::string,
          void (std::vector<std::string > const& ) > {{
              {"quit", quit_fn},
              {"addAccount", insert_account_fn},
              {"updateAccount", update_account_fn}
          }};
}

void Application::initStoreListener()
{
  struct Listener : public data::Listener
  {
    Application* app;
    virtual void onStateChanged() {
      data::Model state = app->store.getState();
      app->renderSingleFrame(state);
    }
  };

  static Listener listener;
  listener.app = this;
  store.addListener( &listener );
}
