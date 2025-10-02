#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Train {
    string destination;
    int trainNumber;
    string departureTime;
};

bool compareByDestination(const Train& train1, const Train& train2) {
    return train1.destination < train2.destination;
}

int main() {
    setlocale(LC_CTYPE, "Rus");
    const int numTrains = 8;
    Train trains[numTrains];

    cout << "Введите информацию о поездах:\n";
    for (int i = 0; i < numTrains; ++i) {
        cout << "Поезд " << i + 1 << ":\n";
        cout << "Название пункта назначения: ";
        cin >> trains[i].destination;
        cout << "Номер поезда: ";
        cin >> trains[i].trainNumber;
        cout << "Время отправления: ";
        cin >> trains[i].departureTime;
    }

    sort(trains, trains + numTrains, compareByDestination);

    string inputTime;
    cout << "\nВведите время отправления для фильтрации: ";
    cin >> inputTime;

    bool found = false;
    cout << "\nПоезда, отправляющиеся после " << inputTime << ":\n";
    for (const Train& train : trains) {
        if (train.departureTime > inputTime) {
            found = true;
            cout << "Пункт назначения: " << train.destination << "\n";
            cout << "Номер поезда: " << train.trainNumber << "\n";
            cout << "Время отправления: " << train.departureTime << "\n\n";
        }
    }

    if (!found) {
        cout << "Нет поездов, отправляющихся после указанного времени.\n";
    }

    return 0;
}