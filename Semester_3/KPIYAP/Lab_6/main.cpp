#include <iostream>
using namespace std;

class Product {
public:

    Product(int ID = 0, string Name = "Name not entered", double Price = 0.0): ID(ID), Name(Name), Price(Price){
    }
    virtual int getId() const {
        return ID;
    }
    void setId(int id) {
        ID = id;
    }
    virtual const string &getName() const {
        return Name;
    }
    void setName(const string &name) {
        Name = name;
    }
    virtual double getPrice() const {
        return Price;
    }
    void setPrice(double price) {
        Product::Price = price;
    }

    virtual int getAmount() const {
    }

    virtual double getWeight() const {
    }


    virtual void output() = 0;
    virtual void input(int ) = 0;
    virtual const double finalPrice() = 0;



    virtual ~Product()= default;

protected:
    int ID;
    double Price;
    string Name;
};

const double Product::finalPrice() {
    return Price*ID;
}
void Product::output() {
    cout << "ID: " << ID << endl << "Name: " << Name << endl << "Price: " << Price;
}
void Product::input(int) {
    cout << "Enter your data";
}



class NonElectricProduct: virtual public Product{
private:
    string NonElectricProductInfo = "Non Electric Product";
public:

    NonElectricProduct(int ID, string Name, double Price, int Amount = 0)
            : Product(ID, Name, Price), Amount(Amount){

    }

    const string &getNonElectricProductInfo() const {
        return NonElectricProductInfo;
    }
    void setNonElectricProductInfo(const string &nonElectricProductInfo) {
        NonElectricProductInfo = nonElectricProductInfo;
    }
    virtual int getAmount() const {
        return Amount;
    }
    void setAmount(int amount) {
        Amount = amount;
    }

    virtual void output() override{
        Product::output();
        cout << endl << "= = = = = ="
             << endl << NonElectricProductInfo
             << endl
             << "Amount: " << Amount
             << endl;
    }
    const double finalPrice(){
        return Price*Amount;
    }

    virtual ~NonElectricProduct() = default;

protected:
    int Amount;
};

class ElectricProduct: virtual public Product{
private:
    string ElectricProductInfo = "Electric Product";
public:

    ElectricProduct(int ID, string Name, double Price, double Voltage = 220)
            :  Product(ID, Name, Price), Voltage(Voltage){

    }

    const string &getElectricProductInfo() const {
        return ElectricProductInfo;
    }
    void setElectricProductInfo(const string &electricProductInfo) {
        ElectricProductInfo = electricProductInfo;
    }
    double getVoltage() const {
        return Voltage;
    }
    void setVoltage(double voltage) {
        Voltage = voltage;
    }

    virtual const double finalPrice() override{
        return Product::finalPrice();
    }
    virtual void output() override {
        Product::output();
        cout << endl << "= = = = = ="
             << endl << ElectricProductInfo
             << endl
             << "Voltage: " << Voltage
             <<  endl << "Final price: " << finalPrice();;
    }


    virtual ~ElectricProduct() = default;

protected:
    double Voltage;
};

class Table: virtual public NonElectricProduct{
public:
    Table(int ID = 0, string Name = "Not entered", double Price = 0.0, int Amount = 1, double Weight = 10.0)
            : Product(ID, Name, Price),
              NonElectricProduct(ID, Name, Price, Amount), Weight(Weight){

    }

    virtual void input (int index) override{
        ID = index;
        cout << endl << "ID = " << ID;
        cout << endl << "Enter Product name: ";
        cin >> Name;
        cout << "Enter Product price: ";
        cin >> Price;
        cout << "Enter amount: ";
        cin >> Amount;
        cout << "Enter weight: ";
        cin >> Weight;
    }

    /*
     void deleteDublecate (Product ** array, int length) {
        string tempName;
        float tempPrice, tempWeight;
        int tempAmount, flag = 0;
        cout << "deleting dublecates" << endl ;

        for (int i = 0; i < length; i++){
            tempName = array[i]->getName();
            tempPrice = array[i]->getPrice();
            tempAmount = array[i]->getAmount();
            tempWeight = array[i]->getWeight();
            for (int j = i+1; j < length; j++){
                if ((tempName == array[j]->getName()) && (tempPrice == array[j]->getPrice()) && (tempAmount == array[j]->getAmount()) && (tempWeight == array[j]->getWeight())){
                    flag = j;
//                    array[j]->ID = -1;
//                    array[j]->Name = "DELETED";
//                    array[j]->Price = 0;
//                    array[j]->Amount = 0;
//                    array[j]->Weight = 0;
                    for(int y = j; y < length-1; y++){
                        array[y] = array[y+1];
                    }
                    length = length-1;

                }
            }

        }
    }

*/

