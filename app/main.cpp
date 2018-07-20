
#include <framework/terminal/components/component.hpp>
#include <framework/terminal/terminal.hpp>

//#include <allocate/dispatcher.hpp>
#include <allocate/model.hpp>
#include <allocate/widgets.hpp>

#include <vector>


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
    data::Model model {
        {
            {"Spending", "00-0000-0000000-000"},
            {"Saving", "00-0000-0000000-000"}
        },
        {
            {"Wages", 3251.22, "Fortnightly", "06/07/2018" },
            {"Mortgage", -4350.98, "Monthly", "18/07/2018" },
            {"Car", -260.89, "Monthly", "23/07/2018" },
            {"Car Insurance", -98.71, "Monthly", "07/07/2018" },
            {"Internet", -99.99, "Monthly", "23/07/2018" }
        }
    };

    // Show the current state.
    framework::VirtualTerminal vt;
    vt = vt.flip( ui::render(model).render(80).toString() );

    return 0;
}
