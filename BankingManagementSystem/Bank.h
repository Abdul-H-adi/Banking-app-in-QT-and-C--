#include<iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "Account.h"
using namespace std;

#ifndef BANK_H
#define BANK_H

class Bank{
private:
    Account accounts[10];
    string bank_helpline = "111-111-111";
    string bank_address = "123, ABC Street, Karachi, Pakistan";
    string bank_gmail = "bankybanky@gmail.com";
public:
    Account* current_account;
    Bank(){
        current_account = NULL;
        loadAccounts();
    }
    bool login(string username, string password);
    void registration(int account_number, string username, string password, string email, string phone_number, string cnic, string date_of_birth, int age, double balance);
    int fundsTransfer(double amount, string receiver_username);
    void logout();

    //Auxiliary functions
    void saveAccounts();
    void loadAccounts();
    string serializeAccount(Account account);
    Account deserializeAccount(char* buffer, int& offset);
    string getBankHelpline();
    string getBankAddress();
    string getBankGmail();

};

#endif
