#include <iostream>
#include <string>
#include <limits>

#if defined(_WIN32) || defined(_WIN64)
  #include <conio.h>
  // on Windows, _getch() reads one char without echo
  static char getch_noecho() { return _getch(); }
#else
  #include <termios.h>
  #include <unistd.h>
  // on Unix, implement getch(): turn off echo, read one char, restore
  static char getch_noecho() {
      struct termios oldt, newt;
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ECHO | ICANON);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      char c = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      return c;
  }
#endif

const std::string DEFAULT_PASSWORD = "PICT123";

// Reads a line of input, masking with '*' as the user types.
// Supports backspace editing.
std::string getMaskedInput() {
    std::string password;
    while (true) {
        char c = getch_noecho();
        if (c == '\r' || c == '\n') {
            std::cout << '\n';
            break;
        }
        if (c == '\b' || c == 127) {
            if (!password.empty()) {
                password.pop_back();
                // move cursor back, overwrite, move back again
                std::cout << "\b \b";
            }
        } else {
            password += c;
            std::cout << '*';
        }
    }
    return password;
}

void displayMaskedPassword() {
    std::cout << "Enter the password: ";
    std::string pwd = getMaskedInput();
    if (pwd == DEFAULT_PASSWORD) {
        std::cout << "Correct password: " << pwd << "\n";
    } else {
        std::cout << "Incorrect password.\n";
    }
}

int main() {
    int choice;
    do {
        std::cout << "\n1. Check Default Password\n"
                  << "2. Display Masked Password\n"
                  << "3. Exit\n"
                  << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string input;
                std::cout << "Enter the password: ";
                std::getline(std::cin, input);
                std::cout << (input == DEFAULT_PASSWORD
                              ? "It is the default password.\n"
                              : "It is not the default password.\n");
                break;
            }
            case 2:
                displayMaskedPassword();
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
