#include "mainqt.h"
#include "ui_mainqt.h"
#include <QTimer>
using namespace std;

mainQt::mainQt(QWidget *parent): QMainWindow(parent), ui(new Ui::mainQt) , bank()
{
    bank = Bank();
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->centralwidget->setStyleSheet("images/triangles.png");
    ui->full_sidebar->hide();
    the_great_reset();
    ui->SignUp_CNIC_lineEdit->setInputMask("99999-9999999-9;");
    ui->SignUp_DOB_lineEdit->setInputMask("99/99/9999;");
    ui->cardManagment_expiry_le->setInputMask("99/99;");
    ui->cardManagment_cvc_le->setInputMask("999;");
    ui->cardManagment_number_le->setInputMask("9999 9999 9999 9999;");
    ui->mainPage_collapse_btn->click();
    ui->DonationsPage_btn->hide();
    ui->manageBeneficiariesPage_btn->hide();
    ui->cardManagementPage_btn->hide();
    ui->viewActivityPage_btn->hide();
}
mainQt::~mainQt()
{
    delete ui;
}

void mainQt::on_icon_menu_home_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(0);
    ui->funds_widget->setCurrentIndex(0);
}

void mainQt::on_icon_menu_history_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(1);
}


void mainQt::on_full_menu_home_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(0);
    ui->funds_widget->setCurrentIndex(0);
}

void mainQt::on_full_menu_history_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(1);
}


void mainQt::on_userProfile_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(2);
}

void mainQt::on_changeProfile_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(4);
}


void mainQt::on_full_menu_support_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(3);
}


void mainQt::on_icon_menu_support_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(3);
}


void mainQt::on_Move_To_SignUp_btn_clicked()
{
    ui->LoginSignUpStack->setCurrentIndex(1);
    ui->login_username_lineEdit->clear();
    ui->login_pass_lineEdit->clear();
    border_color_reset();
}

void mainQt::on_ProfileChangePage_back_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(2);
}


void mainQt::on_LoginEnter_btn_clicked()
{
    string name, password;
    int result;
    name = ui->login_username_lineEdit->text().toStdString();
    password = ui->login_pass_lineEdit->text().toStdString();
    const char* nameCharArray = name.c_str();
    const char* passwordCharArray = password.c_str();
    if(!(name=="" || password==""))
    {
        result = bank.login(nameCharArray,passwordCharArray);
    }
    else
    {
        result=0;
    }
    if(result==0)
    {
        ui->login_username_lineEdit->setStyleSheet("border-color: red;");
        ui->login_pass_lineEdit->setStyleSheet("border-color: red;");
    }
    else if(result==1)
    {
        border_color_reset();
        balanceUpdate();
        ui->MainStackWidget->setCurrentIndex(0);
        current_account_profile_setup();
        display_all_billers_in_table();
        display_all_beneficiaries();
        display_all_loan_types();
        display_past_user_transactions();
    }
}


