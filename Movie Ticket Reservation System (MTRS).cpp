//Name: Mathavan A/L Krishnan, Nicole Ha Yah Yie, Ooi Weishan, Sofea Athirah, Lee Chow Wei
//Date: 14/9/2021
//Program Description: MTRS, Movie Ticket Reservation System

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <algorithm>
#include <conio.h>
using namespace std;

int counter, selection_movie;
const int WIDTH = 77, MAXMOVIES = 15;
char name[50], icno[25], email[40], phone_number[25],acc_num[25],password[25],month[25], year[25];

vector<string> movie_name(25);
vector<string> movie_day(25);  //added
vector<string> showtime1(25);
vector<string> showtime2(25);
vector<string> showtime3(25);

class Movie{
    public:
        string name, day, time1, time2, time3;
};

class Customer{
    protected:
        string name, email, phone_number;
    public:
        void setName(){
            cout<< "                  Enter your name : ";
            cin.ignore();
            getline(cin, name);
            cout << endl;
        }

        void setEmail(){
            int valid_email = 0;
            char temp;
            cout << "                  Enter your email address: ";
            cin >> email;
            cout << endl;

            int email_length = email.length();

            for (int i=0; i<email.length(); ++i){
                temp = email.at(i);
                if (temp == '@' ){
                    valid_email = 1;
                }
            }

            while (valid_email != 1){
                cout << "               Enter a valid email address: ";
                cin.ignore();
                cin >> email;
                cout << endl;

                for (int i=0; i<email.length(); ++i){
                  temp = email.at(i);
                  if (temp == '@' ){
                     valid_email = 1;
                  }
                }
            }
        }

        void setPhonenumber(){
            cout << "                  Enter your phone number : ";
            cin >> phone_number;

            int phone_length = phone_number.length();

            while (phone_length != 10){
               cout << endl;
               cout << "                Enter a valid phone number: ";
               cin >> phone_number;
               phone_length = phone_number.length();
            }

            cout << endl;
        }

        string getName(){
            return name;
        }

        string getPhonenumber(){
            return phone_number;
        }

        string getEmail(){
            return email;
        }

        ~Customer(){}; //destructor (dlt the obj)
};

class Member : public Customer {
    protected:
        string icno, acc_num;
        char password[50];
        int valid_month, valid_year;
    public:
         time_t t = time(NULL);  //Source: https://stackoverflow.com/questions/58151350/more-elegant-way-to-get-the-current-year-in-c
         tm* timePtr = localtime(&t);

         void MemberInitialize(string name,string icno,string email, string phone_number, string acc_num, string password, int valid_month, int valid_year)
         {
            this -> name = name;
            this -> email = email;
            this -> phone_number = phone_number;
            this -> icno = icno;
            this -> password[50] = password[50];
            this -> acc_num = acc_num;
            this -> valid_month = valid_month;
            this -> valid_year = valid_year;
         }
         void setIC(){
             int length;
             char name[50],icnum[25],email[40],phone_number[25],acc_num[25],password[25],month[25],year[25];
             bool icFound = 0;
             fstream membership;

             int i = 0;
             do{
                 if(i == 0){
                    cout << "\t\t  Enter your Identification Number(IC) without dash (-) : ";
                    cin >> icno;
                    cout << endl;
                 }
                 else{
                    cout << "\t\t  Enter a valid IC Number: ";
                    cin >> icno;
                    cout << endl;
                 }

                 length = icno.length();

                 membership.open("Membership.txt", ios::in);
                 while(!membership.eof())
                 {
                     membership.getline(name,50,'|');
                     membership.getline(icnum,25,'|');
                     membership.getline(email,40,'|');
                     membership.getline(phone_number,25, '|');
                     membership.getline(acc_num,25, '|');
                     membership.getline(password,25,'|' );
                     membership.getline(month,25,'|' );
                     membership.getline(year, 25);

                     for(int i=0; i<length; i++){
                        if(icno[i] == icnum[i]){
                            icFound = 1;
                        }
                        else{
                            icFound = 0;
                            break;
                        }
                     }
                     if(icFound){
                        break;
                     }
                 }
                 membership.close();
                 i++;
            }while(length != 12 || icFound);
        }
         void setAccNum(){
             srand(time(0));
             int AccNum1 = (rand() % 999999 )+ 100000;
             acc_num = to_string(AccNum1);
        }
         void setPassword(){
            char password_1[50];

            cout << "  ENTER YOUR PASSWORD : ";
            //cin >> password;
            int a = 0;
            while(password[a - 1] != '\r'){
                password[a] = getch();
                if(password[a-1]!='\r'){
                    cout << "*";
                }
                a++;
            }
            password[a-1] = '\0';
            string pw = password;

            cout << "\n  REENTER YOUR PASSWORD :";
            //cin >> password_1;
            a = 0;
            while(password_1[a - 1] != '\r'){
                password_1[a] = getch();
                if(password_1[a-1]!='\r'){
                    cout << "*";
                }
                a++;
            }
            password_1[a-1] = '\0';
            string pw1 = password_1;

            while (pw1 != pw){
                cout << "\n  Your password does not match. Try again !!"
                     << "\n\n  Please enter your password: ";
                a = 0;
                while(password[a - 1] != '\r'){
                    password[a] = getch();
                    if(password[a-1]!='\r'){
                        cout << "*";
                    }
                    a++;
                }
                password[a-1] = '\0';
                pw = password;

                cout << "\n\n  Please reenter your password: ";
                a = 0;
                while(password_1[a - 1] != '\r'){
                    password_1[a] = getch();
                    if(password_1[a-1]!='\r'){
                        cout << "*";
                    }
                    a++;
                }
                password_1[a-1] = '\0';
                pw1 = password_1;
            }
        }
         string getAccNum(){
            return acc_num;
        }
         string getIC(){
            return icno;
         }

         void setMonth(){
            valid_month = timePtr->tm_mon + 1 ;
         }

         void setYear(){
            valid_year = timePtr->tm_year + 1900 + 1;  //give extra one year upon registration for validity
         }

         int getMonth(){
            return valid_month;
         }

         int getYear(){
            return valid_year;
         }

         string getPassword(){
            return password;
         }

        Member (const Member& mb);
        Member (){};
};

class Food {
    private:
        string fname[10];
        float fprice[10];

    public:
        void setFood(string food, float price, int arrElmt){
                fname[arrElmt] = food;
                fprice[arrElmt] = price;
                //cout << food << " " << price;
        }

        void getFoodMenu(int arrSize){
            for(int i=0; i<arrSize; i++){
                cout << "\t\t" << i+1 << ") " << fname[i] << "\t\t\t  " << fprice[i] << endl;
            }
        }

        float getFoodPrice(int arrElmt){
            return fprice[arrElmt];
        }
};

class Drink {
    public:
        string dname[10];
        float dprice[10];

        void setDrink(string drink, float price, int arrElmt){
                dname[arrElmt] = drink;
                dprice[arrElmt] = price;
        }

        string getDrinkMenu(int arrSize){
            for(int i=0; i<arrSize; i++){
                cout << "\t\t" << i+1 << ") " << dname[i] << "\t\t\t " << dprice[i] << endl;
            }
        }

        float getDrinkPrice(int arrElmt){
            return dprice[arrElmt];
        }

};

Member *MemberProg = new Member;
using MOVIE = Movie[MAXMOVIES];

