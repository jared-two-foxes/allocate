#ifndef __STORE_HPP__
#define __STORE_HPP__

#include <foundation/logger/logger.hpp>
#include <functional>
#include <vector>

namespace data
{

template <typename State, typename Action >
State reduce( State state, Action action );

struct Listener
{
  virtual void onStateChanged() = 0;
};


template <typename State >
class Store
///
/// Encapsulates all the data of the application and provides a single point of
/// interaction.
///
{
private:
  State currentState;
  std::vector<Listener* > listeners;

public:
  Store( State initialState ) :
    currentState(initialState)
  { }

  State getState()
  {
    return currentState;
  }

  void addListener( Listener* listener )
  {
    listeners.push_back( listener );
  }

  template <typename... Args >
  void dispatch( Args... args )
  {
    currentState = reduce( currentState, args... );
    for ( auto& listener : listeners )
    {
      listener->onStateChanged();
    }
    //return action;
  }
};

}

#endif // __STORE_HPP__
