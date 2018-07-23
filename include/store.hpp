#ifndef __STORE_HPP__
#define __STORE_HPP__

template <typename T >
class Store {
private:
    T store;
    std::vector<listener > Listeners;

public:
    template <typename FN, typename Action>
    Action dispatch(FN reducer, Action action) {
        store = reducer(store, action);

    }
};

#endif // __STORE_HPP__