void title();
bool CompareNames(Movie movie1, Movie movie2);
int ReadFile(MOVIE& movies, int& movieCount);
void showmovielist(MOVIE& movies, const int movieCount);
void time_checking(int time[], int i);
void showTicket();
void payment(float pay);
void movie_booking();
void ticket_cancel();
void food_drinks();
void displayMenu();
void member_reg();
void member_info();
void member_renew();
void membership();
void add_movie();
void delete_movie();
void update_movie();
void management();
string member_login();

int main()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    char selection_role;
    system("CLS");
    title();
    cout << "                  The local date and time is: " << dt << endl;
    cout <<
    "                  ========================        ==========================        ======================\n"
    "                  * (A)  MOVIE BOOKING   *        * (B) TICKET CANCELLATION *        * (C) SNACKS & DRINKS *\n"
    "                  ========================        ==========================        ======================\n\n"
    "                  ========================        ==========================        ======================\n"
    "                  * (D)    MEMBERSHIP    *        * (E)     EMPLOYEES      *        * (F)     QUIT       *\n"
    "                  *=======================        ==========================        ======================\n\n";

    do{
        cout << "                                                       SELECT AN OPTION: ";
        cin >> selection_role;
        cin.ignore(10000, '\n');
        selection_role = tolower(selection_role);
        if (selection_role < 'a' || selection_role > 'f')
            cout << "                                         You have entered a wrong selection. Try again.\n\n";
    }while(selection_role < 'a' || selection_role > 'f');


    if (selection_role == 'a'){
       movie_booking();
    }else if (selection_role == 'b'){
        ticket_cancel();
    }else if (selection_role == 'c'){
        food_drinks();
    }else if (selection_role == 'd'){
        membership();
    }else if (selection_role == 'e'){
        management();
    }else{
        exit(1);
    }
}

void title()
{
    const int WIDTH = 88;
    const int WIDTH1 =  18;
    const string heading =  "MOVIE TICKET RESERVATION SYSTEM (MTRS)" ;
    cout << "\n\n ";
         for(int i = 0; i < WIDTH1; i++){
                    cout << ' ';
            }
         for(int i = 0; i < WIDTH; i++){
                cout << '*';
            }
    cout << "\n\n";
    cout << "                                            " << heading;
    cout << "\n\n ";
         for(int i = 0; i < WIDTH1; i++){
                    cout << ' ';
            }
         for(int i = 0; i < WIDTH; i++){
                cout << '*';
            }
    cout << "\n\n";
}

bool CompareNames(Movie movie1, Movie movie2)
{
    if (movie2.name > movie1.name)
        return true;  // <--- Means to swap.
        return false;  // <--- Means do nothing.
}

int ReadFile(MOVIE& movies, int& movieCount)
{

    string file_name = "Movies.txt";  // <--- Put File name here.
    int i=0; //added
    ifstream movies_file(file_name);

    if (!movies_file){
        cout << "\n File " << "\"" << file_name << "\"" << " did not open." << endl;
    }

    while (getline(movies_file, movies[i].name, '|')){
        getline(movies_file, movies[i].day, '|');
        getline(movies_file, movies[i].time1, '|');
        getline(movies_file, movies[i].time2, '|');
        getline(movies_file, movies[i].time3);
        movies_file.clear();

        i++;
    }

    movieCount = i + 1;  //added
}

void showmovielist(MOVIE& movies, const int movieCount)
{
    system("CLS");
    ifstream movie("Movies.txt");
    title();
    cout << "\n ";
    for(int i = 0; i < WIDTH; i++){
                    cout << '=';
            }
    cout << endl
         << "| SERIAL |";
           for(int i = 0; i < 55; i++){
                    cout << '=';
           }
    cout << "|  SHOWTIME  | " << '\n'
         << "| NUMBER |                 MOVIE NAME                    |  DAY  |  AVAILABLE | " << '\n'
         << ' ';
    for(int i = 0; i < WIDTH; i++){
                cout << '=';
        }
    cout << endl;

    int j = 1;
    int i = 1;

    sort(movies, movies + movieCount, CompareNames);

    int m;
    for (m = 1; m < movieCount; m++)
    {
        if (movies[m+1].name == movies[m].name)
        {
            cout <<
                "   (" << m << ")     " <<
                std::left << setw(40) <<
                setw(45)<< movies[m].name << "    " <<
                setw(7) << movies[m].day <<
                "(" << j << ") " <<
                movies[m].time1 << "\n" <<
                setw(68) << "                                                                   ("<< j + 1 << ") " <<
                movies[m].time2 << "\n" <<
                setw(67) << "                                                                   ("<< j + 2 << ") " <<
                movies[m].time3 << "\n";
        }

        else{
                cout <<
                    "   (" << m <<  ")     " << std::left << setw(40) <<
                    setw(45) << movies[m].name << "    " <<
                    setw(7) << movies[m].day <<
                    "("<<j<<") " <<
                    movies[m].time1 << "\n" <<
                    setw(68) << "                                                                   ("<<j + 1<<") " <<
                    movies[m].time2 << "\n" <<
                    setw(68) << "                                                                   ("<<j + 2<<") " <<
                    movies[m].time3 << "\n";

                cout << ' ' ;
                for(int i = 0; i < WIDTH; i++){
                        cout << '=';
                }
                cout << endl;
        }

         movie_name[i] = movies[m].name;
         movie_day[i] = movies[m].day;   //added
         showtime1[i] = movies[m].time1;
         showtime2[i] = movies[m].time2;
         showtime3[i] = movies[m].time3;
         i = i + 1;
         j = 1;
    }

     counter = m;
}

void time_checking(int time[], int i)
{
    while(!cin >> time[i])
    {
        cout << endl;
        cout << " Enter a valid time: " ;
        cin.clear();
        cin.ignore(25,'\n');
        cin >> time[i];
    }

    while((time[i] > 2400) || (time[i] < 0))
    {
        cout << endl;
        cout << " You have entered a wrong time for movie. Enter again!!"<< endl;
        cout << " Enter the time for " << i << " show  (HHMM): ";
        cin >> time[i];
    }
}

void showTicket(){

    int ticket_num;

    ticket_num = rand() % 9999999999 + 10000000000;
    cout << endl << "        --------------------------------------" << endl;
    cout << "        |              " << ticket_num << "             |" << endl;
    cout << "        --------------------------------------" << endl << endl;
    cout << " This is your ticket number !!! " << endl;
    cout << " Thank you !!!" << endl;
}

void payment(float pay)
{
    char resp;
    string card_type, card_num, ccv;
    cout << " Select the payment method: " << endl;
    cout << "                 (A) CASH  " << endl;
    cout << "                 (B) DEBIT CARD " << endl;
    cout << "                 (C) CREDIT CARD " << endl << endl;
    cout << " Your option [A, B, C] :  ";
    cin >> resp;
    while((resp != 'A') && (resp != 'a') && (resp != 'B') && (resp != 'b') && (resp != 'C') && (resp != 'c') )
    {
        cout << " Please select a correct option [ a, b, c] : ";
        cin >> resp;
    }

    system("ClS");
    title();
    if (resp == 'A' || resp == 'a'){
        cout << " You have selected to pay on cash" << endl;
        cout << " The amount you need to pay is : RM " << pay << endl << endl;
    }

    else {
        if(resp == 'B' || resp == 'b'){
            card_type = "debit card";
        }
        else{
        card_type = "credit card";
        }

        cout << "You have selected " << card_type << " to pay !!" << endl << endl;
        cout << "The amount you need to pay is : RM " << pay << endl << endl;
        cout << "Enter your " << card_type << " number: " ;
        cin >> card_num;
        cout << "\n Enter your CCV : " ;
        cin >> ccv;
    }

}

