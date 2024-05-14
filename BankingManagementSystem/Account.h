#include <iostream>
#include <regex>
#include <chrono>
#include <ctime>
#include <string>
using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
private:
    // Account information
    int account_number;
    string username;
    string password;
    string email;
    string phone_number;
    string cnic;
    string date_of_birth;
    int age;
    double balance;
    string card_number[5];
    string card_expiry_date[5];
    string card_cvv[5];
    string card_type[5];


    // Functions in sprints start here
    // Sprint 1 & 2
    // view balance
    // deposit amount
    // Account login
    // Account registration

    // Sprint 3
    // Bill Payment
    // Transaction History
    string transactions[25];
    string billers[10] = {"K-Electric", "Sui Southern Gas Company", "Sui Northern Gas Pipelines Limited", "PTCL", "Sui Northern Gas Pipelines Limited", "Sui Southern Gas Company", "K-Electric", "PTCL", "Sui Northern Gas Pipelines Limited", "Sui Southern Gas Company"};
    string donations[10] = {"Edhi Foundation", "Shaukat Khanum Memorial Cancer Hospital", "The Citizens Foundation", "SOS Children's Villages Pakistan", "LRBT", "The Hunar Foundation", "The Indus Hospital", "Zindagi Trust", "Kashf Foundation", "The Kidney Centre"};
    string loan_types[5] = {"Car Loan", "House Loan", "Personal Loan", "Business Loan", "Student Loan"};
    // Sprint 4, 5 & 6
    string sms_alerts = "Disabled";
    string logs[30];
    string beneficiaries_names[10];
    string beneficiaries_account_numbers[10];
    string beneficiaries_bank_names[10];
    string scheduled_payments[10];

