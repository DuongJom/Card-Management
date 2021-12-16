#include <iostream>
#include<fstream>
#include<string.h>
#include<math.h>
#include <unistd.h>
#include <direct.h>
#include<limits.h>
#include<time.h>
#include<stdlib.h>
#define MAX 100
#define file "DATA.DAT"
using namespace std;

class Card{
//Khai bao friend class
friend class CreditCard;
friend class DebitCard;

private:
    //Properties of card
    char accountNumber[15];
    char customerName[31];
    char dateEffect[11];
    char bankName[50];
    long balance;
    int PIN;
    bool status;
    int type;
public:
    //Ham khoi tao khong tham so
    Card(){
        //Copy chuoi rong vao bien accountNumber
        strcpy(accountNumber,"");
        //Copy chuoi rong vao bien customerName
        strcpy(customerName,"");
        //Khoi tao gia tri ban dau cho bien accountNumber
        strcpy(dateEffect,"01/01/1900");
        //Copy chuoi rong vao bien accountNumber
        strcpy(bankName,"");
        //Khoi tao gia tri ban dau cho bien balance va status
        srand(time(NULL));
        PIN = rand()%(9999-1000+1)+1000;
        balance = 0;
        status = true;
    }
    //Ham khoi tao co tham so
    Card(char accNumber[], char cusName[], char date[], char bank[],bool _status){
        //Copy chuoi accNumber vao bien accountNumber
        strcpy(accountNumber,accNumber);
        //Copy chuoi cusName vao bien customerName
        strcpy(customerName,cusName);
        //Copy chuoi date vao bien dateEffect
        strcpy(dateEffect,date);
        //Copy chuoi bank vao bien bankName
        strcpy(bankName,bank);
        //Khoi tao gia tri ban dau cho bien balance va status
        srand(time(NULL));
        PIN = rand()%(9999-1000+1)+1000;
        balance = 0;
        status =_status;
    }
    //Dong 54->100: Ham get va set gia tri cua cac thuoc tinh lop Card
    char* getAccountNumber(){
        return this->accountNumber;
    }

    void setAccountNumber(char acc[]){
        strcpy(accountNumber,acc);
    }

    char* getCustomerName(){
        return this->customerName;
    }

    void setCustomerName(char cust[]){
        strcpy(customerName,cust);
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

    int getPIN(){
        return PIN;
    }

    void setPIN(int pin){
        PIN = pin;
    }

    //Kiem tra account number la chuoi so
    bool checkAccountNumberValid(char accNumber[]){
        int n = strlen(accNumber);
        for(int i=0;i<n;i++){
            //Neu account number chua ki tu khac '0'->'9' thi khong hop le
            if(accNumber[i]<'0'||accNumber[i]>'9'){
                return false;
            }
        }
        return true;
    }

    bool checkNullValue(char info[]){
        if(strcmp(info,"")==0){
            return false;
        }
        return true;
    }
    //Ham nhap thong tin cho card
    void typeInfo(){
        //Neu nhap account number khong hop le thi cho nhap lai
        cin.ignore();
        do{
            cout<<"\t+ Enter account number: ";
            cin.getline(accountNumber,sizeof(accountNumber)/sizeof(char));
            //Kiem tra account number hop le hay khong
            if(checkAccountNumberValid(accountNumber)==false || checkNullValue(accountNumber)==false){
                cout<<">>> INVALID ACCOUNT NUMBER!"<<endl;
            }
        }while(checkAccountNumberValid(accountNumber)==false || checkNullValue(accountNumber)==false);

        do{
            cout<<"\t+ Enter name's customer: ";
            cin.getline(customerName,sizeof(customerName)/sizeof(char));
            if(checkNullValue(customerName)==false){
                cout<<">>> INVALID VALUE!"<<endl;
            }
        }while(checkNullValue(customerName)==false);

        do{
            cout<<"\t+ Enter effective date(dd/MM/yyyy): ";
            cin.getline(dateEffect,sizeof(dateEffect)/sizeof(char));
            if(checkNullValue(dateEffect)==false){
                cout<<">>> INVALID VALUE!"<<endl;
            }
        }while(checkNullValue(dateEffect)==false);

        do{
            cout<<"\t+ Enter name's bank: ";
            cin.getline(bankName,sizeof(bankName)/sizeof(char));
            if(checkNullValue(bankName)==false){
                cout<<">>> INVALID VALUE!"<<endl;
            }
        }while(checkNullValue(bankName)==false);
    }

    //Ham hien thi thong tin Card ra man hinh console
    void showInfo(){
        printf("|%15s|%25s|%5d|%18s|%20s|%15ld|",this->accountNumber,this->customerName, this->PIN,
               this->dateEffect,this->bankName,this->balance);
        if(this->status==true){
            printf("%6s%9s|"," ","Active");
        }
        else{
            printf("%6s%9s|"," ","No active");
        }
        if(this->getType()==0){
            printf("%6s%9s|\n"," ","CREDIT");
        }
        else{
            printf("%6s%9s|\n"," ","DEBIT");
        }
    }
    //Ham truu tuong: gui tien va rut tien(dong 147-164)
    virtual void sendMoney(long money){
        this->setBalance(this->getBalance()+money);
    }

    virtual void getMoney(long money){
        if(this->getStatus()==true){
            if(this->getType()==0){//CREDIT CARD
                if(this->getBalance()<=0){
                    this->setBalance(this->getBalance()-money);
                    cout<<">>>(*)NOTICE: YOU OWE THE BANK "<<this->getBankName()<<": "<<abs(this->getBalance())<<" VND"<<endl;
                    return;
                }
                else{
                    if(this->getBalance()<money){
                        this->setBalance(this->getBalance()-money);
                        cout<<">>>(*)NOTICE: YOU OWE THE BANK "<<this->getBankName()<<": "<<abs(this->getBalance())<<" VND"<<endl;
                        return;
                    }
                    else{
                        this->setBalance(this->getBalance()-money);
                        cout<<">>> WITHDRAW SUCCESSFULLY!"<<endl;
                        return;
                    }
                }
            }
            else if(this->getType()==1){ //DEBIT CARD
                if(this->getBalance()<=0 || this->getBalance()<money){
                    cout<<">>> YOU DON'T HAVE ENOUGH BALANCE TO WITHDRAW!"<<endl;
                    return;
                }
                else{
                    this->setBalance(this->getBalance()-money);
                    cout<<">>> WITHDRAW SUCCESSFULLY!"<<endl;
                    return;
                }
            }
        }
        else{
            cout<<">>> ACCOUNT WAS DISABLE!"<<endl;
        }
    }
};

class CreditCard: public Card{
public:
    //Ke thua ham khoi tao cua lop Card
    using Card::Card;
    //Dinh nghia lai ham tru tuong cua lop Card(dong 147-149)
    void sendMoney(long _sendMoney){
        this->setBalance(this->getBalance()+_sendMoney);
    }

