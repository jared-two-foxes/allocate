
#include <allocate/application.hpp>
#include <allocate/actions.hpp>
#include <allocate/reducers.hpp>
#include <allocate/widgets.hpp>

#include <terminal/components/component.hpp>
#include <foundation/logger/logger.hpp>
#include <foundation/strings/utils.hpp>

#include <assert.h>
#include <exception>


Application::Application() :
  store_({}),
  quit_(false)
{}

Application::~Application()
{}

void Application::setup()
{
  initStoreListener();
  initDispatcher();
  store_.dispatch( actions::initState() );
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
  terminal_ = terminal_.flip( next + prompt );
}

void Application::processCmd( std::string& cmd, std::vector<std::string >& args )
{
  dispatcher_.process( cmd, args );
}

void Application::run()
{
  Log( 0, "Starting main loop.\n" );

  std::string line;
  std::vector<std::string > args;

  while (!quit_)
  {
    // Grab the next operation from the command line.
    getline( std::cin, line );

    terminal_ = terminal_.append( line + '\n' );

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
    quit_ = true;
  };

  // Account Functions.
  auto insert_account_fn = [this](const std::vector<std::string >& args ) {
    assert( args.size() >= 3 );
    store_.dispatch( actions::addAccount( args[1], args[2] ) );
  };

  auto update_account_fn = [this](const std::vector<std::string >& args ) {
    assert( args.size() >= 3 );
    store_.dispatch( actions::updateAccount( args[1], args[2] ) );
  };

  // Create the actual dispatcher
  dispatcher_ =
      framework::CommandDispatcher<std::string,
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
      data::Model state = app->store_.getState();
      app->renderSingleFrame(state);
    }
  };

  static Listener listener;
  listener.app = this;
  store_.addListener( &listener );
}
