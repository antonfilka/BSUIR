#include <iostream>
using namespace std;

class Product {
public:

    Product(int ID = 0, string Name = "Name not entered", double Price = 0.0): ID(ID), Name(Name), Price(Price){
    }

    Product(Product &other){
        this->ID = other.ID;
        this->Name = other.Name;
        this->Price = other.Price;
    }

    int getId() const {
        return ID;
    }
    void setId(int id) {
        ID = id;
    }
    const string &getName() const {
        return Name;
    }
    void setName(const string &name) {
        Name = name;
    }
    double getPrice() const {
        return Price;
    }
    void setPrice(double price) {
        Product::Price = price;
    }

    virtual void output(){
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl;
    }

    ~Product()= default;


protected:
    double Price;
    int ID;
    string Name;
};

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
    int getAmount() const {
        return Amount;
    }
    void setAmount(int amount) {
        Amount = amount;
    }

    virtual void output(){
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl << "= = = = = ="
             << endl << NonElectricProductInfo
             << endl
             << "Amount: " << Amount
             << endl;
    }

    ~NonElectricProduct() = default;

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

    virtual void output() override {
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl << "= = = = = ="
             << endl << ElectricProductInfo
             << endl
             << "Voltage: " << Voltage
             << endl;
    }

    ~ElectricProduct() = default;

protected:
    double Voltage;
};

class Table: virtual public NonElectricProduct{
public:
    Table(int ID, string Name, double Price, int Amount, double Weight = 10.0)
            : Product(ID, Name, Price),
              NonElectricProduct(ID, Name, Price, Amount), Weight(Weight){

    }
    double getWeight() const {
        return Weight;
    }
    void setWeight(double weight) {
        Weight = weight;
    }

    virtual void output() override {
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl << "= = = = = ="
             << endl << getNonElectricProductInfo()
             << endl
             << "Amount: " << Amount
             << endl << "Weight: " << Weight
             << endl;
    }

    ~Table() = default;

protected:
    double Weight;
};

class TV: virtual public ElectricProduct{
public:
    TV(int ID, string Name, double Price, int Amount, double ScreenInchSize = 13.0)
            : Product(ID, Name, Price),
              ElectricProduct(ID, Name, Price, Amount), ScreenInchSize(ScreenInchSize){

    }

    double getScreenInchSize() const {
        return ScreenInchSize;
    }
    void setScreenInchSize(double screenInchSize) {
        ScreenInchSize = screenInchSize;
    }

    virtual void output() override {
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl << "= = = = = ="
             << endl << getElectricProductInfo()
             << endl
             << "Voltage: " << Voltage << " V"
             << endl << "Screen size: " << ScreenInchSize << " inches"
             << endl;
    }

    ~TV() = default;

protected:
    double ScreenInchSize;
};

class RoomSetup: public Table, public TV{
public:
    RoomSetup(RoomSetup &other): TV(other), Table(other), ElectricProduct(other), NonElectricProduct(other), Product(other){
        this->ID = other.ID;
        this->Name = other.Name;
        this->Price = other.Price;
        this->Amount = other.Amount;
        this->Voltage = other.Voltage;
        this->Weight = other.Weight;
        this->ScreenInchSize = other.ScreenInchSize;
        this->Rating = other.Rating;
    }

    RoomSetup(int ID = 0, string Name = "Not entered", double Price = 10.0, int Amount = 5, double Voltage = 220, double Weight = 10.0, double ScreenInchSize = 13.0, double Rating = 5.0)
    : Product(ID, Name, Price),
      NonElectricProduct(ID, Name, Price, Amount),
      ElectricProduct(ID, Name, Price, Voltage),
      Table(ID, Name, Price, Amount, Weight),
      TV(ID, Name, Price, Voltage, ScreenInchSize), Rating(Rating){

    }

    double getRating() const {
        return Rating;
    }
    void setRating(double rating) {
        Rating = rating;
    }

    void inputData(){
        cout << endl << "Enter Id: ";
        cin >> ID;
        cout << endl << "Enter Price: ";
        cin >> Price;
        cout << endl << "Enter Name: ";
        cin >> Name;
        cout << endl << "Enter Amount: ";
        cin >> Amount;
        cout << endl << "Enter Voltage: ";
        cin >> Voltage;
        cout << endl << "Enter Weight: ";
        cin >> Weight;
        cout << endl << "Enter Screen Inch Size: ";
        cin >> ScreenInchSize;
        cout << endl << "Enter Rating: ";
        cin >> Rating;
        cout << endl;
    }

    virtual void output() override {
        cout << "ID: " << ID
             << endl << "Name: " << Name
             << endl << "Price: " << Price << "$"
             << endl << "= = = = = ="
             << endl << getNonElectricProductInfo()
             << endl
             << "Amount: " << Amount
             << endl << "Weight: " << Weight << " kg"
             << endl << "= = = = = ="
             << endl << getElectricProductInfo()
             << endl
             << "Voltage: " << Voltage << " V"
             << endl << "Screen size: " << ScreenInchSize << " inches"
             << endl << "Rating: " << Rating
             << endl;
    }

    virtual ~RoomSetup(){
        //cout << "Destructor was activated" << endl;
    };

protected:
    double Rating;
};

int main(){



    int ArrSize = 0;
    const char *ArrNames[ArrSize];
    cout << "Enter Array size: ";
    cin >> ArrSize;

    RoomSetup *arr = new RoomSetup[ArrSize]();

    for(int i = 0; i < ArrSize; i++){
        cout << "Enter Data for array[" << i << "]:" << endl;
        arr[i].inputData();
    }

    for(int i = 0; i < ArrSize; i++){
        cout << endl << endl << "Array[" << i << "]:" << endl;
        arr[i].output();
    }

    return 0;
}