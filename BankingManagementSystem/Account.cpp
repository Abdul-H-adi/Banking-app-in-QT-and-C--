#include "Account.h"

//Getters
string Account::getUsername(){
    return username;
}
string Account::getPassword(){
    return password;
}
string Account::getEmail(){
    return email;
}
string Account::getPhoneNumber(){
    return phone_number;
}
string Account::getCnic(){
    return cnic;
}
string Account::getDateOfBirth(){
    return date_of_birth;
}
int Account::getAge(){
    return age;
}
double Account::getBalance(){
    return balance;
}

int Account::getAccountNumber(){
    return account_number;
}

void Account::displayAccountDetails(){
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    cout << "Phone Number: " << phone_number << endl;
    cout << "CNIC: " << cnic << endl;
    cout << "Date of Birth: " << date_of_birth << endl;
    cout << "Age: " << age << endl;
    cout << "Balance: " << balance << endl;
}

//Setters
void Account::setUsername(string new_username){
    if(new_username.length() >= 6 && new_username.length() <= 20){
        username = new_username;
    }
    else{
        cout << "Invalid username length. Must be between 6 and 20 characters." << endl;
    }
}

void Account::setPassword(string new_password){
    if(new_password.length() >= 8 && new_password.length() <= 20){
        password = new_password;
    }
    else{
        cout << "Invalid password length. Must be between 8 and 20 characters." << endl;
    }
}

void Account::setEmail(string new_email){
    regex email_regex("^[a-zA-Z0-9+_.-]+@[a-zA-Z0-9.-]+$");
    if(regex_match(new_email, email_regex)){
        email = new_email;
    }
    else{
        cout << "Invalid email format." << endl;
    }
}

void Account::setPhoneNumber(string new_phone_number){
    regex phone_regex("^[0-9]{11}$");
    if(regex_match(new_phone_number, phone_regex)){
        phone_number = new_phone_number;
    }
    else{
        cout << "Invalid phone number format. Must be 11 digits." << endl;
    }
}

void Account::setCnic(string new_cnic){
    regex cnic_regex("^[0-9]{5}-[0-9]{7}-[0-9]{1}$");
    if(regex_match(new_cnic, cnic_regex)){
        cnic = new_cnic;
    }
    else{
        cout << "Invalid CNIC format. Must be in the format 12345-1234567-1." << endl;
    }
}

void Account::setDateOfBirth(string new_date_of_birth){
    regex dob_regex("^[0-9]{2}/[0-9]{2}/[0-9]{4}$");
    if(regex_match(new_date_of_birth, dob_regex)){
        date_of_birth = new_date_of_birth;
        //Calculate age
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int current_year = 1900 + ltm->tm_year;
        int current_month = 1 + ltm->tm_mon;
        int current_day = ltm->tm_mday;

        stringstream ss(new_date_of_birth);
        int year, month, day;
        char delim;
        ss >> month >> delim >> day >> delim >> year;

        age = current_year - year;
        if(current_month < month || (current_month == month && current_day < day)){
            age--;
        }
    }
    else{
        cout << "Invalid date of birth format. Must be in the format MM/DD/YYYY." << endl;
    }
}

void Account::setBalance(double new_balance){
    if(new_balance >= 0){
        balance = new_balance;
    }
    else{
        cout << "Invalid balance. Must be non-negative." << endl;
    }
}

void Account::setAccountNumber(int new_account_number){
    if(new_account_number >= 0){
        account_number = new_account_number;
    }
    else{
        cout << "Invalid account number. Must be non-negative." << endl;
    }
}

void Account::setAge(int new_age){
    if(new_age >= 0){
        age = new_age;
    }
    else{
        cout << "Invalid age. Must be non-negative." << endl;
    }
}


//Functions in sprints start here
//Sprint 1 & 2
void Account::deposit(double amount, string card_number,string card_type){
    if(amount > 0){
        balance += amount;
        cout << "Amount deposited successfully." << endl;
        recordTransaction("Deposit of " + to_string(amount) + " from " + card_type + " Number: " + card_number);
        recordLog("Deposit of " + to_string(amount) + " from " + card_type + " Number: " + card_number);
    }
    else{
        cout << "Invalid amount. Must be non-negative." << endl;
    }
}

void Account::withdraw(double amount){
    if(amount > 0){
        if(amount <= balance){
            balance -= amount;
            cout << "Amount withdrawn successfully." << endl;
            recordTransaction("Withdrawal of " + to_string(amount));
            recordLog("Withdrawal of " + to_string(amount));
        }
        else{
            cout << "Insufficient balance." << endl;
        }
    }
    else{
        cout << "Invalid amount. Must be non-negative." << endl;
    }
}

