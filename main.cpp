#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>

using namespace std;

/**Directory of the App**/
const char DIR_PASSWORD[] = "password.dat";

/**Struct of the password**/
struct Password{
    char sitename[50];
    char passwordname[50];
    char mail[50];
    char notes[400];
};

/**Functions of the app**/
void CreatePassword(Password pw);
Password readPassword();
bool isPassword(char sitename[],char passwordname[]);
Password searchPassword(char sitename[],char passwordname[]);
void ShowPassword(Password pw);
void ListPassword();
void DeletePassword(char sitename[],char passwordname[]);
void UpdatePassword(char sitename[],char passwordname[]);

/**Menus**/
void CreatePasswordMenu();
void SearchPasswordMenu();
void ListPasswordMenu();
void DeletePasswordMenu();
void UpdatePasswordMenu();

/**Main menu**/
int main(){

    int sel;
    do{
        system("cls");
        cout<<"\t\t\t\t\tPASSWORD KEEPER"<<endl;
        cout<<"\t\t\t\tCreate Password..............[1]"<<endl;
        cout<<"\t\t\t\tDelete Password..............[2]"<<endl;
        cout<<"\t\t\t\tList Passwords...............[3]"<<endl;
        cout<<"\t\t\t\tUpdate Password..............[4]"<<endl;
        cout<<"\t\t\t\tSearch Password..............[5]"<<endl;
        cout<<"\t\t\t\tExit.........................[6]"<<endl;
        cout<<"\t\t\t\tChoose an option ->:";
        cin>>sel;
        cin.ignore();
        switch(sel)
        {
            case 1 : system("cls");
                     CreatePasswordMenu();
                     break;
            case 2 : system("cls");
                     SearchPasswordMenu();
                     break;
            case 3 : system("cls");
                     ListPasswordMenu();
                     break;
            case 4 : system("cls");
                     DeletePasswordMenu();
                     break;
            case 5 : system("cls");
                     UpdatePasswordMenu();
                     break;
            case 6 : break;
            default: cout<<"\t\t\tOpcion incorrecta"<<endl;
        }
    }while(sel!=6);
    return 0;
}

/**Creation Of A Password**/
void CreatePassword(Password pw)
{
    ofstream outStream;
    outStream.open(DIR_PASSWORD,ios::binary | ios::app);
    outStream.write((char*)&pw,sizeof(Password));
    outStream.close();
}

/**Password To Read When Called**/
Password readPassword()
{
    Password pw;
    cout<<"\t\t\tSITE   : ";
    cin.getline(pw.sitename,50);
    cout<<"\t\t\tPASSWORD : ";
    cin.getline(pw.passwordname,50);
    cout<<"\t\t\tASSOCIATED MAIL : ";
    cin.getline(pw.mail,50);
    cout<<"\t\t\tNOTAS     : ";
    cin>>pw.notes;
    cin.ignore();
    return pw;
}

/**Bool To See If Password Exists**/
bool isPassword(char sitename[])
{

    Password pw;
    ifstream inStream;
    inStream.open(DIR_PASSWORD,ios::binary);

    if(inStream.good())
    {
        while(inStream.read((char*)&pw,sizeof(Password)))
        {
            if(strcmp(sitename,pw.sitename)==0)
            {
                inStream.close();
                return true;
            }
        }

        inStream.close();
        return false;
    }

    else
    {
        inStream.close();
        return false;
    }
}

Password searchPassword(char sitename[])
{
    Password pw;
    ifstream inStream;
    inStream.open(DIR_PASSWORD,ios::binary);

    if(inStream.good())
    {

        while(inStream.read((char*)&pw,sizeof(Password)))
        {
            if(strcmp(sitename,pw.sitename)==0)
            {
                inStream.close();
                return pw;
            }
        }
    }
}

/**Functions Of The App**/
void ShowPassword(Password pw)
{
    cout<<endl;
    cout<<"\t\t\t SITE      : "<<pw.sitename<<endl;
    cout<<"\t\t\t PASSWORD  : "<<pw.passwordname<<endl;
    cout<<"\t\t\t E-MAIL    : "<<pw.mail<<endl;
    cout<<"\t\t\t NOTES     : "<<pw.notes<<endl;
    cout<<"Press Any Key To Exit"<<endl;
    cout<<endl;
}

