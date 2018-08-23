#ifndef __STORE_HPP__
#define __STORE_HPP__

#include <functional>
#include <vector>

namespace data
{

struct Listener
{
  virtual void onStateChanged() = 0;
};

// struct Action
// {
//   int type;
// };

constexpr const int INIT = 0;

template <typename State >
class Store
///
/// Encapsulates all the data of the application and provides a single point of
/// interaction.
///
{
  //using ReducerFunction = State ( State, Action );

private:
  bool isDispatching;
  State currentState;
  //std::function<ReducerFunction > currentReducer;
  std::vector<Listener* > listeners;

public:
  Store( /*ReducerFunction reducer,*/ State initialState/*, enhancer*/ ) :
    isDispatching(false),
    //currentReducer(reducer),
    currentState(initialState)
  {
    //dispatch( { INIT } );
  }

  State getState()
  {
    return currentState;
  }

  void addListener( Listener* listener )
  {
    listeners.push_back( listener );
  }

  template <typename Action >
  Action dispatch( Action action )
  {
    isDispatching = true;
    //currentState = currentReducer( currentState, action );
    isDispatching = false;

    Log( 0, "Iterate listeners.\n" );
    for ( auto& listener : listeners )
    {
      Log( 0, "Calling listener.\n" );
      listener->onStateChanged();
    }

    return action;
  }
};

}

#endif // __STORE_HPP__
