//-lmingw32 -lSDL2main -lSDL2
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <windows.h>

using namespace std::chrono;
using namespace std;

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void print_asterisk(int n)
{
   for (int i =0; i<n ; i++ )
   {
       cout << '*' ;
   }
}
void format()
{
    cout << "\n\n\n\n\n";
    cout << "\t\t";
    print_asterisk(60);
    cout << "\n\t\t  ";
    print_asterisk(15);
    cout << "+------------------------+";
    print_asterisk(15);
    cout << "\n\t\t    ";
    print_asterisk(13);
    cout << "|Cryptocurrency  Exchange|";
    print_asterisk(13);
    cout << "\n\t\t  ";
    print_asterisk(15);
    cout << "+------------------------+";
    print_asterisk(15);
    cout << "\n\t\t";
    print_asterisk(60);
    cout << "\n\n";
}

struct user
{
    string username, email, password;
    double coins[10];
};
struct transfer
{
    string sender, reciever;
    int ID;
    double amount;
};
struct conversion
{
    string user_ID;
    int old_coin, new_coin;
    double old_amount, new_amount;
};
struct CoinClass
{
private:
    string abbrev_coin, name_coin;
    double fixed_rate;
    double rate_coin;
public:
    CoinClass(string name, string abbrev ,double rate)
    {
        name_coin = name;
        abbrev_coin = abbrev;
        fixed_rate = rate;
        rate_coin = rate;
    }
    string get_abbrev()
    {
        return abbrev_coin;
    }
    string get_name()
    {
        return name_coin;
    }
    double get_rate()
    {
        return rate_coin;
    }
    void update(double multiplier)
    {
        rate_coin = fixed_rate*multiplier;
    }
};
vector<CoinClass>coin;
void dynamicUpdate(bool* running)
{
    auto r = high_resolution_clock::now();
    while(*running)
    {
        for(int i = 1; i<10 ;++i)
        {
            auto t = high_resolution_clock::now();
            auto u = duration_cast<microseconds>(t-r);
            srand(u.count());
            int n = (rand()%200)+900;
            coin[i].update(n/1000.0);
        }
        this_thread::sleep_for(200ms);
    }
}
void dynamicPrint(char* c)
{
    while((*c) == '\0')
    {
        for(int i = 1 ;i<11 ;++i)
        {
            gotoxy(46,11+i);
            cout << ' ' << left << setw(7) << coin[i].get_rate();
        }
        this_thread::sleep_for(1200ms);
    }
}
void print_asterisk()
{
   for (int i =0; i<25 ; i++ )
   {
       cout << "*";
   }
   cout << "\n";
}
int authenticate(bool &status,string input, vector <user> v)
{
    status = false;
    int i=0;
    while(i<v.size())
    {
        if(v[i].username == input)
        {
            status = true;
            break;
        }
        i++;
    }
    return i;
}
void add_coin()
{
    coin.push_back(CoinClass("Default","Error",1));
    coin.push_back(CoinClass("Bitcoin", "BTC",56000));
    coin.push_back(CoinClass("Ethereum", "ETH",4400));
    coin.push_back(CoinClass("Dogecoin", "DOGE",1.4));
    coin.push_back(CoinClass("Polkadot", "DOT",52));
    coin.push_back(CoinClass("Solana", "SOL",232));
    coin.push_back(CoinClass("Chainlink", "LINK",28));
    coin.push_back(CoinClass("Thorchain", "RUNE",14));
    coin.push_back(CoinClass("Uniswap", "UNI",35));
    coin.push_back(CoinClass("Litecoin", "LTC",215));
    coin.push_back(CoinClass("Tether", "USDT",1));
}
void add_transfer(vector <transfer> &v,string Sender, string Reciever, int coin_ID, double Amount)
{
    transfer slot;
    slot.sender = Sender;
    slot.reciever = Reciever;
    slot.ID = coin_ID;
    slot.amount = Amount;
    v.push_back(slot);
}
void add_conversion(vector <conversion> &v,string current_user, int OLD_COIN, int NEW_COIN, double OLD_A , double NEW_A)
{
    conversion log;
    log.user_ID = current_user;
    log.old_coin = OLD_COIN;
    log.new_coin = NEW_COIN;
    log.old_amount = OLD_A;
    log.new_amount = NEW_A;
    v.push_back(log);
}
void add_data(vector <user> &v)
{
    user cred;
    string dummy;
    bool check;
    system("CLS");
    format();
    cout << "\t\tEnter your username: ";
    getline(cin, dummy);
    authenticate(check,dummy,v);
    while(check)
    {
        system("CLS");
        format();
        cout << "\t\tThere is already a username with " << dummy;
        cout << "\n\t\tsuggested usernames:\n";
        cout << "\t\t<23" << dummy << "> ";
        cout << "<" << dummy << "_5618> ";
        cout << "<045" << dummy << "op> \n";
        cout << "\t\tTry another one:\n\t\t";
        getline(cin, dummy);
        authenticate(check,dummy,v);
    }
    cred.username = dummy;
    system("CLS");
    format();
    cout << "\n\t\tEnter your email: \n\t\t";
    getline(cin, dummy);
    int special_sign = 0;
    for (int i =0; i<dummy.size() ; i++ )
    {
        char c = dummy[i];
        if(c =='@'){special_sign++;}
        if(c==' ' || c =='/'){special_sign+=100;}
    }
    while(special_sign!=1)
    {
        special_sign = 0;
        system("CLS");
        format();
        cout << "\t\tInvalid email format.\n\t\t";
        getline(cin, dummy);
        special_sign=0;
        for (int i =0; i<dummy.size() ; i++ )
        {
            char c = dummy[i];
            if(c =='@'){special_sign++;}
            if(c==' ' || c =='/'){special_sign+=100;}
        }
    }
    cred.email = dummy;
    dummy.clear();
    system("CLS");
    format();
    cout << " \n\t\tEnter your password: \n\t\t";
    getline(cin, dummy);
    int s = dummy.size();
    while(s<6)
    {
        system("CLS");
        format();
        cout << "\t\tPassword must be at least 6 characters.\n\t\t";
        getline(cin, dummy);
        s = dummy.size();
    }
    cred.password = dummy;
    system("CLS");
    format();
    double deposit_amount;
    cout << "\t\tEnter your depositing amount: \n\t\t";
    cin >> deposit_amount;
    while(cin.fail() || deposit_amount <= 0)
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("CLS");
        format();
        cout << "\t\tEnter appropriate deposit amount: \n\t\t";
        cin >> deposit_amount;
    }
