#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace std::chrono;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Game Configuration
const int MAX_LEVEL = 4;
int currentLevel = 1;
int playerScore = 0;
bool gameOver = false;

// NetworkPacket structure
struct NetworkPacket {
    string srcIP;
    string destIP;
    string protocolType;
    string headerInfo;
    string dataPayload;
    unsigned int packetChecksum;
    unsigned short srcPort;
    unsigned short destPort;
    string encryptionMethod;
    bool isEncryptedFlag;
    unsigned int uniquePacketID;
};

// Utility functions
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void typewriter(const string& text, int speed = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(milliseconds(speed));
    }
}

void printHeader(const string& title) {
    cout << BOLD CYAN "\n=== " << title << " ===\n\n" RESET;
}

void printSuccess(const string& msg) {
    cout << GREEN << "[✓] " << msg << RESET << endl;
}

void printError(const string& msg) {
    cout << RED << "[✗] " << msg << RESET << endl;
}

void pressAnyKey() {
    cout << MAGENTA "\nPress any key to continue..." RESET;
    cin.ignore();
    cin.get();
}

// Clear input buffer to avoid leftover newlines
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Random number generator with better randomness
unsigned int generateRandomID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100000);
    return dist(gen);
}

// Level 1 Functions
void teachLinuxCommands() {
    clearScreen();
    printHeader("LINUX COMMAND TUTORIAL");
    
    typewriter("Essential Linux commands:\n\n");
    typewriter("1. File Operations:\n");
    typewriter("   ls - List files\n   cd - Change directory\n");
    typewriter("   mkdir - Create directory\n   rm - Remove files\n");
    typewriter("   cp - Copy files\n   mv - Move/rename files\n\n");
    
    typewriter("2. Process Management:\n");
    typewriter("   ps - View processes\n   kill - Terminate processes\n");
    typewriter("   top - System monitor\n\n");
    
    typewriter("3. Network Commands:\n");
    typewriter("   ping - Test connectivity\n   ifconfig - Network config\n");
    typewriter("   netstat - Network stats\n   ssh - Secure shell\n\n");
    
    pressAnyKey();
}

bool level1() {
    teachLinuxCommands();
    
    clearScreen();
    printHeader("LEVEL 1: LINUX COMMAND CHALLENGE");
    
    vector<pair<string, string>> challenges = {
        {"List all files (including hidden)", "ls -a"},
        {"Create directory 'documents'", "mkdir documents"},
        {"Show running processes", "ps aux"},
        {"Ping google.com 3 times", "ping -c 3 google.com"},
        {"Change permissions of secret.txt to owner read-only", "chmod 400 secret.txt"}
    };

    int score = 0;
    for (const auto& challenge : challenges) {
        clearScreen();
        cout << "Task " << (score + 1) << "/5\n\n";
        cout << challenge.first << "\n> ";
        
        string input;
        getline(cin, input);
        
        if (input == challenge.second) {
            score++;
            printSuccess("Correct! +20 points");
            playerScore += 20;
        } else {
            printError("Incorrect! Correct answer: " + challenge.second);
        }
        pressAnyKey();
    }
    
    if (score >= 3) {
        printSuccess("LEVEL 1 COMPLETED!");
        return true;
    }
    return false;
}

// Level 2 Functions (Password Security)
bool level2() {
    clearScreen();
    printHeader("LEVEL 2: PASSWORD SECURITY");
    
    typewriter("In this level, we will explore password cracking techniques.\n");
    typewriter("To proceed, crack the following password using a brute-force method.\n\n");
    
    string password = "qwerty123"; // Sample password
    string attempt;
    int attempts = 0;

    while (true) {
        clearScreen();
        cout << "Enter the password attempt: ";
        cin >> attempt;
        attempts++;
        
        if (attempt == password) {
            printSuccess("Password cracked! It took " + to_string(attempts) + " attempts.");
            playerScore += 50;
            return true;
        } else {
            printError("Incorrect password. Try again.");
        }
    }
}

// Level 3 Functions
NetworkPacket createPacket(const string& srcIP, const string& destIP, 
                         const string& protocol, unsigned short srcPort,
                         unsigned short destPort) {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string payload;
    for (int i = 0; i < 30; i++) {
        payload += charset[rand() % charset.length()];
    }

    unsigned int checksum = 0;
    for (char ch : payload) {
        checksum ^= ch;
    }
    
   return {srcIP, destIP, protocol, "Header", payload, checksum,srcPort, destPort, "AES", static_cast<bool>(rand() % 2), generateRandomID()};
}

