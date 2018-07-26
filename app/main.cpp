
#include <framework/terminal/components/component.hpp>
#include <framework/terminal/terminal.hpp>

#include <allocate/dispatcher.hpp>
#include <allocate/model.hpp>
#include <allocate/widgets.hpp>

#include <vector>


std::vector<std::string > split( std::string str, std::string token )
{
    std::vector<std::string > result;

    while( str.size() )
    {
        int index = str.find( token );
        if( index != std::string::npos )
        {
            result.push_back( str.substr( 0, index ) );
            str = str.substr( index + token.size() );
            if( str.size() == 0 )
            {
                result.push_back(str);
            }
        }
        else
        {
            result.push_back( str );
            str = "";
        }
    }

    return result;
}


int main(int argc, char* argv[])
{
    std::string line;
    std::vector<std::string > args;
    framework::VirtualTerminal vt;
    bool quit = false;

    data::Model model {
        {
            {"Spending", "00-0000-0000000-000"},
            {"Saving", "00-0000-0000000-000"}
        },
        {
            {"Wages", 3251.22f, "Fortnightly", "06/07/2018" },
            {"Mortgage", -4350.98f, "Monthly", "18/07/2018" },
            {"Car", -260.89f, "Monthly", "23/07/2018" },
            {"Car Insurance", -98.71f, "Monthly", "07/07/2018" },
            {"Internet", -99.99f, "Monthly", "23/07/2018" }
        }
    };

    auto quit_fn = [&quit](const std::vector<std::string >& args) {
        quit = true;
    };

    CommandDispatcher<std::string, void (const std::vector<std::string >& ) > dispatcher {{
        {"quit", quit_fn}
    }};

    do
    {
        // Show the current state.
        vt = vt.flip( ui::show(model).render(100).toString() );
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
