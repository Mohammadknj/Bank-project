#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
#define lli long long
string date;
lli random(int digits){
    lli res=0;
    for(int i=0;i<digits;i++){
        res+=rand()%9;
        res*=10;
    }
    return res;
}
class account{
private:
    string account_type;
    lli card_num;
    lli sheba;
    lli account_num;
    lli cvv2,pass1;
    lli pass2;
    lli stock;
    string date;
    lli pouya_pass;
    account * next_acc;
    account * pre_acc;
public:
    template<typename Z>
    friend class linklist;
    account(string type,int pass,lli stock,string date){
        account_type=type;
        card_num=random(16);
        sheba=random(18);
        account_num=random(13);
        cvv2=random(4);
        pass1=pass;
        pass2=0;
        this->stock=stock;
        this->date=date;
        pouya_pass=0;
        next_acc=nullptr;
        pre_acc=nullptr;
    }
    void set_pass2(lli p){
        pass2=p;
    }
    void set_pass1(lli p){
        pass1=p;
    }
    string get_type(){
        return account_type;
    }
    account * getNextacc(){
        return next_acc;
    }
    lli get_pass1(){
        return pass1;
    }
    lli get_pass2(){
        return pass2;
    }
    void set_rand_pouya_pass(){
        pouya_pass=random(8);
    }
    lli get_stock(){
        return stock;
    }
    lli get_card_num(){
        return card_num;
    }
    string get_date(){
        return date;
    }
    void add_stock(lli num){
        stock+=num;
    }
};
template<typename T>
class linklist{
private:
    int size;
    T *head_acc;
    T *tail_acc;
public:
    linklist(){
        head_acc=nullptr;
        tail_acc=nullptr;
        size=0;
    }
    ~linklist(){

    }
    int getSize(){
        return size;
    }
    void set_tail(T t){
        tail_acc=t;
    }
    T *get_tail(){
        return tail_acc;
    }
    void push_acc(T *acc){
        if(head_acc==nullptr){
            head_acc=acc;
            tail_acc=acc;
            size++;
        }
        else{
            tail_acc->pre_acc=acc;
            acc->next_acc=tail_acc;
            tail_acc=acc;
            size++;
        }
    }
    linklist(linklist<T> const &x){
        head_acc=nullptr;
        tail_acc=nullptr;
        size=0;
        T *acc=x.tail_acc;
        while(acc!=nullptr){
            this->push_acc(acc);
            acc=acc->getNextacc();
        }
    }
    void print(){
        if(size==0){
            cout<<"Empty";
        }
        else{
            T* acc=tail_acc;
            while(acc!=nullptr){
                cout<<acc->get_type()<<"\t";
                acc=acc->getNextacc();
            }
        }
        cout<<endl;
    }
    void print_acc_nums(){
        if(size==0){
            cout<<"Empty\n";
        }
        else{
            T* acc=tail_acc;
            while(acc!=nullptr){
                cout<<acc->get_card_num()<<"\n";
                acc=acc->getNextacc();
            }
        }
    }
};
template<class T>
class user{
private:
    string name,family;
    lli ID;
    int age;
    string username;
    string password;
    linklist<T> cards;
public:
    int get_size(){
        return cards.getSize();
    }
    template<class Z>
    friend void make_account(user<Z> &u);
    template<class R>
    friend void change_pass(user<R> &u);
    template<class O>
    friend void check_stock(user<O> &u);
    template<class W>
    friend void card_by_card(user<W> &u);
    user(string name,string family,lli id,int age,string username,string password){
        this->name=name;
        this->family=family;
        ID=id;
        this->age=age;
        this->username=username;
        this->password=password;
    }
    user(const user& x) {
        name = x.name;
        family = x.family;
        ID = x.ID;
        age = x.age;
        username = x.username;
        password = x.password;
        cards = x.cards;
    }
    string get_name(){
        return name;
    }
    string get_family(){
        return family;
    }
    string get_username(){
        return username;
    }
    string get_password(){
        return password;
    }
};
template<class T>
vector<user<T>>users;
template<class T>
void make_account(user<T> &u){
    if(u.cards.getSize()<5){
        cout<<"Enter account's type: ";
        string type;
        cin>>type;
        cout<<"Enter the number of first transition: ";
        lli num;
        while(true){
            cin>>num;
            if(num>=50000){
                cout<<"Enter your 4 digited password: ";
                int pass;
                cin>>pass;
                cout<<"Enter date(seprate year and month with .): ";
                string date;
                int year,month;char c;
                cin>>year>>c>>month;
                year+=3;
                date=to_string(year);
                date+=c;
                date+=to_string(month);
                account *acc=new account(type,pass,num,date);
                cout<<"Do you want second pass?\nYes\tNo "<<endl<<"Enter a choice: ";
                string str;
                cin>>str;
                if(str=="Yes"){
                    lli ps2;
                    cout<<"Enter the second pass: ";
                    cin>>ps2;
                    acc->set_pass2(ps2);
                }
                u.cards.push_acc(acc);
                break;
            }
            else cout<<"You should enter more than 50000\nTry again: ";
        }
    }
    else{
        cout<<"You have more than 5  accounts\n";
    }
}

