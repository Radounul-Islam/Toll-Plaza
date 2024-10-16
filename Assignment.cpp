#include <bits/stdc++.h>
using namespace std;
string getCurrentTime();
string date();
void waitforpress();
void loginMenu();
void searchMenu();
void actionMenu();
bool dateComparator(string d1, string d2);
string formatDate(string date);
string formatAmount(int amount);
string formatAmount(string amount);
string formatOperator(string operatorid);
string formatVehicle(string vehicle);
string formatDate(string date);
string formatTime(string time);
class Vehicle
{
public:
    string name_of_vehicle;
    string Date = date();
    string Reg_No;
    string Time = getCurrentTime();
    string Operator_ID;
    int toll_amount;
    virtual void getInput(string oper, string reg_no, string vehicle_name) = 0;
    virtual void tollCalculate(int tool_price) = 0;
};
class Bus : public Vehicle
{
public:
    int seats;
    void getInput(string oper, string reg_no, string vehicle_name)
    {
        name_of_vehicle = vehicle_name;
        Reg_No = reg_no;
        Operator_ID = oper;
    }
    void tollCalculate(int tool_price)
    {
        toll_amount = tool_price;
    }
};
class Car : public Vehicle
{
public:
    void getInput(string oper, string reg_no, string vehicle_name)
    {
        name_of_vehicle = vehicle_name;
        Reg_No = reg_no;
        Operator_ID = oper;
    }
    void tollCalculate(int toll_price)
    {
        toll_amount = toll_price;
    }
};
class Truck : public Vehicle
{
public:
    void getInput(string oper, string reg_no, string vehicle_name)
    {
        name_of_vehicle = vehicle_name;
        Reg_No = reg_no;
        Operator_ID = oper;
    }
    void tollCalculate(int toll_price)
    {
        toll_amount = toll_price;
    }
};
class TollPlaza
{
    int bus_toll = 500;
    int truck_toll = 400;
    int car_toll = 150;
    map<string, string> admin_users = {{"admin", "2004"}, {"radoun", "6789"}}; //
    map<string, string> user_id_passward;
    vector<Vehicle *> vehicles;

public:
    void searchVehicle()
    {
        string regis;
        cout << "Enter Vehicle Registration No: ";
        cin >> regis;
        cout << formatDate("Date") << formatTime("Time")
             << formatVehicle("Vehicle")
             << formatAmount("Amount") << formatOperator("Operator_ID") << endl;
        cout << setfill('-') << setw(50) << "-" << endl;
        cout << setfill(' '); // Reset the fill character to space
        for (auto v : vehicles)
        {
            if (v->Reg_No == regis)
            {
                cout << formatDate(v->Date) << formatTime(v->Time)
                     << formatVehicle(v->name_of_vehicle) << formatAmount(v->toll_amount)
                     << formatOperator(v->Operator_ID) << endl;
            }
        }
        waitforpress();
    }
    void searchDateToDate()
    {
        string d1, d2;
        cout << "Enter start Date: ";
        cin >> d1;
        cout << "Enter End Date: ";
        cin >> d2;
        cout << formatDate("Date") << formatTime("Time")
             << formatVehicle("Vehicle") << formatAmount("Amount")
             << formatOperator("Operator_ID") << endl;
        cout << setfill('-') << setw(49) << "-" << endl;
        cout << setfill(' '); // Reset the fill character to space
        for (auto v : vehicles)
        {
            if (dateComparator(v->Date, d1) && dateComparator(d2, v->Date))
            {
                cout << formatDate(v->Date) << formatTime(v->Time)
                     << formatVehicle(v->name_of_vehicle) << formatAmount(v->toll_amount)
                     << formatOperator(v->Operator_ID) << endl;
            }
        }
        waitforpress();
    }
    void searchOperator()
    {
        string opertor;
        cout << "Enter Operator Name: ";
        cin >> opertor;
        cout << formatDate("Date") << formatTime("Time")
             << formatAmount("Amount") << formatVehicle("Vehicle") << endl;
        cout << setfill('-') << setw(35) << "-" << endl;
        cout << setfill(' ');
        for (auto v : vehicles)
        {
            if (v->Operator_ID == opertor)
            {
                cout << formatDate(v->Date) << formatTime(v->Time)
                     << formatAmount(v->toll_amount) << formatVehicle(v->name_of_vehicle) << endl;
            }
        }
        waitforpress();
    }
    void search()
    {
        while (1)
        {
            searchMenu();
            int option;
            cin >> option;
            switch (option)
            {
            case 1:
                searchVehicle();
                break;
            case 2:
                searchDateToDate();
                break;
            case 3:
                searchOperator();
                break;
            default:
                return;
            }
        }
    }
    void statistics()
    {
        int bus = 0, track = 0, car = 0;
        long long bus_am = 0, track_am = 0, car_am = 0, total;
        string date;
        cout << "Enter date (DD/MM/YY): ";
        cin >> date;
        if (date.size() != 10)
        {
            cout << "Invalid date format!" << endl;
            cout << "Press any key go to main menu....";
            cin.ignore();
            cin.get();
            return;
        }
        for (Vehicle *v : vehicles)
        {
            if (v->Date == date)
            {
                if (v->name_of_vehicle == "Bus")
                {
                    bus++;
                    bus_am += bus_toll;
                }
                else if (v->name_of_vehicle == "Car")
                {
                    car++;
                    car_am += car_toll;
                }
                else
                {
                    track++;
                    track_am += truck_toll;
                }
            }
        }

        total = bus_am + track_am + car_am;
        cout << "Vehicle   Number   Amount" << endl;
        cout << "--------------------------" << endl;
        cout << "Bus       " << std::left << std::setw(6) << bus << "   " << std::left << std::setw(9) << bus_am << endl;
        cout << "Track     " << std::left << std::setw(6) << track << "   " << std::left << std::setw(9) << track_am << endl;
        cout << "Car       " << std::left << std::setw(6) << car << "   " << std::left << std ::setw(9) << car_am << endl
             << endl;
        cout << "--------------------------" << endl;
        cout << "Total Amount: " << total << endl;
        waitforpress();
    }