void mainQt::on_SignUpEnter_btn_clicked()
{
    border_color_reset();

    regex CNICPattern("^\\d{5}-\\d{7}-\\d{1}$");
    regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    regex phonePattern("^\\d{11}$");
    regex DOBPattern("^\\d{2}/\\d{2}/\\d{4}$");
    //char name[20], password[20], CNIC[20], phone[20], email[20],DOB[20];
    string name, password, CNIC, phone, email, DOB;
    int age;
    bool pass=1;
    name = ui->SignUp_username_LineEdit->text().toStdString();
    password = ui->SignUp_password_lineEdit->text().toStdString();
    email = ui->SignUp_Email_lineEdit->text().toStdString();
    phone = ui->SignUp_phone_lineEdit->text().toStdString();
    DOB = ui->SignUp_DOB_lineEdit->text().toStdString();
    CNIC = ui->SignUp_CNIC_lineEdit->text().toStdString();
    age = ui->SignUp_Age_lineEdit->text().toInt();
    if(!(name.length() >= 6 && name.length() <= 20))
    {
        pass=0;
        ui->SignUp_username_LineEdit->setStyleSheet("border-color: red;");
    }
    if(!(password.length() >= 8 && password.length() <= 20))
    {
        pass=0;
        ui->SignUp_password_lineEdit->setStyleSheet("border-color: red;");
    }
    if(!regex_match(CNIC, CNICPattern))
    {
        pass=0;
        ui->SignUp_CNIC_lineEdit->setStyleSheet("border-color: red;");
    }
    cout<<phone<<endl;
    if(!regex_match(phone, phonePattern))
    {
        pass=0;
        ui->SignUp_phone_lineEdit->setStyleSheet("border-color: red;");
    }
    if(!regex_match(email, emailPattern))
    {
        pass=0;
        ui->SignUp_Email_lineEdit->setStyleSheet("border-color: red;");
    }
    if(!regex_match(DOB, DOBPattern))
    {
        pass=0;
        ui->SignUp_DOB_lineEdit->setStyleSheet("border-color: red;");
    }
    if(age < 18)
    {
        pass=0;
        ui->SignUp_Age_lineEdit->setStyleSheet("border-color: red;");
    }
    if(pass==1)
    {
        border_color_reset();
        bank.registration(1,name,password,email,phone,CNIC,DOB,age,0);
        current_account_profile_setup();
        balanceUpdate();
        display_past_user_transactions();
        display_all_billers_in_table();
        display_all_beneficiaries();
        display_all_loan_types();
        ui->MainStackWidget->setCurrentIndex(0);
    }
}
void mainQt::border_color_reset()
{
    ui->login_username_lineEdit->setStyleSheet("border-color: black;");
    ui->login_pass_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_Age_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_username_LineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_CNIC_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_DOB_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_password_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_phone_lineEdit->setStyleSheet("border-color: black;");
    ui->SignUp_Email_lineEdit->setStyleSheet("border-color: black;");

    ui->ProfileChange_Email_lineEdit->setStyleSheet("border-color: black;");
    ui->ProfileChange_phone_lineEdit->setStyleSheet("border-color: black;");
    ui->ProfileChange_password_lineEdit->setStyleSheet("border-color: black;");
    ui->ProfileChange_UnregisterPass_lineEdit->setStyleSheet("border-color: black;");

    ui->billpayment_amount_lineEdit->setStyleSheet("border-color: black;");
    ui->amount_sendmoney_lineEdit->setStyleSheet("border-color: black;");
    ui->recieverName_sendmoney_lineEdit->setStyleSheet("border-color: black;");

    ui->loanPage_amount_le->setStyleSheet("border-color: black;");
}
void mainQt::current_account_profile_setup()
{
    ui->profilePage_displayEmail->setText(QString::fromStdString(bank.current_account->getEmail()));
    ui->profilePage_displayAge->setText(QString::number(bank.current_account->getAge()));
    ui->profilePage_displayCNIC->setText(QString::fromStdString(bank.current_account->getCnic()));
    ui->profilePage_displayPhone->setText(QString::fromStdString(bank.current_account->getPhoneNumber()));
    ui->profilePage_displayName->setText(QString::fromStdString(bank.current_account->getUsername()));
    ui->profilePage_displayPassword->setText(QString::fromStdString(bank.current_account->getPassword()));
    ui->profilePage_displayDOB->setText(QString::fromStdString(bank.current_account->getDateOfBirth()));
    ui->ProfileChange_sms_lineEdit->setText(QString::fromStdString(bank.current_account->getSmsAlerts()));
}
void mainQt::logOutClear()
{
    ui->profilePage_displayEmail->clear();
    ui->profilePage_displayAge->clear();
    ui->profilePage_displayCNIC->clear();
    ui->profilePage_displayPhone->clear();
    ui->profilePage_displayName->clear();
    ui->profilePage_displayPassword->clear();
    ui->profilePage_displayDOB->clear();

    ui->SignUp_username_LineEdit->clear();
    ui->SignUp_password_lineEdit->clear();
    ui->SignUp_CNIC_lineEdit->clear();
    ui->SignUp_phone_lineEdit->clear();
    ui->SignUp_Email_lineEdit->clear();
    ui->SignUp_DOB_lineEdit->clear();
    ui->SignUp_Age_lineEdit->clear();

    ui->login_username_lineEdit->clear();
    ui->login_pass_lineEdit->clear();

    //ui->current_balance_output_funds->clear();
    ui->current_balance_output_main->clear();

    ui->ProfileChange_UnregisterPass_lineEdit->clear();
    ui->ProfileChange_Email_lineEdit->clear();
    ui->ProfileChange_password_lineEdit->clear();
    ui->ProfileChange_phone_lineEdit->clear();

    ui->billpayment_amount_lineEdit->clear();
    ui->billpayment_company_lineEdit->clear();

    ui->addmoney_lineEdit->clear();
    ui->amount_sendmoney_lineEdit->clear();

    ui->loanPage_loanType_le->clear();
    ui->loanPage_amount_le->clear();
}
void mainQt::display_all_billers_in_table()
{
    // Set the resize mode of all columns to Stretch.
    ui->billpayment_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->billpayment_table->setRowCount(10);
    for(int i=0;i<10;i++)
    {
        ui->billpayment_table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getBillers(i))));
    }
}
void mainQt::on_billpayment_table_cellClicked(int row, int column)
{
   ui->billpayment_company_lineEdit->clear();
   QTableWidgetItem *cell = ui->billpayment_table->item(row,column);
   QString temp = cell->text();
   ui->billpayment_company_lineEdit->setText(temp);
}
void mainQt::on_billpayment_fr_btn_3_clicked()
{
   double fee, temp = bank.current_account->getBalance();
   string biller;
   string feeStr =  ui->billpayment_amount_lineEdit->text().toStdString();
   biller = ui->billpayment_company_lineEdit->text().toStdString();
   fee = ui->billpayment_amount_lineEdit->text().toDouble();
   if(!((temp-fee)<0))
   {
        bank.current_account->billPayment(biller,fee);
        ui->billpayment_amount_lineEdit->setStyleSheet("border-color: black;");
        notificationBarUpdates("Bill Payment of " + feeStr + " successfully paid to " + biller,1);
   }
   else
   {
        ui->billpayment_amount_lineEdit->setStyleSheet("border-color: red;");
   }
   balanceUpdate();
   ui->billpayment_amount_lineEdit->clear();
   ui->billpayment_company_lineEdit->clear();

}