template<class T>
void change_pass(user<T> &u){
    cout<<"Your accounts: ";
    u.cards.print();
    cout<<"Which account's pass do u wanna change?\nEnter it's type: ";
    string type;
    cin>>type;
    T *acc=u.cards.get_tail();
    int cnt=0;
    while(acc->get_type()!=type){
        acc=acc->getNextacc();
        cnt++;
    }
    if(cnt!=u.get_size()){
        cout<<"Do you wanna change first pass or second?\n1.first\n2.second"<<endl;
        cout<<"Enter a num: ";int n;
        while (true){
            cin >> n;
            if (n == 1) {
                cout<<"Enter your current first pass: ";
                lli p;cin>>p;
                if(p==acc->get_pass1()){
                    cout<<"Enter new password: ";
                    cin>>p;
                    acc->set_pass1(p);
                    cout<<"Password changed successfully\n";
                }
                else cout<<"Password wasn't correct\n";
                break;
            } else if (n == 2) {
                cout<<"Enter your current second pass: ";
                int p;cin>>p;
                if(p==acc->get_pass2()){
                    cout<<"Enter new password: ";
                    cin>>p;
                    acc->set_pass2(p);
                }
                else cout<<"Password wasn't correct\n";
                break;
            } else
                cout << "Invalid! Try again: ";
        }
    }
    else cout<<"Type didn't find\n";
}
template<class T>
void check_stock(user<T> &u){
    cout<<"Accounts: ";
    u.cards.print();
    cout<<"Which account's stock do u wanna check?\nEnter it's type: ";
    string type;
    cin>>type;
    account acc=*u.cards.get_tail();
    while(acc.get_type()!=type){
        acc=*acc.getNextacc();
    }
    cout<<acc.get_stock()<<endl;
}
bool check_date(string str){
    int y1=0,m1=0,y2=0,m2=0;
    for(int i=0;i<(int)str.length();i++){
        if(str[i]=='.'){
            while(i<(int)str.length()-1){
                i++;
                m1+=str[i]-48;
                m1*=10;
            }
            y1/=10;
            m1/=10;
            break;
        }
        y1+=str[i]-48;y1*=10;
    }
    for(int i=0;i<(int)date.length();i++){
        if(date[i]=='.'){
            while(i<(int)date.length()-1){
                i++;
                m2+=date[i]-48;
                m2*=10;
            }
            y2/=10;
            m2/=10;
            break;
        }
        y2+=date[i]-48;y2*=10;
    }
    if(y1>y2)
        return false;
    if(y1<y2){
        return true;
    }
    else{
        if(m1>m2)
            return false;
        return true;
    }
}
template<class T>
void card_by_card(user<T>&u){
    cout<<"Account numbers:\n";
    u.cards.print_acc_nums();
    cout<<"Enter your card number: ";
    lli num,num1;cin>>num;
    account acc=*u.cards.get_tail();
    int cnt=0;
    while(acc.get_card_num()!=num){
        acc=*acc.getNextacc();
        cnt++;
    }
    if(cnt==u.cards.getSize())
        cout<<"Card didn't find\n";
    else {
        if (!check_date(acc.get_date())) {
            cout << "Enter your second pass: ";
            lli pass2;
            cin >> pass2;
            if(pass2==acc.get_pass2()){
                cout << "Enter the card number you wanna send to: ";
                cin >> num1;
                bool found = false;
                for (int i = 0; i < (int)users<T>.size(); i++) {
                    int c = 0;
                    T *Acc = users<T>[i].cards.get_tail();
                    while (Acc != nullptr && Acc->get_card_num() != num1) {
                        Acc = Acc->getNextacc();
                        c++;
                    }
                    if (c != users<T>[i].cards.getSize()) {
                        found = true;
                        cout << users<T>[i].get_name() << " " << users<T>[i].get_family()
                             << endl;
                        cout << "Enter the number of money you wanna send to: ";
                        double money;
                        while (true) {
                            cin >> money;
                            money -= (money * 0.0001);
                            if (money > 3000000) {
                                cout << "You should enter less than 3000000 in one "
                                        "transition\nTry again: ";
                            } else {
                                if (acc.get_stock() >= money) {
                                    if (money >= 100000) {
                                        cout << "You should use your pouya password\n";
                                        acc.set_rand_pouya_pass();
                                        cout << "A random poya pass was entered to your "
                                                "pouya pass\n";
                                    }
                                    Acc->add_stock(money);
                                    money-=2*money;
                                    acc.add_stock(money);
                                    cout << "Successful tansition:)\n";
                                } else
                                    cout << "Insufficient inventory(mojoodi kafi nist)\n";
                                break;
                            }
                        }
                    }
                    //}
                }
                if (!found)
                    cout << "The entered card number is not valid\n";
            }else cout<<"Second password was wrong\n";
        } else
            cout << "This card has expired\nIt should be changed\n";
    }
}

