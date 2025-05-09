#include <iostream>
#include <string>
using namespace std;
int main()
{
string password = "Admin123";
cout << "Press:\n";
cout << "1. Check the default password\n";
cout << "2. Reset password\n";
cout << "3. Print masked password\n";
cout << "4. Exit\n";
while (true)
{
cout << "\nChoose: ";
int choice;
cin >> choice;
if (choice == 1)
{
string pass;
cout << "\nEnter the password : ";
cin >> pass;
if (pass == password)
{
cout << "It is default password" << endl;
}
else
{
cout << "You have entered wrong password";
}
}
else if (choice == 2)
{
string oldPass, newPass;
cout << "Enter current password: ";
cin >> oldPass;
if (oldPass == password)
{
cout << "Enter new password: ";
cin >> newPass;
password = newPass;
cout << "Password updated successfully." << endl;
}
else
{
cout << "Incorrect current password. Password not updated." << endl;
}
}
else if (choice == 3)
{
cout << "Masked password: ";
for (int i = 0; i < password.size(); i++)
{
cout << "*";
}
cout << endl;
}
else if (choice == 4)
{
cout << "Exited" << endl;
break;
}
else
{
cout << "Invalid choice. Try again!" << endl;
}
}
return 0;
}