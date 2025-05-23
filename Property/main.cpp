#include "Property.h"
#include "Apartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include "Owner.h"

void clearInputBuffer();
unique_ptr<Property> createProperty();
void mainMenu(vector<unique_ptr<Owner>>& owners);

int main() {
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<unique_ptr<Owner>> owners;

    try {
        auto owner1 = make_unique<Owner>("Иванов Иван Иванович", "123456789012");
        owner1->addProperty(new Apartment(5000000, 85));
        owner1->addProperty(new Car(2000000, 90));
        owner1->addProperty(new CountryHouse(8000000, 20));
        owner1->addProperty(new Car(3500000, 180));
        owners.push_back(move(owner1));

        auto owner2 = make_unique<Owner>("Петров Петр Петрович", "987654321098");
        owner2->addProperty(new Apartment(7500000, 120));
        owner2->addProperty(new Car(5000000, 250));
        owner2->addProperty(new CountryHouse(12000000, 50));
        owner2->addProperty(new Apartment(3000000, 60));
        owners.push_back(move(owner2));

        auto owner3 = make_unique<Owner>("Сидорова Анна Михайловна", "456123789045");
        owner3->addProperty(new Apartment(4000000, 75));
        owner3->addProperty(new Car(1500000, 85));
        owner3->addProperty(new CountryHouse(6000000, 15));
        owner3->addProperty(new Car(2800000, 150));
        owners.push_back(move(owner3));

    }
    catch (const exception& e) {
        cerr << "Ошибка при создании тестовых данных: " << e.what() << endl;
        return 1;
    }

    mainMenu(owners);

    return 0;
}


void clearInputBuffer() {
    cin.clear();
    cin.ignore(32768, '\n');
    system("cls");
}

