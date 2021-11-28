#include <iostream>
#include<string.h>
#include<math.h>
#include <unistd.h>
#include <direct.h>
#include<limits.h>
#define MAX 100
using namespace std;

class Card{

friend class CreditCard;
friend class DebitCard;

private:
    //Properties of card
    char accountNumber[15];
    char customerName[31];
    char dateEffect[11];
    char bankName[50];
    long balance;
    bool status;
    int type;
public:
    //No-parameter constructor
    Card(){
        //copy content of accNumber variable to accountNumber property
        strcpy(accountNumber,"");
        //copy content of cusName variable to customerName property
        strcpy(customerName,"");
        //copy content of dateEffect variable to dateEffect property
        strcpy(dateEffect,"01/01/1900");
        //copy content of bank variable to bankName property
        strcpy(bankName,"");
        //Initialization balance is 0(VND)
        balance = 0;
        status = true;
    }
    //Parameter constructor
    Card(char accNumber[], char cusName[], char date[], char bank[],bool _status){
        //copy content of accNumber variable to accountNumber property
        strcpy(accountNumber,accNumber);
        //copy content of cusName variable to customerName property
        strcpy(customerName,cusName);
        //copy content of dateEffect variable to dateEffect property
        strcpy(dateEffect,date);
        //copy content of bank variable to bankName property
        strcpy(bankName,bank);
        //Initialization balance is 0(VND)
        balance = 0;
        //Initialization status is true
        status =_status;
    }

    char* getAccountNumber(){
        return this->accountNumber;
    }

    char* getCustomerName(){
        return this->customerName;
    }

    char* getDateEffect(){
        return this->dateEffect;
    }

    void setDateEffect(char date[]){
        strcpy(this->dateEffect,date);
    }

    char* getBankName(){
        return this->bankName;
    }

    void setBankName(char bank[]){
        strcpy(this->bankName,bank);
    }

    long getBalance(){
        return this->balance;
    }

    void setBalance(long bal){
        this->balance = bal;
    }

    bool getStatus(){
        return this->status;
    }

    void setStatus(bool _status){
        this->status = _status;
    }

    int getType(){
        return this->type;
    }

    void setType(int _type){
        this->type = _type;
    }

    bool checkAccountNumberValid(char accNumber[]){
        int n = strlen(accNumber);
        for(int i=0;i<n;i++){
            if(accNumber[i]<'0'||accNumber[i]>'9'){
                return false;
            }
        }
        return true;
    }
    //function type information of card
    void typeInfo(){
        do{
            cout<<"Enter account number: ";
            cin>>accountNumber;
            if(checkAccountNumberValid(accountNumber)==false){
                cout<<">>> INVALID ACCOUNT NUMBER!"<<endl;
            }
        }while(checkAccountNumberValid(accountNumber)==false);

        cin.ignore();
        cout<<"Enter name's customer: ";
        cin.getline(customerName,sizeof(customerName)/sizeof(char));
        cout<<"Enter effective date: ";
        cin>>dateEffect;
        cin.ignore();
        cout<<"Enter name's bank: ";
        cin.getline(bankName,sizeof(bankName)/sizeof(char));
    }

    //function will show information of card to screen
    void showInfo(){
        printf("|%15s|%25s|%14s|%20s|%15ld|",this->accountNumber,this->customerName,
               this->dateEffect,this->bankName,this->balance);
        if(this->status==true){
            printf("%6s%9s|\n"," ","Active");
        }
        else{
            printf("%6s%9s|\n"," ","No active");
        }
    }

    virtual void sendMoney(long money){
        this->setBalance(this->getBalance()+money);
    }

    virtual void getMoney(long money){
        if(this->getType()==0){
            if(this->getBalance()<=0){
                cout<<">>>(*)NOTICE: YOU OWE THE BANK "<<this->getBankName()<<": "<<abs(this->getBalance())<<" VND"<<endl;
            }
        }
        else if(this->getType()==1){
            if(this->getBalance()<=0){
                cout<<">>> YOU DON'T HAVE ENOUGH BALANCE TO WITHDRAW!"<<endl;
                return;
            }
        }
        this->setBalance(this->getBalance()-money);
    }
};

class CreditCard: public Card{
public:
    using Card::Card;
    //Re-define function sendMoney() of class Card
    void sendMoney(long _sendMoney){
        this->setBalance(this->getBalance()+_sendMoney);
    }

