#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

string encrypt(const string& message, const string& key) 
{
    // Create char to index mapping
    map<char, int> char_index;
    for (int i = 0; i < key.length(); i++) 
    {
        char_index[key[i]] = i;
    }
    
    // Store the positions of spaces
    vector<int> space_positions;
    for (int i = 0; i < message.length(); i++) 
    {
        if (message[i] == ' ') 
        {
            space_positions.push_back(i);
        }
    }
    
    // Remove spaces for encryption
    string processed_message = message;
    processed_message.erase(remove(processed_message.begin(), processed_message.end(), ' '),processed_message.end());
    
    // Sort the key for column ordering
    string sorted_key = key;
    sort(sorted_key.begin(), sorted_key.end());
    
    int keyLength = key.length();
    int messageLength = processed_message.length();
    int rows = (messageLength / keyLength) + (messageLength % keyLength > 0 ? 1 : 0);
    
    // Create the matrix and fill it with the message
    vector<vector<char>> matrix(rows, vector<char>(keyLength, ' '));
    
    int k = 0;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < keyLength; j++) 
        {
            if (k < messageLength) 
            {
                matrix[i][j] = processed_message[k++];
            }
        }
    }
    
    // Read out the encrypted message column by column based on the key order
    string encrypted = "";
    for (int i = 0; i < keyLength; i++) 
    {
        int col = char_index[sorted_key[i]];
        for (int j = 0; j < rows; j++) 
        {
            if (matrix[j][col] != ' ') 
            {
                encrypted.push_back(matrix[j][col]);
            }
        }
    }
    
    return encrypted;
}

string decrypt(const string& encrypted, const string& key, const vector<int>& space_positions) 
{
    // Create mapping from original key to sorted positions
    map<char, int> char_index;
    for (int i = 0; i < key.length(); i++) 
    {
        char_index[key[i]] = i;
    }
    
    string sorted_key = key;
    sort(sorted_key.begin(), sorted_key.end());
    
    int keyLength = key.length();
    int encryptedLength = encrypted.length();
    int rows = (encryptedLength / keyLength) + (encryptedLength % keyLength > 0 ? 1 : 0);
    
    // Calculate how many characters in each column
    vector<int> col_lengths(keyLength, rows);
    int remaining = encryptedLength % keyLength;
    if (remaining > 0) 
    {
        for (int i = keyLength - 1; i >= keyLength - remaining; i--) 
        {
            col_lengths[i]--;
        }
    }
    
    // Create the decryption matrix
    vector<vector<char>> matrix(rows, vector<char>(keyLength, ' '));
    
    // Fill the matrix column by column according to the encrypted message
    int k = 0;
    for (int i = 0; i < keyLength; i++) 
    {
        int col = char_index[sorted_key[i]];
        for (int j = 0; j < rows && (j < col_lengths[col] || (col_lengths[col] == rows)); j++) 
        {
            if (k < encrypted.length()) 
            {
                matrix[j][col] = encrypted[k++];
            }
        }
    }
    
    // Read out row by row to get the original message without spaces
    string decrypted = "";
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < keyLength; j++) 
        {
            if (matrix[i][j] != ' ') 
            {
                decrypted.push_back(matrix[i][j]);
            }
        }
    }
    
    // Restore spaces
    for (size_t i = 0; i < space_positions.size(); i++) 
    {
        int pos = space_positions[i];
        if (pos <= decrypted.length()) 
        {
            decrypted.insert(pos, 1, ' ');
        }
    }
    
    return decrypted;
}

int main() 
{
    string key = "MEGABUCK";
    string message = "please transfer one million dollars to my swiss bank account six two two four";
    
    // Store the positions of spaces
    vector<int> space_positions;
    for (int i = 0; i < message.length(); i++) 
    {
        if (message[i] == ' ') 
        {
            space_positions.push_back(i);
        }
    }
    
    string encrypted = encrypt(message, key);
    cout << "Original message: " << message << endl;
    cout << "Encrypted: " << encrypted << endl;
    
    string decrypted = decrypt(encrypted, key, space_positions);
    cout << "Decrypted: " << decrypted << endl;
    
    return 0;
}