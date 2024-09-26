#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура для хранения данных об оборудовании
struct Equipment {
    int id;
    string name;
    string manufacturer;
    double price;
    int quantity;
};

// Функция для чтения данных из файла в динамический массив
int loadData(Equipment*& equipment) {
    ifstream inFile("equipment.txt");
    if (!inFile) {
        cout << "File not found!" << endl;
        return 0;
    }

    int count = 0;
    while (!inFile.eof()) {
        Equipment temp;
        inFile >> temp.id >> temp.name >> temp.manufacturer >> temp.price >> temp.quantity;
        if (inFile) {
            Equipment* newEquipment = new Equipment[count + 1];
            for (int i = 0; i < count; i++) {
                newEquipment[i] = equipment[i];
            }
            newEquipment[count] = temp;
            delete[] equipment;
            equipment = newEquipment;
            count++;
        }
    }
    inFile.close();
    return count;
}

// Функция для отображения данных
void viewData(Equipment* equipment, int count) {
    for (int i = 0; i < count; i++) {
        cout << "ID: " << equipment[i].id << endl;
        cout << "Name: " << equipment[i].name << endl;
        cout << "Manufacturer: " << equipment[i].manufacturer << endl;
        cout << "Price: " << equipment[i].price << endl;
        cout << "Quantity: " << equipment[i].quantity << endl;
        cout << "-------------------------------" << endl;
    }
}

// Функция для редактирования данных
void editRecord(Equipment* equipment, int count) {
    int id;
    cout << "Enter the ID of the equipment you want to edit: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (equipment[i].id == id) {
            cout << "Editing record with ID: " << id << endl;
            cout << "Enter new name: ";
            cin >> equipment[i].name;
            cout << "Enter new manufacturer: ";
            cin >> equipment[i].manufacturer;
            cout << "Enter new price: ";
            cin >> equipment[i].price;
            cout << "Enter new quantity: ";
            cin >> equipment[i].quantity;
            return;
        }
    }
    cout << "No record found with ID: " << id << endl;
}

// Функция для вычисления общей стоимости оборудования
void calculateTotalValue(Equipment* equipment, int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += equipment[i].price * equipment[i].quantity;
    }
    cout << "Total value of all equipment: " << total << endl;
}

// Функция для сохранения данных в новый файл
void saveToFile(Equipment* equipment, int count) {
    string filename;
    cout << "Enter the name of the file to save the data: ";
    cin >> filename;

    ofstream outFile(filename);
    for (int i = 0; i < count; i++) {
        outFile << equipment[i].id << " " 
                << equipment[i].name << " " 
                << equipment[i].manufacturer << " " 
                << equipment[i].price << " " 
                << equipment[i].quantity << endl;
    }
    outFile.close();
    cout << "Data saved to " << filename << endl;
}

int main() {
    Equipment* equipment = nullptr;
    int count = loadData(equipment);

    int choice;
    do {
        cout << "1. View data\n";
        cout << "2. Edit data\n";
        cout << "3. Calculate total value\n";
        cout << "4. Save data to new file\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewData(equipment, count);
                break;
            case 2:
                editRecord(equipment, count);
                break;
            case 3:
                calculateTotalValue(equipment, count);
                break;
            case 4:
                saveToFile(equipment, count);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    delete[] equipment;
    return 0;
}
