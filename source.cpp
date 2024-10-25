#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class House {
protected:
    double area;
    int floors;
    string address;
    string owner;

public:
    House(double area, int floors, const string& address, const string& owner)
        : area(area), floors(floors), address(address), owner(owner) {}

    virtual unique_ptr<House> clone() const = 0;

    virtual void display() const {
        cout << "Address: " << address << "\n"
            << "Area: " << area << " sqm\n"
            << "Floors: " << floors << "\n"
            << "Owner: " << owner << "\n";
    }

    virtual void edit() {
        cout << "Enter new address: ";
        getline(cin, address);
        cout << "Enter new area: ";
        cin >> area;
        cout << "Enter number of floors: ";
        cin >> floors;
        cin.ignore(); 
        cout << "Enter new owner's name: ";
        getline(cin, owner);
    }

    virtual ~House() = default;
};

class ApartmentBuilding : public House {
private:
    int apartments;

public:
    ApartmentBuilding(double area, int floors, const string& address, const string& owner, int apartments)
        : House(area, floors, address, owner), apartments(apartments) {}

    unique_ptr<House> clone() const override {
        return make_unique<ApartmentBuilding>(*this);
    }

    void display() const override {
        House::display();
        cout << "Apartments: " << apartments << "\n";
    }

    void edit() override {
        House::edit();
        cout << "Enter new number of apartments: ";
        cin >> apartments;
        cin.ignore(); 
    }
};

class Cottage : public House {
public:
    Cottage(double area, int floors, const string& address, const string& owner)
        : House(area, floors, address, owner) {}

    unique_ptr<House> clone() const override {
        return make_unique<Cottage>(*this);
    }
};

class HouseManager {
private:
    vector<unique_ptr<House>> houses;

public:
    void addHouse(const House& house) {
        houses.push_back(house.clone());
    }

    void displayHouses() const {
        if (houses.empty()) {
            cout << "No houses available.\n";
        }
        else {
            for (size_t i = 0; i < houses.size(); ++i) {
                cout << "House #" << i + 1 << ":\n";
                houses[i]->display();
                cout << "-------------------------\n";
            }
        }
    }

    void editHouse(size_t index) {
        if (index < houses.size()) {
            houses[index]->edit();
        }
        else {
            cout << "Invalid index!\n";
        }
    }
};

int main() {
    HouseManager manager;
    ApartmentBuilding apt1(300.0, 5, "123 Main St", "John Doe", 10);
    Cottage cot1(120.0, 2, "456 Oak St", "Jane Smith");
    manager.addHouse(apt1);
    manager.addHouse(cot1);
    cout << "All Houses:\n";
    manager.displayHouses();
    cout << "\nEditing house #1:\n";
    manager.editHouse(0);
    cout << "\nAll Houses after editing:\n";
    manager.displayHouses();
    return 0;
}
