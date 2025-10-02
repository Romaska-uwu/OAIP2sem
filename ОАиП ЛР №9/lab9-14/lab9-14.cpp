#include <iostream>
#include <fstream>
using namespace std;
const unsigned int NAME_SIZE = 30;
const unsigned int CITY_SIZE = 20;

struct Address {
    char name[NAME_SIZE];
    char city[CITY_SIZE];
    Address* next;
    Address* prev;
};

int menu(void) {
    char s[80];
    int c;
    cout << endl;
    cout << "1. Ввод имени" << endl;
    cout << "2. Удаление имени" << endl;
    cout << "3. Вывод на экран" << endl;
    cout << "4. Поиск" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "7. Проверить пустоту списка" << endl;
    cout << "8. Выход" << endl;
    cout << endl;

    do {
        cout << "Ваш выбор: ";
        cin.sync();
        cin.getline(s, 80); 
        c = atoi(s); 
    } while (c < 1 || c > 8); 

    return c;
}

void insert(Address* e, Address** phead, Address** plast) {
    if (*plast == nullptr) { 
        e->next = nullptr;
        e->prev = nullptr;
        *plast = e;
        *phead = e;
    }
    else {
        (*plast)->next = e; 
        e->next = nullptr;
        e->prev = *plast;
        *plast = e;
    }
}

Address* setElement() {
    Address* temp = new Address(); 
    if (!temp) {
        cerr << "Ошибка выделения памяти" << endl;
        return nullptr;
    }

    cout << "Введите имя: ";
    cin.getline(temp->name, NAME_SIZE); 
    cin.ignore(); 

    cout << "Введите город: ";
    cin.getline(temp->city, CITY_SIZE); 

    temp->next = nullptr;
    temp->prev = nullptr;

    return temp;
}

void outputList(Address** phead, Address** plast) {
    Address* t = *phead;
    while (t != nullptr) { 
        cout << t->name << ' ' << t->city << endl;
        t = t->next;
    }
    cout << "" << endl;
}

void find(char name[NAME_SIZE], Address** phead) {
    Address* t = *phead;
    while (t != nullptr) {
        if (!strcmp(name, t->name)) {
            cout << t->name << ' ' << t->city << endl;
            return;
        }
        t = t->next;
    }
    cerr << "Имя не найдено" << endl;
}

void delet(char name[NAME_SIZE], Address** phead, Address** plast) {
    Address* t = *phead;
    while (t != nullptr) {
        if (!strcmp(name, t->name)) {
            if (*phead == t) {
                *phead = t->next;
                if (*phead != nullptr)
                    (*phead)->prev = nullptr;
                else
                    *plast = nullptr;
            }
            else {
                t->prev->next = t->next;
                if (t->next != nullptr)
                    t->next->prev = t->prev;
                else
                    *plast = t->prev;
            }
            delete t;
            cout << "Элемент удален" << endl;
            return;
        }
        t = t->next;
    }
    cerr << "Имя не найдено" << endl;
}

void writeToFile(Address** phead) {
    FILE* fp;
    errno_t err = fopen_s(&fp, "mlist", "wb");
    if (err) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    cout << "Сохранение в файл" << endl;
    Address* t = *phead;
    while (t != nullptr) {
        fwrite(t, sizeof(Address), 1, fp);
        t = t->next;
    }
    fclose(fp);
}

void readFromFile(Address** phead, Address** plast) {
    FILE* fp;
    errno_t err = fopen_s(&fp, "mlist", "rb");
    if (err) {
        cerr << "Файл не открывается" << endl;
        exit(1);
    }
    while (*phead != nullptr) { 
        *plast = (*phead)->next;
        delete* phead;
        *phead = *plast;
    }
    *phead = *plast = nullptr; 
    cout << "Загрузка из файла" << endl;
    Address* t;
    while (!feof(fp)) {
        t = new Address();
        if (!t) {
            cerr << "Ошибка выделения памяти" << endl;
            return;
        }
        if (1 != fread(t, sizeof(Address), 1, fp)) 
            break;
        insert(t, phead, plast);
    }
    fclose(fp);
}

bool returnN(Address** phead) {
    return (*phead == nullptr);
}

int main(void) {
    Address* head = nullptr; 
    Address* last = nullptr; 

    setlocale(LC_CTYPE, "Rus");

    while (true) {
        switch (menu()) {
        case 1:
            insert(setElement(), &head, &last);
            break;
        case 2: {
            char dname[NAME_SIZE];
            cout << "Введите имя: ";
            cin.getline(dname, NAME_SIZE);
            cin.ignore();
            delet(dname, &head, &last);
            break;
        }
        case 3:
            outputList(&head, &last);
            break;
            case 4: {
                char fname[NAME_SIZE];
                cout << "Введите имя: ";
                cin.getline(fname, NAME_SIZE);
                cin.ignore();
                find(fname, &head);
                break;
            }
            case 5:
                writeToFile(&head);
                break;
            case 6:
                readFromFile(&head, &last);
                break;
            case 7:
                if (returnN(&head))
                    cout << "Список пуст" << endl;
                else
                    cout << "Список не пуст" << endl;
                break;
            case 8:
                exit(0);
            default:
                exit(1);
        }
    }
    return 0;
}

