#include <iostream>

using namespace std;
class ListElem
{
public:
    int* value;
    ListElem *next, *previous;
};

class List
{
    ListElem *Head, *End;
public:
    List(): Head(NULL), End(NULL){}

    ~List()
    {
        if (Head != NULL)
        {
            while (Head)
            {
                End = Head->next;
                delete Head;
                Head = End;
            }
        }
    }

    void Add(int elem)
    {
        ListElem *temp1 = new ListElem;
        temp1->next = NULL;
        temp1->value = new int(elem);
        if (Head != NULL)
            {
                temp1->previous = End;
                End->next = temp1;
                End = temp1;
            }
        else
        {
            temp1->previous = NULL;
            Head = End = temp1;
        }
        cout << *temp1->value << endl;
    }

    void DeleteElem(int val)
    {
        ListElem *del = Head;
        ListElem *temp2 = Head;
        while (temp2 != End)
        {
            if (*temp2->value == val)
            {
                del = temp2;
                break;
            }
            else
            {
                temp2 = temp2->next;
            }
        }
        if (del->previous != NULL && del->next != NULL)
        {
            del->previous->next = del->next;
            del->next->previous = del->previous;
        }
        else if (del->next != NULL)
        {
            del->next->previous = NULL;
            Head = del->next;
        }
        else if (del->previous != NULL)
        {
            del->previous->next = NULL;
            End = del->previous;
        }
        del->value = NULL;
    }

    bool srch(int val)
    {
        if (Head != NULL)
        {
            if (*Head->value == val)
            {
                cout << "true" << endl;
                return true;
            }
            ListElem* temp3 = Head;
            while (temp3->next)
            {
                if (*temp3->value == val)
                {
                    cout << "true" << endl;
                    return true;
                }
                else
                {
                    temp3 = temp3->next;
                }
            }
            if (*End->value == val)
            {
                cout << "true" << endl;
                return true;
            }
        }
        cout << "false" << endl;
        return false;
    }
};

int main()
{
    List L;

    L.Add(1);
    L.Add(2);
    L.Add(3);
    L.Add(4);
    L.Add(5);
    L.Add(6);

    L.srch(3);

    L.DeleteElem(3);
    L.DeleteElem(5);

    L.srch(3);
    L.srch(5);

    return 0;
}
