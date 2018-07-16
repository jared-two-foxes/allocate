#ifndef __COMMAND_DISPATCHER_HPP__
#define __COMMAND_DISPATCHER_HPP__

#include <functional>
#include <map>

/*
 *
 *   auto fn = [](){ do_something_interesting };
 *   CommandDispatcher<std::string, void() >
 *       dispatcher {{
 *           {"init", fn}}};
 *
 *   std::string command = "init";
 *   dispatcher.process(command); //< calls fn?
 *
 */
template <typename Key, typename Fn >
struct CommandDispatcher {
    std::map<Key, std::function<Fn > > m_CommandMap;

    template <typename ...Args>
    void process(Key command, Args&&... args) {
        //Todo: Assert that command is in map.
        m_CommandMap[command](args...);
    }
};



// template <typename T>
// bool FindInList(std::vector<T> list, T command)
// {
//     auto it = std::find(list.begin(), list.end(), command);
//     return (it != list.end());
// }
//
// bool IsQuitMessage(std::string command)
// {
//     static const std::vector<std::string > quit_messages = {"exit","quit"};
//     return FindInList(quit_messages, command);
// }



#endif // __COMMAND_DISPATCHER_HPP__
