#include "Bank.h"

bool Bank::login(string username, string password){
    for(int i = 0; i < 10; i++){
        if(accounts[i].getUsername() == username && accounts[i].getPassword() == password){
            current_account = &accounts[i];
            current_account->recordLog("Logged in.");
            return true;
        }
    }
    return false;
}

void Bank::registration(int account_number, string username, string password, string email, string phone_number, string cnic, string date_of_birth, int age, double balance){
    Account new_account(account_number, username, password, email, phone_number, cnic, date_of_birth, age, balance);

    for(int i = 0; i < 10; i++){
        if(accounts[i].getUsername() == ""){
            accounts[i].setAccountNumber(account_number);
            accounts[i].setUsername(username);
            accounts[i].setPassword(password);
            accounts[i].setEmail(email);
            accounts[i].setPhoneNumber(phone_number);
            accounts[i].setCnic(cnic);
            accounts[i].setDateOfBirth(date_of_birth);
            accounts[i].setAge(age);
            accounts[i].setBalance(balance);
            current_account = &accounts[i];
            return;
        }
    }
}

int Bank::fundsTransfer(double amount, string receiver_username){
    for(int i = 0; i < 10; i++){
        if(accounts[i].getUsername() == receiver_username)
        {
            Account &receiver_account = accounts[i];
            bool res = this->current_account->fundsTransfer(amount, receiver_account);
            if(!res)
                return 1;
            else
                return 2;
        }
    }
    cout << "Receiver account not found." << endl;
    return 0;
}

void Bank::logout(){
    current_account->recordLog("Logged out.");
    current_account = NULL;
    //Save accounts to file
    saveAccounts();
}

void Bank::saveAccounts()
{
    ofstream file("accounts.bin", ios::out | ios::binary | ios::trunc);
    if(file.is_open())
    {
        for(int i = 0; i < 10; i++)
        {
            if(accounts[i].getUsername() != "")
            {
                bool is_duplicate = false;
                for(int j = 0; j < i; j++)
                {
                    if(accounts[i].getUsername() == accounts[j].getUsername()){
                        is_duplicate = true;
                        break;
                    }
                }
                if(!is_duplicate)
                {
                    string account_data = serializeAccount(accounts[i]);
                    file.write(account_data.c_str(), account_data.size());
                }
            }
        }
        file.close();
    }
}

void Bank::loadAccounts(){
    ifstream file("accounts.bin", ios::in | ios::binary);
    if(file.is_open()){
        file.seekg(0, ios::end);
        int file_size = file.tellg();
        file.seekg(0, ios::beg);

        char* buffer = new char[file_size];
        file.read(buffer, file_size);

        int offset = 0;
        while(offset < file_size){
            Account account = deserializeAccount(buffer, offset);
            if(account.getUsername() != ""){
                for(int i = 0; i < 10; i++){
                    if(accounts[i].getUsername() == ""){
                        accounts[i] = account;
                        break;
                    }
                }
            }
        }

        delete[] buffer;
        file.close();
    }
}

string Bank::serializeAccount(Account account){
    stringstream ss;
    ss << account.getAccountNumber() << ",";
    ss << account.getUsername() << ",";
    ss << account.getPassword() << ",";
    ss << account.getEmail() << ",";
    ss << account.getPhoneNumber() << ",";
    ss << account.getCnic() << ",";
    ss << account.getDateOfBirth() << ",";
    ss << account.getAge() << ",";
    ss << account.getBalance() << ",";
    for(int i = 0; i < 25; i++){
        ss << account.getTransactions(i) << ",";
    }
    for(int i = 0; i < 10; i++){
        ss << account.getBillers(i) << ",";
    }
    for(int i = 0; i < 5; i++){
        ss << account.getLoanTypes(i) << ",";
    }
    for(int i = 0; i < 5; i++){
        ss << account.getCardNumbers(i) << ",";
        ss << account.getCardTypes(i) << ",";
        ss << account.getCardExpiryDates(i) << ",";
        ss << account.getCardCvvs(i) << ",";
    }
    ss << account.getSmsAlerts() << ",";
    for(int i = 0; i < 30; i++){
        ss << account.getLogs(i) << ",";
    }
    for(int i = 0; i < 10; i++){
        ss << account.getBeneficiaryName(i) << ",";
        ss << account.getBeneficiaryAccountNumber(i) << ",";
        ss << account.getBeneficiaryBankName(i) << ",";
    }
    for(int i = 0; i < 10; i++){
        ss << account.getScheduledPayment(i) << ",";
    }
    ss << "\n";
    return ss.str();
}