template<class T>
void panel(user<T>&u){
    int choice;
    do{
        cout<<"Panel:"<<endl;
        cout<<"1.Make bank account\n";
        cout<<"2.Change password\n";
        cout<<"3.Stock\n";
        cout<<"4.Card by card\n";
        cout<<"0.Exit\n";
        cout<<"Enter a number: ";
        cin>>choice;
        switch(choice){
        case 1:
            make_account(u);
            break;
        case 2:
            change_pass(u);
            break;
        case 3:
            check_stock(u);
            break;
        case 4:
            card_by_card(u);
            break;
        case 0:
            break;
        default:
            cout<<"Invalid choice! try again.\n";
        }
    }while(choice!=0);
}

template<class T>
void Enter(){
    string usn,pas;
    cout<<"Enter your username: ";
    cin>>usn;
    cout<<"Enter your password: ";
    cin>>pas;
    bool found1=false,found2=false;
    for(int i=0;i<(int)users<T>.size();i++){
        if(users<T>[i].get_username()==usn){
            found1=true;
            if(users<T>[i].get_password()==pas){
                found2=true;
                cout<<"Welcome "<<users<T>[i].get_name()<<" "<<users<T>[i].get_family()<<endl;
                user<T> &u=users<T>[i];
                panel(u);
                break;
            }
        }
    }
    if(!found1)
        cout<<"Username didn't find\n";
    if(!found2)
        cout<<"Password wasn't true\n";
}
template<class T>
void registreing(){
    string name,family,username,password;
    cout<<"Enter your name: ";
    cin>>name;
    cout<<"Enter your family: ";
    cin>>family;
    cout<<"Enter your ID: ";
    lli id;
    cin>>id;
    int age;
    cout<<"Enter your age: ";
    cin>>age;
    cout<<"Enter your username: ";
    cin>>username;
    cout<<"Enter your user password: ";
    cin>>password;
    user<T> u(name,family,id,age,username,password);
    users<T>.push_back(u);
}
template<class T>
void menu(){
    int n;
    do{
        cout<<"1.Register\n2.Enter\n0.Exit"<<endl;
        cout<<"Enter a number: ";
        cin>>n;
        switch(n){
        case 1:
            registreing<T>();
            break;
        case 2:
            Enter<T>();
            break;
        case 0:
            break;
        default:
            cout<<"Invalid choice! try again.\n";
        }
    }while(n!=0);
}
std::tm getCurrentTime() {
    std::time_t now = std::time(nullptr);
    return *std::localtime(&now);
}
int getYear(const std::tm& date) {
    return date.tm_year - 100;
}
int getMonth(const std::tm& date) {
    return date.tm_mon + 1;
}
int main(){
    srand(time(0));
    string type;
    cout << "Enter datatype: ";
    cin>>type;
    std::tm now = getCurrentTime();
    date=to_string(getYear(now));
    date+='.';
    date+=to_string(getMonth(now));
    if(type=="account"){
        menu<account>();
    }
    cout<<"Hope you enjoyed!\nGoodbye\n";
    return 0;
}
