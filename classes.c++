#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <iomanip>
#include <utility>
#include <algorithm> 
static const int EXIT_OPTION = 5;
static const std::string CUSTOMER_FILE = "customers.txt";

class Customer {
private:
    std::string name;
    std::string surname;
    std::string address;
    double balance;

public:

    Customer(const std::string& name, const std::string& surname, const std::string& address, double balance)
        : name(name), surname(surname), address(address), balance(balance) {}
    std::string getName() const { return name; }
    std::string getSurname() const { return surname; }
    std::string getAddress() const { return address; }
    double getBalance() const { return balance; }
void receiveMoney(double amount){
    this->balance += amount;
}
 void addMoney(double amount) {
    if (amount > 0) {
       this->balance += amount;
        std::cout << "Added " << amount << " to your balance. Your new balance is: "<<std::setprecision(2) <<std::fixed << balance<<"$"<<std::endl;
    } else {
        std::cout << "Amount must be positive." << std::endl;
    }
}

void sendMoney(double amount){
    this->balance -= amount;
       std::cout << "Send " <<  amount << " to your balance. Your new balance is: "<<std::setprecision(2) <<std::fixed << balance<<"$"<<std::endl;
}
    void withdrawMoney(double amount) {
        if (amount > 0 && amount <= balance) {
           this-> balance -= amount;
            std::cout << "Withdrawn " <<  amount << " to your balance. Your new balance is: "<<std::setprecision(2) <<std::fixed << balance<<"$"<<std::endl;
        } else {
            std::cout << "Insufficient balance or invalid amount." << std::endl;
        }
    }
};

class BankAccount {
private:
    Customer customer;
    std::string username;
    std::string password;

public:
    BankAccount(const Customer& customer, const std::string& username, const std::string& password)
        : customer(customer), username(username), password(password) {}
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    Customer getCustomer() const { return customer; }
 Customer& getCustomerRef() {
        return customer;
    }
    void addMoney(double amount) {
        customer.addMoney(amount);
    }

    void withdrawMoney(double amount) {
        customer.withdrawMoney(amount);
    }

    double getBalance() const {
        return customer.getBalance();
    }
};

std::vector<std::pair<std::string, BankAccount>> customers;
 