Account Bank::deserializeAccount(char* buffer, int& offset){
    string account_data = "";
    while(buffer[offset] != '\n'){
        account_data += buffer[offset];
        offset++;
    }
    offset++;

    stringstream ss(account_data);
    string account_number_str, username, password, email, phone_number, cnic, date_of_birth, age_str, balance_str;
    getline(ss, account_number_str, ',');
    getline(ss, username, ',');
    getline(ss, password, ',');
    getline(ss, email, ',');
    getline(ss, phone_number, ',');
    getline(ss, cnic, ',');
    getline(ss, date_of_birth, ',');
    getline(ss, age_str, ',');
    getline(ss, balance_str, ',');
    string transactions[25];
    string billers[10];
    string loan_types[5];
    string card_numbers[5];
    string card_types[5];
    string card_expiry_dates[5];
    string card_cvvs[5];
    string sms_alerts;
    string logs[30];
    string beneficiaries_names[10];
    string beneficiaries_account_numbers[10];
    string beneficiaries_bank_names[10];
    string scheduled_payments[10];
    for(int i = 0; i < 25; i++){
        getline(ss, transactions[i], ',');
    }
    for(int i = 0; i < 10; i++){
        getline(ss, billers[i], ',');
    }
    for(int i = 0; i < 5; i++){
        getline(ss, loan_types[i], ',');
    }
    for(int i = 0; i < 5; i++){
        getline(ss, card_numbers[i], ',');
        getline(ss, card_types[i], ',');
        getline(ss, card_expiry_dates[i], ',');
        getline(ss, card_cvvs[i], ',');
    }
    getline(ss, sms_alerts, ',');
    for(int i = 0; i < 30; i++){
        getline(ss, logs[i], ',');
    }
    for(int i = 0; i < 10; i++){
        getline(ss, beneficiaries_names[i], ',');
        getline(ss, beneficiaries_account_numbers[i], ',');
        getline(ss, beneficiaries_bank_names[i], ',');
    }
    for(int i = 0; i < 10; i++){
        getline(ss, scheduled_payments[i], ',');
    }

    int account_number = stoi(account_number_str);
    int age = stoi(age_str);
    double balance = stod(balance_str);

    Account account(account_number,username, password, email, phone_number, cnic, date_of_birth, age, balance);
    account.setAccountNumber(account_number);
    account.setTransactions(transactions);
    account.setBillers(billers);
    account.setLoanTypes(loan_types);
    account.setCardNumbers(card_numbers);
    account.setCardTypes(card_types);
    account.setCardExpiryDates(card_expiry_dates);
    account.setCardCvvs(card_cvvs);
    account.setAllSmsAlerts(sms_alerts);
    account.setLogs(logs);
    account.setBeneficiaryNames(beneficiaries_names);
    account.setBeneficiaryAccountNumbers(beneficiaries_account_numbers);
    account.setBeneficiaryBankNames(beneficiaries_bank_names);
    account.setScheduledPayments(scheduled_payments);

    return account;
}

string Bank::getBankHelpline(){
    return bank_helpline;
}

string Bank::getBankAddress(){
    return bank_address;
}

string Bank::getBankGmail(){
    return bank_gmail;
}
