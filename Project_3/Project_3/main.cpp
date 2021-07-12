#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//BST
struct Tnode
{
    int data;
    Tnode *left;
    Tnode *right;
};

//list
struct SElem
{
    int data;
    SElem *next;
};

// part 1 BST
//Adding data to the BST
void Add (Tnode *&node, int value)
{
    if (node == NULL)
    {
        node = new Tnode;
        node->data = value;
        node->left=NULL;
        node->right=NULL;
    }
    else if (value < node->data) Add(node->left, value);
    else if (value > node->data) Add(node->right, value);
}

//Shows data in inorder traversal
void Write(Tnode *node)
{
    if(node != NULL)
    {
        Write(node->left);
        cout<<node->data<<" ";
        Write(node->right);
    }
}

//Searches the BST
Tnode *Search(Tnode *node, int value)
{
    if (node == NULL || value == node->data) return node;
    
    if (value < node->data ) return Search(node->left, value);
    else return Search(node->right, value);
}

//Gives the height of the BST
int Height(Tnode *node, int l = 0, int p = 0)
{
    if (node!= NULL)
    {
        l = Height(node->left);
        l++;
        p = Height(node->right);
        p++;
        if (l>p) return l;
        else return p;
    }
    else return 0;
}

//gives the number of elements in the BSI
int Size(Tnode *node, int count =0)
{
    if (node != NULL)
    {
        count = Size(node->left);
        count += Size(node->right);
        count++;
        return count;
    }else return 0;
}

//searches for the biggest number
Tnode *Max(Tnode *node)
{
    if (node != NULL)
    {
    if (node->right!= NULL) return Max(node->right);
    }
    return node;
}

//deletes BST
void Del(Tnode *node)
{
    Tnode *u;
    if (node != NULL)
    {
        Del(node->left);
        Del(node->right);
        u=node;
        node= NULL;
        delete u;
    }
}

//adds elements to the list in inorder traversal
SElem *AddInorder(Tnode *node)
{
    if (node == NULL) return NULL;
    
    SElem *head = AddInorder(node->left);
    SElem *newE = new SElem;
    newE->data = node->data;
    newE->next = NULL;
    
    if (head)
    {
        SElem *current = head;
        while (current->next)
        {
            current=current->next;
        }
        current->next = newE;
    }
    else head = newE;
    
    SElem *pHead = AddInorder(node->right);
    if(pHead)
    {
        newE->next = pHead;
    }
    return head;
}

// part 2 list
//adds the element at the end
void Add2(SElem * & head, int data)
{
    SElem *newE = new SElem;
    newE->data = data;
    newE->next = NULL;
    if (head == NULL)
    {
        head = newE;
    }else
    {
        SElem *last = head;
        while(last->next!=NULL)
        {
            last=last->next;
        }
        last->next=newE;
    }
}
//writes the list
void Write2 (SElem *head)
{
    if (head)
    {
        cout<<head->data<<" ";
        Write2(head->next);
    }
}
//deletes the list
void Del2(SElem * & head)
{
    while (head != NULL)
    {
        SElem *tmp = head;
        head = head->next;
        delete tmp;
    }
    head = NULL;
}

//sort

//additional functions for the MergeSort
//merges a divided list
SElem* Merge(SElem* a, SElem* b)
{
    SElem* result = NULL;
    
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;
    
    if (a->data <= b->data) {
        result = a;
        result->next = Merge(a->next, b);
    }
    else {
        result = b;
        result->next = Merge(a, b->next);
    }
    return result;
}
//divides a list
void Devide(SElem* head, SElem * & p, SElem * & s)
{
    SElem* end;
    SElem* mid;
    mid = head;
    end = head->next;
    
    // determines the middle element
    while (end != NULL) {
        end = end->next;
        if (end != NULL) {
            mid = mid->next;
            end = end->next;
        }
    }
    
    p = head;
    s = mid->next;
    mid->next = NULL;
}

//MergeSort
void Sort(SElem * & head)
{
    SElem* current = head;
    SElem* l1;
    SElem* l2;
    
    if ((current == NULL) || (current->next == NULL)) {
        return;
    }
    
    Devide(current, l1, l2);
    
    Sort(l1);
    Sort(l2);
    
    head = Merge(l1, l2);
}

int main(int argc, const char * argv[]) {
    int tab[15] = {8,4,12,2,6,10,14,1,3,5,7,9,11,13,15};
    Tnode *node = NULL;
    //creates a BST
    for (int i = 0; i<=14; i++)
    {
        Add(node, tab[i]);
    }
    Write(node);
    cout<<endl<<"wysokosc drzewa: "<<Height(node)<<" ";
    //adds 10 random numbers
    srand(time(NULL));
    for (int i=0; i<10 ;i++)
    {
        Add(node, 16+(rand()%(30+1-16)));
    }
    cout<<endl<<"After adding: "<<endl;
    Write(node);
    
    Tnode *max = Max(node);
    cout<<endl<<"max: "<<max->data<<" ";
    
    cout<<endl<<"Size of the BST: "<<Size(node)<<" ";
    
    if (Search(node, 22)) cout<<endl<<"Number 22 is inside of the BST";
    else cout<<endl<<"number 22 is not inside of the BST";
    
    SElem *head = NULL;
    head = AddInorder(node);
    
    Del(node);
    
    //list
    cout<<endl<<"Content of the list: ";
    Write2(head);
    //adds 10 random numbers
    for (int i=0; i<10 ;i++)
    {
        Add2(head, 31+(rand()%(50+1-31)));
    }
    //sorting
    Sort(head);
    cout<<endl<<"Content of the list after sorting: ";
    Write2(head);
    
    Del2(head);
    return 0;
}
