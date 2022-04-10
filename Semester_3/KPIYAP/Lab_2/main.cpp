#include <iostream>

using namespace std;


//  Сделать меню (использовать динамический массив)
// 1. Добавить новый элемент 2. Показать все элементы 3. Задать пробег 4. Фильтр по пробегу ( показать элементы с пробегом от до)


class Cars {
private:
    string id;
    string ownerName;
    float mileage;
public:
    Cars() {
        id = "0";
        ownerName = "Not entered";
        mileage = 0;
    }

    Cars(string id_numb, string ownerName, float mileage) {
        id = id_numb;
        this->ownerName = ownerName;
        this->mileage = mileage;
    }
    ~Cars() {}

    friend void output(Cars info);
    friend class Sto;
};

void output(Cars info) {
    cout << info.id << ". "<< info.ownerName << ". "<< info.mileage << "\n\n";
}

int check(string name) {
    for (int i = 0; i < sizeof(name); i++) {
        if (!(islower(name[i])) && !(isupper(name[i]))) {
            if (name[i] != '-' && name[i] != ' ')
            {
                return 0;
            }
            else
            if (i != 0) {
                if (name[i - 1] == ' ' || name[i - 1] == '-') {
                    return 0;
                }
            }
            else
                return 0;
        }
    }
    return 1;
}

float input_float();

class Sto{
public:
    Cars car;
    void setName() {
        do {
            cout << "Input car's owner name: ";
            rewind(stdin);
            getline(cin, car.ownerName);
        } while (check(car.ownerName));

        cout << "Input id: ";
        rewind(stdin);
        getline(cin, car.id);
    }
    void setMileage() {
        cout << "Input mileage: ";
        car.mileage = input_float();
        while (car.mileage < 0)
        {
            cout << "error!\ninput again: ";
            car.mileage = input_float();
        }
        cout << "\n";
    }
    void copy(Cars original) {
        car.ownerName = original.ownerName;
        car.id = original.id;
        car.mileage = original.mileage;
    }
    int compare(string search=".") {
        if (car.ownerName==search || car.id == search)
            return 1;
        else
            return 0;
    }
    
    int mileageCompare(int min_mileage, int max_mileage) {
        if (car.mileage > min_mileage && car.mileage < max_mileage)
            return 1;
        else
            return 0;
    }
};

void menu() {
    cout << "1. Add notes\n2. Show cars\n3. Set mileage\n4. Show filtered by mileage\n5. Exit\n";
}

int input_integer() {
    while (true) {
        int number;
        cin >> number;
        if (cin.fail())
        {
            cout << "error!\n";
            cin.clear();
            cin.ignore(32767, '\n');
        }
        else
            return number;

    }
}

float input_float() {
    while (true) {
        float number;
        cin >> number;
        if (cin.fail())
        {
            cout << "error!\n";
            cin.clear();
            cin.ignore(32767, '\n');
        }
        else
            return number;

    }
}

int main()
{
    Sto* origin, *temp2;
    int action = 5, amount = 0;
    origin = nullptr;
    string search;

    do {
        menu();
        cout << "Choose menu option: ";
        action = input_integer();
        while (action < 1 || action>5) {
            cout << "Error!\n";
            action = input_integer();
        }
        
        
        switch (action) {
            case 1:
                int option;
                do {
                    if (origin == nullptr) {
                        origin = new Sto[1];
                        origin[0].setName();
                        amount += 1;
                    }
                    else {
                        amount += 1;
                        temp2 = new Sto[amount];
                        int k;
                        for (k = 0; k < amount - 1; k++) {
                            temp2[k].copy(origin[k].car);
                        }
                        temp2[k].setName();
                        delete[] origin;
                        origin = new Sto[amount];
                        for (k = 0; k < amount; k++) {
                            origin[k].copy(temp2[k].car);
                        }
                        delete[] temp2;
                    }
                    cout << "If you want to add more notes, press 1, else 0: ";
                    option = input_integer();
                } while (option);
                break;



            case 2:
                if (origin != nullptr) {
                    for (int k = 0; k < amount; k++) {
                        output(origin[k].car);
                    }
                }
                else {
                    cout << "Create first note.\n";
                }
                break;

            case 3:
                if (origin != nullptr) {
                    cout << "Input car's id or owner name to set car's mileage: ";
                    rewind(stdin);
                    getline(cin, search);
                    for (int k = 0; k < amount; k++) {
                        if (origin[k].compare(search)) {
                            origin[k].setMileage();
                            break;
                        }
                    }
                }
                else{
                    cout << "Create note.\n";
                }
                break;
            case 4:
                if (origin != nullptr) {
                    float min_mileage, max_mileage;
                    cout << "Input minimal mileage: ";
                    min_mileage = input_float();
                    while (min_mileage < 0)
                    {
                        cout << "error!\ninput again: ";
                        min_mileage = input_float();
                    }
                    
                    cout << "Input max mileage: ";
                    max_mileage = input_float();
                    while (max_mileage < min_mileage)
                    {
                        cout << "error!\ninput again: ";
                        max_mileage = input_float();
                    }
                    
                    
                    for (int k = 0; k < amount; k++) {
                        if (origin[k].mileageCompare(int(min_mileage), int(max_mileage)) == 1)
                            output(origin[k].car);
                    }
                }
                else {
                    cout << "Create note.\n";
                }
                break;
            case 5:
                cout << "Exit...\n";
                delete[] origin;
                return 0;
                break;
            default:
                cout << "Error! No function under this number\n";
                break;
        }
    } while (action != 5);
    return 0;
}


