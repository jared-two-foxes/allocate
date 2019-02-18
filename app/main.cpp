
#include <allocate/application.hpp>
#include <foundation/logger/logger.hpp>

#include <vector>
#include <fstream>

int main( int argc, char* argv[] )
{
  // Setup Loggers.
  std::ofstream file( "log.txt" );
  BasicLogger fileLogger( file );
  RegisterLogger( &fileLogger, 0 );

  // Setup Application.
  Application app;
  app.setup();

  // Run!
  app.run();

  // Exiting
  std::cout << "exiting...\n";
  std::cout << "done!\n";

  return 0;
}