void simulateEncryption(NetworkPacket* pkt) {
    if (pkt->isEncryptedFlag) {
        pkt->dataPayload = "Decrypted: " + pkt->dataPayload;
    } else {
        pkt->dataPayload = "Encrypted: " + pkt->dataPayload;
        pkt->isEncryptedFlag = true;
    }
}

bool validatePacket(NetworkPacket* pkt) {
    unsigned int check = 0;
    for (char ch : pkt->dataPayload) {
        check ^= ch;
    }
    return check == pkt->packetChecksum;
}

bool level3() {
    clearScreen();
    printHeader("LEVEL 3: NETWORK FORENSICS");
    
    srand(time(0));
    vector<NetworkPacket> packets = {
        createPacket("192.168.1.2", "10.0.0.1", "TCP", 443, 8080),
        createPacket("10.0.0.3", "192.168.1.5", "UDP", 53, 123),
        createPacket("172.16.0.4", "10.0.0.2", "TCP", 80, 8000)
    };

    int correct = 0;
    for (auto& pkt : packets) {
        clearScreen();
        cout << "Packet Analysis:\n\n";
        cout << "Source: " << pkt.srcIP << ":" << pkt.srcPort << "\n";
        cout << "Destination: " << pkt.destIP << ":" << pkt.destPort << "\n";
        cout << "Protocol: " << pkt.protocolType << "\n";
        cout << "Encrypted: " << (pkt.isEncryptedFlag ? "Yes" : "No") << "\n\n";
        
        cout << "1. Decrypt packet\n2. Validate integrity\n3. Skip\nChoice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            simulateEncryption(&pkt);
            cout << "Payload: " << pkt.dataPayload << "\n";
            pressAnyKey();
        } else if (choice == 2) {
            if (validatePacket(&pkt)) {
                printSuccess("Packet integrity valid!");
                correct++;
            } else {
                printError("Packet corrupted!");
            }
            pressAnyKey();
        }
    }
    
    if (correct >= 2) {
        playerScore += 100;
        printSuccess("LEVEL 3 COMPLETED!");
        return true;
    }
    return false;
}

// Level 4 Functions (Web Security)
bool level4() {
    clearScreen();
    printHeader("LEVEL 4: WEB SECURITY");

    typewriter("In this level, we will explore web security concepts.\n");
    typewriter("To proceed, identify and exploit a basic vulnerability in a web form.\n\n");

    string username = "admin";
    string password = "password123";
    string inputUser, inputPass;

    while (true) {
        clearScreen();
        cout << "Enter Username: ";
        cin >> inputUser;
        cout << "Enter Password: ";
        cin >> inputPass;

        if (inputUser == username && inputPass == password) {
            printSuccess("Login successful! Web security vulnerability exploited.");
            playerScore += 100;
            return true;
        } else {
            printError("Incorrect credentials. Try again.");
        }
    }
}

// Menu System
void mainMenu() {
    while (!gameOver) {
        clearScreen();
        printHeader("MAIN MENU");
        cout << BOLD "Current Score: " << playerScore << RESET "\n\n";
        cout << "1. Level 1: Linux Commands\n";
        cout << "2. Level 2: Password Security\n";
        cout << "3. Level 3: Network Analysis\n";
        cout << "4. Level 4: Web Security\n";
        cout << "5. Exit\n\nChoice: ";
        
        int choice;
        cin >> choice;
        clearInputBuffer();
        
        bool result = false;
        switch (choice) {
            case 1: result = level1(); break;
            case 2: result = level2(); break;
            case 3: result = level3(); break;
            case 4: result = level4(); break;
            case 5: gameOver = true; break;
            default: printError("Invalid choice!"); 
        }
        
        if (result) {
            printSuccess("Level completed successfully!");
        } else if (choice != 5) {
            printError("Level failed!");
        }
        pressAnyKey();
    }
}

