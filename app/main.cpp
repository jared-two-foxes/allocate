
#include <framework/terminal/components/stacklayout.hpp>
#include <framework/terminal/terminal.hpp>

#include <allocate/dispatcher.hpp>

#include <vector>


constexpr const char* DATABASE_FILENAME = "data.sqlite3";


std::vector<std::string> split(std::string str, std::string token){
    std::vector<std::string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}


// Calculate the total value required in the various registered accounts today and display as "header"


int main(int argc, char* argv[])
{
    bool quit = false;
    std::string command;
    const std::string prompt = ">>";
    framework::VirtualTerminal vt;


    auto quit_fn = [&quit](const std::vector<std::string >& args) {
        quit = true;
    };

    auto help = [](const std::vector<std::string >& args) {
        std::cout << "print a bunch of help strings.";
    };

    auto buildView = [=]() -> framework::Component {
        return framework::StackLayout<>(
            framework::Text{"Allocate!"},
            framework::Text{"Enter command to execute or 'help' for a list of available commands. "}, //< segfaults on an empty string (""), needs to have a space in it.
            framework::Text{prompt}
        );
    };


    CommandDispatcher<std::string, void (const std::vector<std::string >& ) >
        dispatcher {{
            {"quit", quit_fn},
            {"help", help}
        }};


    std::string line;
    std::vector<std::string > args;

    do
    {
        // Show the current state.
        vt = vt.flip(buildView().render(80).toString());
        std::cout << framework::clearLines(0);

        // Grab the next operation from the command line.
        getline( std::cin, line );

        // Pre-process command, splitting out all the args
        args = split( line, " " );

        // Pass to the parse to do with it what it will.
        dispatcher.process( args[0], args );
    } while (!quit);


    std::cout << framework::clearLines(0);
    return 0;
}
