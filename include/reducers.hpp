#ifndef ALLOCATE_REDUCERS_HPP__
#define ALLOCATE_REDUCERS_HPP__

#include <allocate/actions.hpp>
#include <allocate/store.hpp>

namespace data {

Model reduce( Model other, actions::Init action );
Model reduce( Model other, actions::AddAccount action );
Model reduce( Model other, actions::UpdatedAccount action );

}

#endif // ALLOCATE_REDUCERS_HPP__
