#ifndef __STORE_HPP__
#define __STORE_HPP__

class Store {
private:
    //FN Reducer; //??
    std::vector<listener > Listeners;

public:
    template <typename T, typename FN>
    T dispatch(T data, FN reducer) {
        return data;
    }
};

#endif // __STORE_HPP__
