#include <iostream>
using namespace std;

int menu_choice();
void menu_first();
void menu_second();
float get_num(int);
float to_base (float, int);
float to_target (float, int);
void result_output (float, float, int, int);

//1. Проверка на ввод чисел значений
//2. Перевод в мили
//3. Продолжать перевод предыдущего числа в новые величины


int main()
{
    int first_measure = 0, second_measure = 0, round = 0;
    float num1 = 0, num2 = 0;
    cout << "This is convertor of measures" << endl;
    while (1)
    {
        if ( round == 0)
        {
            menu_first();
            first_measure = menu_choice();
            if (first_measure == 6)
                break;
        }
        menu_second();
        second_measure = menu_choice();
        if (second_measure == 6)
            break;
        if ( round == 0)
            num1 = get_num(first_measure);
        num2 = to_base(num1, first_measure);
        num2 = to_target(num2, second_measure);
        result_output(num1, num2, first_measure, second_measure);
        num1 = num2;
        first_measure = second_measure;
        round++;
    }
    return 0;
}

void result_output(float num1, float num2, int first_measure, int second_measure)
{
    switch (first_measure) {
        case 1:
            cout << "\n||  " << num1 << " mm   equals   ";
            break;
        case 2:
            cout << "\n||  " << num1 << " sm   equals   ";
            break;
        case 3:
            cout << "\n||  " << num1 << " m   equals   ";
            break;
        case 4:
            cout << "\n||  " << num1 << " km   equals   ";
            break;
        case 5:
            cout << "\n||  " << num1 << " miles   equals   ";
            break;
        default:
            break;
    }
    switch (second_measure) {
        case 1:
            cout << num2 << " mm.\n" << endl;
            break;
        case 2:
            cout << num2 << " sm.\n" << endl;
            break;
        case 3:
            cout << num2 << " m.\n" << endl;
            break;
        case 4:
            cout << num2 << " km.\n" << endl;
            break;
        case 5:
            cout << num2 << " miles.\n" << endl;
            break;
        default:
            break;
    }
}

float to_base (float num1, int first_measure)
{
    switch (first_measure) {
        case 1:
            return num1;
            break;
        case 2:
            return num1*10;
            break;
        case 3:
            return num1*1000;
            break;
        case 4:
            return num1*1000000;
            break;
        case 5:
            return num1*1.609*1000000;
            break;
        default:
            break;
    }
    return num1;
}

float to_target (float num2, int second_measure)
{
    switch (second_measure) {
        case 1:
            return num2;
            break;
        case 2:
            return num2/10;
            break;
        case 3:
            return num2/1000;
            break;
        case 4:
            return num2/1000000;
            break;
        case 5:
            return num2/1000000/1.609;
            break;
        default:
            break;
    }
    return num2;;
}

float get_num (int measure)
{
    while (true)
    {
        float num;
        switch (measure) {
            case 1:
                cout << "Enter value in (mm).. ";
                cin >> num;
                break;
            case 2:
                cout << "Enter value in (sm).. ";
                cin >> num;
                break;
            case 3:
                cout << "Enter value in (m).. ";
                cin >> num;
                break;
            case 4:
                cout << "Enter value in (km).. ";
                cin >> num;
                break;
            case 5:
                cout << "Enter value in (miles).. ";
                cin >> num;
                break;
            default:
                num = 0;
                break;
        }

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100,'\n');
        }
        else
            return num;
    }
}

int menu_choice()
{
    while (true)
    {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(100,'\n');
        }
        else
            return choice;
    }
}

void menu_first()
{
    cout << "Enter type of source measure: " << endl;
    cout << "1. mm  " << endl;
    cout << "2. sm  " << endl;
    cout << "3. m  " << endl;
    cout << "4. km  " << endl;
    cout << "5. miles  " << endl;
    cout << "6. Exit " << endl;
}

void menu_second()
{
    cout << "\nEnter type of target measure: " << endl ;
    cout << "1. mm  " << endl;
    cout << "2. sm  " << endl;
    cout << "3. m  " << endl;
    cout << "4. km  " << endl;
    cout << "5. miles  " << endl;
    cout << "6. Exit " << endl;
}