void serializeCustomer(const std::string& username, const std::string& password,
                       const std::string& name, const std::string& surname,
                       const std::string& address, double balance) {
    std::ofstream file(CUSTOMER_FILE, std::ios::app);
    if (file.is_open()) {
        file << username << ',' << password << ',' << name << ',' << surname << ',' << address << ',' << balance << std::endl;
        file.close();
        std::cout << "Account created successfully." << std::endl;
        Customer customer(name, surname, address, balance);
        BankAccount account(customer, username, password);
        customers.push_back(std::make_pair(username, account));
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}
void updateCustomerFile() {
    std::ofstream file(CUSTOMER_FILE);
    if (file.is_open()) {
        for (const auto& cust : customers) {
            Customer customer = cust.second.getCustomer();
            file << cust.first << ',' << cust.second.getPassword() << ',' << customer.getName() << ',' << customer.getSurname() << ',' << customer.getAddress() << ',' << customer.getBalance() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
    }
}

void deserializeCustomers() {
    std::ifstream file(CUSTOMER_FILE);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream fin(line);
            std::string username, password, name, surname, address, balanceStr;
            double balance;
            std::getline(fin, username, ',');
            std::getline(fin, password, ',');
            std::getline(fin, name, ',');
            std::getline(fin, surname, ',');
            std::getline(fin, address, ',');
            std::getline(fin, balanceStr, ',');
            balance = std::stod(balanceStr);
            Customer customer(name, surname, address, balance);
            BankAccount bankAcc(customer, username, password);
            customers.push_back(std::make_pair(username, bankAcc));
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
    }
}

bool usernameFound(std::string username) {
    for (const auto& cust : customers) {
        if (cust.first == username) {
            return true;
        }
    }
    return false;
}

bool checkPassword(std::string password, std::string username) {
    for (const auto& cust : customers) {
        if (cust.first == username && cust.second.getPassword() == password) {
            return true;
        }
    }
    return false;
}

bool isValidName(const std::string& name) {
    return name.length() >= 3 && name.length() <= 14;
}

bool isValidUsername(const std::string& username) {
    return username.length() >= 3 && username.length() <= 14;
}

bool isValidAddress(const std::string& address) {
    return address.length() >= 5 && address.length() <= 50;
}

bool isValidPassword(const std::string password) {
    bool correctPasswordLength = false;
    bool containsSpecialSymbol=false;
    bool containsNumber=false;
    std::vector<char> specialSymbols= {'!','@','~','#','$','&','*'};
    std::vector<char> numbers= {'0','1','2','3','4','5','6','7','8','9'};
    for(int i = 0; i < password.length();i++){
        if (std::find(specialSymbols.begin(), specialSymbols.end(), password[i]) != specialSymbols.end()){
        containsSpecialSymbol = true; break;}
    }
    for(int i = 0; i < password.length();i++){
        if (std::find(numbers.begin(), numbers.end(), password[i]) != numbers.end()){
        containsNumber = true; break;}
    }
    if(password.length()>=7){
        correctPasswordLength = true;
    }
    if(!containsSpecialSymbol)std::cout<<"Password must contain at least one of this special characters : '!','@','~','#','$','&','*'"<<std::endl;
    if(!correctPasswordLength)std::cout<<"Password must contain at least 7 characters long "<<std::endl;
    if(!containsNumber)std::cout<<"Password must contain a number "<<std::endl;
if(containsNumber && containsSpecialSymbol && correctPasswordLength)
    return true;
    else return false;
}

double getValidInitialBalance() {
    double balance;
    while (true) {
        std::cout << "Enter your initial balance: ";
        if (std::cin >> balance && balance > 0) {
            break;
        } else {
            std::cout << "Invalid balance. Please enter a positive number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return balance;
}

int main() {
    deserializeCustomers();
    int decision = 0, action = 0;
    std::string name, surname, address, username, password;
    double initialBalance;
    std::cout << "Welcome to the bank!" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Create an account" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Enter your decision: ";
    std::cin >> decision;
    while (std::cin.fail() || decision < 1 || decision > 3) {
        std::cout << "Invalid input. Please enter a number between 1 and 3: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> decision;
    }

    switch (decision) {
    case 1: {
        std::cout << "You chose to create a new account\n";
        std::cout << "We will just need you to fill some information for us\n";
        std::cout << "Enter your name: ";
        std::cin >> name;
        while (!isValidName(name)) {
            std::cout << "Name must be between 3 and 14 characters. Enter your name again: ";
            std::cin >> name;
        }

        std::cout << "Enter your surname: ";
        std::cin >> surname;
        while (!isValidName(surname)) {
            std::cout << "Surname must be between 3 and 14 characters. Enter your surname again: ";
            std::cin >> surname;
        }

        std::cin.ignore();
        std::cout << "Enter your address: ";
        std::getline(std::cin >> std::ws, address);
        while (!isValidAddress(address)) {
            std::cout << "Address must be between 5 and 50 characters. Enter your address again: ";
            std::getline(std::cin >> std::ws, address);
        }

        initialBalance = getValidInitialBalance();

        std::cout << "Enter your username: ";
        std::cin >> username;
        while (!isValidUsername(username)) {
            std::cout << "Username must be between 3 and 14 characters. Enter your username again: ";
            std::cin >> username;
        }
        while(usernameFound(username)) {
            std::cout << "Username already exists. Enter another username: ";
            std::cin >> username;
        }

        std::cout << "Enter your password: ";
        std::cin >> password;
        while (!isValidPassword(password)) {
             std::cout << "Enter your password: ";
            std::cin >> password;
        }

        Customer customer(name, surname, address, initialBalance);
        BankAccount account(customer, username, password);

        serializeCustomer(username, password, name, surname, address, initialBalance);
        std::cout << "Account created successfully." << std::endl;
        break;
    }
 case 2: {
    bool found = false;
    while(!found) {
    std::cout << "To login into your bank account, please enter your username and password." << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    for (const auto& cust : customers) {
        if (cust.first == username && cust.second.getPassword() == password) {
            found = true;
            Customer customer = cust.second.getCustomer();
            BankAccount account = cust.second;
            std::cout << "Login successful" << std::endl;
            std::cout << "Welcome " << customer.getName() << std::endl;
            name = customer.getName();
            surname = customer.getSurname();
            address = customer.getAddress();
            username = cust.first;
            break;
        }
    }
    if (!found) {
        std::cout << "Invalid username or password" << std::endl;
    }}
    break;
}

    case 3: {
        std::cout << "Thank you for using the bank!" << std::endl;
        action=EXIT_OPTION;
        break;
    }
    }


    while (action != EXIT_OPTION) {
        std::cout << "\nWhat would you like to do?" << std::endl;
        std::cout << "1. Add money to your account" << std::endl;
        std::cout << "2. Withdraw money from your account" << std::endl;
        std::cout << "3. Check Your Balance" << std::endl;
        std::cout << "4. Transfer money between accounts" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your action: ";
        std::cin >> action;

        while (std::cin.fail() || action < 1 || action > 5) {
            std::cout << "Invalid input. Please enter a number between 1 and 5: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> action;
        }
            std::string usernameToSend="";
            double amountToSend=0;
        switch (action) {
case 1: {
    double amount;
    std::cout << "Enter amount to add: ";
    std::cin >> amount;
    while (std::cin.fail() || amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> amount;
    }
    for (int i=0;i<customers.size();i++) {
        if (customers[i].first == username) {
            customers[i].second.getCustomerRef().addMoney(amount);
             updateCustomerFile();
            break;
        }
    }
    break;
}
case 2: {
    double amount;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;
    while (std::cin.fail() || amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> amount;
    }
    for (auto& cust : customers) {
        if (cust.first == username) {
            cust.second.getCustomerRef().withdrawMoney(amount);
            updateCustomerFile();
            break;
        }
    }
    break;
}
        case 3:

                  for (const auto& cust : customers) {
        if (cust.first == username) {
            std::cout << "Your balance is: " << std::fixed << std::setprecision(2) << cust.second.getBalance() << std::endl;
            break;
        }
    }
            
            break;
        case 4:
            
            std::cout << "Enter the username of the account you would like to transfer to: ";
            std::cin >> usernameToSend;
            while(usernameToSend==username) {
                std::cout << "You cannot transfer to yourself" << std::endl;
                std::cout << "Enter the username of the account you would like to transfer to: ";
                std::cin >> usernameToSend;
            }
            while(!usernameFound(usernameToSend)){
                std::cout << "Account not found. Please enter the username of the account you would like to transfer to: ";
                std::cin >> usernameToSend;
            }
            std::cout << "Enter amount to transfer: ";
            std::cin >> amountToSend;
            while (std::cin.fail() || amountToSend <= 0) {
        std::cout << "Invalid amount. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> amountToSend;
    }
              for (auto& cust : customers) {
        if (cust.first == username) {
            if (amountToSend > 0 && amountToSend <= cust.second.getCustomerRef().getBalance()) {
           cust.second.getCustomerRef().sendMoney(amountToSend);
         for(auto& users: customers){
            if(users.first==usernameToSend){
                users.second.getCustomerRef().receiveMoney(amountToSend);
                break;
            }
         }
        } else {
            std::cout << "Insufficient balance or invalid amount." << std::endl;
        }
            updateCustomerFile();
            break;
        }
    }
    break;
            case 5:
            
            break;
                   std::cout << "Thank you for using the bank!" << std::endl;
            action = EXIT_OPTION;
            break;
        default:
            std::cout << "Invalid option. Please enter a number between 1 and 5." << std::endl;
            break;
        }
       
    }

    return 0;
}