int main() {
    srand(time(0));
    mainMenu();
    clearScreen();
    cout << BOLD CYAN "Game Over. Final Score: " << playerScore << RESET << endl;
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;
using namespace std::chrono;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

// Game Configuration
const int MAX_LEVEL = 4;
int currentLevel = 1;
int playerScore = 0;
bool gameOver = false;

// NetworkPacket structure
struct NetworkPacket {
    string srcIP;
    string destIP;
    string protocolType;
    string headerInfo;
    string dataPayload;
    unsigned int packetChecksum;
    unsigned short srcPort;
    unsigned short destPort;
    string encryptionMethod;
    bool isEncryptedFlag;
    unsigned int uniquePacketID;
};

// Utility functions
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void typewriter(const string& text, int speed = 30) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(milliseconds(speed));
    }
}

void printHeader(const string& title) {
    cout << BOLD CYAN "\n=== " << title << " ===\n\n" RESET;
}

void printSuccess(const string& msg) {
    cout << GREEN << "[✓] " << msg << RESET << endl;
}

void printError(const string& msg) {
    cout << RED << "[✗] " << msg << RESET << endl;
}

void pressAnyKey() {
    cout << MAGENTA "\nPress any key to continue..." RESET;
    cin.ignore();
    cin.get();
}

// Clear input buffer to avoid leftover newlines
void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Random number generator with better randomness
unsigned int generateRandomID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100000);
    return dist(gen);
}

// Level 1 Functions
void teachLinuxCommands() {
    clearScreen();
    printHeader("LINUX COMMAND TUTORIAL");
    
    typewriter("Essential Linux commands:\n\n");
    typewriter("1. File Operations:\n");
    typewriter("   ls - List files\n   cd - Change directory\n");
    typewriter("   mkdir - Create directory\n   rm - Remove files\n");
    typewriter("   cp - Copy files\n   mv - Move/rename files\n\n");
    
    typewriter("2. Process Management:\n");
    typewriter("   ps - View processes\n   kill - Terminate processes\n");
    typewriter("   top - System monitor\n\n");
    
    typewriter("3. Network Commands:\n");
    typewriter("   ping - Test connectivity\n   ifconfig - Network config\n");
    typewriter("   netstat - Network stats\n   ssh - Secure shell\n\n");
    
    pressAnyKey();
}

bool level1() {
    teachLinuxCommands();
    
    clearScreen();
    printHeader("LEVEL 1: LINUX COMMAND CHALLENGE");
    
    vector<pair<string, string>> challenges = {
        {"List all files (including hidden)", "ls -a"},
        {"Create directory 'documents'", "mkdir documents"},
        {"Show running processes", "ps aux"},
        {"Ping google.com 3 times", "ping -c 3 google.com"},
        {"Change permissions of secret.txt to owner read-only", "chmod 400 secret.txt"}
    };

    int score = 0;
    for (const auto& challenge : challenges) {
        clearScreen();
        cout << "Task " << (score + 1) << "/5\n\n";
        cout << challenge.first << "\n> ";
        
        string input;
        getline(cin, input);
        
        if (input == challenge.second) {
            score++;
            printSuccess("Correct! +20 points");
            playerScore += 20;
        } else {
            printError("Incorrect! Correct answer: " + challenge.second);
        }
        pressAnyKey();
    }
    
    if (score >= 3) {
        printSuccess("LEVEL 1 COMPLETED!");
        return true;
    }
    return false;
}

// Level 2 Functions (Password Security)
bool level2() {
    clearScreen();
    printHeader("LEVEL 2: PASSWORD SECURITY");
    
    typewriter("In this level, we will explore password cracking techniques.\n");
    typewriter("To proceed, crack the following password using a brute-force method.\n\n");
    
    string password = "qwerty123"; // Sample password
    string attempt;
    int attempts = 0;

    while (true) {
        clearScreen();
        cout << "Enter the password attempt: ";
        cin >> attempt;
        attempts++;
        
        if (attempt == password) {
            printSuccess("Password cracked! It took " + to_string(attempts) + " attempts.");
            playerScore += 50;
            return true;
        } else {
            printError("Incorrect password. Try again.");
        }
    }
}

// Level 3 Functions
NetworkPacket createPacket(const string& srcIP, const string& destIP, 
                         const string& protocol, unsigned short srcPort,
                         unsigned short destPort) {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string payload;
    for (int i = 0; i < 30; i++) {
        payload += charset[rand() % charset.length()];
    }

    unsigned int checksum = 0;
    for (char ch : payload) {
        checksum ^= ch;
    }
    
    return {srcIP, destIP, protocol, "Header", payload, checksum,
            srcPort, destPort, "AES", (rand() % 2), generateRandomID()};
}

