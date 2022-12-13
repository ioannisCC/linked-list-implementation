#include <iostream>
#include <random>
#include <functional>

using namespace std;

/*in this program we excluded the rest of the methods which are used for linked lists functionality because for this
specific purpose we did not use them*/

template <class T>
class Chain; //in order for the friend to work we need to pre-declare the class

template <class T>
class ChainNode{
    friend Chain<T>;
private:
    T data;
    T occurrence;
    ChainNode<T> *link;
};

template <class T>
class Chain{
public:
    Chain() {first = 0;}    //initializes the first pointer
    ~Chain();
    // const because the object called by these functions cannot be modified (security)
    int Count(const T& x) const;
    void Output(ostream& out) const;
    /* this function lets you decide where the data should be written to.
     * If you want the data written in the terminal you pass "cout" as the argument.
     * If you want it in a file, you open a file as an ostream and pass that
     * to the function instead.*/
    void OutputHistogram(ostream &out) const;
    Chain<T>& AppendHistogram(const T& x, const T& z);
    Chain<T>& Insert(int k, const T& x);
private:
    ChainNode<T> *first; //pointer to first node
    ChainNode<T> *last;  //pointer to last node
};



int main() {
    int n,a=0,b=100; //n (array size), a (lower bound), b (higher bound)

    default_random_engine generator;
    uniform_int_distribution<int> data_element_distribution(a, b);
    auto random_element = bind(data_element_distribution,generator);

    cout<<"provide size of the list: "<<endl;
    cin>>n;
    while(n<=0)
    {
        cout<<"provide a valid size of the list (>0): "<<endl;
        cin>>n;
    }

    try {
        Chain<int> L;
        //initialize L nodes with random elements
        for (int i = 0; i < n; i++) {
            int data_element = random_element();
            L.Insert(i,data_element);
        }


    cout<<"elements in L are: ";
    L.Output(cout);
    cout<<endl;

    Chain<int> histogram;

    //checking if numbers within the range (a,b) are in L
    for (int i=a; i<=b; i++)
    {
       int temp = L.Count(i);  //temp stores the multitude of each number
       if (temp != 0)             //if the number is in L then temp will be !=0
       {
           histogram.AppendHistogram(i,temp);  //append in histogram the number and the multitude of it
       }
    }

    cout<<"elements in histogram are: "<<endl;
    histogram.OutputHistogram(cout);
    cout<<endl;

    return 0;
    }
    catch(exception){
        cerr<<"An exception has occurred"<<endl;
    }
}

string OutOfBounds()
{
    cout<<"out of bounds"<<endl;
    return 0;
}

template <class T>
Chain<T>::~Chain()
{   // deletes all nodes of chain
    ChainNode<T> *next; //next node
    while(first){ //while first is True because when is NULL means there is no other node left
        next = first->link;
        delete first;
        first = next;
    }
}

template <class T>
int Chain<T>::Count(const T& x) const
{   //locate x; return number of times x shows up
    //return 0 if x not in the chain
    ChainNode<T> *current = first;
    int count = 0;
    while(current && (current->link != NULL)){    //check if current!=0 and if the node we are accessing is not the last one
        if (current->data == x)                   //check if the value we passed as parameter is the same with the value in data
            count++;                              //increase by one the value of counter which represents the multitude
        current = current->link;                  //move to next node
    }
    if (current->link == NULL && (current->data == x))  //take into consideration the last node because with the check we
        count++;                                        //did above we did not check the data of last node and if we find
    return count;                                       //the value we passed as a parameter inside data then counter+=1
}

template <class T>
void Chain<T>::Output(ostream &out) const
{   //insert the chain element into the stream out
    ChainNode<T> *current;
    for (current = first; current; current = current->link)
    {
        out<<current->data<<" ";
    }
}

template <class T>
void Chain<T>::OutputHistogram(ostream &out) const
{   //insert the chain element into the stream out
    ChainNode<T> *current;
    for (current = first; current; current = current->link)
    {
        out<<"data (number): "<<current->data<<" ";
        out<<"|| occurence (of number): "<<current->occurrence<<" ";
        out<<endl;
    }
}

//overload <<
template <class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
{
    x.Output(out);
    return out;
}

//in data will be stored the number and in occurrence the multitude of number
//so first parameter is the number from L and the second one is the multitude of number
template <class T>
Chain<T>& Chain<T>::AppendHistogram(const T& x, const T& z)
{   //add x at right end
    ChainNode<T> *y;
    y = new ChainNode<T>;
    y->data = x;        //access the first variable which stores the number from L list
    y->occurrence = z; //access the second variable of the node which stores multitude of number
    y->link = 0;
    if (first)
    {   //chain is not empty
        last->link = y;
        last = y;
    }
    else //chain is empty
        first = last = y;  //the first and the last pointer will refer to the same node
    return *this;
}

template <class T>
Chain<T>& Chain<T>::Insert(int k, const T& x)
{   //Insert x after the k'th element.
    //Throw OutOfBounds exception if no k'th element.
    //Pass NoMem exception if inadequate space.
    if (k < 0) throw OutOfBounds();
    //p will eventually point to k'th node
    ChainNode<T> *p = first;
    for (int index = 1; index < k && p; index++)
        p = p->link; //move p to k'th
    if (k > 0 && !p) throw OutOfBounds(); //no k'th
    //insert
    ChainNode<T> *y = new ChainNode<T>; y->data = x;
    if (k)
    {   //insert after p
        y->link = p->link; p->link = y;
    }
    else
    {   //insert as first element
        y->link = first; first = y;
    }
    if (!y->link) last = y; //new last element
    return *this;
}