void member_reg(){
    fstream member;
    member.open("Membership.txt",ios::app);
    int acc_num;
    char resp, r;
    Member * m1 = new Member;

    system("CLS");
        title();
        cout << "\t\t\t\WELCOME TO THIS CINEMA !!\t\t\t\n\n"
                "\t\t\tWe are glad on your interest to be a part of our family\t\t\n\n\n";
    m1 -> setName();
    m1 -> setPhonenumber();
    m1 -> setIC();
    m1 -> setEmail();
    m1 -> setMonth();
    m1 -> setYear();

    details:
    system("CLS");
    title();
    cout << "\n\t-------------------------------------------------------------------------------------------------\n\n" <<
         setw(30)<< "\tHello Mr/MS , " << endl << endl <<

         setw(50)<< "Your Name is : " << m1 -> getName() << endl << endl <<
         setw(50)<< "Your IC is : " << m1 -> getIC() << endl << endl <<
         setw(50)<< "Your Phone Number is : " << m1 -> getPhonenumber() << endl << endl <<
         setw(50)<< "Your Email is : " << m1 -> getEmail() << endl << endl
         << "\t --------------------------------------------------------------------------------------------------\n\n"
         << "\t\t\tWOULD YOU LIKE TO CONFIRM YOUR DETAILS [Y/N] : ";
    cin >> resp;
    resp = tolower(resp);

    while ((resp != 'y') && (resp != 'n') ){
            cout << "\nEnter a valid response: ";
            cin >> resp;
        }

    if (resp == 'n'){
    system("CLS");
        title();
        cout << "\n\t\tWHICH DATA YOU WOULD LIKE TO CHANGE :\t\t\n\n"
             << "\t\t\t(A) NAME\n\n"
             << "\t\t\t(B) IDENTIFICATION NUMBER\n\n"
             << "\t\t\t(C) EMAIL ADDRESS\t\n\n"
             << "\t\t\t(D) PHONE NUMBER\t\n\n"
             << "\t\t\tEnter your response:\t" ;
        cin >> resp;
        resp = tolower(resp);

        while ((resp != 'a') &&  (resp != 'b') && (resp != 'c') && (resp != 'd') ){
              cout << "\nEnter a valid response: ";
              cin >> resp;
        }
        cout << endl << endl;
        if (resp == 'a'){
                m1 -> setName();
                goto details;
            }
        else if (resp == 'b'){
            m1 -> setIC();
            goto details;
        }
        else if (resp == 'c'){
            m1 -> setEmail();
            goto details;
        }
        else{
            m1 -> setPhonenumber();
            goto details;
        }
    }

    else{
        system("CLS");
        title();
        cout << endl;
        m1 -> setAccNum();

        cout <<setw(80)<< "\t\t--------------------------------------\t\t";
        cout << "\n\t\t      Your Account Number is : |\t\t" << m1 -> getAccNum() << setw(18)<<"|\n";
        cout <<setw(80)<< "\t\t--------------------------------------\n\n";
        cout << "  You are required to set a password for your account: \n\n";

        m1 ->setPassword();

        cout << endl << endl;
        cout << "\t\t\tYou are done with your account registration !!\n"
             << "\t\t\tNO FEES FOR NEW MEMBERS \n"
             << "\t\t\tOne point will be given for each ringgit in purchase\n"
             << "\t\t\tThere are alot of exciting rewards that you can claim using the points\n";

      member << m1 ->getName() << '|' << m1->getIC() << '|' << m1->getEmail() << '|' << m1->getPhonenumber() <<  '|' << m1->getAccNum() <<  '|'
             << m1 ->getPassword() << '|' << m1-> getMonth () << '|' << m1-> getYear() << '\n';
      member.close();
    }

    cout << "\nIf you wish continue to go back to the main menu please press 'b' :";
    cin >> r;
    r = tolower(r);

    while (r != 'b'){
         cout << "Please enter the correct input: ";
         cin >> r;
        r = tolower(r);
   }

   main();
}

void member_renew()
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);
    fstream member, temp;
    int count = 0 , extend, pay_amount, acc_renew, current_year, i,  y = 0, year_int, month_int;
    char resp;
    string account_num, line;

    system("CLS");

    account_num = member_login();
    system("CLS");
    title();
    cout << endl << endl;
    cout << " Hello " << MemberProg ->getName() << " ,\n\n"
         << " Your account is valid until " << MemberProg->getMonth() << " - " << MemberProg->getYear() << endl << endl;

    if ((MemberProg->getYear() <= current_year) && ((MemberProg->getMonth()) < (timePtr->tm_mon + 1))){
        cout << " YOUR ACCOUNT HAS EXPIRED !!!\n\n" ;
    }

    cout << " Select an option to extend your membership :- \n\n"
         << "\t\t---------------\t\t----------------\t---------------\n"
         << "\t\t/ (a) 1 years  /\t/  (b) 3 years  /\t/ (c) 5 years  /\n"
         << "\t\t---------------\t\t----------------\t----------------\n\n";

    checking:
    cout << " Your selection [ A, B, C ] = ";
    cin >> resp;
    resp = tolower(resp);

    while((resp != 'a') && (resp != 'b') && (resp != 'c')){
        cout << " Please select a correct option [ a, b, c] : ";
        cin >> resp;
    }

    if (resp == 'a'){
        extend = 1;
    }else if (resp == 'b'){
        extend = 3;
    }
    else{
        extend = 5;
    }

    cout << endl;
    cout << " You have selected " << extend << " years to extend your membership !!!\n" ;

    member.open("Membership.txt",ios::in);
    while (!member.eof()){
        getline(member, line);
        count++;
    }
    member.close();

    cout << "\n Do you want to change the years to be extended [Y/N]: ";
    cin >> resp;
    resp = tolower(resp);

    if (resp == 'y'){
        goto checking;
    }

    member.open("Membership.txt",ios::in);
    temp.open("temp.txt",ios::out);

    count = count - 2;
    while(y <= count){
        member.getline(name,25,'|');
        member.getline(icno,25,'|');
        member.getline(email,40,'|');
        member.getline(phone_number,25, '|');
        member.getline(acc_num,25, '|');
        member.getline(password,25,'|' );
        member.getline(month,25,'|' );
        member.getline(year, 25);

        sscanf(year, "%d", &year_int);
        sscanf(month, "%d", &month_int);
        if (acc_num == account_num){
            if (((month_int) < (timePtr->tm_mon + 1)) && (year_int <= current_year)){
                temp << name << '|' << icno << '|' << email << '|' << phone_number <<  '|' << acc_num <<  '|' << password << '|' << timePtr->tm_mon + 1 << '|' << (current_year + extend) << '\n';
            }
            else if((year_int >= current_year) && (month_int >= (timePtr->tm_mon + 1))){
                temp << name << '|' << icno << '|' << email << '|' << phone_number <<  '|' << acc_num <<  '|' << password << '|' << month << '|' << (year_int + extend) << '\n';
            }
        }

        else{
            temp << name << '|' << icno << '|' << email << '|' << phone_number <<  '|' << acc_num <<  '|' << password << '|' << month << '|' << year << '\n';
        }

        y++;
    }
    member.close();
    temp.close();

    if (extend == 1){
        pay_amount = 10;
    }else if(extend == 3){
        pay_amount = 20;
    }else if(extend == 5){
        pay_amount = 30;
    }

    system("CLS");
    title();
    payment(pay_amount);
    temp.open("temp.txt",ios::in);
    member.open("Membership.txt",ios::out);

    y = 0;
    while(y <= count){
        temp.getline(name,25,'|');
        temp.getline(icno,25,'|');
        temp.getline(email,40,'|');
        temp.getline(phone_number,25, '|');
        temp.getline(acc_num,25, '|');
        temp.getline(password,25,'|' );
        temp.getline(month,25,'|' );
        temp.getline(year,25);
        member << name << '|' << icno << '|' << email << '|' << phone_number <<  '|' << acc_num <<  '|' << password << '|' << month << '|' << year << '\n';
        y++;
    }

    member.close();
    temp.close();
    remove ("temp.txt");
    cout << " You are done our beloved customer !!!";
    cout << "\nIf you wish continue to go back to the main menu please press 'b' :";
    cin >> resp;
    resp = tolower(resp);

   while (resp != 'b'){
         cout << "Please enter the correct input: ";
         cin >> resp;
        resp = tolower(resp);
   }

   main();
}