	//Dinh nghia lai ham tru tuong cua lop Card(dong 151-181)
    void getMoney(long _getMoney){
        this->setBalance(this->getBalance()-_getMoney);
    }
};

class DebitCard:public Card{
public:
    //Ke thua ham khoi tao cua lop Card
    using Card::Card;
    //Dinh nghia lai ham tru tuong cua lop Card(dong 147-149)
    void sendMoney(long _sendMoney){
        this->setBalance(this->getBalance()+_sendMoney);
    }

	//Dinh nghia lai ham tru tuong cua lop Card(dong 151-181)
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

//Ham lay phan tu co account number tuong ung trong mang co n phan tu
int getCardByAccountNumber(Card cards[], int n, char accountNumber[]){
    //Duyet qua toan bo phan tu trong mang
    for(int i=0;i<n;i++){
        //Kiem tra account number truyen vao co giong account number trong mang hay khong
        if(strcmp(cards[i].getAccountNumber(),accountNumber)==0){
            //Tim thay thi tra ve vi tri xuat hien
            return i;
        }
    }
    //Khong tim thay thi tra ve -1
    return -1;
}

//Ham kiem tra account ton tai hay khong
//Trong cung 1 ngan hang thì khong có 2 account cùng so tai khoan va ten khach hang
bool checkAccountExist(Card cards[], int n, char accNumber[], char cusName[], char bank[]){
    //Lay ra phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accNumber);
    //Co ton tai account
    if(index!=-1){
        //Kiem tra ten khach hang co ton tai hay khong
        if(strcmp(cards[index].getCustomerName(),cusName)==0){
            //Kiem tra ten ngan hang co ton tai hay khong
            if(strcmp(cards[index].getBankName(),bank)==0){
                //Co thi tra ve true(ton tai)
                return true;
            }
            else{
                //Khong ton tai
                return false;
            }
        }
        else{
            //Khong ton tai
            return false;
        }
    }
    //Khong ton tai account
    return false;
}

//Ham them account vao mang
void addCard(Card cards[], int &n){
    //Hien menu loai card cho user chon
    cout<<"+++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"|   1. Credit      |    2. Debit    |"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++"<<endl;
    int choice;
    //Yeu cau user chon loai card tuong ung trong menu
    cout<<">>Please select type of card: ";
    cin>>choice;
    //Khoi tao 1 doi tuong Card
    Card card;
    //Thuc hien them account vao mang theo loai card ma user chon
    switch(choice){
        //Truong hop user chon credit card
        case 1:
            {
                //Khoi tao 1 doi tuong credit card
                CreditCard cre;
                //Nhap thong tin cho doi tuong cre
                cre.typeInfo();
                //Ep kieu cre ve card
                card = cre;
                //Kiem tra ton tai hay khong, khong ton tai thi them vao mang
                if(checkAccountExist(cards,n,card.getAccountNumber(),card.getCustomerName(),card.getBankName())==false){
                    //Thiết lập type cho doi tuong la CREDIT_CARD
                    card.setType(0);
                    cards[n++] = card;
                }
                else{
                    cout<<">>> ACCOUNT HAS ALREADY EXIST!"<<endl;
                }
                break;
            }
        //Truong hop user chon debit card
        case 2:
            {
                //Khoi tao 1 doi tuong debit card
                DebitCard debit;
                //Nhap thong tin cho doi tuong debit
                debit.typeInfo();
                //Ep kieu debit ve card
                card = debit;
                //Kiem tra ton tai hay khong, khong ton tai thi them vao mang
                if(checkAccountExist(cards,n,card.getAccountNumber(),card.getCustomerName(),card.getBankName())==false){
                    //Thiết lập type cho doi tuong la DEBIT_CARD
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

//Ham cap nhat thong tin ngay hieu luc, ten ngan hang
void updateCard(Card cards[], int n, int choice, char accountNumber[], char newInfo[]){
    //Lay phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accountNumber);
    //Account ton tai
    if(index!=-1){
        //Truong hop cap nhat ngay hieu luc cua card
        if(choice==1){
            //Cap nhat lai ngay hieu luc bang ham setDateEffect() cua lop Card
            cards[index].setDateEffect(newInfo);
        }
        else{ //Truong hop cap nhat ten ngan hang
            //Cap nhat lai ten ngan hang bang ham setBankName() cua lop Card
            cards[index].setBankName(newInfo);
        }
        cout<<">>> UPDATE SUCCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> ACCOUNT NOT EXIST!"<<endl;
    }
}

void changePIN(Card cards[], int n, char accountNumber[]){
    int index = getCardByAccountNumber(cards,n,accountNumber);
    if(index!=-1){
        int newPIN, cofirmNewPIN;
        do{
            cout<<"Type new PIN: ";
            cin>>newPIN;
            if(newPIN<1000||newPIN>=10000){
                cout<<">>> INCORRECT PIN! PIN HAS 4 DIGITS!"<<endl;
            }
        }while(newPIN<1000||newPIN>=10000);
        cout<<"Confirm new PIN: ";
        cin>>cofirmNewPIN;
        if(newPIN==cofirmNewPIN){
            cards[index].setPIN(newPIN);
            cout<<">>> CHANGE PIN SUCCESSFULLY!"<<endl;
        }
        else{
            cout<<">>> INCORRECT PIN"<<endl;
        }
    }
    else{
        cout<<">>> ACCOUNT NOT EXIST!"<<endl;
    }
}

//Ham thay doi trang thai card
void changeStatus(Card cards[], int n, char accountNumber[]){
    //Lay phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accountNumber);
    //Account ton tai
    if(index!=-1){
        //Cap nhat lai trang thai bang ham setStatus() cua lop Card
        //Neu trang thai dang la Active thi doi thanh No active va nguoc lai
        cards[index].setStatus(!cards[index].getStatus());
        cout<<">>> CHANGE STATUS SUCCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> ACCOUNT NOT EXIST!"<<endl;
    }
}

//Ham gui tien vao account
void sendMoneyToCard(Card cards[], int n, char accountNumber[], long _sendMoney){
    //Lay phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accountNumber);
    //Account ton tai
    if(index!=-1){
        //Goi ham sendMoney() cua class Card
        cards[index].sendMoney(_sendMoney);
        cout<<"SEND MONEY SUCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> ACCOUNT NOT EXIST!"<<endl;
    }
}

//Ham rut tien tu account
void WithDrawMoney(Card cards[], int n, char accountNumber[], int pin, long getMoney){
    //Lay phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accountNumber);
    //Account ton tai
    if(index!=-1){
        if(cards[index].getPIN()==pin){
            //Goi ham getMoney() cua class Card
            cards[index].getMoney(getMoney);
        }
        else{
            cout<<">>> INVALID PIN CODE!"<<endl;
        }
        
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

//Ham xoa card ra khoi danh sach
void removeCard(Card cards[], int &n, char accountNumber[]){
    //Lay phan tu co account number tuong ung trong mang
    int index = getCardByAccountNumber(cards,n,accountNumber);
    //Account ton tai
    if(index!=-1){
        for(int i=n-1;i>=0;i--){  //1 2 3 4 --> 1 3 4
            //Tim thay phan tu can xoa
            if(i==index){
                    //Tien hanh xoa phan tu
                    for(int j=index;j<n;j++){
                        //Di chuyen cac phan tu phia sau ve truoc 1 don vi
                        cards[j]=cards[j+1];
                    }
                    //Giam kich thuoc mang
                    n--;
            }
        }
        cout<<">>> DELETE SUCESSFULLY!"<<endl;
    }
    else{
        cout<<">>> CAN'T FIND CARD HAS ACCOUNT NUMBER "<<accountNumber<<"!"<<endl;
    }
}

//Ham hien thi danh sach card ra man hinh console
void showListCard(Card cards[], int n){
    //Hien thi tieu de cua bang
    cout<<"+-----+---------------+-------------------------+-----+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    printf("|%-2s%-3s|%-4s%-11s|%-5s%-20s|%-2s%-3s|%-4s%-8s|%-10s%-10s|%-6s%-9s|%-6s%-9s|%-3s%-10s|\n"," ","No."," ","Account"," ","Customer"," ","PIN"," ","Effective date"," ","Bank"," ","Balance"," ","Status"," ","Type of card");
    cout<<"+-----+---------------+-------------------------+-----+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    int index=1;
    //Duyet qua toan bo danh sach
    for(int i=0;i<n;i++){
        //In thong tin cua tung doi tuong card trong danh sach
        printf("|%5d",index);
        cards[i].showInfo();
        index++;
    }
    cout<<"+-----+---------------+-------------------------+-----+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    cout<<"COMPLETE SUCCESSFULLY!"<<endl;
}

bool checkCustomerExist(Card cards[], int n, char cusName[]){
    for(int i=0;i<n;i++){
        if(strcmp(cards[i].getCustomerName(),cusName)==0){
            return true;
        }
    }
    return false;
}

bool checkBankExist(Card cards[], int n, char bank[]){
    for(int i=0;i<n;i++){
        if(strcmp(cards[i].getBankName(),bank)==0){
            return true;
        }
    }
    return false;
}

//Ham tra ve danh sach the so huu cua khach hang ten tuong ung
void findListCardByCustomerName(Card cards[], int n, char customerName[]){
    cout<<"+-----+---------------+-------------------------+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    printf("|%-2s%-3s|%-4s%-11s|%-5s%-20s|%-4s%-8s|%-10s%-10s|%-6s%-9s|%-6s%-9s|%-3s%-10s|\n"," ","No."," ","Account"," ","Customer"," ","Effective date"," ","Bank"," ","Balance"," ","Status"," ","Type of card");
    cout<<"+-----+---------------+-------------------------+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    if(checkCustomerExist(cards,n,customerName)==true){
        int index=1;
        //Duyet qua toan bo danh sach
        for(int i=0;i<n;i++){
            if(strcmp(cards[i].getCustomerName(),customerName)==0){
                printf("|%5d",index);
                //In thong tin cua tung doi tuong card trong danh sach
                cards[i].showInfo();
                index++;
            }
        }
    }
    else{
        printf("|%15s|%25s|%14s|%20s|%15s|%15s|\n"," "," "," "," "," "," ");
    }
    cout<<"+-----+---------------+-------------------------+------------------+--------------------+---------------+---------------+---------------+"<<endl;
    cout<<"COMPLETE SUCCESSFULLY!"<<endl;
}

void statisticAmountOfCardByBank(Card cards[], int n, char bank[]){
    Card filter[100];
    int m=0;
    if(checkBankExist(cards,n,bank)==true){
        int numberOfCredit=0, numberOfDebit=0;
        for(int i=0;i<n;i++){
            if(strcmp(cards[i].getBankName(),bank)==0){
                filter[m++] = cards[i];
            }
        }
        showListCard(filter,m);
    }
    else{
        cout<<">>> INVALID BANK!"<<endl;
    }
}

//Ham luu thong tin card vao file nhi phan(Binary File)
void writeListCardToFile(Card cards[], int n, char* fileName){
   fstream f;
   f.open(fileName,ios::out);
   f<<n<<endl;
   for(int i=0;i<n;i++){
       f<<cards[i].getAccountNumber()<<","<<cards[i].getCustomerName()<<","<<cards[i].getPIN()<<","<<cards[i].getDateEffect()<<","
        <<cards[i].getBankName()<<","<<cards[i].getBalance()<<","<<cards[i].getStatus()<<","<<cards[i].getType()<<endl;
   }
   f.close();
    cout<<">>> EXPORT TO FILE SUCESSFULLY!"<<endl;
    //Lay duong dan luu file
    char buff[PATH_MAX];
    _getcwd(buff,PATH_MAX);
    string current_working_dir(buff);
    cout<<">>> Location: "<<current_working_dir<<endl;
}

void readCard(ifstream &f, Card &card){
    //Acc,Cus,Date,Bank,Bal,Status,Type
    char tmp[50],simicolon;
    char delChar[3], del;
    double bal;
    int status;
    int type,pin;
    f.getline(tmp,15,',');
    card.setAccountNumber(tmp);
    f.getline(tmp,30,',');
    card.setCustomerName(tmp);
    f>>pin>>del;
    card.setPIN(pin);
    f.getline(tmp,11,',');
    card.setDateEffect(tmp);
    f.getline(tmp,20,',');
    card.setBankName(tmp);
    f>>bal>>simicolon>>status>>simicolon>>type;
    card.setBalance(bal);
    card.setStatus(status);
    card.setType(type);
    f.getline(delChar,3,'\n');
}
//Ham doc thong tin card tu file nhi phan(Binary File)
void readListCardFromFile(Card cards[], int &n, char* fileName){
    ifstream fo;
    //Mo file de doc
    fo.open(fileName);
    //Kiem tra file ton tai hay khong
    if(!fo){
        //File khong ton tai thi in ra cau thong bao va thoat khoi ham
        printf("Loi doc file!\n");
        return;
    }
    //Doc so luong mon an tu file
    char tmp[30];
    fo.getline(tmp,sizeof(tmp)/sizeof(char),'\n');
    n = atoi(tmp);
    //Lan luot doc du lieu mon an tu file va luu vao danh sach mon an
    for(int i=0;i<n;i++){
        //Lan luot doc du lieu mon an tu file va luu vao mon an thu i
        readCard(fo,cards[i]);
    }
    //Dong file
    fo.close();
    showListCard(cards,n);
    cout<<">>> IMPORT FROM FILE SUCCESSFULLY!"<<endl;
}

int menu(){
    cout<<"+--------------------MENU---------------------------+"<<endl;
    cout<<"|          1. Add new card                          |"<<endl;
    cout<<"|          2. Update information card               |"<<endl;
    cout<<"|          3. Show list cards                       |"<<endl;
    cout<<"|          4. Send money                            |"<<endl;
    cout<<"|          5. Withdraw money                        |"<<endl;
    cout<<"|          6. Remove card                           |"<<endl;
    cout<<"|          7. Chang PIN code                        |"<<endl;
    cout<<"|          8. Change status of card                 |"<<endl;
    cout<<"|          9. Write list of cards to file           |"<<endl;
    cout<<"|         10. Read list of card from file           |"<<endl;
    cout<<"|         11. List card of customer                 |"<<endl;
    cout<<"|         12. Statistic amount of card of bank      |"<<endl;
    cout<<"|         13. Exit                                  |"<<endl;
    cout<<"+---------------------------------------------------+"<<endl;
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
                    int pin;
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    cout<<"Enter your PIN code: ";
                    cin>>pin;
                    do{
                        cout<<"Enter money to withdraw: ";
                        cin>>money;
                        if(money<0){
                            cout<<"Invalid money!"<<endl;
                        }
                    }while(money<0);
                    WithDrawMoney(cards,n,accountNumber,pin, money);
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
                    changePIN(cards,n,accountNumber);
                    break;
                }
            case 8:
                {
                    char accountNumber[15];
                    cout<<"Enter account number: ";
                    cin>>accountNumber;
                    changeStatus(cards,n,accountNumber);
                    break;
                }
            case 9:
                {
                    writeListCardToFile(cards,n,(char*)file);
                    break;
                }
            case 10:
                {
                    readListCardFromFile(cards,n,(char*)file);
                    break;
                }
            case 11:
                {
                    cin.ignore();
                    char customerName[30];
                    cout<<"Type customer name: ";
                    cin.getline(customerName,sizeof(customerName)/sizeof(char));
                    findListCardByCustomerName(cards,n,customerName);
                    break;
                }
            case 12:
                {
                    cin.ignore();
                    char bankName[30];
                    cout<<"Type bank name: ";
                    cin.getline(bankName,sizeof(bankName)/sizeof(char));
                    statisticAmountOfCardByBank(cards,n,bankName);
                    break;
                }
            case 13:
                {
                    checked = -1;
                    goto end_program;
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
    end_program:
    return 0;
}
