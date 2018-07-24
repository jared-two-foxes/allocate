#ifndef WIDGETS_HPP__
#define WIDGETS_HPP__

#include <allocate/model.hpp>
#include <allocate/render.hpp>

namespace ui
{

template <>
framework::Component render( const data::Account& account )
{
    return flow(
        std::string(","),
        std::make_pair( account.Name, 24 ),
        account.AccountNumber
    );
}

template <>
framework::Component render( const data::Transaction& transaction )
{
    return flow(
        std::string(","),
        std::make_pair( transaction.Name, 24 ),
        std::make_pair( transaction.Amount, 10 ),
        std::make_pair( transaction.Frequency, 14 ),
        transaction.StartDate
    );
}

framework::Component render( const data::Model& model )
{
    return framework::StackLayout<> {
        framework::Text {"Accounts"},
        render_stack( model.Accounts ),
        framework::Text {" "},
        framework::Text {"Transactions"},
        render_stack( model.Transactions ),
        framework::Text {" "},
        framework::Text {" "},
        framework::Text {"Please enter a command:"},
        framework::Text {">>"}
    };
}

}

#endif // WIDGETS_HPP__
