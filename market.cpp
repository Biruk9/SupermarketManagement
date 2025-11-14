#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class shopping
{
private:
    int pCode;
    float price;
    float dis;
    string pName;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
    int choice;
    string email, password;

    while (true)
    {
        cout << "\n\n\t\t************************************\n";
        cout << "\t\t      SUPERMARKET MAIN MENU\n";
        cout << "\t\t************************************\n";

        cout << "\t\t1) Administrator\n";
        cout << "\t\t2) Buyer\n";
        cout << "\t\t3) Exit\n";
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n\t\tLOGIN\n";
            cout << "\t\tEmail: ";
            cin >> email;
            cout << "\t\tPassword: ";
            cin >> password;

            if (email == "akibiruk39@gmail.com" && password == "biruk0942")
            {
                administrator();
            }
            else
            {
                cout << "\nInvalid email or password\n";
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            cout << "Exiting...\n";
            exit(0);

        default:
            cout << "Please select a valid option.\n";
        }
    }
}

void shopping::administrator()
{
    int choice;
    while (true)
    {
        cout << "\n\n\t\tAdministrator Menu\n";
        cout << "\t\t1) Add Product\n";
        cout << "\t\t2) Modify Product\n";
        cout << "\t\t3) Delete Product\n";
        cout << "\t\t4) Back to Main Menu\n";
        cout << "\t\tEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}

void shopping::buyer()
{
    int choice;
    while (true)
    {
        cout << "\n\n\t\tBuyer Menu\n";
        cout << "\t\t1) Buy Product\n";
        cout << "\t\t2) Back\n";
        cout << "\t\tEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            receipt();
            break;
        case 2:
            return;
        default:
            cout << "Invalid choice\n";
        }
    }
}

void shopping::add()
{
    fstream data;
    int token = 0;

    cin.ignore(); // flush input buffer
    cout << "\nAdd New Product\n";
    cout << "Product Code: ";
    cin >> pCode;
    cin.ignore();
    cout << "Name: ";
    getline(cin, pName);
    cout << "Price: ";
    cin >> price;
    cout << "Discount (%): ";
    cin >> dis;

    // Check for duplicate
    data.open("database.txt", ios::in);
    if (data.is_open())
    {
        int c;
        float p, d;
        string n;
        while (data >> c >> n >> p >> d)
        {
            if (c == pCode)
            {
                token = 1;
                break;
            }
        }
        data.close();
    }

    if (token == 1)
    {
        cout << "Product already exists.\n";
        return;
    }

    // Add product
    data.open("database.txt", ios::app);
    data << pCode << " " << pName << " " << price << " " << dis << "\n";
    data.close();

    cout << "Record inserted successfully.\n";
}

void shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "Enter product code to modify: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File does not exist.\n";
        return;
    }
    data1.open("database1.txt", ios::out);

    int c;
    float p, d;
    string n;
    while (data >> c >> n >> p >> d)
    {
        if (c == pkey)
        {
            cout << "New Code: ";
            cin >> c;
            cin.ignore();
            cout << "New Name: ";
            getline(cin, n);
            cout << "New Price: ";
            cin >> p;
            cout << "New Discount(%): ";
            cin >> d;
            token = 1;
        }
        data1 << c << " " << n << " " << p << " " << d << "\n";
    }

    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (!token)
        cout << "Record not found.\n";
    else
        cout << "Record edited successfully.\n";
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "Enter product code to delete: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File not found.\n";
        return;
    }
    data1.open("database1.txt", ios::out);

    int c;
    float p, d;
    string n;
    while (data >> c >> n >> p >> d)
    {
        if (c == pkey)
        {
            token = 1;
            continue;
        }
        data1 << c << " " << n << " " << p << " " << d << "\n";
    }

    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (!token)
        cout << "Record not found.\n";
    else
        cout << "Product deleted successfully.\n";
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "No products available.\n";
        return;
    }

    int c;
    float p, d;
    string n;
    cout << "\nCode\tName\tPrice\tDiscount\n";
    while (data >> c >> n >> p >> d)
        cout << c << "\t" << n << "\t" << p << "\t" << d << "%\n";

    data.close();
}

void shopping::receipt()
{
    fstream data;
    int arrc[100], arrq[100], c = 0;
    char choice;
    float amount, total = 0;

    cout << "\n--- Available Products ---\n";
    list();

    cout << "\nPlace your order:\n";
    do
    {
        cout << "Product code: ";
        cin >> arrc[c];
        cout << "Quantity: ";
        cin >> arrq[c];

        // Check duplicates
        bool dup = false;
        for (int i = 0; i < c; i++)
            if (arrc[c] == arrc[i])
            {
                dup = true;
                break;
            }

        if (dup)
        {
            cout << "Duplicate code. Try again.\n";
            continue;
        }

        c++;
        cout << "Add another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << fixed << setprecision(2);
    cout << "\n--- Final Receipt ---\n";
    cout << "Code | Name | Qty | Price | Amount | After Discount\n";

    for (int i = 0; i < c; i++)
    {
        data.open("database.txt", ios::in);
        int code;
        float price, dis;
        string name;
        while (data >> code >> name >> price >> dis)
        {
            if (code == arrc[i])
            {
                amount = price * arrq[i];
                float discounted = amount - (amount * dis / 100);
                total += discounted;

                cout << code << " | " << name << " | " << arrq[i] << " | "
                     << price << " | " << amount << " | " << discounted << "\n";
            }
        }
        data.close();
    }

    cout << "\nTOTAL AMOUNT: " << total << "\n";
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