void mainQt::display_past_user_transactions()
{
   ui->transactionsTable->setRowCount(25);
   ui->transactionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   for(int i=0;i<25;i++)
   {
        ui->transactionsTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getTransactions(i))));
   }
}
void mainQt::on_icon_menu_logout_btn_clicked()
{
    logOutClear();
    ui->MainStackWidget->setCurrentIndex(1);
    bank.logout();
    the_great_reset();
}


void mainQt::on_full_menu_logout_btn_clicked()
{
    logOutClear();
    ui->MainStackWidget->setCurrentIndex(1);
    bank.logout();
    the_great_reset();
}


void mainQt::on_Move_To_logIn_btn_clicked()
{
    ui->LoginSignUpStack->setCurrentIndex(0);
    ui->SignUp_Age_lineEdit->clear();
    ui->SignUp_CNIC_lineEdit->clear();
    ui->SignUp_DOB_lineEdit->clear();
    ui->SignUp_password_lineEdit->clear();
    ui->SignUp_Email_lineEdit->clear();
    ui->SignUp_username_LineEdit->clear();
    border_color_reset();
}


void mainQt::on_billpayment_option_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(2);
}


void mainQt::on_sendmoney_option_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(1);
}


void mainQt::on_addmoney_option_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(3);
    displayCardsTable();
}



