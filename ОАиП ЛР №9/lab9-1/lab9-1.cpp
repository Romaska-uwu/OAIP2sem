#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address {
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address* next;
    Address* prev;
};

int menu(void);
void insert(Address* e, Address** phead, Address** plast);
Address* setElement();
void outputList(Address** phead, Address** plast);
void find(char name[NAME_SIZE], Address** phead);
void delet(char name[NAME_SIZE], Address** phead, Address** plast);
void writeToFile(Address** phead);
void readFromFile(Address** phead, Address** plast);
void deleteDouble(Address** phead, Address** plast);

int main(void) {
    Address* head = nullptr;
    Address* last = nullptr;
    setlocale(LC_CTYPE, "Rus");

    readFromFile(&head, &last);

    while (true) {
        switch (menu()) {
        case 1:
            insert(setElement(), &head, &last);
            deleteDouble(&head, &last);
            break;
        case 2: {
            char dname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(dname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            delet(dname, &head, &last);
            break;
        }
        case 3:
            outputList(&head, &last);
            break;
        case 4: {
            char fname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(fname, NAME_SIZE - 1, '\n');
            cin.ignore(cin.rdbuf()->in_avail());
            cin.sync();
            find(fname, &head);
            break;
        }
        case 5:
            writeToFile(&head);
            exit(0);
        default:
            exit(1);
        }
    }

    return 0;
}

int menu(void) {
    char s[80];
    int c;
    cout << endl;
    cout << "1. Ввод имени" << endl;
    cout << "2. Удаление имени" << endl;
    cout << "3. Вывод на экран" << endl;
    cout << "4. Поиск" << endl;
    cout << "5. Сохранить в файл и выйти" << endl;
    cout << endl;
    do {
        cout << "Ваш выбор: ";
        cin.sync();
        cin.getline(s, 80);
        cout << endl;
        c = atoi(s);
    } while (c < 0 || c > 5);
    return c;
}

void insert(Address* e, Address** phead, Address** plast) {
    Address* p = *plast;
    if (*plast == nullptr) {
        e->next = nullptr;
        e->prev = nullptr;
        *plast = e;
        *phead = e;
        return;
    }
    else {
        p->next = e;
        e->next = nullptr;
        e->prev = p;
        *plast = e;
    }
}

Address* setElement() {
    Address* temp = new Address();
    if (!temp) {
        cerr << "Ошибка выделения памяти памяти";
        return nullptr;
    }
    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE - 1, '\n');
    cin.clear();
    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE - 1, '\n');
    cin.clear();
    temp->next = nullptr;
    temp->prev = nullptr;
    return temp;
}

void outputList(Address** phead, Address** plast) {
    Address* t = *phead;
    while (t) {
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead) {
    Address* t = *phead;
    while (t) {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else
        cout << t->name << ' ' << t->city << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast) {
    Address* t = *phead;
    while (t) {
        if (!strcmp(name, t->name)) break;
        t = t->next;
    }
    if (!t)
        cerr << "Имя не найдено" << endl;
    else {
        if (*phead == t) {
            *phead = t->next;
            if (*phead)
                (*phead)->prev = nullptr;
            else
                *plast = nullptr;
        }
        else {
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

void writeToFile(Address** phead) {
    Address* t = *phead;
    ofstream file("mlist", ios::binary);
    if (!file) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    cout << "Сохранение в файл" << endl;
    while (t) {
        file.write(reinterpret_cast<char*>(t), sizeof(Address));
        t = t->next;
    }
    file.close();
}

void readFromFile(Address** phead, Address** plast) {
    ifstream file("mlist", ios::binary);
    if (!file) {
        cerr << "Файл не открывается" << endl;
        return;
    }
    cout << "Загрузка из файла" << endl;
    while (true) {
        Address* t = new Address();
        if (!file.read(reinterpret_cast<char*>(t), sizeof(Address))) {
            delete t;
            break;
        }
        insert(t, phead, plast);
    }
    file.close();
}

void deleteDouble(Address** phead, Address** plast) {
    Address* current = *phead;
    while (current != nullptr) {
        Address* runner = current->next;
        while (runner != nullptr) {
            if (strcmp(current->name, runner->name) == 0 || strcmp(current->city, runner->city) == 0) {
                Address* temp = runner;
                runner = runner->next;
                if (temp->prev)
                    temp->prev->next = temp->next;
                if (temp->next)
                    temp->next->prev = temp->prev;
                if (temp == *phead)
                    *phead = temp->next;
                if (temp == *plast)
                    *plast = temp->prev;
                delete temp;
            }
            else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