void ListPassword()
{
    ifstream inStream;
    inStream.open(DIR_PASSWORD,ios::binary);
    Password pw;
    if(inStream.good())
    {
        while(inStream.read((char*)&pw,sizeof(Password)))
        {
            ShowPassword(pw);
        }

    }
    else
    {
        cout<<"File Can Not Be Opened"<<endl;
    }
    inStream.close();
}

void DeletePassword(char sitename[]){
    ifstream inStream;
    ofstream tempStream;
    inStream.open(DIR_PASSWORD,ios::binary);
    tempStream.open("temp.dat",ios::binary);
    Password pw;
    if(inStream.good())
    {
        while(inStream.read((char*)&pw,sizeof(Password)))
        {
            if(strcmp(sitename,pw.sitename)!=0)
            {
                tempStream.write((char*)&pw,sizeof(Password));
            }
        }
    }
    inStream.close();
    tempStream.close();
    remove(DIR_PASSWORD);
    rename("temp.dat",DIR_PASSWORD);
}

void UpdatePassword(char sitename[])
{
    ifstream inStream;
    ofstream tempStream;
    inStream.open(DIR_PASSWORD,ios::binary);
    tempStream.open("temp.dat",ios::binary);
    Password pw;

    if(inStream.good())
    {
        while(inStream.read((char*)&pw,sizeof(Password)))
        {
            if(strcmp(sitename,pw.passwordname)==0)
            {
                Password updated = readPassword();
                tempStream.write((char*)&updated,sizeof(Password));
            }
            else
            {
                tempStream.write((char*)&pw,sizeof(Password));
            }
        }
    }

    inStream.close();
    tempStream.close();
    remove(DIR_PASSWORD);
    rename("temp.dat",DIR_PASSWORD);
}

void CreatePasswordMenu()
{

    cout<<"\t\t\t\tINSERT THE NEW PASSWORD"<<endl;
    Password New = readPassword();
    CreatePassword(New);
    cout<<"\t\t\tNew Password Created Succesfully"<<endl;
}

void SearchPasswordMenu()
{
    cout<<"\t\t\t\tSEARCH PASSWORD"<<endl;
    char sitename[50];
    cout<<"\t\t\tWrite The Name Of The Site You Are Looking For:"<<endl;
    cout<<"\t\t\SITE   : ";
    cin.getline(sitename,50);
    if(isPassword(sitename))
    {
        Password SearchedPassword = searchPassword(sitename);
        ShowPassword(SearchedPassword);
    }
    else
    {
        cout<<"\t\t\tCouldn´t Find The Site"<<endl;
    }
}

/**Menus**/
void ListPasswordMenu()
{
    cout<<"\t\t\t\tLIST OF PASSWORDS"<<endl;
    ListPassword();
    getch();
}

void DeletePasswordMenu()
{
    cout<<"\t\t\t\tDELETE PASSWORD"<<endl;
    char sitename[50];
    cout<<"\t\t\tInsert The Password You Want To Delete:"<<endl;
    cout<<"\t\t\tSITE    : ";
    cin.getline(sitename,30);
    if(isPassword(sitename))
    {
        Password deleted = searchPassword(sitename);
        int sel;
        cout<<"\t\t\t Are You Sure You Want To Delete This Password?";
        ShowPassword(deleted);
        do{
            cout<<"\t\t\tYES....[1]";
            cout<<"\t\t\tNO.....[2]";
            cin>>sel;
            switch(sel)
            {
                case 1: DeletePassword(sitename);
                        cout<<"\t\t\tThe Password Has Been Deleted"<<endl;
                        break;
                case 2: break;
                default: cout<<"\t\t\tNo Option Selected"<<endl;
            }
        }while(sel!=1 && sel!=2);
    }
    else{
        cout<<"\t\t\tNO PASSWORD TO DELETE"<<endl;
    }
}
void UpdatePasswordMenu()
{
    cout<<"\t\t\t\tUPDATE PASSWORD"<<endl;
    char sitename[50];
    cout<<"\t\t\tInsert Password You Want To Update:"<<endl;
    cout<<"\t\t\tsite   : ";
    cin.getline(sitename,50);
    if(isPassword(sitename))
    {
        Password SearchedPassword = searchPassword(sitename);
        cout<<"\t\t\tPassword:"<<endl;
        ShowPassword(SearchedPassword);
        UpdatePassword(sitename);
        cout<<"\t\t\tPassword Has Been Updated"<<endl;
    }
    else
    {
        cout<<"\t\t\tNO PASSWORD TO UPDATE"<<endl;
    }
}