void mainQt::on_sendmoney_fr_btn_clicked()
{
    string name;
    double money;
    string moneyStr = ui->amount_sendmoney_lineEdit->text().toStdString();
    name = ui->recieverName_sendmoney_lineEdit->text().toStdString();
    money = ui->amount_sendmoney_lineEdit->text().toDouble();
    int result = bank.fundsTransfer(money,name);
    if(result==0)
    {
        ui->recieverName_sendmoney_lineEdit->setStyleSheet("border-color: red;");
    }
    else if(result == 1)
    {
        ui->amount_sendmoney_lineEdit->setStyleSheet("border-color: red;");
    }
    else if(result == 2)
    {
       ui->recieverName_sendmoney_lineEdit->setStyleSheet("border-color: black;");
       ui->amount_sendmoney_lineEdit->setStyleSheet("border-color: black;");
       notificationBarUpdates("Amount of " + moneyStr + " successfully sent to " + name,1);
    }
    balanceUpdate();
    ui->recieverName_sendmoney_lineEdit->clear();
    ui->amount_sendmoney_lineEdit->clear();
}



void mainQt::on_addmoney_fr_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
}


void mainQt::on_sideBar_btn_2_clicked()
{
    ui->icon_only_sidebar->hide();
    ui->full_sidebar->show();
}


void mainQt::on_sideBar_btn_clicked()
{
    ui->full_sidebar->hide();
    ui->icon_only_sidebar->show();
}
void mainQt::the_great_reset()
{
    ui->funds_widget->setCurrentIndex(0);
    ui->LoginSignUpStack->setCurrentIndex(0);
    ui->MainStackWidget->setCurrentIndex(1);
    ui->MenuPages->setCurrentIndex(0);
}

void mainQt::on_profile_back_btn_clicked()
{
    ui->MenuPages->setCurrentIndex(0);
}

void mainQt::on_exitIcon_btn_clicked()
{
    bank.logout();
}


void mainQt::on_fullmenu_exit_btn_clicked()
{
    bank.logout();
}


void mainQt::on_addmoney_fr_btn_clicked()
{
    double money;
    string moneyStr = ui->addmoney_lineEdit->text().toStdString();
    string cardNum = ui->addMoney_card_le->text().toStdString();
    string type = ui->addMoney_card_type_le->text().toStdString();
    money = ui->addmoney_lineEdit->text().toDouble();
    bank.current_account->deposit(money,cardNum,type);
    notificationBarUpdates("Amount of " + moneyStr + " successfully added to wallet",1);
    balanceUpdate();

}

void mainQt::balanceUpdate()
{
    display_past_user_transactions();
    ui->current_balance_output_main->setText(QString::number(bank.current_account->getBalance()));
    //ui->current_balance_output_funds->setText(QString::number(bank.current_account->getBalance()));
}




void mainQt::on_ProfileChangePage_smsToggle_btn_clicked()
{
    string sms = ui->ProfileChange_sms_lineEdit->text().toStdString();
    if(sms=="Disabled")
    {
        bank.current_account->setSmsAlerts("Enabled");
    }
    else if(sms=="Enabled")
    {
        bank.current_account->setSmsAlerts("Disabled");
    }
    ui->ProfileChange_sms_lineEdit->setText(QString::fromStdString(bank.current_account->getSmsAlerts()));
}


void mainQt::on_ProfileChangePage_changeDetails_btn_2_clicked()
{
    regex emailPattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    regex phonePattern("^\\d{11}$");
    bool pass=1;
    string email, phone, password;
    email = ui->ProfileChange_Email_lineEdit->text().toStdString();
    phone = ui->ProfileChange_phone_lineEdit->text().toStdString();
    password = ui->ProfileChange_password_lineEdit->text().toStdString();
    if(!email.empty())
    {
        if(!regex_match(email, emailPattern))
        {
            pass=0;
            ui->ProfileChange_Email_lineEdit->setStyleSheet("border-color: red;");
        }
    }
    if(!password.empty())
    {
        if(!(password.length() >= 8 && password.length() <= 20))
        {
            pass=0;
            ui->ProfileChange_password_lineEdit->setStyleSheet("border-color: red;");
        }
    }
    if(!phone.empty())
    {
        if(!regex_match(phone, phonePattern))
        {
            pass=0;
            ui->ProfileChange_phone_lineEdit->setStyleSheet("border-color: red;");
        }
    }
    if(pass==1)
    {
        ui->ProfileChange_phone_lineEdit->setStyleSheet("border-color: black;");
        ui->ProfileChange_password_lineEdit->setStyleSheet("border-color: black;");
        ui->ProfileChange_Email_lineEdit->setStyleSheet("border-color: black;");
        if(!phone.empty())
            bank.current_account->setPhoneNumber(phone);
        if(!password.empty())
            bank.current_account->setPassword(password);
        if(!email.empty())
            bank.current_account->setEmail(email);

        current_account_profile_setup();
    }
}