    void tollSettings()
    {
        string name, pass;
        cout << "Enter Admin username: ";
        cin >> name;
        cout << "Enter Admin passward: ";
        cin >> pass;
        if (admin_users.count(name) && admin_users[name] == pass)
        {
            cout << "Enter Toll for Bus: ";
            cin >> bus_toll;
            cout << "Enter Toll for Track: ";
            cin >> truck_toll;
            cout << "Enter Toll for Car: ";
            cin >> car_toll;
            cout << "\nToll Change is Successful" << endl;
        }
        else
        {
            cout << "Invalid username or passward" << endl;
        }
        waitforpress();
    }
    void creatNewOperator()
    {
        string user_name;
        string prev_pass;
        string curr_pass;
        cout << "\nUsername: ";
        cin >> user_name;
        cout << "Password: ";
        cin >> prev_pass;
        cout << "Reconfirm Password: ";
        cin >> curr_pass;
        if (curr_pass == prev_pass)
        {
            user_id_passward[user_name] = curr_pass;
            cout << "Registration is Successful" << endl;
        }
        else
        {
            cout << "Password mismatch!" << endl;
        }
        cout << "Press any key go to login menu....";
        cin.ignore();
        cin.get();
    }
    void loginOperation()
    {
        string user_name;
        string pass;
        cout << "Enter username: ";
        cin >> user_name;
        cout << "Enter passward: ";
        cin >> pass;
        if ((user_id_passward.count(user_name) && user_id_passward[user_name] == pass) ||
            admin_users.count(user_name) && admin_users[user_name] == pass)
        {
            cout << "Login is Successful" << endl;
            while (1)
            {
                int option;
                actionMenu();
                cin >> option;
                switch (option)
                {
                case 1:
                    bus(user_name);
                    break;

                case 2:
                    truck(user_name);

                    break;
                case 3:
                    car(user_name);

                    break;
                case 4:
                    search();
                    break;
                case 5:
                    statistics();
                    break;
                case 6:
                    tollSettings();
                    break;
                case 7:
                    cout << "Loged out!" << endl;
                    cout << "Press any key go to login menu....";
                    cin.ignore();
                    cin.get();
                    return;
                }
            }
        }

        else
        {
            cout << "Invalid username or password " << endl;
            cout << "Press any key go to login menu....";
            cin.ignore();
            cin.get();
        }
    }
    void bus(string oper)
    {
        string regi;
        int given_amount = 0;
        cout << "Enter Bus Registration No: ";
        cin >> regi;
        cout << "Enter Amount (Tk." << bus_toll << "): ";
        cin >> given_amount;
        while (given_amount < bus_toll)
        {
            cout << "Insufficient amount!" << endl;
            cout << "Enter Amount (Tk." << bus_toll << "): ";
            cin >> given_amount;
        }
        cout << "Return Amount : " << (given_amount - bus_toll) << endl;
        Bus *b = new Bus();
        b->getInput(oper, regi, "Bus");
        b->tollCalculate(bus_toll);
        vehicles.push_back(b);

        cout << "Toll Collection is Successful" << endl;
        waitforpress();
    }
    void car(string oper)
    {
        string regi;
        int given_amount = 0;
        cout << "Enter Car Registration No: ";
        cin >> regi;
        cout << "Enter Amount (Tk." << car_toll << "): ";
        cin >> given_amount;
        while (given_amount < car_toll)
        {
            cout << "Insufficient amount!" << endl;
            cout << "Enter Amount (Tk." << car_toll << "): ";
            cin >> given_amount;
        }
        cout << "Return Amount : " << (given_amount - car_toll) << endl;
        Car *c = new Car();
        c->getInput(oper, regi, "Car");
        c->tollCalculate(car_toll);
        vehicles.push_back(c);
        cout << "Toll Collection is Successful" << endl;
        waitforpress();
    }
    void truck(string oper)
    {
        string regi;
        int given_amount = 0;
        cout << "Enter Truck Registration No: ";
        cin >> regi;
        cout << "Enter Amount (Tk." << truck_toll << "): ";
        cin >> given_amount;
        while (given_amount < truck_toll)
        {
            cout << "Insufficient amount!" << endl;
            cout << "Enter Amount (Tk." << truck_toll << "): ";
            cin >> given_amount;
        }
        cout << "Return Amount : " << (given_amount - truck_toll) << endl;
        Truck *t = new Truck();
        t->getInput(oper, regi, "Truck");
        t->tollCalculate(truck_toll);
        vehicles.push_back(t);
        cout << "Toll Collection is Successful" << endl;
        waitforpress();
    }
};

