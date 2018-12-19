#ifndef __ALLCOATE_APPLICATION_HPP__
#define __ALLCOATE_APPLICATION_HPP__

#include <terminal/terminal.hpp>

#include <allocate/dispatcher.hpp>
#include <allocate/store.hpp>
#include <allocate/model.hpp>

#include <SQLiteCpp/Database.h>


class Application
{
private:
  using CallbackSignature = void (const std::vector<std::string >& );

private:
  framework::terminal terminal;
  CommandDispatcher<std::string, CallbackSignature > dispatcher;
  data::Store<data::Model > store;
  bool quit;

  public:
    Application();
    ~Application();

    void setup();
    void renderSingleFrame( data::Model const& model );
    void processCmd( std::string& cmd, std::vector<std::string >& args );

    void run();

  private:
    void initStoreListener();
    void initDispatcher();

};

#endif // __ALLCOATE_APPLICATION_HPP__