void mainQt::on_ProfileChangePage_UnregisterAccount_btn_clicked()
{
    string password = ui->ProfileChange_UnregisterPass_lineEdit->text().toStdString();
    if(password==bank.current_account->getPassword())
    {
        bank.current_account->unregisterAccount(password);
        border_color_reset();
        logOutClear();
        ui->MainStackWidget->setCurrentIndex(1);
        bank.logout();
        the_great_reset();
    }
    else
    {
        ui->ProfileChange_UnregisterPass_lineEdit->setStyleSheet("border-color: red;");
    }
}


void mainQt::on_BillPayment_fr_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
    border_color_reset();
}

void mainQt::display_all_beneficiaries()
{
    ui->beneficiaries_table->setRowCount(10);
    ui->beneficiaries_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<10;i++)
    {
        ui->beneficiaries_table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getBeneficiaryName(i))));
        cout<<bank.current_account->getNameOfBeneficiaries(i)<<endl;
        cerr<<bank.current_account->getNameOfBeneficiaries(i)<<endl;
    }
}
void mainQt::on_beneficiaries_table_cellClicked(int row, int column)
{
    ui->recieverName_sendmoney_lineEdit->clear();
    QTableWidgetItem *cell = ui->beneficiaries_table->item(row,column);
    QString temp = cell->text();
    ui->recieverName_sendmoney_lineEdit->setText(temp);
}
void mainQt::on_loan_option_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(6);
    ui->loanPage_amount_le->clear();
    ui->loanPage_loanType_le->clear();
}
void mainQt::display_all_loan_types()
{
    ui->LoanTable->setRowCount(5);
    ui->LoanTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<5;i++)
    {
        ui->LoanTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getLoanTypes(i))));
    }
}
void mainQt::on_LoanTable_cellClicked(int row, int column)
{
    ui->loanPage_loanType_le->clear();
    QTableWidgetItem *cell = ui->LoanTable->item(row,column);
    QString temp = cell->text();
    ui->loanPage_loanType_le->setText(temp);
}


void mainQt::on_LoanPage_fr_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
    ui->loanPage_amount_le->clear();
    ui->loanPage_loanType_le->clear();
    border_color_reset();
}

void mainQt::on_loanPage_confirmLoan_btn_clicked()
{
    display_all_loan_types();
    string loanType;
    double loanAmount;
    string loanAmountString = ui->loanPage_amount_le->text().toStdString();
    loanType = ui->loanPage_loanType_le->text().toStdString();
    loanAmount = ui->loanPage_amount_le->text().toDouble();
    int result = bank.current_account->applyForLoan(loanType,loanAmount);
    if(result==1)
    {
        ui->loanPage_amount_le->setStyleSheet("border-color: black;");
        ui->loanPage_amount_le->clear();
        ui->loanPage_loanType_le->clear();
        balanceUpdate();
        notificationBarUpdates("Loan successful",1);
    }
    else
    ui->loanPage_amount_le->setStyleSheet("border-color: red;");
    notificationBarUpdates("Loan unsuccessful",0);
    ui->loanPage_loanType_le->clear();
    ui->loanPage_amount_le->clear();
}

void mainQt::on_viewActivityPage_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(7);
    viewActivity();
}
void mainQt::viewActivity()
{
    ui->activityTable->setRowCount(30);
    ui->activityTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<30;i++)
    {
        ui->activityTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->returnLog(i))));
    }
}
void mainQt::on_manageBeneficiariesPage_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(6);
    ui->beneficiaries_toggle_le->setText("Add");
    ui->addBeneficiary_bankName_le->show();
    ui->addBeneficiary_id_le->show();
    ui->beneficiary_bankname_label->show();
    ui->beneficiary_userID_label->show();
}


