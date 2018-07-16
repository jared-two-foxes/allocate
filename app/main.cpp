
#include <framework/terminal/components/stacklayout.hpp>
#include <framework/terminal/terminal.hpp>

#include <allocate/dispatcher.hpp>

#include <SQLiteCpp/Database.h>
#include <SQLiteCpp/Statement.h>
#include <SQLiteCpp/VariadicBind.h>

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


void InitDatabase(SQLite::Database& db)
{
    if (!db.tableExists("accounts")) {
        db.exec("CREATE TABLE accounts (AccountID INTEGER PRIMARY KEY, Name VARCHAR(255), AccountNumber VARCHAR(18))");
    }

    if (!db.tableExists("overheads")) {
        db.exec("CREATE TABLE overheads (ExpenseID INTEGER PRIMARY KEY, Name VARCHAR(255), Amount DECIMAL(18, 2), Frequency INT, StartDate DATE)");
    }
}

int main(int argc, char* argv[])
{
    bool quit = false;
    std::string command;
    const std::string prompt = ">>";
    framework::VirtualTerminal vt;

    try {
        SQLite::Database db( DATABASE_FILENAME,
            SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE );

        InitDatabase(db);

        SQLite::Statement query(db, "INSERT INTO accounts (Name, AccountNumber) VALUES ( @name, @account )");


        auto quit_fn = [&quit](const std::vector<std::string >& args) {
            quit = true;
        };

        auto help = [](const std::vector<std::string >& args) {
            std::cout << "print a bunch of help strings.";
        };

        auto add = [&query](const std::vector<std::string >& args) {
            SQLite::bind( query, args[1], args[2] );
            query.exec();
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
                {"add", add},
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
    }
    catch (std::exception& e) {
        std::cout << "exception: " << e.what() << std::endl;
    }

    std::cout << framework::clearLines(0);
    return 0;
}
