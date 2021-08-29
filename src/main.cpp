#include <iostream>
#include <stdexcept>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <cstdio>

using namespace std;

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && (std::isdigit(*it) || (*it == '-' && it == s.begin()) || *it == '.')) ++it;
    return !s.empty() && it == s.end();
}

int main(int args, char *arg[]) {
  bool debtmode = true;
  float owe;
  try
  {
    owe = stof(arg[1], nullptr);
  }
  catch(const std::exception& e)
  {
    string strowe = "";
    while(strowe == ""){
      std::cerr << "Please enter a number -[? to 0] for savings [1 to ?] for debts. ";
      getline(cin, strowe);
      if(strowe != "") {
        try
        {
          owe = stod(strowe, nullptr);
        }
        catch(const std::exception& e)
        {
          strowe = "";
          std::cerr << "Please enter a number." << endl;
        }
      } 
    }    
  }

  if(owe <= 0) debtmode = false;

  std::cout << "You " << (debtmode ? "owe " : "have ") << (debtmode ? owe : owe * -1) << endl;
  std::cout << endl;
  double interest = 0;
  if (args >= 3 && is_number(arg[2]) && (strlen(arg[2]) == 1 && arg[2][0] != '-')){
    interest = stod(arg[2], nullptr);
    std::cout << "Your monthly interest rate is " << arg[2] << endl;
  } else {
    string strinterest = "";
    while(strinterest == ""){
      std::cout << "What's the monthly interest rate? ";
      getline(cin, strinterest);
      if(strinterest != "") {
        try
        {
          interest = stod(strinterest, nullptr);
        }
        catch(const std::exception& e)
        {
          strinterest = "";
          std::cerr << "Please enter a number." << endl;
        }
      } 
      else std::cout << "Please enter an interest rate." << endl;
    }
  }

  string strpayment = "";
  float payment = 0;
  if (args >= 4 && is_number(arg[3]) && (strlen(arg[3]) == 1 && arg[3][0] != '-')){
    payment = stod(arg[3], nullptr);
    std::cout << "Your monthly " << (debtmode ? "payment is " : "savings are ") <<  arg[3] << endl;
  } else {
    while(strpayment == ""){
      std::cout << "How much will you " << (debtmode ? "pay" : "save") << " per month? ";
      getline(cin, strpayment);
      if(strpayment != "") {
        try
        {
          payment = stod(strpayment, nullptr);
        }
        catch(const std::exception& e)
        {
          strpayment = "";
          std::cerr << "Please enter a number." << endl;
        }
      } 
      else std::cout << "Please enter your monthly " << (debtmode ? "payment" : "savings") << "." << endl;
    }
  }

  std::cout << endl;
  int month = 0;
  int underpaying;
  float debt = (debtmode ? owe : owe * -1);
  float totinterest, currinterest = 0;
  float prevdebt;
  bool inflates = false;

  while(debt >= 0 && !inflates){
    month++;
    totinterest += currinterest;
    currinterest = debt * (interest / 100);
    prevdebt = debt;
    debt = (debt *  (1 + (interest / 100))) - (debtmode ? payment : payment * -1);
    printf("Month %02d     Interest: %#10.2f$     %s: %#10.2f$     (%+#.2f$) \n", month, currinterest, (debtmode ? "Debt" : "Savings"), debt, debt - prevdebt);

    if(debt > owe) {
      inflates = true;
      string strunderpaying;
      if(debtmode) std::cout << "Debt will never be paid." << endl;

      while(strunderpaying == ""){
        std::cout << "For how long do you want to compound? ";
        getline(cin, strunderpaying);
        if(strunderpaying != "") {
          try
          {
            underpaying = stoi(strunderpaying, nullptr);
          }
          catch(const std::exception& e)
          {
            strunderpaying = "";
            std::cerr << "Please enter a number of months." << endl;
          }
        } 
        else std::cout << "Please enter a number of months." << endl;
      }

      for(int i = 2; i <= underpaying; i++){
        totinterest += currinterest;
        currinterest = debt * (interest / 100);
        prevdebt = debt;
        debt = (debt *  (1 + (interest / 100))) - (debtmode ? payment : payment * -1);
        printf("Month %02d     Interest: %#10.2f$     %s: %#10.2f$     (%+#.2f$) \n", i, currinterest, (debtmode ? "Debt" : "Savings"), debt, debt - prevdebt);
      }

    }

  }

  totinterest += currinterest;

  std::cout << endl;

  if(!inflates) std::cout << owe << "$ debt will be totally paid in " << month << " months!" << endl;
  else printf("You'll %s %#.2f$ in %d month(s) \n", (debtmode ? "owe" : "have"), debt, underpaying);
  printf("Total interest: %#.2f$ \n", totinterest);
  printf("Total %s: %#.2f$ \n\n", (debtmode ? "paid" : "saved"), (inflates ? payment * underpaying : payment * month + debt));

  std::cout << "Press enter to close...";
  //clear buffer, wait for input to close program
  std::cin.clear();
  std::cin.ignore(INT_MAX, '\n');
  std::cin.get();
  return 0;
}

// add switches (maximum interest, )