void mainQt::on_viewActivity_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
}


void mainQt::on_Beneficiary_toggle_btn_clicked()
{
    ui->addBeneficiary_bankName_le->clear();
    ui->addBeneficiary_name_le->clear();
    ui->addBeneficiary_id_le->clear();
    string toggle = ui->beneficiaries_toggle_le->text().toStdString();
    if(toggle=="Add")
    {
        ui->beneficiaries_toggle_le->setText("Remove");
        ui->addBeneficiary_bankName_le->hide();
        ui->addBeneficiary_id_le->hide();
        ui->beneficiary_bankname_label->hide();
        ui->beneficiary_userID_label->hide();
    }
    else if(toggle=="Remove")
    {
        ui->addBeneficiary_bankName_le->show();
        ui->addBeneficiary_id_le->show();
        ui->beneficiary_bankname_label->show();
        ui->beneficiary_userID_label->show();
        ui->beneficiaries_toggle_le->setText("Add");
    }

}
void mainQt::on_BeneficiaryAddRemove_confirm_btn_clicked()
{
    string bankName, username, userID;
    string toggle = ui->beneficiaries_toggle_le->text().toStdString();
    bool pass=1;
    bankName = ui->addBeneficiary_bankName_le->text().toStdString();
    username = ui->addBeneficiary_name_le->text().toStdString();
    userID = ui->addBeneficiary_id_le->text().toStdString();
    if(username.empty())
        pass=0;
    if(pass==1)
    {
        if(toggle=="Add")
        {
            if(bankName.empty())
                pass=0;
            if(userID.empty())
                pass=0;
            if(pass==1)
            {
                bank.current_account->addBeneficiary(username,userID,bankName);
                ui->addBeneficiary_bankName_le->clear();
                ui->addBeneficiary_name_le->clear();
                ui->addBeneficiary_id_le->clear();
                notificationBarUpdates("Beneficiary successfully added",1);
            }
        }
        else if(toggle=="Remove")
        {
            bank.current_account->removeBeneficiary(username);
            ui->addBeneficiary_name_le->clear();
            notificationBarUpdates("Beneficiary successfuly removed",1);
        }
    }

}


void mainQt::on_sendMoney_fr_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
    ui->addBeneficiary_bankName_le->clear();
    ui->addBeneficiary_name_le->clear();
    ui->addBeneficiary_id_le->clear();
}


void mainQt::on_addBeneficiary_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
}

void mainQt::on_cardManagementPage_btn_clicked()
{
    ui->cardManagement_toggle_le->setText("Add Card");
    displayCardsTable();
    ui->funds_widget->setCurrentIndex(5);
    ui->CardsTable->hide();
    ui->label_62->show();
    ui->cardManagment_cvc_le->show();
    ui->label_63->show();
    ui->cardManagment_expiry_le->show();
    ui->cardManagment_type_le->clear();
    ui->cardManagment_number_le->clear();
    ui->cardManagment_expiry_le->clear();
    ui->cardManagment_cvc_le->clear();
}


void mainQt::on_DonationsPage_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(4);
    displayDonationsTable();
    ui->DonationPage_organisation_le->clear();
    ui->DonationPage_Amount_le->clear();
}



void mainQt::on_DonationsPage_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
}


void mainQt::on_cardManagement_back_btn_clicked()
{
    ui->funds_widget->setCurrentIndex(0);
}


void mainQt::on_cardManagement_removeAddToggle_btn_clicked()
{
    string toggle = ui->cardManagement_toggle_le->text().toStdString();
    if(toggle=="Add Card")
    {
        ui->cardManagement_toggle_le->setText("Remove Card");
        ui->CardsTable->show();
        ui->label_62->hide();
        ui->cardManagment_cvc_le->hide();
        ui->label_63->hide();
        ui->cardManagment_expiry_le->hide();
    }
    else if(toggle=="Remove Card")
    {
        ui->cardManagement_toggle_le->setText("Add Card");
        displayCardsTable();
        ui->CardsTable->hide();
        ui->label_62->show();
        ui->cardManagment_cvc_le->show();
        ui->label_63->show();
        ui->cardManagment_expiry_le->show();
    }
}


