# allocate

## problem

I need help to know what days and how much are going to be coming out of my
accounts via direct debit and automatic payment which have been setup.  
The payments are likely going to be monthly or fortnightly and taken from
checking accounts or credit cards.


## plan

We're going to build this in a manner to emulate Redux - React with a
external database interacted from the action step which will store information
on the various transactions which are to occur and when they will happen.

It will be presented to the user via a console command interface which will
contain a command prompt as well as a current summary of the accounts and expenses
registered.


## Steps

* Build a static representation of the console command interface
* Implement a quit command to close the application.
* Implement the redux store, reducer & action trio for the system.
* Implement the database interface and implement required actions for polling
  the database to populate the store.
* Implement commands to dispatch to the store via actions.


## Example Database

Accounts
 * {"Spending", "00-0000-0000000-000"},
 * {"Saving", "00-0000-0000000-000"}

Expenses
 * {"Wages", 3251.22f, "Fortnightly", "06/07/2018" },
 * {"Mortgage", -4350.98f, "Monthly", "18/07/2018" },
 * {"Car", -260.89f, "Monthly", "23/07/2018" },
 * {"Car Insurance", -98.71f, "Monthly", "07/07/2018" },
 * {"Internet", -99.99f, "Monthly", "23/07/2018" }