    virtual double getWeight() const {
        return Weight;
    }
    void setWeight(double weight) {
        Weight = weight;
    }

    virtual void output() override {
        NonElectricProduct::output();
        cout << "Weight: " << Weight
             << endl << "Final price: " << finalPrice() <<"$";
    }
    const double finalPrice(){
        return NonElectricProduct::finalPrice();
    }

    virtual ~Table() = default;

protected:
    double Weight;
};

void searchMenu(){
    cout << endl << "Choose option to search by: " << endl;
    cout << "1. ID" << endl;
    cout << "2. Name" << endl;
    cout << "3. Price" << endl;
    cout << "4. Amount" << endl;
    cout << "5. Weight" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";
}

void searchById(Product **array, int length, int comp){
    int flag = 0;
    for(int i = 0; i < length; i++){
        if (array[i]->getId() == comp){
            cout << " =========== " << endl;
            array[i]->output();
            cout << endl << " =========== " << endl;
            flag = 1;
        }
    }
    if (!flag)
        cout << endl << "No Matches were found" << endl;
}
void searchByName(Product **array, int length, string comp){
    int flag = 0;
    for(int i = 0; i < length; i++){
        if (array[i]->getName() == comp){
            cout << " =========== " << endl;
            array[i]->output();
            cout << endl <<  " =========== " << endl;
            flag = 1;
        }
    }
    if (!flag)
        cout << endl << "No Matches were found" << endl;
}
void searchByPrice(Product **array, int length, double compMin, double compMax){
    int flag = 0;
    for(int i = 0; i < length; i++){
        if (array[i]->getPrice() >= compMin && array[i]->getPrice() <= compMax){
            cout << " =========== " << endl;
            array[i]->output();
            cout << endl << " =========== " << endl;
            flag = 1;
        }
    }
    if (!flag)
        cout << endl << "No Matches were found" << endl;
}
void searchByAmount(Product **array, int length, int comp){
    int flag = 0;
    for(int i = 0; i < length; i++){
        if (array[i]->getAmount() == comp){
            cout << " =========== " << endl;
            array[i]->output();
            cout << endl <<  " =========== " << endl;
            flag = 1;
        }
    }
    if (!flag)
        cout << endl << "No Matches were found" << endl;
}
void searchByWeight(Product **array, int length, double comp){
    int flag = 0;
    for(int i = 0; i < length; i++){
        if (array[i]->getWeight() == comp){
            cout << " =========== " << endl;
            array[i]->output();
            cout << endl << " =========== " << endl;
            flag = 1;
        }
    }
    if (!flag)
        cout << endl << "No Matches were found" << endl;
}

int main() {
    int amount;
    int index;
    cout << "Enter the number of notes you want to enter: ";
    cin >> amount;
    cout << endl;
    Product *arr[amount];

    for(int i = 0; i < amount; i++){
        index = i+1;
        cout << "Enter information about "<< index << " item: " << endl;
        arr[i] = new Table();
        arr[i]->input(index);
        arr[i]->output();
        cout << endl << endl;
    }
    //temp.Table::deleteDublecate(arr, amount);
    cout << endl << endl << "Output of all items: " << endl;
    for(int i = 0; i < amount; i++){
        cout << " = | = | = | = | = | = | = " << endl;
        arr[i]->output();
        cout << endl << endl;
    }

    string tempName;
    double tempPriceMin, tempPriceMax;
    double tempWeight;
    int tempAmount, tempID, flag = 0;
    int option = 0;
    do{
        searchMenu();
        cin >> option;

        switch (option) {
            case 1:
                cout << "Enter ID to search by: ";
                cin >> tempID;
                searchById(arr, amount, tempID);
                break;
            case 2:
                cout << "Enter Name to search by: ";
                cin >> tempName;
                searchByName(arr, amount, tempName);
                break;
            case 3:
                cout << "Enter minimal Price: ";
                cin >> tempPriceMin;
                cout << "Enter max Price: ";
                cin >> tempPriceMax;
                searchByPrice(arr, amount, tempPriceMin, tempPriceMax);
                break;
            case 4:
                cout << "Enter Amount to search by: ";
                cin >> tempAmount;
                searchByAmount(arr, amount, tempAmount);
                break;
            case 5:
                cout << "Enter Weight to search by: ";
                cin >> tempWeight;
                searchByWeight(arr, amount, tempWeight);
                break;
            default:
                break;
        }

    } while (option != 6);


    for(int i = 0; i < 4; i++){
        delete arr[i];
    }
    delete[] arr[4];

    return 0;
}