void simulateEncryption(NetworkPacket* pkt) {
    if (pkt->isEncryptedFlag) {
        pkt->dataPayload = "Decrypted: " + pkt->dataPayload;
    } else {
        pkt->dataPayload = "Encrypted: " + pkt->dataPayload;
        pkt->isEncryptedFlag = true;
    }
}

bool validatePacket(NetworkPacket* pkt) {
    unsigned int check = 0;
    for (char ch : pkt->dataPayload) {
        check ^= ch;
    }
    return check == pkt->packetChecksum;
}

bool level3() {
    clearScreen();
    printHeader("LEVEL 3: NETWORK FORENSICS");
    
    srand(time(0));
    vector<NetworkPacket> packets = {
        createPacket("192.168.1.2", "10.0.0.1", "TCP", 443, 8080),
        createPacket("10.0.0.3", "192.168.1.5", "UDP", 53, 123),
        createPacket("172.16.0.4", "10.0.0.2", "TCP", 80, 8000)
    };

    int correct = 0;
    for (auto& pkt : packets) {
        clearScreen();
        cout << "Packet Analysis:\n\n";
        cout << "Source: " << pkt.srcIP << ":" << pkt.srcPort << "\n";
        cout << "Destination: " << pkt.destIP << ":" << pkt.destPort << "\n";
        cout << "Protocol: " << pkt.protocolType << "\n";
        cout << "Encrypted: " << (pkt.isEncryptedFlag ? "Yes" : "No") << "\n\n";
        
        cout << "1. Decrypt packet\n2. Validate integrity\n3. Skip\nChoice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            simulateEncryption(&pkt);
            cout << "Payload: " << pkt.dataPayload << "\n";
            pressAnyKey();
        } else if (choice == 2) {
            if (validatePacket(&pkt)) {
                printSuccess("Packet integrity valid!");
                correct++;
            } else {
                printError("Packet corrupted!");
            }
            pressAnyKey();
        }
    }
    
    if (correct >= 2) {
        playerScore += 100;
        printSuccess("LEVEL 3 COMPLETED!");
        return true;
    }
    return false;
}

// Level 4 Functions (Web Security)
bool level4() {
    clearScreen();
    printHeader("LEVEL 4: WEB SECURITY");

    typewriter("In this level, we will explore web security concepts.\n");
    typewriter("To proceed, identify and exploit a basic vulnerability in a web form.\n\n");

    string username = "admin";
    string password = "password123";
    string inputUser, inputPass;

    while (true) {
        clearScreen();
        cout << "Enter Username: ";
        cin >> inputUser;
        cout << "Enter Password: ";
        cin >> inputPass;

        if (inputUser == username && inputPass == password) {
            printSuccess("Login successful! Web security vulnerability exploited.");
            playerScore += 100;
            return true;
        } else {
            printError("Incorrect credentials. Try again.");
        }
    }
}

// Menu System
void mainMenu() {
    while (!gameOver) {
        clearScreen();
        printHeader("MAIN MENU");
        cout << BOLD "Current Score: " << playerScore << RESET "\n\n";
        cout << "1. Level 1: Linux Commands\n";
        cout << "2. Level 2: Password Security\n";
        cout << "3. Level 3: Network Analysis\n";
        cout << "4. Level 4: Web Security\n";
        cout << "5. Exit\n\nChoice: ";
        
        int choice;
        cin >> choice;
        clearInputBuffer();
        
        bool result = false;
        switch (choice) {
            case 1: result = level1(); break;
            case 2: result = level2(); break;
            case 3: result = level3(); break;
            case 4: result = level4(); break;
            case 5: gameOver = true; break;
            default: printError("Invalid choice!"); 
        }
        
        if (result) {
            printSuccess("Level completed successfully!");
        } else if (choice != 5) {
            printError("Level failed!");
        }
        pressAnyKey();
    }
}

int main() {
    srand(time(0));
    mainMenu();
    clearScreen();
    cout << BOLD CYAN "Game Over. Final Score: " << playerScore << RESET << endl;
    return 0;
}