bool Account::fundsTransfer(double amount, Account &receiver_account){
    if(amount > 0){
        if(amount <= balance){
            balance -= amount;
            receiver_account.balance += amount;
            cout << "Amount transferred successfully." << endl;
            recordTransaction("Funds transfer of " + to_string(amount) + " to " + receiver_account.getUsername());
            receiver_account.recordTransaction("Funds transfer of " + to_string(amount) + " from " + receiver_account.getUsername());
            recordLog("Funds transfer of " + to_string(amount));
            return 1;
        }
        else{
            cout << "Insufficient balance." << endl;
            return 0;
        }
    }
    else{
        return 0;
        cout << "Invalid amount. Must be non-negative." << endl;
    }
}

//Sprint 3

void Account::recordTransaction(string transaction){
    for(int i = 0; i < 25; i++){
        if(transactions[i] == ""){
            transactions[i] = transaction;
            return;
        }
    }
}

void Account::viewTransactionHistory(){
    for(int i = 0; i < 25; i++){
        if(transactions[i] != ""){
            cout << transactions[i] << endl;
        }
    }
}

void Account::billPayment(string biller, double amount){
    if(amount > 0){
        if(amount <= balance){
            balance -= amount;
            cout << "Bill payment successful." << endl;
            recordTransaction("Bill payment of " + to_string(amount) + " to " + biller);
            recordLog("Bill payment of " + to_string(amount));
        }
        else{
            cout << "Insufficient balance." << endl;
        }
    }
    else{
        cout << "Invalid amount. Must be non-negative." << endl;
    }
}

bool Account::donateMoney(string foundation, double amount){
    if(amount > 0){
        if(amount <= balance){
            balance -= amount;
            cout << "Donation successful." << endl;
            recordTransaction("Donation of " + to_string(amount) + " to " + foundation);
            recordLog("Donation of " + to_string(amount));
            return 1;
        }
        else{
            cout << "Insufficient balance." << endl;
            return 0;
        }
    }
    else{
        cout << "Invalid amount. Must be non-negative." << endl;
        return 0;
    }
}
//Sprint 4
void Account::changePhoneNumber(string new_phone_number){
    regex phone_regex("^[0-9]{11}$");
    if(regex_match(new_phone_number, phone_regex)){
        phone_number = new_phone_number;
        cout << "Phone number changed successfully." << endl;
        recordLog("Phone number changed to " + new_phone_number);
    }
    else{
        cout << "Invalid phone number format. Must be 11 digits." << endl;
    }
}

void Account::changePassword(string new_password){
    if(new_password.length() >= 8 && new_password.length() <= 20){
        password = new_password;
        cout << "Password changed successfully." << endl;
        recordLog("Password changed");
    }
    else{
        cout << "Invalid password length. Must be between 8 and 20 characters." << endl;
    }
}

void Account::changeEmail(string new_email){
    regex email_regex("^[a-zA-Z0-9+_.-]+@[a-zA-Z0-9.-]+$");
    if(regex_match(new_email, email_regex)){
        email = new_email;
        cout << "Email changed successfully." << endl;
        recordLog("Email changed to " + new_email);
    }
    else{
        cout << "Invalid email format." << endl;
    }
}

void Account::changeUsername(string new_username){
    if(new_username.length() >= 6 && new_username.length() <= 20){
        username = new_username;
        cout << "Username changed successfully." << endl;
        recordLog("Username changed to " + new_username);
    }
    else{
        cout << "Invalid username length. Must be between 6 and 20 characters." << endl;
    }
}

void Account::unregisterAccount(string password){
    if(password == this->password){
        username = "";
        password = "";
        email = "";
        phone_number = "";
        cnic = "";
        date_of_birth = "";
        age = 0;
        balance = 0;
        account_number = 0;
        for(int i = 0; i < 25; i++){
            transactions[i] = "";
        }
        cout << "Account unregistered successfully." << endl;
    }
    else{
        cout << "Invalid password. Account cannot be unregistered." << endl;
    }
}

void Account::setSmsAlerts(string txt){
    sms_alerts = txt;
}

string Account::getSmsAlerts(){
    return sms_alerts;
}

