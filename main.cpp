#include <iostream>

using namespace std;

struct fridge {
    int milk;
    int meat;
    int cheese;
    int apples;
};

int main() {
    fridge indesit;

    cout << "Put food in fridge:" << endl;
    cout << "Milk" << endl;
    cin >> indesit.milk;
    cout << "Meat" << endl;
    cin >> indesit.meat;
    cout << "Cheese" << endl;
    cin >> indesit.cheese;
    cout << "Apples" << endl;
    cin >> indesit.apples;
    cout << endl;

    cout << "Take food from fridge:" << endl;
    int n;
    cout << "Milk" << endl;
    cin >> n;
    indesit.milk -= n;
    cout << "Meat" << endl;
    cin >> n;
    indesit.meat -= n;
    cout << "Cheese" << endl;
    cin >> n;
    indesit.cheese -= n;
    cout << "Apples" << endl;
    cin >> n;
    indesit.apples -= n;
    cout << endl;

    cout << "Fridge status:" << endl;
    cout << "Milk: " << indesit.milk << endl;
    cout << "Meat: " << indesit.meat << endl;
    cout << "Cheese: " << indesit.cheese << endl;
    cout << "Apples: " << indesit.apples << endl;

//    cout << "Fridge status:" << endl;
//    cout << "Milk: " << indesit.milk << endl;
//    cout << "Meat: " << indesit.meat << endl;
//    cout << "Cheese: " << indesit.cheese << endl;
//    cout << "Apples: " << indesit.apples << endl;
    return 0;
}
