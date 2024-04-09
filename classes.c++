#include<iostream>
#include<iostream>
class bankAccount{
private:
double balance=0;
std::string name="";
std::string surname="";
std::string address="";
public:
void setName(){
    std::string name="";
    std::cout<<"Enter your name: ";
    std::cin>>name;
    while(name.length()<=2 || name.length()>=15){
        std::cout<<"Name must be between 3 and 14 characters"<<std::endl;
        std::cout<<"Enter your name: ";
        std::cin>>name;
    }
    this->name=name;
}

void setSurname(){

    std::string surname="";
    std::cout<<"Enter your surname: ";
    std::cin>>surname;
    while(surname.length()<=2 || surname.length()>=15){
        std::cout<<"Surname must be between 3 and 14 characters"<<std::endl;
        std::cout<<"Enter your surname: ";
        std::cin>>surname;
    }
    this->surname=surname;
}
void setAddress(){
    std::string address="";
    std::cout<<"Enter your address: ";
   std::getline(std::cin>>std::ws,address);
    while(address.length()<=5 || address.length()>=50){
        std::cout<<"Address must be between 5 and 50 characters"<<std::endl;
        std::cout<<"Enter your address: ";
        std::cin>>address;
    }
    this->address=address;
}
std::string getName(){
return this->name;
}
std::string getSurname(){
    return this->surname;
}
std::string getAddress(){
    return this->address;
}
void addMoney(){
 double amount;
            std::cout<<"How much money would you like to add?"<<std::endl;
            std::cin>>amount;
while(amount<=0){
    std::cout<<"Amount must be positive"<<std::endl;
    std::cout<<"How much money would you like to add?"<<std::endl;
    std::cin>>amount;
}
    this->balance+=amount;
    std::cout<<"Your balance is: "<<this->balance<<std::endl;
}
double getBalance(){
    return balance;
}
void withdrawMoney(double amount){
    if(amount>this->balance){
        std::cout<<"Insufficient balance"<<std::endl;
    }else {
    this->balance-=amount;
    std::cout<<"Balance left: "<<this->balance<<std::endl;
    }
}
};
int main(){
    bankAccount account;
    int action = 0;
    while(account.getName()==""){
        std::cout<<"Lets first make you a new bank account"<<std::endl;
       account.setName();
       account.setSurname();
       account.setAddress();
    }
    std::cout<<"Now that you have an account you can start using our services"<<std::endl;
    while(action!=4){
        std::cout<<std::endl;
        std::cout<<"What would you like to do "<<account.getName()<<"?"<<std::endl;
        std::cout<<"1. Add money to your account"<<std::endl;
        std::cout<<"-----------------------------------------------"<<std::endl;
        std::cout<<"2. Withdraw money from your account"<<std::endl;
        std::cout<<"-----------------------------------------------"<<std::endl;
        std::cout<<"3. Check Your Balance"<<std::endl;
        std::cout<<"-----------------------------------------------"<<std::endl;
        std::cout<<"4. Exit"<<std::endl;
        std::cin>>action;
        if(action==1){
           
            account.addMoney();
    
    }else if(action==2){
        double amount;
        std::cout<<"How much money would you like to withdraw?"<<std::endl;
        std::cin>>amount;
        account.withdrawMoney(amount);
    }else if(action==3){
        std::cout<<"Your balance is "<<account.getBalance()<<std::endl;
    }else if(action==4)break;
    else std::cout<<"Wrong Input"<<std::endl;

    }
}