public:
    // Default Constructor
    Account()
    {
        username = "";
        password = "";
        email = "";
        phone_number = "";
        cnic = "";
        date_of_birth = "";
        age = 0;
        balance = 0.0;
        for (int i = 0; i < 25; i++)
        {
            transactions[i] = "";
        }
        for (int i = 0; i < 30; i++)
        {
            logs[i] = "";
        }
        for (int i = 0; i < 10; i++)
        {
            beneficiaries_names[i] = "";
            beneficiaries_account_numbers[i] = "";
            beneficiaries_bank_names[i] = "";
            scheduled_payments[i] = "";
        }
        for(int i = 0; i < 5; i++){
            card_number[i] = "";
            card_expiry_date[i] = "";
            card_cvv[i] = "";
            card_type[i] = "";
        }
    }
    // Parameterized Constructor
    Account(int account_number, string username, string password, string email, string phone_number, string cnic, string date_of_birth, int age, double balance)
    {
        this->account_number = account_number;
        this->setUsername(username);
        this->setPassword(password);
        this->setEmail(email);
        this->setPhoneNumber(phone_number);
        this->setCnic(cnic);
        this->setDateOfBirth(date_of_birth);
        this->setAge(age);
        this->setBalance(balance);
    }

    // Getters
    string getCardNumbers(int i)
    {
        return card_number[i];
    }

    string getCardExpiryDates(int i)
    {
        return card_expiry_date[i];
    }
    string getCardCvvs(int i)
    {
        return card_cvv[i];
    }
    string getCardTypes(int i)
    {
        return card_type[i];
    }
    void addCard(string card_number, string card_expiry_date, string card_cvv, string card_type)
    {
        for (int i = 0; i < 5; i++)
        {
            if (this->card_number[i] == "")
            {
                this->card_number[i] = card_number;
                this->card_expiry_date[i] = card_expiry_date;
                this->card_cvv[i] = card_cvv;
                this->card_type[i] = card_type;
                recordLog("Added a new card: " + to_string(card_number[i]) + ", Type: " + card_type[i]);
                break;
            }
        }
    }
    void removeCard(string card_number)
    {
        for (int i = 0; i < 5; i++)
        {
            if (this->card_number[i] == card_number)
            {
                this->card_number[i] = "";
                this->card_expiry_date[i] = "";
                this->card_cvv[i] = "";
                this->card_type[i] = "";
                recordLog("Removed a card: " + to_string(card_number[i]) + ", Type: " + card_type[i]);
                break;
            }
        }
    }
    string getUsername();
    string getPassword();
    string getEmail();
    string getPhoneNumber();
    string getCnic();
    string getDateOfBirth();
    int getAge();
    double getBalance();
    int getAccountNumber();
    void displayAccountDetails();
    // Setters
    void setUsername(string username);
    void setPassword(string password);
    void setEmail(string email);
    void setPhoneNumber(string phone_number);
    void setCnic(string cnic);
    void setDateOfBirth(string date_of_birth);
    void setAge(int age);
    void setBalance(double balance);
    void setAccountNumber(int account_number);

    // Functions in sprints start here
    // Sprint 1 & 2
    void deposit(double amount, string card_number, string card_type);
    void withdraw(double amount);
    bool fundsTransfer(double amount, Account &receiver_account);

    // Sprint 3
    void recordTransaction(string transaction);
    void viewTransactionHistory();
    void billPayment(string biller, double amount);
    string getBillers(int i)
    {
        return billers[i];
    }
    void setBillers(string billers[10])
    {
        for (int i = 0; i < 10; i++)
        {
            this->billers[i] = billers[i];
        }
    }
    void setTransactions(string transactions[25])
    {
        for (int i = 0; i < 25; i++)
        {
            this->transactions[i] = transactions[i];
        }
    }
    string getTransactions(int i)
    {
        return transactions[i];
    }
    void displayTransactionHistory()
    {
        for (int i = 0; i < 25; i++)
        {
            if (transactions[i] != "")
            {
                cout << transactions[i] << endl;
            }
        }
    }
    void changePhoneNumber(string new_phone_number);
    void changePassword(string new_password);
    void changeEmail(string new_email);
    void changeUsername(string new_username);
    void unregisterAccount(string password);
    void setSmsAlerts(string txt);
    string getSmsAlerts();
    int applyForLoan(string loan_type, double amount);
    void recordLog(string);
    string returnLog(int i);
    void addBeneficiary(string name, string account_number, string bank_name);
    void removeBeneficiary(string name);
    void displayBeneficiaries();
    string getNameOfBeneficiaries(int i)
    {
        return beneficiaries_names[i];
    }
    string getDonations(int i)
    {
        return donations[i];
    }
    void schedulePayment(string name, string date, double amount);
    void displayScheduledPayments();
    string getCurrentDateTime();
    void displayLogs();
    string getLoanTypes(int i)
    {
        return loan_types[i];
    }
    string getLogs(int i)
    {
        return logs[i];
    }
    string getBeneficiaryName(int i)
    {
        return beneficiaries_names[i];
    }
    string getBeneficiaryAccountNumber(int i)
    {
        return beneficiaries_account_numbers[i];
    }
    string getBeneficiaryBankName(int i)
    {
        return beneficiaries_bank_names[i];
    }
    string getScheduledPayment(int i)
    {
        return scheduled_payments[i];
    }
    void setLoanTypes(string loan_types[5])
    {
        for (int i = 0; i < 5; i++)
        {
            this->loan_types[i] = loan_types[i];
        }
    }
    void setLogs(string logs[30])
    {
        for (int i = 0; i < 30; i++)
        {
            this->logs[i] = logs[i];
        }
    }
    void setBeneficiaryNames(string beneficiaries_names[10])
    {
        for (int i = 0; i < 10; i++)
        {
            this->beneficiaries_names[i] = beneficiaries_names[i];
        }
    }
    void setBeneficiaryAccountNumbers(string beneficiaries_account_numbers[10])
    {
        for (int i = 0; i < 10; i++)
        {
            this->beneficiaries_account_numbers[i] = beneficiaries_account_numbers[i];
        }
    }
    void setBeneficiaryBankNames(string beneficiaries_bank_names[10])
    {
        for (int i = 0; i < 10; i++)
        {
            this->beneficiaries_bank_names[i] = beneficiaries_bank_names[i];
        }
    }
    void setScheduledPayments(string scheduled_payments[10])
    {
        for (int i = 0; i < 10; i++)
        {
            this->scheduled_payments[i] = scheduled_payments[i];
        }
    }
    void setAllSmsAlerts(string sms_alerts)
    {
        this->sms_alerts = sms_alerts;
    }
    void setCardNumbers(string card_numbers[5])
    {
        for (int i = 0; i < 5; i++)
        {
            this->card_number[i] = card_numbers[i];
        }
    }
    void setCardTypes(string card_types[5])
    {
        for (int i = 0; i < 5; i++)
        {
            this->card_type[i] = card_types[i];
        }
    }
    void setCardExpiryDates(string card_expiry_dates[5])
    {
        for (int i = 0; i < 5; i++)
        {
            this->card_expiry_date[i] = card_expiry_dates[i];
        }
    }
    void setCardCvvs(string card_cvvs[5])
    {
        for (int i = 0; i < 5; i++)
        {
            this->card_cvv[i] = card_cvvs[i];
        }
    }
    //Final Sprint
    bool donateMoney(string foundation, double amount);
    int applyForCreditCard(string credit_card_number, string credit_card_expiry_date, string credit_card_cvv, string credit_card_type);
};
#endif