// Initialize balance for the user.
    for (int i =0; i<9 ; i++ )
    {
        cred.coins[i] = 0;
    }
    cred.coins[9]=deposit_amount;

    v.push_back(cred);
    system("CLS");
    format();
    cout << "\t\t";
    print_asterisk();
    cout << "\t\tYour account was succesfully created.\n";
    cout << "\t\tYou can log in with your credentials.\n\t\t";
    print_asterisk();
    char temp = getch();
    return;
}
void coin_index()
{
    cout << "\t\t------- COIN ID INDEX --------\n\t\t";
    cout << setw(18) << left << "COIN NAME" << "|COIN ID|\n";
    cout << "\t\t\t\t  " << "|\t  |\n";
    for (int i =1; i<=10 ; i++ )
    {
        cout << "\t\t";
        cout << setw(12) << left << coin[i].get_name()
             << setw(6)  << left << coin[i].get_abbrev()
             << "|   " << setw(2) << i << "  |" << "\n";
    }
    cout << "\t\t------------------------------\n";
}
void print_wallet(vector <user> &v ,int login_index)
{
    system("CLS");
    format();
    cout << "\t\t***** WALLET INFORMATION *****\n";
    for (int i =0; i<10 ; i++ )
    {
        cout << "\t\t";
        cout << setw(10) << left << coin[i+1].get_name() << ": ";
        cout << setw(10) << left << v[login_index].coins[i]
             << setw(4) << coin[i+1].get_abbrev() << "  |$"
             << setw(8) << "  ----  " << "|" << "\n";
    }
    char temp;
    thread _print(dynamicPrint,&temp);
    temp = getch();
    _print.join();
}
void print_transfer_history(vector <transfer> v ,string login_username)
{
    system("CLS");
    format();
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].reciever == login_username)
        {
            cout << "\t\t";
            int _ID = v[i].ID+1;
            cout << v[i].sender << " sent you "
                 << v[i].amount << " " << coin[_ID].get_name() << endl;
        }
        else if(v[i].sender == login_username && i>5)
        {
            int _ID = v[i].ID+1;
            cout << "\t\tYou sent " << v[i].reciever << " "
                 << v[i].amount << " " << coin[_ID].get_name() << endl;
        }
        else if(v[i].sender == login_username && i<=5)
        {
            int _ID = v[i].ID+1;
            cout << "\t\tYou paid " << v[i].reciever << " "
                 << v[i].amount << " " << coin[_ID].get_name() << endl;
        }
    }
    char temp;
    cout << "\t\t";
    temp = getch();
}
void print_conversion_history(vector <conversion> v , string login_username)
{
    char temp;
    system("CLS");
    format();
    for (int i =0; i<v.size() ; i++ )
    {
        if(v[i].user_ID == login_username)
        {
            cout << "\t\t";
            int _ID = v[i].old_coin+1;
            cout << "You swapped " << v[i].old_amount << " "
                 << coin[_ID].get_name() << " (" << coin[_ID].get_abbrev();
            _ID = v[i].new_coin+1;
            cout << ") for " << v[i].new_amount << " " << coin[_ID].get_name()
            << " (" << coin[_ID].get_abbrev() << ")\n";
        }
    }
    cout << "\t\t";
    temp = getch();
}
void save_file(vector <user> v, vector <transfer> t, vector <conversion> c)
{
    ofstream database;
    database.open("database.txt",ios::out);
    for (int i =0; i<v.size() ; i++ )
    {
        database << v[i].username << endl;
        database << v[i].email << endl;
        database << v[i].password << endl;
        for (int j =0; j<10 ; j++ )
        {
            database << v[i].coins[j] << endl;
        }
    }
    /****************************************/
    ofstream transfer_log;
    transfer_log.open("transfer_log.txt",ios::out);
    for (int j =0; j<t.size() ; j++ )
    {
        transfer_log << t[j].sender << endl;
        transfer_log << t[j].reciever << endl;
        transfer_log << t[j].ID << endl;
        transfer_log << t[j].amount << endl;
    }
    /*****************************************/
    ofstream conversion_log;
    conversion_log.open("conversion_log.txt",ios::out);
    for (int k =0; k<t.size() ; k++ )
    {
        conversion_log << c[k].user_ID << endl;
        conversion_log << c[k].old_coin << endl;
        conversion_log << c[k].old_amount << endl;
        conversion_log << c[k].new_coin << endl;
        conversion_log << c[k].new_amount << endl;
    }
}
void open_file(vector <user> &v, vector <transfer> &t, vector <conversion> &c)
{
    string line;
    int i=0, int0;
    double doub;
    ifstream database;
    user cred;
    database.open("database.txt",ios::in);
    if(database.is_open())
   {
       while(getline(database,line))
       {
           if(i%13==0){cred.username=line;}
           else if(i%13==1){cred.email=line;}
           else if(i%13==2){cred.password=line;}
           else
           {
               doub = stod(line);
               cred.coins[(i%13)-3]=doub;
           }
           if(i%13==12){v.push_back(cred);}
           i++;
       }
   }
   database.close();
   /*************************************/
   ifstream transfer_log;
   transfer tran;
   transfer_log.open("transfer_log.txt",ios::in);
   if(transfer_log.is_open())
   {
       i = 0;
       while(getline(transfer_log,line))
       {
           if(i%4==0)     {tran.sender= line;}
           else if(i%4==1){tran.reciever = line;}
           else if(i%4==2)
           {
               int0 = stoi(line);
               tran.ID = int0;
           }
           else
           {
               doub = stod(line);
               tran.amount = doub;
               t.push_back(tran);
           }
           i++;
       }
   }
   transfer_log.close();
   /*************************************/
   ifstream conversion_log;
   conversion conv;
   conversion_log.open("conversion_log.txt",ios::in);
   if(conversion_log.is_open())
   {
       i = 0;
       while(getline(conversion_log,line))
       {
           if(i%5==0){conv.user_ID = line;}
           else if(i%5==1)
           {
               int0 = stoi(line);
               conv.old_coin = int0;
           }
           else if(i%5==2)
           {
               doub = stod(line);
               conv.old_amount = doub;
           }
           else if(i%5==3)
           {
               int0 = stoi(line);
               conv.new_coin = int0;
           }
           else
           {
               doub = stod(line);
               conv.new_amount = doub;
               c.push_back(conv);
           }
           i++;
       }
   }
   conversion_log.close();
}
void miner(int current_user, vector <user> &v)
{
    static const char pool[] = {"0123456789abcdef"};
    string choice;
    char temp;
    string Hash = "";
    srand(time(NULL));
    system("CLS");
    format();
    while(1)
    {
        cout << "\t\tSelect the coin you want to mine: \n";
        cout << "\t\tPress 1 for Bitcoin\n";
        cout << "\t\tPress 2 for Ethereum\n\t\t";
        cin >> choice;
        if(choice == "1" || choice == "2"){break;}
        cout << "\t\tEnter a valid number\n\n";
    }
    system("CLS");
    format();
    cout << "\t\tMining Blocks\n";
    cout << "\t\tElapsed time: " ;
    auto start = high_resolution_clock::now();
    for (int i =0; i<30 ; i++ )
    {
        auto _end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(_end-start);
        gotoxy(30,12);
        cout << duration.count()/1000000.0 << "s\n\n";
        Hash = "";
        for (int j =0; j<18 ; j++ )
        {
            Hash += "\t\t";
            for (int k =0; k<60 ; k++ )
            {
                temp = pool[rand()%16];
                Hash += temp;
            }
            Hash += '\n';
        }
        gotoxy(0,13);
        cout << Hash;
        usleep(400000);
    }
    cout << "\t\t-----You mined a new block------\n";
    if(choice=="1")
    {
        v[current_user].coins[0]+=2.5;
        cout << "\t\tCongrats! You have got 2.5 BTC as reward.\n";
    }
    else if(choice=="2")
    {
        v[current_user].coins[1]+=12;
        cout << "\t\tCongrats! You have got 12 ETH as reward.\n";
    }
    cout << "\t\t";
    temp = getch();
}
void transfer_menu(int current_user, vector <user> &v, vector <transfer> &t)
{
    string user, choice = "1";
    int coin_ID;
    double amount;
    bool status;
    while(choice == "1")
    {
        system("CLS");
        format();
        cout << "\t\tEnter the username of person you want to transfer funds:\n\t\t";
        getline(cin, user);
        int user_pos = authenticate(status,user,v);
        if(!status)
        {
            system("CLS");
            format();
            cout << "\t\tUser not found!\n";
            cout << "\t\tPress 0 to return back.\n";
            cout << "\t\tPress 1 to retry.\n\t\t";
            getline (cin, choice);
        }
        else if(user==v[current_user].username)
        {
            system("CLS");
            format();
            cout << "\t\tYou can not transfer to yourself.\n";
            cout << "\t\t---------------------------------\n";
            cout << "\t\tPress 0 to return back.\n";
            cout << "\t\tPress 1 to retry.\n\t\t";
            getline (cin, choice);
        }
        else
        {
            choice = "0";
            system("CLS");
            format();
            coin_index();
            cout << "\t\tEnter the coin ID you want to transfer:\n\t\t";
            cin >> coin_ID;
            while(cin.fail() || coin_ID < 1 || coin_ID > 10)
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                system("CLS");
                format();
                coin_index();
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter a valid coin ID.\n";
                cout << "\t\t----------------------\n\n";
                cout << "\t\tEnter the coin ID you want to transfer:\n\t\t";
                cin >> coin_ID;
            }
            coin_ID--;
            system("CLS");
            format();
            cout << "\t\tEnter the amount you want to transfer:\n\t\t";
            cin >> amount;
            while(cin.fail() || amount < 0 || amount > v[current_user].coins[coin_ID])
            {
                cin.clear();
                cin.ignore();
                system("CLS");
                format();
                cout << "\t\t----------------------\n";
                cout << "\t\tInvalid Input or Insufficient balance.\n";
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter the amount you want to transfer:\n\t\t";
                cin >> amount;
            }
                v[current_user].coins[coin_ID] -= amount;
                v[user_pos].coins[coin_ID] += amount;
                string dummy = v[current_user].username;
                if(amount!=0)
                {
                    add_transfer(t,dummy,user,coin_ID,amount);
                }
                cout << "\t\t--------------------------------------\n";
                cout << "\t\tTransaction is successful.\n";
                cout << "\t\t--------------------------------------\n\t\t";
                usleep(1*1000000);
                int _ID = coin_ID+1;
                print_asterisk();
                cout << "\t\tYou successfully transfered " << amount << " "
                << coin[_ID].get_abbrev() << " to " << user << ".\n\t\t";
                print_asterisk();
                char temp = getch();
        }
    }
}
void conversion_menu(int current_user, vector <user> &v, vector <conversion> &c)
{
    string choice;
    int old_coin, new_coin;
    double old_amount , new_amount;
    system("CLS");
    format();
    coin_index();
    cout << "\t\tEnter the coin ID of old asset:\n\t\t";
    cin >> old_coin;
    while(cin.fail() || old_coin < 1 || old_coin > 10)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            format();
            coin_index();
            cout << "\t\t----------------------\n";
            cout << "\t\tEnter a valid coin ID.\n";
            cout << "\t\t----------------------\n\n";
            cout << "\t\tEnter the coin ID of old asset:\n\t\t";
            cin >> old_coin;
        }
    cout << "\t\tEnter the coin ID of new asset:\n\t\t";
    cin >> new_coin;
    while(cin.fail() || new_coin < 1 || new_coin > 10 || old_coin==new_coin)
    {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            format();
            coin_index();
            cout << "\t\t----------------------\n";
            cout << "\t\tEnter a valid coin ID.\n";
            cout << "\t\t----------------------\n\n";
            cout << "\t\tEnter the coin ID of new asset:\n\t\t";
            cin >> new_coin;
    }
    system("CLS");
    format();
    //add_coin(old_coin);
    cout << "\t\tHow many " << coin[old_coin].get_abbrev() << " do you want to swap:\n\t\t";
    cin >> old_amount;
    while(cin.fail() || v[current_user].coins[old_coin-1] < old_amount || old_amount <0)
        {
            cin.clear();
            cin.ignore(INT_MAX,'\n');
            system("CLS");
            format();
            cout << "\t\t----------------------\n";
            cout << "\t\tInvalid Input or Insufficient balance!\n";
            cout << "\t\t----------------------\n\n";
            cout << "\t\tHow many " << coin[old_coin].get_abbrev() << " do you want to swap:\n\t\t";
            cin >> old_amount;
        }
    //add_coin(old_coin);
    double rate_old = coin[old_coin].get_rate();
    //add_coin(new_coin);
    double rate_new = coin[new_coin].get_rate();
    new_amount = (old_amount*rate_old)/(rate_new*1.000001);
    old_coin--;
    new_coin--;
    system("CLS");
    format();
    string user_n = v[current_user].username;
    add_conversion(c,user_n,old_coin,new_coin,old_amount,new_amount);
    v[current_user].coins[old_coin] -= old_amount;
    v[current_user].coins[new_coin] += new_amount;
    cout << "\t\t--------------------------------------\n";
    cout << "\t\tAssets have been successfully swapped.\n";
    cout << "\t\t--------------------------------------\n\t\t";
    char temp = getch();
}
void log_in(vector <user> v ,int &current_user)
{
    system("CLS");
    format();
    string username;
    string pass;
    bool status = false;
    cout << "\t\tEnter you username:\n\t\t";
    getline(cin, username);
    current_user = authenticate(status, username, v);
    while(!status)
    {
        system("CLS");
        format();
        cout << "\t\tNo account exist with such username!\n";
        cout << "\t\tTry again\n";
        cout << "\t\tEnter you username:\n\t\t";
        getline(cin, username);
        current_user = authenticate(status, username, v);
    }
    cout << "\n\t\tEnter your password:\n\t\t";
    getline(cin, pass);
    while(v[current_user].password!=pass)
    {
        system("CLS");
        format();
        cout << "\t\tWrong password!!!!\n";
        cout << "\t\tPress 0 and Enter to Return back.\n";
        cout << "\t\tEnter your password:\n\t\t";
        getline(cin, pass);
        if(pass=="0")
        {
            current_user = -1;
            break;
        }
    }
}
void payment_window(int current_user, vector <user> &v, vector <transfer> &t)
{
    bool Exit = false;
    bool valid = true;
    unsigned int coin_ID, pos=1;
    double amount;
    while(!Exit)
    {
        system("CLS");
        format();
        if(!valid)
        {
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter a valid option.\n";
                cout << "\t\t----------------------\n\n";
        }
        cout << "\t\tPress 1 to pay PDC(Pepsi Dining Centre.\n";
        cout << "\t\tPress 2 to pay Zakir Tikka.\n";
        cout << "\t\tPress 3 to pay Subway.\n";
        cout << "\t\tPress 4 to pay Bunker.\n";
        cout << "\t\tPress 5 to pay Superstore.\n";
        cout << "\t\tPress 6 to pay Khokha store.\n";
        cout << "\t\tPress 0 to Exit.\n\t\t";
        cin >> pos;
        if(pos==0 && !cin.fail())
        {
            Exit = true;
            valid = true;
        }
        else if(pos>0 && pos<=6 && !cin.fail())
        {
            valid = true;
            system("CLS");
            format();
            coin_index();
            cout << "\t\tEnter the coin ID you want to transfer:\n\t\t";
            cin >> coin_ID;
            while(cin.fail() || coin_ID < 1 || coin_ID > 10)
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                system("CLS");
                format();
                coin_index();
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter a valid coin ID.\n";
                cout << "\t\t----------------------\n\n";
                cout << "\t\tEnter the coin ID you want to transfer:\n\t\t";
                cin >> coin_ID;
            }
            coin_ID--;
            system("CLS");
            format();
            cout << "\t\tEnter the amount you want to transfer:\n\t\t";
            cin >> amount;
            while(cin.fail() || amount < 0)
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                system("CLS");
                format();
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter a valid input\n";
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter the amount you want to transfer:\n\t\t";
                cin >> amount;
            }
            while(amount > v[current_user].coins[coin_ID])
            {
                cin.clear();
                cin.ignore(INT_MAX,'\n');
                system("CLS");
                format();
                cout << "\t\t----------------------\n";
                cout << "\t\tYou do not have enough funds.\n";
                cout << "\t\t----------------------\n";
                cout << "\t\tEnter the amount you want to transfer:\n\t\t";
                cin >> amount;
            }
            v[current_user].coins[coin_ID] -= amount;
            v[pos-1].coins[coin_ID] += amount;
            string dummy1 = v[current_user].username;
            string dummy2 = v[pos].username;
            add_transfer(t,dummy1,dummy2,coin_ID,amount);
            cout << "\t\t--------------------------------------\n";
            cout << "\t\tTransaction is Successful!.\n";
            cout << "\t\t--------------------------------------\n\t\t";
            char temp = getch();
        }
        else
        {
            valid = false;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        }
    }
}
void change_pass(int current_user,vector <user> &v)
{
    string input, real, update;
    system("CLS");
    format();
    cout << "\t\t";
    print_asterisk();
    cout << "\t\tEnter you previous password:\n\t\t";
    getline(cin, input);
    real = v[current_user].password;
    while(real!=input && input!="0")
    {
        system("CLS");
        format();
        cout << "\t\t";
        print_asterisk();
        cout << "\t\t!!!!!Wrong Password. Try again!!\n";
        cout << "\t\tor Press 0 to leave.\n\t\t";
        getline(cin, input);
    }
    if(input!="0")
    {
        system("CLS");
        format();
        cout << "\t\tEnter your new password:\n\t\t";
        getline(cin, update);
        while(update.size() <6)
        {
            system("CLS");
            format();
            cout << "\t\tPassword must be at least 6 characters.\n\t\t";
            getline(cin, update);
        }
        if(input!="0")
        {
            v[current_user].password = update;
            cout << "\t\t";
            print_asterisk();
            cout << "\n\t\tPassword changed succesfully.\n\t\t";
            print_asterisk();
            char temp = getch();
        }
    }
}
void main_menu(int current_user,vector <user> &v,vector <transfer> &t, vector <conversion> &c)
{
    char choice;
    bool End = false;
    bool valid  = true;
    system("CLS");
    format();
    while(!End)
    {
        if(!valid)
        {
            cout << "\n\t\t\tEnter a valid choice.\n";
            cout << "\t\t\t*********************\n\t\t";
        }
        cout << "\t\tPress 0 to Exit.\n";
        cout << "\t\tPress 1 to view you assets.\n";
        cout << "\t\tPress 2 to convert assets.\n";
        cout << "\t\tPress 3 to transfer assets.\n";
        cout << "\t\tPress 4 to change you password.\n";
        cout << "\t\tPress 5 to mine coins.\n";
        cout << "\t\tPress 6 to open payment window.\n";
        cout << "\t\tPress 7 to print conversion history.\n";
        cout << "\t\tPress 8 to print transfer history.\n\t\t";
        choice = getch();
        string login_username = v[current_user].username;
        switch (choice)
        {
        case '0' :
            End = true;
            break;
        case '1' :
            valid = true;
            print_wallet(v,current_user);
            break;
        case '2' :
            valid = true;
            conversion_menu(current_user,v,c);
            break;
        case '3' :
            valid = true;
            transfer_menu(current_user,v,t);
            break;
        case '4' :
            valid = true;
            change_pass(current_user,v);
            break;
        case '5' :
            valid = true;
            miner(current_user,v);
            break;
        case '6' :
            valid = true;
            payment_window(current_user,v,t);
            break;
        case '7' :
            valid = true;
            print_conversion_history(c,login_username);
            break;
        case '8' :
            valid = true;
            print_transfer_history(t,login_username);
            break;
        default :
            valid = false;
            break;
        }
        system("CLS");
        format();
    }
}

int main()
{
    bool running = true;
    add_coin();
    thread _update(dynamicUpdate,&running);
    system("Color 0A");
    int current_user; // keeps track of user index
    char choice;
    bool Exit = false;
    bool valid = true;
    vector <user> details;
    vector <transfer> Transfer;
    vector <conversion> Conversion;
    open_file(details,Transfer,Conversion);
    while(!Exit)
    {
        system("CLS");
        format();
        if(!valid)
        {
            cout << "\t\t\t Invalid Input. Try another!\n";
        }
        cout << "\t\tPress 0 to Exit.\n";
        cout << "\t\tPress 1 to Make a new account.\n";
        cout << "\t\tPress 2 to Log In.\n\t\t";
        choice = getch();
        switch (choice)
        {
        case '0' :
            Exit = true;
            valid = true;
            break;
        case '1' :
            add_data(details);
            valid = true;
            break;
        case '2' :
            log_in(details,current_user);
            if(current_user>=0)
            {
                main_menu(current_user,details,Transfer,Conversion);
            }
            valid = true;
            break;
        default:
            valid = false;
            break;
        }
    }
    running = false;
    _update.join();
    save_file(details,Transfer,Conversion);
}