void mainQt::on_cardManagement_confirm_btn_clicked()
{
    string cardType, cardNumber, cardExpiry, cvc;
    string addRemove = ui->cardManagement_toggle_le->text().toStdString();
    cardType = ui->cardManagment_type_le->text().toStdString();
    cardNumber = ui->cardManagment_number_le->text().toStdString();
    cardExpiry = ui->cardManagment_expiry_le->text().toStdString();
    cvc = ui->cardManagment_cvc_le->text().toStdString();
    if(addRemove=="Add Card")
    {
        bank.current_account->addCard(cardNumber,cardExpiry,cvc,cardType);
        notificationBarUpdates("Card successfully added",1);
    }
    else if(addRemove=="Remove Card")
    {
        bank.current_account->removeCard(cardNumber);
        notificationBarUpdates("Card successfully removed",1);
    }
    displayCardsTable();
    ui->cardManagment_type_le->clear();
    ui->cardManagment_number_le->clear();
    ui->cardManagment_expiry_le->clear();
    ui->cardManagment_cvc_le->clear();
}

void mainQt::displayDonationsTable()
{
    ui->DonationsTable->setRowCount(5);
    ui->DonationsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<5;i++)
    {
        ui->DonationsTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getDonations(i))));
    }

}
void mainQt::displayCardsTable()
{
    ui->CardsTable->setRowCount(5);
    ui->CardsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<5;i++)
    {
        ui->CardsTable->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getCardNumbers(i))));
    }
    ui->CardsTable_2->setRowCount(5);
    ui->CardsTable_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for(int i=0;i<5;i++)
    {
        ui->CardsTable_2->setItem(i,0,new QTableWidgetItem(QString::fromStdString(bank.current_account->getCardNumbers(i))));
    }
}
void mainQt::notificationBarUpdates(string noti,bool result)
{
    if(result)
    {
        ui->notificationbar_le->setStyleSheet("color: green; background-color: #1a1a1a;font-size: 14px;");
    }
    else
    {
        ui->notificationbar_le->setStyleSheet("color: red; background-color: #1a1a1a;font-size: 14px;");
    }
    ui->notificationbar_le->setText(QString::fromStdString(noti));

    // Create a QTimer to clear the text after 5000 milliseconds (5 seconds)
    QTimer::singleShot(5000, this, [=]()
    {
        ui->notificationbar_le->clear();
    });
}
void mainQt::on_CardsTable_cellClicked(int row,int column)
{
    QString cardNum = ui->CardsTable->item(row, column)->text();
    ui->cardManagment_number_le->setText(cardNum);
    ui->cardManagment_type_le->setText(QString::fromStdString(bank.current_account->getCardTypes(row)));
}
void mainQt::on_CardsTable_2_cellClicked(int row, int column)
{
    QString cardNum = ui->CardsTable_2->item(row, column)->text();
    ui->addMoney_card_le->setText(cardNum);
    ui->addMoney_card_type_le->setText(QString::fromStdString(bank.current_account->getCardTypes(row)));
}


void mainQt::on_DonationsTable_cellClicked(int row, int column)
{
    QString org = ui->DonationsTable->item(row, 0)->text();
    ui->DonationPage_organisation_le->setText(org);
}




void mainQt::on_DonationPage_confirm_btn_clicked()
{
    string organisation = ui->DonationPage_organisation_le->text().toStdString();
    int amount = ui->DonationPage_Amount_le->text().toInt();
    string amountstr = ui->DonationPage_Amount_le->text().toStdString();
    bool result = bank.current_account->donateMoney(organisation,amount);
    if(result)
    {
        notificationBarUpdates("Donation successful",1);
    }
    else
    {
        notificationBarUpdates("Donation unsuccessful",0);
    }
    ui->DonationPage_organisation_le->clear();
    ui->DonationPage_Amount_le->clear();
    balanceUpdate();
}

