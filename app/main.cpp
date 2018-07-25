
#include <framework/terminal/components/component.hpp>
#include <framework/terminal/terminal.hpp>

//#include <allocate/dispatcher.hpp>
#include <allocate/model.hpp>
#include <allocate/widgets.hpp>

#include <vector>


// Calculate the total value required in the various registered accounts today and display as "header"


int main(int argc, char* argv[])
{
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

    // Show the current state.
    framework::VirtualTerminal vt;
    vt = vt.flip( ui::show(model).render(100).toString() );

    return 0;
}
