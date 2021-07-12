#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

struct SMerch
{
    string name;
    int price;
    SMerch *n;
};

//Adds new merch
void Add(SMerch * & head, string name, int price)
{
    SMerch *p = new SMerch;
    p->name = name;
    p->price = price;
    p->n = head;
    head = p;
}

//Deletes the linked list
void Del (SMerch * & head)
{
    SMerch *p;
    while(head)
    {
        p = head;
        if(p)
        {
            head = p->n;
            delete p;
        }
    }
}

//Writes merch from the linked list
void Write(SMerch *adress)
{
    if(!adress)
        return;
    
    cout<<"Name of the merch: "<<adress->name;
    cout<<" Price: "<<adress->price<<endl;
    Write(adress->n);
}

//Writes prices that are below avarage price
void WriteAv(SMerch *adress, int s)
{
    if(!adress)
        return;
    if(adress->price < s)
    {
        cout<<"Name of the merch: "<<adress->name;
        cout<<" Price: "<<adress->price<<endl;
    }
    WriteAv(adress->n, s);
}

int main(int argc, const char * argv[]) {
    ifstream inFile;
    string name;
    int price, i=0, s=0;
    
    SMerch *head;
    head = NULL;
    inFile.open("merch.txt");
    
    if(inFile.fail())
    {
        cout<<"The file is corrupted or does not exist"<<endl;
        exit(1);
    }
    if(inFile.is_open())
    {
        while(!inFile.eof())
        {
            getline(inFile, name, ' ');
            inFile>>price;
            inFile.ignore( numeric_limits<streamsize>::max(), '\n' );
            Add(head, name, price);
            s+=price;
            i++;
            
        }
    }
    inFile.close();
    
    Write(head);
    cout<<endl<<"Enter name of the new merch: ";
    cin>>name;
    cout<<endl<<"Enter price: ";
    cin>>price;
    s+=price;
    i++;
    
    Add(head, name, price);
    Write(head);
    
    s=s/i;
    if(i>=2)
    {
    cout<<"Prices below avarage price"<<endl;
    WriteAv(head, s);
    }
    
    Del(head);
    cout<<"After deleting "<<endl;
    Write(head);
  
    return 0;
}

