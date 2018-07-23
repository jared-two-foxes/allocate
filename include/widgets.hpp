#ifndef WIDGETS_HPP__
#define WIDGETS_HPP__

#include <framework/terminal/components/component.hpp>
#include <framework/terminal/components/flowlayout.hpp>
#include <framework/terminal/components/stacklayout.hpp>

#include <allocate/model.hpp>

#include <string>
#include <vector>


namespace ui
{

template <typename T >
framework::Component render( const T& value );

template <typename T >
framework::Component render_stack( const std::vector<T >& items )
{
    framework::StackLayout<> stack {};
    for ( const auto& elem : items ) {
        stack.children.push_back( render( elem ) );
    }
    return stack;
}

template <typename T >
framework::Component render_flow( const std::vector<T >& items )
{
    framework::FlowLayout<> flow {};
    for ( const auto& elem : items ) {
        flow.children.push_back( render( elem ) );
    }
    return flow;
}

template <typename Component>
framework::Component renderHelper(Component c, std::string delim) {
    return framework::FlowLayout<> {
        render(c), render(delim)
    };
}

template <typename... Components >
framework::Component flow(std::string delim, Components... c) {
    return framework::FlowLayout<> {
        renderHelper(c, delim)...,
    };
}

template <>
framework::Component render( const float& obj ) {
    return framework::Text { std::to_string(obj) };
}

template <>
framework::Component render( const std::string& str ) {
    return framework::Text {str};
}

// template <typename T>
// framework::Component render( const T& obj ) {
//     return framework::Text { std::to_string(obj) };
// }

template <>
framework::Component render( const data::Account& account )
{
    return flow(
        std::string(", \t"),
        account.Name,
        account.AccountNumber
    );
}

template <>
framework::Component render( const data::Transaction& transaction )
{
    return flow(
        std::string(", \t"),
        transaction.Amount,
        transaction.Name,
        transaction.Frequency,
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
