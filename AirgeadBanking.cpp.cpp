/*******************************************************
 * Name:        Lou Carron
 * Class:       CS 210: Programming Languages
 * Project:     Project Two – Airgead Banking App
 * Date:        November 29, 2025
 * Description:
 *     This program simulates an investment calculator for
 *     Airgead Banking. It allows users to enter their
 *     initial investment amount, monthly deposit, interest
 *     rate, and number of years. It then generates two
 *     balance & interest reports:
 *
 *     1. Without additional monthly deposits
 *     2. With monthly deposits
 *
 *     The program outputs year-end balances and earned
 *     interest following Airgead Banking requirements.
 *******************************************************/

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

//-----------------------------------------------------------
//  Class: Investment
//  Holds the user input and prints the two required reports
//-----------------------------------------------------------
class Investment {
private:
    double initialAmount;
    double monthlyDeposit;
    double annualInterest;  // percent, e.g. 5 for 5%
    int    years;

public:
    Investment()
        : initialAmount(0.0), monthlyDeposit(0.0),
        annualInterest(0.0), years(0) {
    }

    //-------------------------------------------------------
    // Read and validate all user input
    //-------------------------------------------------------
    void getInput() {
        cout << "**********************************" << endl;
        cout << "********** Data Input ************" << endl << endl;

        // Initial investment
        cout << "Initial Investment Amount: $";
        while (!(cin >> initialAmount) || initialAmount < 0.0) {
            cout << "  Please enter a non-negative number: $";
            clearInput();
        }

        // Monthly deposit
        cout << "Monthly Deposit: $";
        while (!(cin >> monthlyDeposit) || monthlyDeposit < 0.0) {
            cout << "  Please enter a non-negative number: $";
            clearInput();
        }

        // Annual interest (as percent)
        cout << "Annual Interest: %";
        while (!(cin >> annualInterest) || annualInterest < 0.0) {
            cout << "  Please enter a non-negative number: %";
            clearInput();
        }

        // Number of years
        cout << "Number of Years: ";
        while (!(cin >> years) || years <= 0) {
            cout << "  Please enter a positive whole number: ";
            clearInput();
        }

        // Clear newline left in the buffer so we can pause later
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << endl;
        cout << "Press any key to continue...";
        cin.get();
        cout << endl << endl;
    }

    //-------------------------------------------------------
    // Print both required tables
    //-------------------------------------------------------
    void printReports() const {
        cout << fixed << setprecision(2);

        printHeader(false);
        reportWithoutDeposit();
        cout << endl << endl;

        printHeader(true);
        reportWithDeposit();
        cout << endl;
    }

private:
    //-------------------------------------------------------
    // Utility: clear failed input and discard the line
    //-------------------------------------------------------
    static void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //-------------------------------------------------------
    // Print table header (with / without monthly deposit)
    //-------------------------------------------------------
    void printHeader(bool withDeposit) const {
        cout << "*******************************" << endl;
        if (withDeposit) {
            cout << "  Balance and Interest With" << endl;
            cout << "  Additional Monthly Deposits" << endl;
        }
        else {
            cout << "  Balance and Interest Without" << endl;
            cout << "  Additional Monthly Deposits" << endl;
        }
        cout << "*******************************" << endl;

        cout << left << setw(6) << "Year"
            << setw(20) << "Year End Balance"
            << setw(25) << "Year End Earned Interest" << endl;

        cout << string(6 + 20 + 25, '=') << endl;
    }

    //-------------------------------------------------------
    // Scenario 1: No additional monthly deposits
    //-------------------------------------------------------
    void reportWithoutDeposit() const {
        double balance = initialAmount;
        double monthlyRate = (annualInterest / 100.0) / 12.0;

        for (int year = 1; year <= years; ++year) {
            double interestEarnedYear = 0.0;

            for (int month = 1; month <= 12; ++month) {
                double interest = balance * monthlyRate;
                interestEarnedYear += interest;
                balance += interest;
            }

            cout << left << setw(6) << year
                << "$" << setw(19) << balance
                << "$" << setw(24) << interestEarnedYear << endl;
        }
    }

    //-------------------------------------------------------
    // Scenario 2: With monthly deposits
    //-------------------------------------------------------
    void reportWithDeposit() const {
        double balance = initialAmount;
        double monthlyRate = (annualInterest / 100.0) / 12.0;

        for (int year = 1; year <= years; ++year) {
            double interestEarnedYear = 0.0;

            for (int month = 1; month <= 12; ++month) {
                // Add the monthly deposit before interest is applied
                balance += monthlyDeposit;

                double interest = balance * monthlyRate;
                interestEarnedYear += interest;
                balance += interest;
            }

            cout << left << setw(6) << year
                << "$" << setw(19) << balance
                << "$" << setw(24) << interestEarnedYear << endl;
        }
    }
};

//-----------------------------------------------------------
// main: creates Investment object, gets input, prints tables
//-----------------------------------------------------------
int main() {
    Investment investment;

    investment.getInput();
    investment.printReports();

    cout << endl;
    return 0;
}
