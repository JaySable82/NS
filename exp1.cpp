#include <iostream>
#include <string>
using namespace std;

const string DEFAULT_PASSWORD = "PICT123";

void checkDefaultPassword() {
    string input;
    cout << "Enter the Password: ";
    cin >> input;
    if (input == DEFAULT_PASSWORD)
        cout << "It is the default password.\n";
    else
        cout << "It is not the default password.\n";
}

void displayMaskedPassword() {
    string password;
    cout << "Enter the Password: ";
    cin >> password;
    cout << "Masked Password: ";
    for (char c : password)
        cout << (isalpha(c) ? c : '*');
    cout << "\n";
}

void displayPlainTextPassword() {
    string password;
    cout << "Enter the Password: ";
    cin >> password;
    cout << "Plain Text Password: " << password << "\n";
}

int main() {
    int choice;
    do {
        cout << "\n1 - Check Default Password\n2 - Display Masked Password\n3 - Display Plain Text\n4 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: checkDefaultPassword(); break;
            case 2: displayMaskedPassword(); break;
            case 3: displayPlainTextPassword(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid option. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
