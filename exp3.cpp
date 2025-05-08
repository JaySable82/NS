#include <iostream>
#include <string>
#include <vector>

using namespace std;

string encryptCaesar(const string& message, int shift) 
{
    string encrypted = "";
    shift = shift % 26;
    if (shift < 0) shift += 26; // Handle negative shifts
    
    for (char c : message) 
    {
        if (isalpha(c)) 
        {
            char base = islower(c) ? 'a' : 'A';
            encrypted += static_cast<char>((c - base + shift) % 26 + base);
        } 
        else 
        {
            // Keep spaces and other characters as is
            encrypted += c;
        }
    }
    
    return encrypted;
}

string decryptCaesar(const string& encrypted, int shift) 
{
    // Decryption is just encryption with the negative shift
    return encryptCaesar(encrypted, 26 - shift);
}

int main() 
{
    string message = "please transfer one million dollars to my swiss bank account six two two four";
    int shift = 3; // Classic Caesar cipher uses shift of 3; Use 5 and 7 if asked in question.
    
    string encrypted = encryptCaesar(message, shift);
    cout << "Original message: " << message << endl;
    cout << "Encrypted (shift " << shift << "): " << encrypted << endl;
    
    string decrypted = decryptCaesar(encrypted, shift);
    cout << "Decrypted: " << decrypted << endl;
    
    return 0;
}