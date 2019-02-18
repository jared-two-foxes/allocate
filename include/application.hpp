#ifndef __ALLCOATE_APPLICATION_HPP__
#define __ALLCOATE_APPLICATION_HPP__

#include <allocate/store.hpp>
#include <allocate/model.hpp>
#include <terminal/terminal.hpp>
#include <foundation/dispatcher.hpp>

class Application
{
private:
  using CallbackSignature = void (const std::vector<std::string >& );

private:
  framework::terminal terminal_;
  framework::CommandDispatcher<std::string, CallbackSignature > dispatcher_;
  data::Store<data::Model > store_;
  bool quit_;

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