unique_ptr<Property> createProperty() {
    cout << "\nВыберите тип имущества:\n";
    cout << "1. Квартира\n";
    cout << "2. Автомобиль\n";
    cout << "3. Загородный дом\n";
    cout << "Выбор: ";

    int choice;
    cin >> choice;
    clearInputBuffer();

    unsigned int worth;
    cout << "Введите стоимость имущества: ";
    cin >> worth;
    clearInputBuffer();

    try {
        switch (choice) {
        case 1: {
            double square;
            cout << "Введите площадь квартиры (кв.м): ";
            cin >> square;
            clearInputBuffer();
            return make_unique<Apartment>(worth, square);
        }
        case 2: {
            double horsepower;
            cout << "Введите мощность автомобиля (л.с.): ";
            cin >> horsepower;
            clearInputBuffer();
            return make_unique<Car>(worth, horsepower);
        }
        case 3: {
            unsigned int distance;
            cout << "Введите расстояние от города (км): ";
            cin >> distance;
            clearInputBuffer();
            return make_unique<CountryHouse>(worth, distance);
        }
        default:
            throw invalid_argument("Неверный тип имущества");
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return nullptr;
    }
}

void mainMenu(vector<unique_ptr<Owner>>& owners) {
    while (true) {
        cout << "\n=== ГЛАВНОЕ МЕНЮ ===\n";
        cout << "1. Просмотреть всех собственников\n";
        cout << "2. Добавить собственника\n";
        cout << "3. Удалить собственника\n";
        cout << "4. Работа с имуществом собственника\n";
        cout << "5. Выход\n";
        cout << "Выбор: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            if (owners.empty()) {
                cout << "Список собственников пуст.\n";
                break;
            }

            cout << "СПИСОК СОБСТВЕННИКОВ:\n";
            for (size_t i = 0; i < owners.size(); ++i) {
                cout << i + 1 << ". " << owners[i]->getFullname()
                    << " (ИНН: " << owners[i]->getINN() << ")\n";
                cout << "   Налог на имущество: " << fixed << setprecision(2)
                    << owners[i]->calculateTotalPropertyTax() << " руб.\n";
                cout << "   Подоходный налог: " << owners[i]->calculateTotalIncomeTax() << " руб.\n";
            }
            break;
        }
        case 2: {
            string name, inn;
            cout << "Введите ФИО собственника: ";
            getline(cin, name);
            cout << "Введите ИНН (12 цифр): ";
            getline(cin, inn);

            try {
                owners.push_back(make_unique<Owner>(name, inn));
                cout << "Собственник успешно добавлен.\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            if (owners.empty()) {
                cout << "Список собственников пуст.\n";
                break;
            }

            cout << "Введите номер собственника для удаления: ";
            size_t index;
            cin >> index;
            clearInputBuffer();

            if (index > 0 && index <= owners.size()) {
                owners.erase(owners.begin() + index - 1);
                cout << "Собственник удален.\n";
            }
            else {
                cout << "Неверный номер собственника.\n";
            }
            break;
        }
        case 4: {
            if (owners.empty()) {
                cout << "Список собственников пуст.\n";
                break;
            }

            cout << "Введите номер собственника: ";
            size_t ownerIndex;
            cin >> ownerIndex;
            clearInputBuffer();

            if (ownerIndex > 0 && ownerIndex <= owners.size()) {
                auto& owner = owners[ownerIndex - 1];

                while (true) {
                    cout << "Собственник: " << owner->getFullname() << "\n";
                    cout << "1. Просмотреть имущество\n";
                    cout << "2. Добавить имущество\n";
                    cout << "3. Удалить имущество\n";
                    cout << "4. Назад\n";
                    cout << "Выбор: ";

                    int propChoice;
                    cin >> propChoice;
                    clearInputBuffer();

                    if (propChoice == 4) break;

                    switch (propChoice) {
                    case 1: {
                        const auto& properties = owner->getProperties();
                        if (properties.empty()) {
                            cout << "У собственника нет имущества.\n";
                            break;
                        }

                        cout << "\nИмущество собственника:\n";
                        for (size_t i = 0; i < properties.size(); ++i) {
                            cout << i + 1 << ". ";
                            if (dynamic_cast<Apartment*>(properties[i])) {
                                auto apt = dynamic_cast<Apartment*>(properties[i]);
                                cout << "Квартира: " << apt->getSquare() << " кв.м, ";
                            }
                            else if (dynamic_cast<Car*>(properties[i])) {
                                auto car = dynamic_cast<Car*>(properties[i]);
                                cout << "Автомобиль: " << car->getHorsepower() << " л.с., ";
                            }
                            else if (dynamic_cast<CountryHouse*>(properties[i])) {
                                auto house = dynamic_cast<CountryHouse*>(properties[i]);
                                cout << "Дом: " << house->getDistanceFromCity() << " км от города, ";
                            }
                            cout << "стоимость: " << properties[i]->getWorth() << " руб.\n";
                            cout << "   Налог: " << fixed << setprecision(2)
                                << properties[i]->calculateTax() << " руб.\n";
                        }
                        break;
                    }
                    case 2: {
                        auto newProperty = createProperty();
                        if (newProperty) {
                            owner->addProperty(newProperty.get());
                            newProperty.release();
                            cout << "Имущество добавлено.\n";
                        }
                        break;
                    }
                    case 3: {
                        const auto& properties = owner->getProperties();
                        if (properties.empty()) {
                            cout << "У собственника нет имущества для удаления.\n";
                            break;
                        }

                        cout << "Введите номер имущества для удаления: ";
                        size_t propIndex;
                        cin >> propIndex;
                        clearInputBuffer();

                        if (propIndex > 0 && propIndex <= properties.size()) {
                            auto prop = properties[propIndex - 1];
                            if (owner->removeProperty(prop)) {
                                delete prop;
                                cout << "Имущество удалено.\n";
                            }
                            else {
                                cout << "Ошибка при удалении имущества.\n";
                            }
                        }
                        else {
                            cout << "Неверный номер имущества.\n";
                        }
                        break;
                    }
                    default:
                        cout << "Неверный выбор.\n";
                    }
                }
            }
            else {
                cout << "Неверный номер собственника.\n";
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }
}