int Account::applyForLoan(string loan_type, double amount)
{
    string amountInString = to_string(amount);
    if (amount > 0)
    {
        if (loan_type == "Personal Loan")
        {
            if (amount <= 1000000)
            {
                cout << "Personal loan applied for successfully." << endl;
                recordTransaction("Personal loan applied for "+ amountInString);
                recordLog("Personal loan applied for " + amountInString);
                balance += amount;
                return 1;
            }
            else
            {
                cout << "Invalid amount. Must be less than or equal to 1000000." << endl;
            }
        }
        else if (loan_type == "Car Loan")
        {
            if (amount <= 5000000)
            {
                cout << "Car loan applied for successfully." << endl;
                recordTransaction("Car loan applied for "+ amountInString);
                recordLog("Car loan applied for " + amountInString);
                balance += amount;
                return 1;
            }
            else
            {
                cout << "Invalid amount. Must be less than or equal to 5000000." << endl;
            }
        }
        else if (loan_type == "House Loan")
        {
            if (amount <= 10000000)
            {
                cout << "House loan applied for successfully." << endl;
                recordTransaction("House loan applied for " + amountInString);
                recordLog("House loan applied for " + amountInString);
                balance += amount;
                return 1;
            }
            else
            {
                cout << "Invalid amount. Must be less than or equal to 10000000." << endl;
            }
        }
        else if (loan_type == "Business Loan")
        {
            if (amount <= 100000)
            {
                cout << "Business loan applied for successfully." << endl;
                recordTransaction("Business loan applied for "+ amountInString);
                recordLog("Business loan applied for " + amountInString);
                balance += amount;
                return 1;
            }
            else
            {
                cout << "Invalid amount for business loan." << endl;
            }
        }
        else if (loan_type == "Student Loan")
        {
            if (amount <= 100000) {
                cout << "Student loan applied for successfully." << endl;
                recordTransaction("Student loan applied for "+ amountInString);
                recordLog("Student loan applied for " + amountInString);
                balance += amount;
                return 1;
            }
            else
            {
                cout << "Invalid amount for student loan." << endl;
            }
        }
        else
        {
            cout << "Invalid loan type." << endl;
        }
    }
    else
    {
        cout << "Invalid amount. Must be non-negative." << endl;
    }
    return 0;
}

void Account::addBeneficiary(string name, string account_number, string bank_name){
    if(name != "" && account_number != "" && bank_name != ""){
        for(int i = 0; i < 10; i++){
            if(beneficiaries_names[i] == ""){
                beneficiaries_names[i] = name;
                beneficiaries_account_numbers[i] = account_number;
                beneficiaries_bank_names[i] = bank_name;
                cout << "Beneficiary added successfully." << endl;
                recordLog("Beneficiary added: " + name);
                return;
            }
        }
        cout << "Beneficiary list full." << endl;
    }
    else{
        cout << "Invalid beneficiary details." << endl;
    }
}
void Account::removeBeneficiary(string name) {
    bool beneficiaryFound = false;
    for (int i = 0; i < 10; i++) {
        if (beneficiaries_names[i] == name) {
            beneficiaries_names[i] = "";
            beneficiaries_account_numbers[i] = "";
            beneficiaries_bank_names[i] = "";
            cout << "Beneficiary " << name << " removed successfully." << endl;
            recordLog("Beneficiary removed: " + name);
            beneficiaryFound = true;
            break;
        }
    }
    if (!beneficiaryFound) {
        cout << "Beneficiary " << name << " not found." << endl;
    }
}

void Account::displayBeneficiaries(){
    for(int i = 0; i < 10; i++){
        if(beneficiaries_names[i] != ""){
            cout << "Beneficiary " << i + 1 << ": " << endl;
            cout << "Name: " << beneficiaries_names[i] << endl;
            cout << "Account Number: " << beneficiaries_account_numbers[i] << endl;
            cout << "Bank Name: " << beneficiaries_bank_names[i] << endl;
        }
    }
}

void Account::schedulePayment(string name, string date, double amount)
{
    if(name != "" && date != "" && amount > 0){
        if(amount <= balance){
            balance -= amount;
            cout << "Payment scheduled successfully." << endl;
            recordTransaction("Payment scheduled: " + name + ", " + date + ", " + to_string(amount));
            recordLog("Payment scheduled: " + name + ", " + to_string(amount));
            for(int i = 0; i < 10; i++){
                if(scheduled_payments[i] == ""){
                    scheduled_payments[i] = name + ", " + date + ", " + to_string(amount);
                    return;
                }
            }
        }
        else{
            cout << "Insufficient balance." << endl;
        }
    }
    else{
        cout << "Invalid payment details." << endl;
    }
}

void Account::displayScheduledPayments(){
    for(int i = 0; i < 10; i++){
        if(scheduled_payments[i] != ""){
            cout << "Payment " << i + 1 << ": " << endl;
            cout << "Name: " << scheduled_payments[i].substr(0, scheduled_payments[i].find(",")) << endl;
            cout << "Date: " << scheduled_payments[i].substr(scheduled_payments[i].find(",") + 2, scheduled_payments[i].find_last_of(",") - scheduled_payments[i].find(",") - 2) << endl;
            cout << "Amount: " << scheduled_payments[i].substr(scheduled_payments[i].find_last_of(",") + 2) << endl;
        }
    }
}

void Account::recordLog(string activity){
    string date_and_time = getCurrentDateTime();
    for(int i = 0; i < 30; i++){
        if(logs[i] == ""){
            logs[i] = "Time: " + date_and_time + " Activity: " + activity;
            return;
        }
    }
}

string Account:: getCurrentDateTime() {
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    string dateTime = ctime(&currentTime);
    dateTime.pop_back(); // Remove the trailing newline character
    return dateTime;
}

string Account::returnLog(int i){
    if(i < 30 && i >= 0){
        return logs[i];
    }
    return "NULL";
}
void Account::displayLogs(){
    for(int i = 0; i < 30; i++){
        if(logs[i] != ""){
            cout << logs[i] << endl;
        }
    }
}
