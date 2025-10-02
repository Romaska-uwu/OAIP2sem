#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Sanatorium {
    string name;
    string location;
    string profile;
    int numTickets;
};

bool compareByProfileAndName(const Sanatorium& san1, const Sanatorium& san2) {
    if (san1.profile == san2.profile) {
        return san1.name < san2.name;
    }
    return san1.profile < san2.profile;
}

int main() {
    setlocale(LC_CTYPE, "Rus");
    const int numSanatoriums = 5;
    vector<Sanatorium> sanatoriums(numSanatoriums);

    cout << "Введите информацию о санаториях:\n";
    for (int i = 0; i < numSanatoriums; ++i) {
        cout << "Санаторий " << i + 1 << ":\n";
        cout << "Название: ";
        cin >> sanatoriums[i].name;
        cout << "Местоположение: ";
        cin >> sanatoriums[i].location;
        cout << "Лечебный профиль: ";
        cin >> sanatoriums[i].profile;
        cout << "Количество путевок: ";
        cin >> sanatoriums[i].numTickets;
    }

    sort(sanatoriums.begin(), sanatoriums.end(), compareByProfileAndName);

    string inputProfile;
    cout << "\nВведите лечебный профиль для поиска: ";
    cin >> inputProfile;

    bool found = false;
    cout << "\nРезультаты поиска для лечебного профиля " << inputProfile << ":\n";
    for (const Sanatorium& san : sanatoriums) {
        if (san.profile == inputProfile) {
            found = true;
            cout << "Название: " << san.name << "\n";
            cout << "Местоположение: " << san.location << "\n";
            cout << "Количество путевок: " << san.numTickets << "\n\n";
        }
    }

    if (!found) {
        cout << "Нет данных о санаториях с указанным лечебным профилем.\n";
    }

    return 0;
}