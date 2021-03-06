#ifndef WIDGETS_HPP__
#define WIDGETS_HPP__

#include <allocate/model.hpp>
#include <allocate/layout.hpp>
#include <foundation/base/functional.hpp>

using foundation::map;

namespace ui
{

framework::Component show( data::Account const & account );
framework::Component show( data::Transaction const & transaction );
framework::Component show( data::Model const & model );


inline framework::Component show( data::Account const & account )
{
  return flow(
    std::make_pair( account.Name, 24 ),
    account.AccountNumber
  );
}

inline framework::Component show( data::Transaction const & transaction )
{
  return flow(
    std::make_pair( transaction.Name, 24 ),
    std::make_pair( transaction.Amount, 10 ),
    std::make_pair( transaction.Frequency, 14 ),
    transaction.StartDate
  );
}

inline framework::Component show( data::Model const & model )
{
  return framework::StackLayout<> {
      render( std::string("Accounts:") ),
      framework::StackLayout<> (
        map( [](auto const & o){ return show( o ); }, model.Accounts ) ),
      render( std::string(" ") ),
      render( std::string("Transactions:") ),
      framework::StackLayout<> (
        map( [](auto const & o){ return show( o ); }, model.Transactions ) ),
  };
}

}

#endif // WIDGETS_HPP__
