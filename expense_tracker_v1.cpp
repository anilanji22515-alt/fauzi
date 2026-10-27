#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Expense
{
    private:
        string name;
        long long amount;
        int date;
    public:
        Expense(string n,long long a,int d) : name(n),amount(a),date(d)
        {}
        void showExpense()const;
        string getName()const;
        long long getAmount()const;
        int getDate()const;
};

class Tracker
{
    private:
        vector<Expense> expenses;
    public:
        int getExpensePosition(const string & name,long long  amount,int date)const;
        void showAllExpenses()const;
        void showCertainExpense(const string & name)const;
        void showExpensesInDates(int date1,int date2);
        void showTotalExpensesAmount()const;
        void addExpense(const string & name,long long amount,int date);
        void removeExpense(const string & name,long long amount,int date);
        void resetTracker();
        long long getTotalExpensesAmount()const;
};

void Expense :: showExpense()const
{
    cout<<"Name: "<<name<<"\n"
        <<"Amount: "<<amount<<"\n"
        <<"Date: "<<date<<"\n\n";
}

string Expense :: getName()const
{
    return name;
}

long long Expense :: getAmount()const
{
    return amount;
}

int Expense :: getDate()const
{
    return date;
}

int Tracker :: getExpensePosition(const string & name,long long amount,int date)const
{
    for(int i=0;i<expenses.size();i++)
    {
        if(name==expenses[i].getName() && amount==expenses[i].getAmount() && date==expenses[i].getDate())
        {
            return i;
        }
    }
    return -1;
}

long long Tracker :: getTotalExpensesAmount()const
{
    long long total=0;
    for(int i=0;i<expenses.size();i++)
    {
        total+=expenses[i].getAmount();
    }
    return total;
}

void Tracker :: showAllExpenses()const
{
    if(expenses.empty())
    {
        cout<<"Tracker is empty so add some expenses to see the expenses\n\n";
        return;
    }
    cout<<"All expenses details:\n\n";
    for(int i=0;i<expenses.size();i++)
    {
        expenses[i].showExpense();
    }
}

void Tracker :: showCertainExpense(const string & name)const
{
    bool isExpenseFound=false;
    for(int i=0;i<expenses.size();i++)
    {
        if(name==expenses[i].getName())
        {
            cout<<name<<" expenses founded & details:\n\n";
            expenses[i].showExpense();
            isExpenseFound=true;
        }
    }
    if(!isExpenseFound)
        cout<<name<<" expense not founded\n\n";
}

void Tracker :: showExpensesInDates(int date1,int date2)
{
    int startDate,endDate;
    if(date1>=date2)
    {
        endDate=date1;
        startDate=date2;
    }
    else
    {
        endDate=date2;
        startDate=date1;
    }

    bool isThatExpenseFound=false;
    for(int i=0;i<expenses.size();i++)
    {
        if(expenses[i].getDate()>=startDate && expenses[i].getDate()<=endDate)
        {
            expenses[i].showExpense();
            isThatExpenseFound=true;
        }
    }
    if(!isThatExpenseFound)
        cout<<"Such expenses not found\n\n";
}

void Tracker :: showTotalExpensesAmount()const
{
    cout<<"Total expenses amount: "<<getTotalExpensesAmount()<<"\n\n";
}

void Tracker :: addExpense(const string & name,long long amount,int date)
{
    Expense temp(name,amount,date);
    expenses.push_back(temp);
}


void Tracker :: removeExpense(const string & name,long long amount,int date)
{
    if(expenses.empty())
    {
        cout<<"Tracker is empty so add some expenses before removing the expenses\n\n";
        return;
    }
    int position=getExpensePosition(name,amount,date);
    if(position!=-1)
    {
        for(int i=position+1;i<expenses.size();i++)
        {
            expenses[i-1]=expenses[i];
        }
        expenses.pop_back();
        cout<<name<<" expense founded and removed\n\n";
    }
    else
    {
        cout<<name<<" expense not found\n\n";
    }
}

void Tracker :: resetTracker()
{
    int size=expenses.size();
    for(int i=0;i<size;i++)
    {
        expenses.pop_back();
    }
    cout<<"Tracker resetted\n\n";
}

string takeValidName()
{
    string input;
    cout<<"Enter name of an expense:\n";
    cin>>input;
    return input;
}

long long takeValidAmount()
{
    long long amount;
    cout<<"Enter amount: ";
    cin>>amount;
    return amount;
}

int takeValidDate()
{
    int date;
    cout<<"Enter date: ";
    cin>>date;
    return date;
}

void displayIntro()
{
    cout<<"This is a expense tracker\n"
        <<"In this you able record,see and manage your expenses\n\n";
}

void showMenu()
{
    cout<<"Menu:\n\n"
        <<"1)Add expenses\n"
        <<"2)Remove expense\n"
        <<"3)Show all expenses\n"
        <<"4)Show certain expense\n"
        <<"5)Show expenses in between dates\n"
        <<"6)Show total amount\n"
        <<"7)Reset tracker\n"
        <<"8)Exit\n\n";
}

void menu(Tracker & t)
{
    int choice;
    do
    {
        showMenu();
        cout<<"Enter choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                string name=takeValidName();
                long long amount=takeValidAmount();
                int date=takeValidDate();
                t.addExpense(name,amount,date);
                break;
            }
            case 2:
            {
                string name=takeValidName();
                long long amount=takeValidAmount();
                int date=takeValidDate();
                t.removeExpense(name,amount,date);
                break;
            }
            case 3:
                t.showAllExpenses();
                break;
            case 4:
            {
                string name=takeValidName();
                t.showCertainExpense(name);
                break;
            }
            case 5:
            {
                int date1=takeValidDate();
                int date2=takeValidDate();
                t.showExpensesInDates(date1,date2);
                break;
            }
            case 6:
                t.showTotalExpensesAmount();
                break;
            case 7:
                t.resetTracker();
                break;
            case 8:
                cout<<"Exiting......\n\n";
                break;
            default:
                cout<<"Invalid choice\n"
                    <<"Try again\n\n";

        }
    } while(choice!=8);
    
}

int main()
{
    Tracker tracker;
    displayIntro();
    menu(tracker);
}