void member_info(){
    system("CLS");

    char r;
    fstream member;
    member.open("Membership.txt", ios::in);
    string account_number,acc_num1;
    account_number = member_login();

    while(!member.eof())
    {
        member.getline(name,50,'|');
        member.getline(icno,25,'|');
        member.getline(email,40,'|');
        member.getline(phone_number,25, '|');
        member.getline(acc_num,25, '|');
        member.getline(password,25,'|' );
        member.getline(month,25,'|' );
        member.getline(year,25);

        acc_num1 = acc_num;
        if (acc_num1 == account_number){
            break;
        }
    }

    system("CLS");
    title();
    cout << "\n\n";
    cout << "\t\t\t\t=========================================================\n"
         << "\t\t\t\t=                  MEMBER INFORMATION                   =\n"
         << "\t\t\t\t=========================================================\n"
         << "\n\t\t\t\tAccount Number : " << acc_num
         << "\n\t\t\t\tName           : " << name
         << "\n\t\t\t\tPhone no.      : " << phone_number
         << "\n\t\t\t\tE-mail         : " << email
         << "\n\t\t\t\tIC Number      : " << icno
         << "\n\t\t\t\tValid month    : " << month
         << "\n\t\t\t\tValid year     : " << year
         << "\n\t\t\t\t---------------------------------------------------------" << endl;

    cout << "\nIf you wish continue to go back to the main menu please press 'b' :";
    cin >> r;
    r = tolower(r);

   while (r != 'b'){
         cout << "Please enter the correct input: ";
         cin >> r;
        r = tolower(r);
   }

   main();
}

void membership()
{
    char resp;
    system("CLS");
    title();
    cout << "\n\t\t========================\t==========================\t==========================\t\t\n"
         << "\t\t* (A) NEW MEMBER  *\t\t*(B) RENEW MEMBERSHIP *\t\t*(C) MEMBER INFORMATION *\t\n"
         << "\t\t========================\t==========================\t==========================\n\n"
         << "\t\t\t\t\t\t\t Input :" ;
    cin >> resp;
    resp = tolower(resp);

    while ((resp != 'a') && (resp != 'b') && (resp != 'c'))
    {
        cout << "\nEnter a valid response: ";
        cin >> resp;
    }

    if (resp == 'a'){
        system("CLS");
        member_reg();
    }else if (resp == 'b'){
        system("CLS");
        member_renew();
    }else{
        member_info();
    }
}

