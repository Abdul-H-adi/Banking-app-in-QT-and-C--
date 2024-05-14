#ifndef MAINQT_H
#define MAINQT_H
#include "Account.h"
#include "Bank.h"
#include<cstring>
#include <QMainWindow>
#include <QStackedWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class mainQt; }
QT_END_NAMESPACE
class mainQt : public QMainWindow
{
    Q_OBJECT
public:
    mainQt(QWidget *parent = nullptr);
    ~mainQt();

private:
    Ui::mainQt *ui;
    Bank bank;
private slots:

    void on_icon_menu_home_btn_clicked();
    void on_icon_menu_history_btn_clicked();
    void on_full_menu_home_btn_clicked();
    void on_full_menu_history_btn_clicked();
    void on_userProfile_btn_clicked();
    void on_Move_To_SignUp_btn_clicked();
    void on_LoginEnter_btn_clicked();
    void on_SignUpEnter_btn_clicked();
    void on_icon_menu_logout_btn_clicked();
    void on_full_menu_logout_btn_clicked();
    void on_Move_To_logIn_btn_clicked();
    void on_billpayment_option_btn_clicked();
    void on_sendmoney_option_btn_clicked();
    void on_addmoney_option_btn_clicked();
    void on_sendmoney_fr_btn_clicked();
    void on_addmoney_fr_back_btn_clicked();
    void on_BillPayment_fr_back_btn_clicked();
    void on_sideBar_btn_2_clicked();
    void on_sideBar_btn_clicked();

    void the_great_reset();
    void display_all_billers_in_table();
    void display_past_user_transactions();
    void display_all_beneficiaries();
    void display_all_loan_types();
    void viewActivity();
    void displayDonationsTable();
    void displayCardsTable();

    void current_account_profile_setup();
    void logOutClear();
    void balanceUpdate();
    void border_color_reset();
    void notificationBarUpdates(string noti, bool result);

    void on_profile_back_btn_clicked();
    void on_exitIcon_btn_clicked();
    void on_fullmenu_exit_btn_clicked();
    void on_billpayment_table_cellClicked(int row, int column);
    void on_billpayment_fr_btn_3_clicked();
    void on_addmoney_fr_btn_clicked();

    void on_changeProfile_btn_clicked();
    void on_full_menu_support_btn_clicked();
    void on_icon_menu_support_btn_clicked();
    void on_ProfileChangePage_back_btn_clicked();
    void on_ProfileChangePage_smsToggle_btn_clicked();
    void on_ProfileChangePage_changeDetails_btn_2_clicked();
    void on_ProfileChangePage_UnregisterAccount_btn_clicked();
    void on_loan_option_btn_clicked();
    void on_beneficiaries_table_cellClicked(int row, int column);
    void on_LoanTable_cellClicked(int row, int column);
    void on_LoanPage_fr_back_btn_clicked();
    void on_loanPage_confirmLoan_btn_clicked();
    void on_viewActivityPage_btn_clicked();
    void on_manageBeneficiariesPage_btn_clicked();
    void on_viewActivity_back_btn_clicked();
    void on_Beneficiary_toggle_btn_clicked();
    void on_BeneficiaryAddRemove_confirm_btn_clicked();
    void on_sendMoney_fr_back_btn_clicked();
    void on_addBeneficiary_back_btn_clicked();
    void on_cardManagementPage_btn_clicked();
    void on_DonationsPage_btn_clicked();
    void on_DonationsPage_back_btn_clicked();
    void on_cardManagement_back_btn_clicked();
    void on_cardManagement_removeAddToggle_btn_clicked();
    void on_cardManagement_confirm_btn_clicked();
    void on_CardsTable_2_cellClicked(int row, int column);
    void on_DonationsTable_cellClicked(int row, int column);
    void on_CardsTable_cellClicked(int row, int column);
    void on_DonationPage_confirm_btn_clicked();
};
#endif // MAINQT_H
