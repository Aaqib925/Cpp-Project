#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

class User
{
protected:
    string username, password;

public:
    static int number;
    virtual string getData()
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        return username + password;
    }

    void createAccount(string userData)
    {
        ofstream fout; // object for writing into the file

        fout.open("Users.txt", ios::app); // opening the file in apppend mode

        fout << userData << "\n";

        cout << "Your Account has been Created" << endl;
        // number += 1;

        fout.close();
    }

    virtual bool checkData(string userData)
    {
        int offset;
        string line;
        ifstream fin;

        fin.open("Users.txt");
        if (fin.is_open())
        {

            while (!fin.eof())
            {

                getline(fin, line);
                if (offset = line.find(userData, 0) != string::npos)
                {
                    cout << "ACCOUNT FOUND" << endl;
                    cout << endl;
                    return true;
                }
                else
                {
                    cout << "ACCOUNT NOT FOUND" << endl;
                    cout << endl;
                    return false;
                }
            }
        }

        fin.close();
        return false;
    }
};

int User::number = rand() % 100 + 10000;

class Customer : public User
{
protected:
    bool ans = false;
    string contactNumber, address;

public:
    void working()
    {
        while (!ans)
        {
            string addedString; // this contains username+password

            addedString = User::getData();

            if (checkData(addedString))
            {
                ans = true;
            }

            else
            {
                cout << "Your Account doesn't exist in out records, Please Create Account" << endl;
                User::createAccount(User::getData());
                ans = true;
            }
        }
    }

    void customerData()
    {
        number += 1;
        cout << "Dear " << username << " , Please enter your Billing address: ";
        cin >> this->address;
        cout << endl;
        cout << "Thank You for the moment!!" << endl
             << "Your id is: " << number << endl;
        cout << endl;
    }
};

// map<string, int> ShoppingCart::mymap;

class ShoppingCart
{
protected:
    vector<vector<string>> customerList;
    bool order = false;
    map<string, int> mymap;

public:
    int validation()
    {
        int x;
        while (!(cin >> x))
        {
            cout << "Enter valid number!!" << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
        return x;
    }
    ShoppingCart()
    {
        mymap["Grocery   "] = 7;
        mymap["Fast food"] = 5;
        mymap["Electronic"] = 15;
        mymap["HouseHolds"] = 20;
    }

    void showItems(string userId)
    {
        cout << "Dear Customer " << userId << ", Select your items from below: " << endl;

        for (auto const &pair : mymap)
        {
            vector<string> userls;
            int x;
            cout << "Package " << pair.first << " of Price " << pair.second << "$ EACH!" << endl;
            cout << "Enter Quantity for " << pair.first << ": ";
            x = validation();
            cout << endl;
            if (x != 0)
            {
                userls.push_back(pair.first);
                userls.push_back(to_string(pair.second));
                userls.push_back(to_string(pair.second * x));
                // customerList.push_back()
            }
            if (!userls.empty())
            {
                customerList.push_back(userls);
            }
        }
    }
};

class Payment : public ShoppingCart
{
protected:
    double totalCost = 0;
    bool done = false;
    static int OrderNumber;
    string paymentMethod;
    string card;
    string pin;

public:
    void showCosts()
    {

        cout << "Your Order Number is: " << OrderNumber << endl;
        cout << "Item\t\t"
             << "Price/Each\t\t"
             << "Total" << endl;

        for (int i = 0; i < customerList.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << customerList[i][j] << "\t\t";
                if (j == 2)
                {
                    stringstream ss(customerList[i][j]);
                    int x = 0;
                    ss >> x;
                    totalCost += x;
                }
            }
            cout << endl;
        }
        cout << endl;
        cout << "YOUR TOTAL COST IS: " << totalCost << "$" << endl;
        cout << endl;
    }

    void agrii()
    {
        cout << "Do you want to continue to Payment step? Y/N: ";
        char y;
        cin >> y;
        if (y == 'Y' || y == 'y')
        {
            done = true;
            OrderNumber += 1;
            cout << "Please Enter your Payment Method 1 or 2" << endl;
            cout << "1: Cash On delivery" << endl;
            cout << "2: Credit Card" << endl;
            cout << endl;
            cout << "Your Method: ";
            int y;
            cin >> y;
            if (y == 1)
            {
                paymentMethod = "Cash On Delivery!";
            }
            else if (y == 2)
            {
                paymentMethod = "Credit Card";
                cout << "Enter Credit Card number: ";
                cin >> card;
                cout << "Enter Your PIN: ";
                cin >> pin;
            }
        }
        else
        {
            done = false;
            cout << "Thank you for using our Service!!" << endl;
        }
    }
};

int Payment::OrderNumber = rand() % 100 + 1000;

class Finalize : virtual public Customer, virtual public Payment
{
public:
    void finalize()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        Customer::working();
        Customer::customerData();
        Payment::showItems(username);
        Payment::showCosts();
        Payment::agrii();
        if (done)
        {
            cout << endl;
            cout << "Your Order Number is: " << OrderNumber << endl;
            cout << endl;
            cout << "Your Total Cost is: " << totalCost << "$" << endl;

            cout << "Your Order will be delivered soon to you at address: " << address << endl;
            cout << endl;
            cout << "For any compliance call us on +923223132233." << endl;

            cout << "Your Order Placed on local date and time: " << dt << endl;
            cout << endl;
            // writing the whole data into the file for record;

            ofstream fout;
            fout.open("RECORDS.txt", ios::app);

            fout << "===================================================\n";
            fout << "User: " << username << "\n";
            fout << "User Record ID: " << number << "\n";
            fout << "Order Number: " << OrderNumber << "\n";
            fout << "\n";
            fout << "Item\t\t"
                 << "Price/Each\t\t"
                 << "Total" << endl;
            for (int i = 0; i < customerList.size(); i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    fout << customerList[i][j] << "\t\t";
                }
                fout << endl;
            }
            fout << endl;

            fout << "Address: " << address << "\n";
            fout << "Payment Method: " << paymentMethod << "\n";

            fout << "The local date and time: " << dt << endl;
            fout << "\n";

            fout.close();
        }
    }
};

int main()
{
    Finalize o1;
    o1.finalize();
}