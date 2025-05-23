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
        auto owner1 = make_unique<Owner>("������ ���� ��������", "123456789012");
        owner1->addProperty(new Apartment(5000000, 85));
        owner1->addProperty(new Car(2000000, 90));
        owner1->addProperty(new CountryHouse(8000000, 20));
        owner1->addProperty(new Car(3500000, 180));
        owners.push_back(move(owner1));

        auto owner2 = make_unique<Owner>("������ ���� ��������", "987654321098");
        owner2->addProperty(new Apartment(7500000, 120));
        owner2->addProperty(new Car(5000000, 250));
        owner2->addProperty(new CountryHouse(12000000, 50));
        owner2->addProperty(new Apartment(3000000, 60));
        owners.push_back(move(owner2));

        auto owner3 = make_unique<Owner>("�������� ���� ����������", "456123789045");
        owner3->addProperty(new Apartment(4000000, 75));
        owner3->addProperty(new Car(1500000, 85));
        owner3->addProperty(new CountryHouse(6000000, 15));
        owner3->addProperty(new Car(2800000, 150));
        owners.push_back(move(owner3));

    }
    catch (const exception& e) {
        cerr << "������ ��� �������� �������� ������: " << e.what() << endl;
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
    cout << "\n�������� ��� ���������:\n";
    cout << "1. ��������\n";
    cout << "2. ����������\n";
    cout << "3. ���������� ���\n";
    cout << "�����: ";

    int choice;
    cin >> choice;
    clearInputBuffer();

    unsigned int worth;
    cout << "������� ��������� ���������: ";
    cin >> worth;
    clearInputBuffer();

    try {
        switch (choice) {
        case 1: {
            double square;
            cout << "������� ������� �������� (��.�): ";
            cin >> square;
            clearInputBuffer();
            return make_unique<Apartment>(worth, square);
        }
        case 2: {
            double horsepower;
            cout << "������� �������� ���������� (�.�.): ";
            cin >> horsepower;
            clearInputBuffer();
            return make_unique<Car>(worth, horsepower);
        }
        case 3: {
            unsigned int distance;
            cout << "������� ���������� �� ������ (��): ";
            cin >> distance;
            clearInputBuffer();
            return make_unique<CountryHouse>(worth, distance);
        }
        default:
            throw invalid_argument("�������� ��� ���������");
        }
    }
    catch (const exception& e) {
        cout << "������: " << e.what() << endl;
        return nullptr;
    }
}

void mainMenu(vector<unique_ptr<Owner>>& owners) {
    while (true) {
        cout << "\n=== ������� ���� ===\n";
        cout << "1. ����������� ���� �������������\n";
        cout << "2. �������� ������������\n";
        cout << "3. ������� ������������\n";
        cout << "4. ������ � ���������� ������������\n";
        cout << "5. �����\n";
        cout << "�����: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            if (owners.empty()) {
                cout << "������ ������������� ����.\n";
                break;
            }

            cout << "������ �������������:\n";
            for (size_t i = 0; i < owners.size(); ++i) {
                cout << i + 1 << ". " << owners[i]->getFullname()
                    << " (���: " << owners[i]->getINN() << ")\n";
                cout << "   ����� �� ���������: " << fixed << setprecision(2)
                    << owners[i]->calculateTotalPropertyTax() << " ���.\n";
                cout << "   ���������� �����: " << owners[i]->calculateTotalIncomeTax() << " ���.\n";
            }
            break;
        }
        case 2: {
            string name, inn;
            cout << "������� ��� ������������: ";
            getline(cin, name);
            cout << "������� ��� (12 ����): ";
            getline(cin, inn);

            try {
                owners.push_back(make_unique<Owner>(name, inn));
                cout << "����������� ������� ��������.\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            if (owners.empty()) {
                cout << "������ ������������� ����.\n";
                break;
            }

            cout << "������� ����� ������������ ��� ��������: ";
            size_t index;
            cin >> index;
            clearInputBuffer();

            if (index > 0 && index <= owners.size()) {
                owners.erase(owners.begin() + index - 1);
                cout << "����������� ������.\n";
            }
            else {
                cout << "�������� ����� ������������.\n";
            }
            break;
        }
        case 4: {
            if (owners.empty()) {
                cout << "������ ������������� ����.\n";
                break;
            }

            cout << "������� ����� ������������: ";
            size_t ownerIndex;
            cin >> ownerIndex;
            clearInputBuffer();

            if (ownerIndex > 0 && ownerIndex <= owners.size()) {
                auto& owner = owners[ownerIndex - 1];

                while (true) {
                    cout << "�����������: " << owner->getFullname() << "\n";
                    cout << "1. ����������� ���������\n";
                    cout << "2. �������� ���������\n";
                    cout << "3. ������� ���������\n";
                    cout << "4. �����\n";
                    cout << "�����: ";

                    int propChoice;
                    cin >> propChoice;
                    clearInputBuffer();

                    if (propChoice == 4) break;

                    switch (propChoice) {
                    case 1: {
                        const auto& properties = owner->getProperties();
                        if (properties.empty()) {
                            cout << "� ������������ ��� ���������.\n";
                            break;
                        }

                        cout << "\n��������� ������������:\n";
                        for (size_t i = 0; i < properties.size(); ++i) {
                            cout << i + 1 << ". ";
                            if (dynamic_cast<Apartment*>(properties[i])) {
                                auto apt = dynamic_cast<Apartment*>(properties[i]);
                                cout << "��������: " << apt->getSquare() << " ��.�, ";
                            }
                            else if (dynamic_cast<Car*>(properties[i])) {
                                auto car = dynamic_cast<Car*>(properties[i]);
                                cout << "����������: " << car->getHorsepower() << " �.�., ";
                            }
                            else if (dynamic_cast<CountryHouse*>(properties[i])) {
                                auto house = dynamic_cast<CountryHouse*>(properties[i]);
                                cout << "���: " << house->getDistanceFromCity() << " �� �� ������, ";
                            }
                            cout << "���������: " << properties[i]->getWorth() << " ���.\n";
                            cout << "   �����: " << fixed << setprecision(2)
                                << properties[i]->calculateTax() << " ���.\n";
                        }
                        break;
                    }
                    case 2: {
                        auto newProperty = createProperty();
                        if (newProperty) {
                            owner->addProperty(newProperty.get());
                            newProperty.release();
                            cout << "��������� ���������.\n";
                        }
                        break;
                    }
                    case 3: {
                        const auto& properties = owner->getProperties();
                        if (properties.empty()) {
                            cout << "� ������������ ��� ��������� ��� ��������.\n";
                            break;
                        }

                        cout << "������� ����� ��������� ��� ��������: ";
                        size_t propIndex;
                        cin >> propIndex;
                        clearInputBuffer();

                        if (propIndex > 0 && propIndex <= properties.size()) {
                            auto prop = properties[propIndex - 1];
                            if (owner->removeProperty(prop)) {
                                delete prop;
                                cout << "��������� �������.\n";
                            }
                            else {
                                cout << "������ ��� �������� ���������.\n";
                            }
                        }
                        else {
                            cout << "�������� ����� ���������.\n";
                        }
                        break;
                    }
                    default:
                        cout << "�������� �����.\n";
                    }
                }
            }
            else {
                cout << "�������� ����� ������������.\n";
            }
            break;
        }
        case 5:
            return;
        default:
            cout << "�������� �����. ���������� �����.\n";
        }
    }
}