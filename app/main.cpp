
#include <foundation/logger.hpp>

#include <allocate/application.hpp>

#include <vector>
#include <fstream>


int main( int argc, char* argv[] )
{
  // Setup Loggers.
  BasicLogger consoleLogger( std::cout );
  RegisterLogger( &consoleLogger, 100 );
  std::ofstream file( "log.txt" );
  // TODO: should we clear the log file before each run?
  BasicLogger fileLogger( file );
  RegisterLogger( &fileLogger, 0 );

  // Setup Application.
  Application app;
  app.setup();

  // Run!
  app.run();

  // Exiting
  std::cout << "exiting...\n";
  //std::cout << framework::clearLines(0);
  std::cout << "done!";

  return 0;
}