    void getMoney(long _getMoney){
        this->setBalance(this->getBalance()-_getMoney);
    }
};

class DebitCard:public Card{
public:
    using Card::Card;
    //Re-define function sendMoney() of class Card
    void sendMoney(long _sendMoney){
        this->setBalance(this->getBalance()+_sendMoney);
    }

    void getMoney(long _getMoney){
        if(this->getBalance()==0 || this->getBalance()<_getMoney){
            cout<<"Your account does not have enough funds to withdraw!"<<endl;
            return;
        }
        else{
            this->setBalance(this->getBalance()-_getMoney);
            cout<<"Getting money successfully!"<<endl;
        }
    }
};

int getCardByAccountNumber(Card cards[], int n, char accountNumber[]){
    for(int i=0;i<n;i++){
        if(strcmp(cards[i].getAccountNumber(),accountNumber)==0){
            return i;
        }
    }
    return -1;
}

bool checkAccountExist(Card cards[], int n, char accNumber[], char cusName[], char bank[]){
    int index = getCardByAccountNumber(cards,n,accNumber);
    if(index!=-1){
        if(strcmp(cards[index].getCustomerName(),cusName)==0){
            if(strcmp(cards[index].getBankName(),bank)==0){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    return false;
}

void addCard(Card cards[], int &n){
    cout<<"+++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"|   1. Credit      |    2. Debit    |"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++"<<endl;
    int choice;
    cout<<">>Please select type of card: ";
    cin>>choice;
    Card card;
    switch(choice){
        case 1:
            {
                CreditCard cre;
                cre.typeInfo();
                card = cre;
                if(checkAccountExist(cards,n,card.getAccountNumber(),card.getCustomerName(),card.getBankName())==false){
                    card.setType(0);
                    cards[n++] = card;
                }
                else{
                    cout<<">>> ACCOUNT HAS ALREADY EXIST!"<<endl;
                }
                break;
            }
        case 2:
            {
                DebitCard debit;
                debit.typeInfo();
                card = debit;
                if(checkAccountExist(cards,n,card.getAccountNumber(),card.getCustomerName(),card.getBankName())==false){
                    card.setType(1);
                    cards[n++] = card;
                }
                else{
                    cout<<">>> ACCOUNT HAS ALREADY EXIST!"<<endl;
                }
                break;
            }
        default:
            cout<<">>> INVALID OPTION!"<<endl;
            break;
    }
}

void updateCard(Card cards[], int n, int choice, char accountNumber[], char newInfo[]){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        if(choice==1){
            cards[index].setDateEffect(newInfo);
        }
        else{
            cards[index].setBankName(newInfo);
        }
        cout<<">>> UPDATE SUCCESSFULLY!"<<endl;
    }

}

void changeStatus(Card cards[], int n, char accountNumber[]){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        cards[index].setStatus(!cards[index].getStatus());
        cout<<">>> CHANGE STATUS SUCCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

void sendMoneyToCard(Card cards[], int n, char accountNumber[], long _sendMoney){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        cards[index].sendMoney(_sendMoney);
        cout<<"SEND MONEY SUCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

void WithDrawMoney(Card cards[], int n, char accountNumber[], long getMoney){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        cards[index].getMoney(getMoney);
        cout<<">>> WITHDRAW SUCCESSFULLY!";
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

void removeCard(Card cards[], int &n, char accountNumber[]){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        for(int i=n-1;i>=0;i--){
            if(i==index){
                    for(int j=index;j<n;j++){
                        cards[j]=cards[j+1];
                    }
                    n--;
            }
        }
        cout<<">>> DELETE SUCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

void showListCard(Card cards[], int n){
    cout<<"+---------------+-------------------------+--------------+--------------------+---------------+---------------+"<<endl;
    printf("|%-15s|%-25s|%12s|%-20s|%-15s|%-15s|\n","Account","Customer","Effective date","Bank","Balance","Status");
    cout<<"+---------------+-------------------------+--------------+--------------------+---------------+---------------+"<<endl;
    for(int i=0;i<n;i++){
        cards[i].showInfo();
    }
    cout<<"+---------------+-------------------------+--------------+--------------------+---------------+---------------+"<<endl;
    cout<<"COMPLETE SUCCESSFULLY!"<<endl;
}

void writeListCardToTextFile(Card cards[], int n, char* fileName){
    FILE* f = fopen(fileName,"wb");
    if(f==NULL){
        cout<<">>> FILE IS CREATING!"<<endl;
    }
    fwrite(&n,sizeof(n),1,f);
	for(int i=0;i<n;i++){
		fwrite(&cards[i],sizeof(Card),1,f);
	}
	fclose(f);
    cout<<">>> EXPORT TO TEXT FILE SUCESSFULLY!"<<endl;
    char buff[PATH_MAX];
    _getcwd(buff,PATH_MAX);
    string current_working_dir(buff);
    cout<<">>> Location: "<<current_working_dir<<endl;
}

void readListCardFromTextFile(Card cards[], int &n, char* fileName){
    FILE* f = fopen(fileName,"rb");
	if(f==NULL){
		cout<<">>> CAN'T READ FILE!!"<<endl;
		return;
	}
	fread(&n,sizeof(n),1,f);
	for(int i=0;i<n;i++){
		fread(&cards[i],sizeof(Card),1,f);
	}
	fclose(f);
    cout<<">>> IMPORT FROM TEXT FILE SUCCESSFULLY!"<<endl;
}

int menu(){
    cout<<"+--------------------MENU---------------------+"<<endl;
    cout<<"|          1. Add new card                    |"<<endl;
    cout<<"|          2. Update information card         |"<<endl;
    cout<<"|          3. Show list cards                 |"<<endl;
    cout<<"|          4. Send money                      |"<<endl;
    cout<<"|          5. Withdraw money                  |"<<endl;
    cout<<"|          6. Remove card                     |"<<endl;
    cout<<"|          7. Change status of card           |"<<endl;
    cout<<"|          8. Write list of cards to file     |"<<endl;
    cout<<"|          9. Read list of card from file     |"<<endl;
    cout<<"|         10. Exit                            |"<<endl;
    cout<<"+---------------------------------------------+"<<endl;
    int choice;
    cout<<" >> Please select option in menu: ";
    cin>>choice;
    return choice;
}

int main()
{
    Card cards[MAX];
    int n;
    int checked=0;
    char * file = (char*)"LIST_OF_CARDS.BIN";
    while(checked==0){
        int choice = menu();
        switch(choice){
            case 1:
                {
                    addCard(cards,n);
                    break;
                }
            case 2:
                {
                    char accountNumber[15], newInfo[50];
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    cin.ignore();
                    cout<<"+------------------UPDATE OPTION------------------+"<<endl;
                    cout<<"|   1. Effective date    |      2. Bank name      |"<<endl;
                    cout<<"+-------------------------------------------------+"<<endl;
                    int updateOption;
                    cout<<">> Please select option for updating: ";
                    cin>>updateOption;
                    cin.ignore();
                    cout<<"Enter new information: ";
                    cin.getline(newInfo,sizeof(newInfo)/sizeof(char));
                    updateCard(cards,n,updateOption,accountNumber,newInfo);
                    break;
                }
            case 3:
                {
                    showListCard(cards,n);
                    break;
                }
            case 4:
                {
                    char accountNumber[15];
                    long money;
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    do{
                        cout<<"Enter money to send: ";
                        cin>>money;
                        if(money<0){
                            cout<<"Invalid money!"<<endl;
                        }
                    }while(money<0);
                    sendMoneyToCard(cards,n,accountNumber, money);
                    break;
                }
            case 5:
                {
                    char accountNumber[15];
                    long money;
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    do{
                        cout<<"Enter money to withdraw: ";
                        cin>>money;
                        if(money<0){
                            cout<<"Invalid money!"<<endl;
                        }
                    }while(money<0);
                    WithDrawMoney(cards,n,accountNumber, money);
                    break;
                }
            case 6:
                {
                    char accountNumber[15];
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    removeCard(cards,n,accountNumber);
                    break;
                }
            case 7:
                {
                    char accountNumber[15];
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    changeStatus(cards,n,accountNumber);
                    break;
                }
            case 8:
                {
                    writeListCardToTextFile(cards,n,file);
                    break;
                }
            case 9:
                {
                    readListCardFromTextFile(cards,n,file);
                    break;
                }
            case 10:
                {
                    checked=-1;
                    break;
                }
            default:
                {
                    cout<<">>> INVALID OPTION MENU!"<<endl;
                    break;
                }
        }
        system("pause");
        system("cls");
    }
    return 0;
}