void displayMenu()
{
	Food *pfood = new Food;
    Drink *pdrink = new Drink;

    int lines;
	char foodname[25], foodprice[25], drinkname[25], drinkprice[25], r;
	string fname_string, dname_string;
	float fprice_float, dprice_float;

	foodmenu:
	fstream food, drink;
	food.open("Food.txt", ios::in);
    drink.open("Drink.txt", ios::in);

	if (!food || !drink)
    {
		cout << "Cannot open input files\n";
		return;
    }

	cout << setw(57) << setfill('-') << '\n';
	cout << "|                  SNACKS AND DRINKS                   | \n";
	cout << setw(57) << setfill('-') << '\n';
	cout << "|              SNACKS AVAILABLE                | PRICE | \n";
	cout << setw(57) << setfill('-') << '\n';

	char count = '0';
    string line;

    ifstream file("Food.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48 ;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);


    int i = 0;
    while(i < lines){
        food.getline(foodname,25,'|');
        food.getline(foodprice,25);
        fname_string = foodname;
        sscanf(foodprice, "%f", &fprice_float);

        pfood ->setFood(fname_string, fprice_float, i);
        i++;
    }

    pfood -> getFoodMenu(lines);

    cout << setw(57) << setfill('-') << '\n';
	cout << "|              DRINKS AVAILABLE                | PRICE | \n";
	cout << setw(57) << setfill('-') << '\n';

	int j = 0;
	while(j< lines){
        drink.getline(drinkname,25,'|');
        drink.getline(drinkprice,25);
        dname_string = drinkname;
        sscanf(drinkprice, "%f", &dprice_float);

        pdrink ->setDrink(dname_string, dprice_float, j);
        j++;
    }

    pdrink -> getDrinkMenu(lines);

    char fod; //food or drink
    int fchoice, fqty, dchoice, dqty;
    float fprice, dprice, pay;

    cout << "\nDo you want to buy Food OR Drink? [f/d]: ";
    cin >> fod;
    fod = tolower(fod);

    while(fod!='f'&&fod!='d'){
        cout << "\nWrong input. Please  enter again. \nDo you want to buy Food OR Drink? [f/d]: ";
        cin >> fod;
    }

    if(fod=='f'){
        cout << "\nYou want to buy Food. Which Food do you want to buy? : ";
        while (!(cin >> fchoice) || fchoice > lines || fchoice < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout<<endl;
        cout << "Enter its quantity that you want to buy: ";
        while(!(cin >> fqty) || fqty < 1){
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        fprice = pfood -> getFoodPrice(fchoice-1);
        pay = fqty*fprice;

    } else {
        cout << "\nYou want to buy Drink. Which Drink do you want to buy? : ";
        while (!(cin >> dchoice) || dchoice > lines || dchoice < 1)
        {
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout<<endl;
        cout << "Enter its quantity that you want to buy: ";
        while(!(cin >> dqty) || dqty < 1){
            cout << "Enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        dprice = pdrink -> getDrinkPrice(dchoice-1);
        pay = dqty*dprice;

    }

    cout << "\nWould you wish to [B]ack, [P]roceed or [R]eselect? :";
    cin >> r;
    r = tolower(r);

    while ( r != 'b' && r != 'p' && r != 'r')
        {
            cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
            cout << "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
            cin >> r;
        }

    if (r != 'b'){
        if (r != 'p'){
              fchoice = 0;
              fqty = 0;
              dchoice = 0;
              dqty = 0;
              system("CLS");
              goto foodmenu;
        }else{
              payment(pay);
              showTicket();
        }
    }
    else{
              fchoice = 0;
              fqty = 0;
              dchoice = 0;
              dqty = 0;
              system("CLS");
              main();
    }
    cout << endl;

}

void food_drinks()
{
    char r;

    system("CLS");
    title();
    displayMenu();

    cout << "\nPress 'b' or 'B' to return to the main menu:";
    cin >> r;
    r = tolower(r);

    while ( r != 'b')
    {
        cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
        cout << "\nPress 'b' or 'B' to return to the main menu:";
        cin >> r;
    }

    system("CLS");
    main();

    cout << endl;
}

void movie_booking()
{
	Customer* c1 = new Customer;
	fstream movie;
	movie.open("Movies.txt", ios::in);
	string showtime;
	int seat_price, lines, select_movie, selection_show;
	char response, r, r2, pay_res, reuse_response, seat_type, temp, seat_row[10], seat_column[10], response1;
	float remaining = 0, cash = 0;
	srand(time(0)); //getting random no.
	int ticket_num; //min val = 10k, value = 10k - 99999

login:
    ticket_num = (rand() % 99999) + 10000;
	system("CLS");
	title();
	cout << "\n\t\t\t*************************\n"
		<< "\t\t\t*    (A) MEMBER LOGIN   * \n"
		<< "\t\t\t************************* \n\n\n"
		<< "\t\t\t************************* \n"
		<< "\t\t\t*    (B) GUEST LOGIN    * \n"
		<< "\t\t\t************************* \n\n\n";

    cout << "\t\t\tSELECT AN OPTION: ";
    cin >> response;
    response = tolower(response);

	while(response != 'a' && response != 'b')
	{
		cout << "\t\t\tYou have entered a wrong selection. Try again: ";
		cin.ignore(10000, '\n');
		cin >> response;
		response = tolower(response);
	}

	if (response == 'a') {
		system("CLS");
		string acc_num = member_login();
		c1 = MemberProg;
	}

	else
	{
		system("CLS");
		title();

		c1->setName();
		c1->setEmail();
		c1->setPhonenumber();
	}

movies:
	int movieCount{}, readStatus{};
	MOVIE movies;
	if (readStatus = ReadFile(movies, movieCount))
		showmovielist(movies, movieCount);
	cout << endl << endl;
	int p = sizeof(movie_name) / sizeof(movie_name[0]);

	cout << " Please select a movie [1,2,3....]: ";
	cin >> select_movie;
	cout << endl;

	while ((!cin >> select_movie) || (select_movie > counter - 1) || (select_movie < 1)) {
		cout << " TRY AGAIN [1,2,3....]: ";
		cin.clear();
		cin.ignore(25, '\n');
		cin >> select_movie;
	}


	cout << "============== You have selected " << movie_name[select_movie] << ".=====================\n"
		<< "\nWhich show you want to select for [SHOW(1) / SHOW(2) / SHOW(3)]: ";
	cin >> selection_show;

	while ((!cin >> selection_show) || (selection_show > 3) || (selection_show < 1)) {
		cout << " TRY AGAIN [1,2,3....]: ";
		cin.clear();
		cin.ignore(25, '\n');
		cin >> selection_show;
	}

	if (selection_show == 1) {
		cout << "============== You have selected " << showtime1[select_movie] << ".=====================" << endl;
		showtime = showtime1[select_movie];
	}
	else if (selection_show == 2) {
		cout << "============== You have selected " << showtime2[select_movie] << ".=====================" << endl;
		showtime = showtime2[select_movie];
	}
	else {
		cout << "============== You have selected " << showtime3[select_movie] << ".=====================" << endl;
		showtime = showtime3[select_movie];
	}


	cout << "\nWould you wish to [B]ack, [P]roceed or [R]eselect? :";
	cin >> r;
	r = tolower(r);

	while (r != 'b' && r != 'p' && r != 'r')
	{
		cout << "\nSorry! You have entered a wrong selection. Please try again.\n\n";
		cout << "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
		cin >> r;
	}

	if (r != 'b') {
		if (r != 'p') {
			int i = 0;
			select_movie = 0;
			selection_show = i;
			system("CLS");
			goto movies;
		}
		else {
			system("CLS");
			goto seats;
		}
	}
	else {
		int i = 0;
		selection_show = i;
		system("CLS");
		goto movies;
	}
	cout << endl;

seats:
	system("CLS");
	title();
	cout << "\t\t    ____________________________________________________________________________________\n"
		<< "\t\t\t\t\t\t           SCREEN\n"
		<< "\t\t    ____________________________________________________________________________________\n\n\n"
		<< "\t\t    [A,1]          [A,2]          [A,3]          [A,4]          [A,5]          [A,6]\n\n"
		<< "\t\t    [B,1]          [B,2]          [B,3]          [B,4]          [B,5]          [B,6]\n\n"
		<< "\t\t    [C,1]          [C,2]          [C,3]          [C,4]          [C,5]          [C,6]\n\n"
		<< "\t\t    [D,1]          [D,2]          [D,3]          [D,4]          [D,5]          [D,6]\n\n"
		<< "\t\t    [E,1]          [E,2]          [E,3]          [E,4]          [E,5]          [E,6]\n\n\n\n";

	int seat_no = 0;
	cout << "Enter the number of seats you want to book [Maximum : 10 seats] : ";
	cin >> seat_no;

    while ((!cin >> seat_no) || (seat_no > 10) || (seat_no < 1)) {  // added
        cout << "\nError: Invalid seat numbers";
        cout << "\nEnter the number of seats you want to book: ";
        cin.clear();
        cin.ignore();
        cin >> seat_no;
	}

	bool check = false;
	for (int i = 0; i < seat_no ; i++) {

		cout << "\nEnter the row of seat you would like to book for [ROW : A,B,C...]: ";
		cin >> seat_row[i];
		seat_row[i] = tolower(seat_row[i]);

		while (seat_row[i] != 'a' && seat_row[i] != 'b' && seat_row[i] != 'c' && seat_row[i] != 'd' && seat_row[i] != 'e') {
			cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
				<< "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
			cin >> seat_row[i];
		}

		cout << "\nEnter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
		cin >> seat_column[i];

		while (seat_column[i] < '1' || seat_column[i] > '6')
		{
			cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
				<< "Enter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
			cin >> seat_column[i];
		}
		for (int j = 0; j < i; j++)
		{
			if (seat_row[j] == seat_row[i] && seat_column[j] == seat_column[i]) {
				check = true;
			}
			else
			{
				check = false;
			}
		}
		while (check)
		{
			cout << "Sorry, this seat has already been chosen.\n";
			cout << "Choose another seat again\n";

			cout << "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
			cin >> seat_row[i];
			seat_row[i] = tolower(seat_row[i]);

			while (seat_row[i] != 'a' && seat_row[i] != 'b' && seat_row[i] != 'c' && seat_row[i] != 'd' && seat_row[i] != 'e') {
				cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
					<< "Enter the row of seat you would like to book for [ROW : A,B,C...]: ";
				cin >> seat_row[i];
			}

			cout << "\nEnter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
			cin >> seat_column[i];

			while (seat_column[i] < '1' || seat_column[i] > '6')
			{
				cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
					<< "Enter the column of seat you would like to book for [COLUMN : 1,2,3...]:  ";
				cin >> seat_column[i];
			}

			for (int j = 0; j < i; j++)
			{
				if (seat_row[j] == seat_row[i] && seat_column[j] == seat_column[i]) {
					check = true;
				}
				else {
					check = false;
				}
			}
		}

	}

	cout << "\nYour selection of seat(s) is : ";
	for (int i = 0; i < seat_no; i++) {
		cout << "(" << seat_row[i] << "," << seat_column[i] << ")";
		// The comma will not be print out after last seat
		if(i < (seat_no-1)){
            cout << ", ";
        }
	}


	cout << "\nThere are two types of seats available:  (A) DELUXE (RM 18) \n"
		<< "\t\t\t\t\t (B) NORMAL (RM 13)\n\n\n"
		<< "Do you want further explanation about the type of seats available in our cinemas before selecting it? (Y/N) :";
	cin >> response1;
	response1 = tolower(response1);

	while (response1 != 'y' && response1 != 'n')
	{
		cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
			<< "Do you want further explanation about the type of seats available in our cinemas before selecting it? (Y/N) :";
		cin >> response1;
	}

	if (response1 == 'y' || response1 == 'Y') {
		cout << "\n- 'DELUXE' seats provides a unique experience to the customers where they will be provided with food during the showtime.";
		cout << "\n- 'NORMAL' seats does not include the special privileges.\n";
	}

    cout << endl;
	cout << "Please select the type of seat (A/B): ";
	cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	cin >> seat_type;
	seat_type = tolower(seat_type);

	while (seat_type != 'a' && seat_type != 'b')
	{
		cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
			<< "Please select the type of seat (A/B): ";
		cin >> seat_type;
	}

	if (seat_type == 'a')
		seat_price = 18.00 * seat_no;

	else
		seat_price = 13.00 * seat_no;

	cout << "Would you wish to [B]ack, [P]roceed or [R]eselect?\n";
	cin >> r2;

	while (r2 != 'b' && r2 != 'p' && r2 != 'r')
	{
		cout << "Sorry! You have entered a wrong selection. Please try again.\n\n"
			<< "Would you wish to [B]ack, [P]roceed or [R]eselect? :";
		cin >> r2;
	}

	if ((r2 != 'b'))
		if ((r2 != 'p')) {
			char seat_row = 0, seat_column = 0, response = 0, seat_type = 0;
			int i = 0;
			selection_show = i;
			system("CLS");
			goto seats;
		}
		else {
			system("CLS");
			goto receipt;
		}
	else {
		char seat_row = 0, seat_column = 0, response = 0, seat_type = 0;
		system("CLS");
		goto movies;
	}
	cout << endl;

receipt:
	system("CLS");
	cout << "=========================================================\n"
		<< "=                         RECEIPT                       =\n"
		<< "---------------------------------------------------------\n"
		<< "=                       MOVIE TICKET                    =\n"
		<< "=========================================================\n\n"
		<< "\nTicket No. : " << ticket_num << endl
		<< "\nTo Mr/Ms " << c1->getName() << ",\n"
		<< "\nYou have booked " << movie_name[select_movie] << " at " << showtime << ", " << movie_day[select_movie];

	cout << "\nYour selection of seat(s) is : ";
	for (int i = 0; i < seat_no; i++) {
		cout << "(" << seat_row[i] << "," << seat_column[i] << ")";
		// The comma will not be print out after last seat
		if(i < (seat_no-1)){
            cout << ", ";
        }
	}


	cout << "\nPrice of seat(s) : " << "RM " << seat_price << endl << endl;
	cout << "---------------------------------------------------------" << endl
		<< left << setw(15) << "\nAmount to PAY : RM " << seat_price << endl;

	payment(seat_price);

	fstream booking;
	booking.open("Booking.txt", ios::app);


	booking << ticket_num << '|' << c1->getName() << '|' << c1->getPhonenumber() << '|' << c1->getEmail() << '|';
	booking << movie_name[select_movie] << '|' << movie_day[select_movie] << '|' << showtime << '|' << seat_type << '|';

	for (int i = 0; i < seat_no; i++) {
		booking << '(' << seat_row[i] << ',' << seat_column[i] << ')';
	}
	booking << '\n';



	cout << endl << endl;
	movie.close();

	cout << "\nDo you wish to use it again, [Y]es or [N]o ?\n";
	cout << "\nResponse : ";
	cin >> reuse_response;
	reuse_response = tolower(reuse_response);

	while (reuse_response != 'y' && reuse_response != 'n')
	{
		cout << "\nWrong selection. Enter Again !!"
			<< "\nResponse : ";
		cin >> reuse_response;
	}
	booking.close();
	if (reuse_response == 'n') {
		delete c1;
		char seat_row = 0, seat_column = 0, response = 0, seat_type = 0, MTRS_response = 0;
		system("CLS");
		main();
	}else

	{
	     goto login;
	}
}

void add_movie()
{
    system("CLS");
    char name [25], day[25];
    int time[3] = {}, i = 0;
    fstream movie;
    movie.open("Movies.txt",ios::app);

    title();
    cout << "Adding new movie!!" << endl << endl;

    cin.ignore();
    cout << " Enter the movie name: ";
    cin.getline(name,25);
    cout<<endl;
    cout << " Enter the day of the showtime: ";
    cin.getline(day,25);
    cout<<endl;
    cout << " Enter the time for First show  (HHMM): ";
    cin >> time[0];
    cout<<endl;
    time_checking(time, i);
    i = 1;

    cout << " Enter the time for Second show (HHMM): ";
    cin >> time[1];
    cout<<endl;
    time_checking(time, i);
    i = 2;

    cout << " Enter the time for Third show  (HHMM): ";
    cin >> time[2];
    cout<<endl;
    time_checking(time, i);

    movie << name << '|'  << day << '|' << std::setfill('0') << std::setw(4) << time[0] << '|' << std::setfill('0') << std::setw(4) << time[1] << '|'  << std::setfill('0') << std::setw(4) << time[2] << '\n';
    cout << endl;
    cout << "You are done, Manager!";
    movie.close();
}

void delete_movie(){
    fstream movie, temp;
    int lines, select_movie;
    char day[25], name[25], time1[25], time2[25], time3[25];
    movie.open("Movies.txt",ios::in);
    temp.open("temp.txt",ios::out);

    int movieCount{}, readStatus{};
    MOVIE movies;
    if (readStatus = ReadFile(movies, movieCount))
    showmovielist(movies, movieCount);

    char count = '0';
    string line;

    ifstream file("Movies.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48 ;

	cout << " Please select a movie [1,2,3....]: ";
	cin >> select_movie;
	cout << endl;

	while ((select_movie > counter - 1) || (select_movie < 1) || (!cin >> select_movie)) {
		cout << " TRY AGAIN [1,2,3....]: ";
		cin.clear();
		cin.ignore(25, '\n');
		cin >> select_movie;
	}

	cout << "============== You have selected to delete " << movie_name[select_movie] << " (" << movie_day[select_movie] << ") " << "=====================\n";

    int i = 0;

    for(int i = 0; i < lines ; i++)
    {
        movie.getline(name,25,'|');
        movie.getline(day,25,'|');
        movie.getline(time1,25,'|');
        movie.getline(time2,25,'|');
        movie.getline(time3,25);

        if (name == movie_name[select_movie] && day == movie_day[select_movie] && time1 == showtime1[select_movie] && time2 == showtime2[select_movie] && time3 == showtime3[select_movie])  //added
        {
            continue;
        }

        else{
             temp << name << '|' << day << '|'  << time1 << '|' << time2 << '|' << time3 <<'\n';
        }
    }

    temp.close();
    movie.close();
    movie.open("Movies.txt",ios::out);
    temp.open("temp.txt",ios::in);

    for (int y =0; y < (lines - 2); y++){
        temp.getline(name,25,'|');
        temp.getline(day,25,'|');
        temp.getline(time1,25,'|');
        temp.getline(time2,25,'|');
        temp.getline(time3,25);
        movie << name << '|' << day << '|'  << time1 << '|'  << time2 << '|' <<  time3 << '\n';
    }

    temp.close();
    movie.close();

    cout << "\n You have done deleting the showtime manager!!! \n";
    remove("temp.txt");
}

void update_movie(){
    fstream movie, temp;
    int lines;
    char selection_movie1, name [25], day[25], time1[25], time2[25], time3[25];
    int select_movie;

    movie.open("Movies.txt",ios::in);
    temp.open("temp.txt",ios::out);
    int movieCount{}, readStatus{};
    MOVIE movies;
    if (readStatus = ReadFile(movies, movieCount))
    showmovielist(movies, movieCount);
    cin.ignore();
    cout << endl;
    //cout << "Enter the serial number of the movie that you want to update [1,2,3...]: ";
    //cin >> selection_movie1;

    char count = '0';
    string line;

    ifstream file("Movies.txt");
    while (!file.eof())
    {
        getline(file, line);
        count++;
    }

    lines = count - 48;

    int p = sizeof(movie_name) / sizeof(movie_name[0]);

	cout << " Please select a movie [1,2,3....]: ";
	cin >> select_movie;
	cout << endl;

	while (!cin >> select_movie) {
		cout << " TRY AGAIN [1,2,3....]: ";
		cin.clear();
		cin.ignore(25, '\n');
		cin >> select_movie;
	}

	while ((select_movie > counter - 1) || (select_movie < 1)) {
		cout << " TRY AGAIN [1,2,3....]: ";
		cin >> select_movie;
	}

	cout << "============== You have selected to update " << movie_name[select_movie] << " (" << movie_day[select_movie] << ") " << "=====================\n";
    cout << endl;

    for (int i=0; i <= lines; i++ )
    {
        movie.getline(name,25,'|');
        movie.getline(day,25,'|');
        movie.getline(time1,25,'|');
        movie.getline(time2,25,'|');
        movie.getline(time3,25);

        if (name == movie_name[select_movie] && day == movie_day[select_movie] && time1 == showtime1[select_movie] && time2 == showtime2[select_movie] && time3 == showtime3[select_movie])  //added
        {
            cout << "Enter the day of the showtime: ";
            cin.ignore();
            string day1;
            cin >> day1;

            int time[3] = {}, x = 0;
            cout << " \nEnter the time for First show  (HHMM): ";
            cin >> time[0];
            time_checking(time, x);
            x = 1;

            cout << " \nEnter the time for Second show (HHMM): ";
            cin >> time[1];
            time_checking(time, x);
            x = 2;

            cout << " \nEnter the time for Third show  (HHMM): ";
            cin >> time[2];
            time_checking(time, x);
            temp << name << '|' << day1 << '|' << std::setfill('0') << std::setw(4) << time[0] << '|' << std::setfill('0') << std::setw(4) << time[1] << '|' << std::setfill('0') << std::setw(4) << time[2] << '\n';
        }

        else
        {
            temp << name << '|' << day << '|' << std::setfill('0') << std::setw(4) << time1 << '|' << std::setfill('0') << std::setw(4) << time2 << '|' << std::setfill('0') << std::setw(4) << time3 << '\n';
        }

    }
    temp.close();
    movie.close();

    movie.open("Movies.txt",ios::out);
    temp.open("temp.txt",ios::in);

    for (int y=0; y <= (lines-2); y++ )
    {
        temp.getline(name,25,'|');
        temp.getline(day,25,'|');
        temp.getline(time1,25,'|');
        temp.getline(time2,25,'|');
        temp.getline(time3,25);
        movie << name << '|' << day << '|' << std::setfill('0') << std::setw(4) << time1 << '|' << std::setfill('0') << std::setw(4) << time2 << '|' << std::setfill('0') << std::setw(4) << time3 << '\n';
    }

    temp.close();
    movie.close();

    cout << "\n You have done editing the showtime manager!!! \n";
    remove("temp.txt");
}

void management()
{
    system("CLS");
    title();
    string userName;
    string pass = "MTRS";
    char userPassword[50];

    int loginAttempt = 0;


    cout << endl << endl;
    while (loginAttempt < 5)
    {
        cout << "\t\t\t\tPlease enter your user name: ";
        cin >> userName;
        cout << endl;
        cout << "\t\t\t\tPlease enter your user password: ";
        int a = 0;
        while(userPassword[a - 1] != '\r'){
            userPassword[a] = getch();
            if(userPassword[a-1]!='\r'){
                cout << "*";
            }
            a++;
        }
        userPassword[a-1] = '\0';

        if (userName == "Mathavan" && userPassword == pass){
            cout << "Welcome Mathavan!" << endl;
            break;
        }
        else if (userName == "Sofea" && userPassword == pass){
            cout << "Welcome Sofea!" << endl;
            break;
        }
        else if (userName == "Nicole" && userPassword == pass){
            cout << "Welcome Nicole!" << endl;
            break;
        }
        else if (userName == "Weishan" && userPassword == pass){
            cout << "Welcome Weishan!" << endl;
            break;
        }
        else if (userName == "ChowWei" && userPassword == pass){
            cout << "Welcome ChowWei!" << endl;
            break;
        }
        else{
            cout << "\n\n\t\t\t\tInvalid login attempt. Please try again.\n" << '\n';
            loginAttempt++;
        }
    }

    if (loginAttempt == 5)
    {
        cout << "Too many login attempts! The program will now terminate.";
    }

    bool flag=true;

    while (flag){
        system("CLS");
        title();
        cout << endl << endl << endl;
        cout << "                                          (1) Enter a new movie " << endl << endl << endl;
        cout << "                                          (2) Update the showtime for a movie" << endl << endl << endl;
        cout << "                                          (3) Delete a movie " << endl << endl << endl;

        char c;
        cout << "Enter your selection manager: ";
        cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
        cin >> c;

        switch (c){
            case '1' :
                add_movie();
                break;
            case '2':
                update_movie();
                break;
            case '3':
                delete_movie();
                break;

            default :
            cout << endl;
            cout << "Please input a correct selection\n";
            cout << "If you continue to use program press ' y ',if no please press any input to restart\n ";
        }

        cout << " if you continue to use program press ' y ', if no please press any key to go back to the main menu \n ";
        char f;
        cin >> f;
        f = tolower(f);
        if(f!='y')
        {
            main();
        }
    }
}

string member_login(){
    title();
    fstream member;
    char pass_input[50];
    string line, acc_num1, password1, accno_input, name1, icno1, email1, phone_number1;
    int login_attempt = 0, count = 0 , account = 0, month_int, year_int;
    char dummy, resp;

    account_num:
    member.open("Membership.txt",ios::in);
    cout << "                                          Enter your account number : ";
    cin >> accno_input;

    ifstream file("Membership.txt");
    while (getline(file, line)) {
        count++;
     }

    int i = 0;
    while(i <= count)
    {
        member.getline(name,25,'|');
        member.getline(icno,25,'|');
        member.getline(email,40,'|');
        member.getline(phone_number,25, '|');
        member.getline(acc_num,25, '|');
        member.getline(password,25,'|' );
        member.getline(month,25,'|' );
        member.getline(year, 25);

        acc_num1 = acc_num;
        if (acc_num == accno_input){
            account = 1;
            break;
        }

        i ++;
    }

    member.close();

    if ( account != 1 ){
        cout << endl;
        cout << "                                  Your account not found !!!"<< endl;
//        cout << "                                  Please try again !!" << endl << endl;
//        cout << "                                  PLEASE ENTER P TO CONTINUE >>> ";
        //cin >> dummy;
        goto account_num;
    }

    password1 = password;
    cout << endl;
    cout << "                                          Enter your account password : ";

    int a = 0;
    while(pass_input[a - 1] != '\r'){
        pass_input[a] = getch();
        if(pass_input[a-1]!='\r'){
            cout << "*";
        }
        a++;
    }
    pass_input[a-1] = '\0';

    for (login_attempt = 1 ; login_attempt <= 2 ; login_attempt ++){
        if (pass_input == password1){
            cout << "Login Successful !!!";
            break;
        }

        cout << endl;
        cout << "Login Failed. Attempt " << login_attempt  << " of 3" << endl;
        cout << "Please re-enter Password: " ;
        int a = 0;
        while(pass_input[a - 1] != '\r'){
            pass_input[a] = getch();
            if(pass_input[a-1]!='\r'){
                cout << "*";
            }
            a++;
        }
        pass_input[a-1] = '\0';

        if (pass_input == password1){
            cout << "Login Successful !!!";
                break;
        }
    }

    if ( login_attempt == 3){
        cout << endl;
        cout << "Login Failed. Attempt 3 of 3" << endl;
        cout << "You have exceeded the login attempt! Press P to go back to the main menu." << endl;
        cin >> resp;
        tolower(resp);
        while(resp != 'p'){
            cout << "You have exceeded the login attempt! Press P to go back to the main menu." << endl;
            cin >> resp;
        }
        main();

    }


    name1 = name, icno1 = icno, email1 = email, phone_number1 = phone_number;
    sscanf(year, "%d", &year_int);
    sscanf(month, "%d", &month_int);

    MemberProg -> MemberInitialize (name1, icno1, email1, phone_number1, acc_num1, password1, month_int, year_int);
    return acc_num1;
}

void ticket_cancel(){

    fstream booking, temp;

    string search_receipt;
    char ticket_num[25], name[25], phone[25], email[40], seat_type[25], movie[25], day[25], showtime[25], seat_booked[60];
    bool isExist = 0, isFound = 0;
    char response;

    do{
        int lines = 0;
        system("CLS");
        title();

        cout << "\t\t\t\t\t\tTICKET CANCELLATION\n\n";
        cout << "\n\t\tEnter your ticket no. : ";
        cin >> search_receipt;

        booking.open("Booking.txt", ios::in);
        while(!booking.eof())
        {
            booking.getline(ticket_num,25,'|');
            booking.getline(name,25,'|');
            booking.getline(phone,25,'|');
            booking.getline(email,40,'|');
            booking.getline(movie,25,'|');
            booking.getline(day,25,'|');
            booking.getline(showtime,25,'|');
            booking.getline(seat_type,25,'|');
            booking.getline(seat_booked,60);

            if(ticket_num == search_receipt){
                isExist = 1;
                break;
            }
            else{
                isExist=0;
            }
        }
        booking.close();

        if(!isExist){
            cout << "\t\tRecord do not exist!" << endl;
        }
        else{
            booking.open("Booking.txt", ios::in);
            temp.open("temp.txt", ios::out);

            while(!booking.eof())
            {
                booking.getline(ticket_num,25,'|');
                booking.getline(name,25,'|');
                booking.getline(phone,25,'|');
                booking.getline(email,40,'|');
                booking.getline(movie,25,'|');
                booking.getline(day,25,'|');
                booking.getline(showtime,25,'|');
                booking.getline(seat_type,25,'|');
                booking.getline(seat_booked,60);

                if(ticket_num == search_receipt){

                    string s_type;
                    for(int i=0; i<1;i++){
                        if(seat_type[i] == 'a'){
                            s_type = "Deluxe";
                        }
                        if(seat_type[i] == 'b'){
                            s_type = "Normal";
                        }
                    }

                    cout << "\t\tRecord is found!\n\n"
                         << "\t\t=========================================================\n"
                         << "\t\t=                  BOOKING RECORD                       =\n"
                         << "\t\t=========================================================\n"
                         << "\n\t\tTicket No.     : " << ticket_num
                         << "\n\t\tName           : " << name
                         << "\n\t\tPhone no.      : " << phone
                         << "\n\t\tE-mail         : " << email
                         << "\n\t\tMovie selected : " << movie
                         << "\n\t\tDay            : " << day
                         << "\n\t\tShowtime       : " << showtime
                         << "\n\t\tSeat selected  : " << seat_booked
                         << "\n\t\tSeat type      : " << s_type << " seat\n"
                         << "\n\t\t---------------------------------------------------------" << endl;
                }
                else{
                    temp << ticket_num << '|' << name << '|' << phone << '|' << email << '|' << movie << '|'
                         << day << '|' << showtime << '|' << seat_type << '|' << seat_booked << '\n';
                }
                lines++;  // Count number of lines in the file
            }
            // Uncomment the next line to count the number of lines in .txt file (FOR TESTING PURPOSE ONLY)
            //cout << "Lines = " << lines << endl;;
            temp.close();
            booking.close();


            char ch;
            cout << "\t\tAre you sure you want to cancel your ticket booking?[Y/n]: ";
            cin >> ch;
            tolower(ch);

            while(ch!='y' && ch !='n'){
                cout << "\t\tWrong input! Are you sure you want to cancel your ticket booking?[Y/n]: ";
                cin >> ch;
                tolower(ch);
            }

            if(ch=='y'){
                lines = lines - 2;                     // Will not read the extra two lines in temp.txt
                booking.open("Booking.txt",ios::out);
                temp.open("temp.txt",ios::in);
                for(int i=0; i<lines; i++){
                    temp.getline(ticket_num,25,'|');
                    temp.getline(name,25,'|');
                    temp.getline(phone,25,'|');
                    temp.getline(email,40,'|');
                    temp.getline(movie,25,'|');
                    temp.getline(day,25,'|');
                    temp.getline(showtime,25,'|');
                    temp.getline(seat_type,25,'|');
                    temp.getline(seat_booked,60);

                    booking << ticket_num << '|' << name << '|' << phone << '|' << email << '|' << movie << '|'
                            << day << '|' << showtime << '|' << seat_type << '|' << seat_booked << '\n';
                }
                temp.close();
                booking.close();
                cout << "\n\t\tTicket cancel successfully !!!";
            }
            else{
                cout << "\n\t\tTicket is not being cancelled." << endl;
            }
            remove("temp.txt");

        }

        cout << "\n\n\t\tDo you want to use it again?[Y/n]: ";
        cin >> response;
        tolower(response);

        while(response!='y' && response!='n'){
            cout << "\n\t\tWrong selection. Enter Again !!"
                 << "\n\t\tResponse : ";
            cin >> response;
        }

    }while(response=='y');

    system("CLS");
    main();
}