int main()
{
    TollPlaza plaza;

    while (1)
    {
        loginMenu();
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            plaza.loginOperation();
            break;
        case 2:
            plaza.creatNewOperator();
            break;
        case 3:
            return 0;
        }
    }

    return 0;
}
void loginMenu()
{
    cout << "\n*Toll Plaza : Operator*\n\n";
    cout << "1. Login \n2. Register \n3. Exit\n\tEnter Your Option:";
}
void searchMenu()
{
    cout << "\n***Toll Plaza : Search ***\n"
         << endl;
    cout << "  1. Vehicle \n  2. Date to Date \n  3. Operator \n  4. Back\nEnter Your Option(1 - 4) : ";
}
void actionMenu()
{
    cout << "\n*******Toll Plaza Menu ******\n\n";
    cout << "  1. Bus \n  2. Truck \n  3. Car \n  4. Search \n  5. Statistics \n  6. Toll Settings(admin) \n  7. Save and Logout\n\tEnter Your Option(1 - 7): ";
}
string getCurrentTime()
{

    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << setw(2) << setfill('0') << ltm->tm_hour << ":"
       << setw(2) << setfill('0') << ltm->tm_min;
    return ss.str();
}
string date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
}
bool dateComparator(string d1, string d2)
{
    if (d1.substr(6, 4) != d2.substr(6, 4))
        return d1.substr(6, 4) > d2.substr(6, 4);
    else if (d1.substr(3, 2) != d2.substr(3, 2))
        return d1.substr(3, 2) != d2.substr(3, 2);
    return d1.substr(0, 2) >= d2.substr(0, 2);
}
string formatDate(string date)
{
    ostringstream oss;
    oss << left << setw(12) << date;
    return oss.str();
}
string formatTime(string time)
{
    ostringstream oss;
    oss << left << setw(8) << time;
    return oss.str();
}
string formatVehicle(string vehicle)
{
    ostringstream oss;
    oss << left << setw(10) << vehicle;
    return oss.str();
}
string formatOperator(string operatorid)
{
    ostringstream oss;
    oss << left << setw(12) << operatorid;
    return oss.str();
}

string formatAmount(int amount)
{
    ostringstream oss;
    oss << left << setw(8) << amount;
    return oss.str();
}
string formatAmount(string amount)
{
    ostringstream oss;
    oss << left << setw(8) << amount;
    return oss.str();
}
void waitforpress()
{
    cout << "Press any key go to main menu....";
    cin.ignore();
    cin.get();
}
