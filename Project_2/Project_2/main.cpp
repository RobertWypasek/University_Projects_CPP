#include <iostream>
#include <limits>
#include <fstream>
#include <cstdlib>

using namespace std;

struct SMerch
{
    string name;
    float weight, price;
    SMerch *next = NULL;
};

void Write(SMerch *head, string header = "")
{
    if(!head) return;
    if(header != "") cout<<header<<endl;
    cout<<head->name<<" Price: "<<head->price<<" Weight: "<<head->weight<<endl;
    Write(head->next);
}

SMerch *Items (SMerch * & head, int mPrice, int mWeight, bool & del)
{
    int uCount = 0, sCount =0;
    float sPrice =0, sWeight =0;
    SMerch *act = head;
    SMerch *prv = NULL;
    Write(head, "After creating ");
    //part 1.
    //deletes max 2 elements
    
    while(act)
    {
        if(act->price > mPrice && act->weight > mWeight && uCount < 2)
        {
            if (!prv)
            {
                act = act->next;
                delete head;
                head = act;
                uCount ++;
            }else
            {
                prv->next = act->next;
                delete act;
                act = prv->next;
                uCount++;
            }
        }else
        {
            prv = act;
            act = act->next;
        }
    }
    
    //checks if 2 elements were deleted
    if(uCount >=2) del = true;
    Write(head, "After deleting ");
    //part 2
    //counts the average and adds it to the end of the list
    if(head!=NULL && head->next != NULL)
    {
        act = head;
        while (act != NULL)
        {
            sPrice+=act->price;
            sWeight+=act->weight;
            sCount++;
            act = act->next;
        }
        cout<<""<<sPrice<<" "<<sWeight<<" "<<sCount<<endl;
        sPrice = sPrice/sCount;
        sWeight = sWeight/sCount;
        SMerch *last = head;
        while (last->next!= NULL)
        {
            last = last->next;
        }
        SMerch *newT = new SMerch;
        newT->name = "Avarage";
        newT->price = sPrice;
        newT->weight = sWeight;
        newT->next = NULL;
        last->next = newT;
        Write(head, "After adding avarage ");
        return newT;
    }else return 0;
}

int main(int argc, const char * argv[]) {
    bool u = false;
    SMerch *info;
    //takes file name from the user
    ifstream inPlik;
    string name; //File name "merch.txt"
    float price =0, weight =0;
    SMerch *head;
    head = NULL;
    
    cout<<"Enter the file name: ";
    cin>>name;
    
   //creates a list from the data in the file
    inPlik.open(name);
    if(inPlik.fail())
    {
        cout<<"The file is corrupted or does not exist"<<endl;
        exit(1);
    }
    if(inPlik.is_open())
    {
        while(!inPlik.eof())
        {
            SMerch *dodaj = new SMerch;
            getline(inPlik, name, ' ');
            inPlik>>price;
            //inPlik.ignore( numeric_limits<streamsize>::max(), '\n' );
            inPlik>>weight;
            //inPlik.ignore( numeric_limits<streamsize>::max(), '\n' );
            dodaj->name = name;
            dodaj->price = price;
            dodaj->weight = weight;
            dodaj->next = NULL;
            
            dodaj->next = head;
            head = dodaj;
        }
    }
    inPlik.close();
    
    cout<<endl<<"Enter the price that you want to be deleted: ";
    cin>>price;
    cout<<endl<<"Enter the weight that you want to be deleted: ";
    cin>>weight;
    cout<<endl;
    
    info = Items(head, price, weight, u);
    
    if (u)
        cout<<"2 items were deleted"<<endl;
    else cout<<"Nothing was deleted"<<endl;
    
    if (info != 0)
        cout<<"Avarage value: price: "<<info->price<<" weight: "<<info->weight<<endl;
    else cout<<"Avarage value was not added"<<endl;
    
    //Deletes linked list
    while (head != NULL)
    {
        SMerch *tmp = head;
        head = head->next;
        delete tmp;
    }
    
    return 0;
}
