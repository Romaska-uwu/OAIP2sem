
#include <iostream>
#include <fstream>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address
{
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address* next;
    Address* prev;
};

int menu(void)
{
    char s[80];
    int c;
    cout << endl;
    cout << "1. Ввод имени" << endl;
    cout << "2. Удаление имени" << endl;
    cout << "3. Вывод на экран" << endl;
    cout << "4. Поиск" << endl;
    cout << "5. Добавить список в начало" << endl;
    cout << "6. Выход" << endl;
    cout << endl;
    do
    {
        cout << "Ваш выбор: ";
        cin.sync();
        gets_s(s);
        cout << endl;
        c = atoi(s);
    } while (c < 0 || c > 6);
    return c;
}

void insert(Address* e, Address** phead, Address** plast)
{
    Address* p = *plast;
    if (*plast == NULL)
    {
        e->next = NULL;
        e->prev = NULL;
        *plast = e;
        *phead = e;
        return;
    }
    else
    {
        p->next = e;
        e->next = NULL;
        e->prev = p;
        *plast = e;
    }
}

Address* setElement()
{
    Address* temp = new Address();
    if (!temp)
    {
        cerr << "Ошибка выделения памяти памяти";
        return NULL;
    }
    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE - 1, '\n');
    cin.ignore(cin.rdbuf()->in_avail());
    cin.clear();
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

void outputList(Address** phead, Address** plast)
{
    Address* t = *phead;
    while (t)
    {
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead)
{
    Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name))
            break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
        cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast)
{
    struct Address* t = *phead;
    while (t)
    {
        if (!strcmp(name, t->name))
            break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
    {
        if (*phead == t)
        {
            *phead = t->next;
            if (*phead)
                (*phead)->prev = NULL;
            else
                *plast = NULL;
        }
        else
        {
            t->prev->next = t->next;
            if (t != *plast)
                t->next->prev = t->prev;
            else
                *plast = t->prev;
        }
        delete t;
        cout << "Элемент удален" << endl;
    }
}

void addLBegin(Address** phead, Address** plast, Address* Lhead, Address* Llast)
{
    if (Lhead == NULL)
        return;

    if (*plast == NULL)
    {
        *phead = Lhead;
        *plast = Llast;
    }
    else
    {
        Llast->next = *phead;
        (*plast)->prev = Llast;
        *phead = Lhead;
    }
}

int main(void)
{
    Address* head = NULL;
    Address* last = NULL;
    setlocale(LC_CTYPE, "Rus");

    Address* Lhead = NULL; // Additional list head
    Address* Llast = NULL; // Additional list last

        while (true)
        {
            switch (menu())
            {
            case 1:
                insert(setElement(), &head, &last);
                break;
            case 2:
            {
                char dname[NAME_SIZE];
                cout << "Введите имя: ";
                cin.getline(dname, NAME_SIZE - 1, '\n');
                cin.ignore(cin.rdbuf()->in_avail());
                cin.sync();
                delet(dname, &head, &last);
            }
            break;
            case 3:
                outputList(&head, &last);
                break;
            case 4:
            {
                char fname[NAME_SIZE];
                cout << "Введите имя: ";
                cin.getline(fname, NAME_SIZE - 1, '\n');
                cin.ignore(cin.rdbuf()->in_avail());
                cin.sync();
                find(fname, &head);
            }
            break;
            case 5:
            {
                // Create and populate the additional list L
                int numElements;
                cout << "Введите количество элементов в списке L: ";
                cin >> numElements;
                cin.ignore(cin.rdbuf()->in_avail());
                cin.clear();

                for (int i = 0; i < numElements; i++)
                {
                    cout << "Элемент " << (i + 1) << ":" << endl;
                    insert(setElement(), &Lhead, &Llast);
                }

                // Add L to the beginning of the main list
                addLBegin(&head, &last, Lhead, Llast);

                // Reset the additional list
                Lhead = NULL;
                Llast = NULL;
            }
            break;
            case 6:
                exit(0);
            default:
                exit(1);
            }
        }
    return 0;
}