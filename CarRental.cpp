#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include <chrono>
#include <sstream>
#include<unordered_set>
#include<unordered_map>

using namespace std;
using namespace std::chrono;

bool isValidDateFormat(const string& dateString) {
    stringstream ss(dateString);
    int year, month, day;
    char dash1, dash2;

    if (!(ss >> year >> dash1 >> month >> dash2 >> day)) {
        return false;
    }
    if (dash1 != '-' || dash2 != '-') {
        return false;
    }
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    return true;
}

system_clock::time_point convertToTimePoint(const string& dateString) {

    int year, month, day;
    char delimiter;
    istringstream iss(dateString);
    iss >> year >> delimiter >> month >> delimiter >> day;

    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900; 
    timeinfo.tm_mon = month - 1;   
    timeinfo.tm_mday = day;      

    time_t time = mktime(&timeinfo);
    return system_clock::from_time_t(time);
}

int daysPassedSinceDueDate(const string& dateString) {
    system_clock::time_point dueDate = convertToTimePoint(dateString);
    system_clock::time_point now = system_clock::now();
    auto duration = now - dueDate;
    return duration_cast<hours>(duration).count() / 24;
}

class User {

    public:
        string name;
        string ID;
        string password;

};

class Customer : public User {
    private:
        double customerRecord;
        string otherDetails;
        double fineDue;

    public:
        unordered_set<string> rentedCars;
        unordered_map<string,string> car_duedates;

        static Customer* addCustomer(string n, string id, string pass, unordered_set<string> cars, double fine, double record, unordered_map<string,string> car_duedates){
            Customer* newcustomer = new Customer;
            newcustomer->name = n;
            newcustomer->ID = id;
            newcustomer->password = pass;
            newcustomer->rentedCars = cars;
            newcustomer->fineDue=fine;
            newcustomer->customerRecord=record;
            newcustomer->car_duedates=car_duedates;
            return newcustomer;           
        }

        static int checkFine(Customer* customer){
            return customer->fineDue;
        }

        static void updateFine(Customer* customer, double fineDue){
            customer->fineDue = fineDue;
        }
        static double getCustomerRecord(Customer* customer){
            return customer->customerRecord;
        }

        static void updateCustomerRecord(Customer* customer,double customerRecord){
            customer->customerRecord=customerRecord;
        }

        static void deleteCustomer(vector<Customer*>& customers, string customerName, string customerId){
            for (vector<Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
                if ((*it)->name == customerName && (*it)->ID == customerId) {
                    delete *it;
                    customers.erase(it);
                    cout << "Customer \"" << customerName << " " << customerId << "\" has been deleted." << endl;
                    return;
                }
            }
            cout << "Customer \"" << customerName << " " << customerId << "\" not Found." << endl;
        }

        static Customer* searchCustomer(vector<Customer*>& customers, string customerName, string customerId) {
            for (vector<Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
                if ((*it)->name == customerName && (*it)->ID == customerId) {
                    return *it; 
                }
            }
            return nullptr; 
        }

        static void updateCustomer(vector<Customer*> customers,string customerName,string customerId,int fine,double record){
            for (auto it = customers.begin(); it != customers.end(); ++it) {
                if((*it)->name == customerName && (*it)->ID == customerId){
                (*it)->fineDue=fine;
                (*it)->customerRecord=record;
                    cout << "Customer \"" << customerName << " " << customerId << "\" has been updated." << endl;
                    return ;
                }
            }
            cout << "Customer \"" << customerName << " " << customerId << "\" not Found." << endl;
            return ;            
        }   

        static void showRentedCar(vector<Customer*> customers , string customerName, string customerId){

            for (vector<Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
                if( (*it)->name==customerName && (*it)->ID==customerId){
                    cout << "Customer Name: " << (*it)->name << endl;
                    if((*it)->rentedCars.size()==0){
                        cout<<"No Rented Cars Currently"<<endl;
                        return;
                    }
                    cout << "Rented Cars: ";
                    for (unordered_set<string>::iterator carIt = (*it)->rentedCars.begin(); carIt != (*it)->rentedCars.end(); ++carIt) {
                        cout << *carIt << " Due-Date: "<< (*it)->car_duedates[*carIt]<<", ";
                    }
                    cout << endl;
                }
            }
        }

        static void showAllRentedCar(vector<Customer*> customers ){

            for (vector<Customer*>::iterator it = customers.begin(); it != customers.end(); ++it) {
                cout << "Customer Name: " << (*it)->name << endl;
                if((*it)->rentedCars.size()==0){
                    cout<<"No Rented Cars Currently"<<endl;
                }
                else{
                    cout << "Rented Cars: ";
                    for (unordered_set<string>::iterator carIt = (*it)->rentedCars.begin(); carIt != (*it)->rentedCars.end(); ++carIt) {
                        cout << *carIt << " Due Date: "<< (*it)->car_duedates[*carIt]<<", ";
                    }
                    cout << endl;
                }
            }
        }
};

class Employee : public User {

    private:
        double employeeRecord;
        string otherDetails;
        int fineDue;

    public:
        unordered_set<string> rentedCars;

        static Employee* addEmployee(string n, string id, string pass, unordered_set<string> cars, double fine, double record){
            Employee* newemployee = new Employee;
            newemployee->name = n;
            newemployee->ID = id;
            newemployee->password = pass;
            newemployee->rentedCars = cars;
            newemployee->fineDue=fine;
            newemployee->employeeRecord=record;
            return newemployee;           
        }

        static int checkFine(Employee* employee){
            return employee->fineDue;
        }

        static void updateFine(Employee* employee,double fineDue){
            employee->fineDue=fineDue;
        }

        static double getEmployeeRecord(Employee* employee){
            return employee->employeeRecord;
        }

        static void updateEmployeeRecord(Employee* employee,double employeeRecord){
            employee->employeeRecord=employeeRecord;
        }

        static Employee* searchEmployee(vector<Employee*>& employees, string employeeName, string employeeId) {
            for (vector<Employee*>::iterator it = employees.begin(); it != employees.end(); ++it) {
                if ((*it)->name == employeeName && (*it)->ID == employeeId) {
                    return *it;
                }
            }
            return nullptr;
        }

        static int updateEmployee(vector<Employee*> employees,string employeeName,string employeeId,int fine,double record){
            for (auto it = employees.begin(); it != employees.end(); ++it) {
                if((*it)->name == employeeName && (*it)->ID == employeeId){
                   (*it)->fineDue=fine;
                   (*it)->employeeRecord=record;
                    cout << "Employee \"" << employeeName << " " << employeeId << "\" has been updated." << endl;
                    return 1;
                }
            }
            cout << "Employee \"" << employeeName << " " << employeeId << "\" not Found." << endl;
            return 0;            
        }   

        static int deleteEmployee(vector<Employee*>& employees, string employeeName, string employeeId){
            for (vector<Employee*>::iterator it = employees.begin(); it != employees.end(); ++it) {
                if ((*it)->name == employeeName && (*it)->ID == employeeId) {
                    delete *it;
                    employees.erase(it);
                    cout << "Employee \"" << employeeName << " " << employeeId << "\" has been deleted." << endl;
                    return 1;
                }
            }
            cout << "Employee \"" << employeeName << " " << employeeId << "\" not Found." << endl;
            return 0;
        }

        static void showRentedCar(vector<Employee*> employees , string employeeName, string employeeId){

            for (vector<Employee*>::iterator it = employees.begin(); it != employees.end(); ++it) {
                if( (*it)->name==employeeName && (*it)->ID==employeeId){
                    cout << "Employee Name: " << (*it)->name << endl;
                    if((*it)->rentedCars.size()==0){
                        cout<<"No Rented Cars Currently"<<endl;
                        return;
                    }
                    for (unordered_set<string>::iterator carIt = (*it)->rentedCars.begin(); carIt != (*it)->rentedCars.end(); ++carIt) {
                        cout << *carIt << ", ";
                    }
                    cout << endl;
                }
            }
        }
};

class Manager : public User {
    public:
        Manager(string n, string id, string pass) {
            name = n;
            ID = id;
            password = pass;
        }
};

class Car{
    private:
        double Conditions;
        double price;
        string otherDetails;   
        string carName;
        string carModel;
  
    public:

        static Car* addcar(string n, string model, double condition,double renting_price, string details){
            Car* newcar = new Car;
            newcar->carName = n;
            newcar->carModel = model;
            newcar->Conditions = condition;
            newcar->price = renting_price;
            newcar->otherDetails = details;  
            return newcar;           
        }

        static string getName(Car* car){
            return car->carName;
        }
        static string getModel(Car* car){
            return car->carModel;
        }

        static double getCondition(Car* car){
            return car->Conditions;
        }
        static double getPrice(Car* car){
            return car->price;
        }
        static string getDetails(Car* car){
            return car->otherDetails;
        }

        static Car* searchCar(vector<Car*>& cars, string carName, string carModel) {
            for (vector<Car*>::iterator it = cars.begin(); it != cars.end(); ++it) {
                if ((*it)->carName == carName && (*it)->carModel == carModel) {
                    return *it;
                }
            }
            return nullptr;
        }

        static int rentCar(vector<Car*>& cars, const string& carName, const string& carModel) {

            for (auto it = cars.begin(); it != cars.end(); ++it) {
                if ((*it)->carName == carName && (*it)->carModel == carModel) {
                    delete *it;  
                    cars.erase(it); 
                    cout << "Car \"" << carName << " " << carModel << "\" has been rented." << endl;
                    return 1;
                }
            }
            cout << "Car \"" << carName << " " << carModel << "\" not Found." << endl;
            return 0;
        }

        static void showAvailableCars(const vector<Car*>& cars){
            cout<<"Car Availble for Rent Details: "<<endl;
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                cout<<"Car Name: "<<(*it)->carName<<" Car Model: "<<(*it)->carModel<<" Price: "<< (*it)->price<<endl;
            }
            cout << endl; 
        }

        static void updateCar(vector<Car*> cars,string carName,string carModel,double carCondition,double renting_price,string details){
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                if((*it)->carName == carName && (*it)->carModel == carModel){
                   (*it)->Conditions=carCondition;
                   (*it)->price=renting_price;
                   (*it)->otherDetails=details;
                    cout << "Car \"" << carName << " " << carModel << "\" details has been updated." << endl;
                    return ;
                }
            }
            cout << "Car \"" << carName << " " << carModel << "\" not Found." << endl;
            return ;            
        }   

        static void deleteCar(vector<Car*>& cars, string carName, string carModel){
            for (vector<Car*>::iterator it = cars.begin(); it != cars.end(); ++it) {
                if ((*it)->carName == carName && (*it)->carModel == carModel) {
                    delete *it;  
                    cars.erase(it); 
                    cout << "Car \"" << carName << " " << carModel << "\" has been removed." << endl;
                    return ;
                }
            }
            cout << "Car \"" << carName << " " << carModel << "\" not Found." << endl;
            return ;            
        }

};

void updateFines(vector<Customer*> customers,vector<Employee*> employees,unordered_map<string,string> car_duedates){

    for (Customer* customer : customers) {
        for (const string& car : customer->rentedCars) {
            if (car_duedates.find(car) != car_duedates.end()) {
                string dueDate = car_duedates.at(car);
                int daysPassed = daysPassedSinceDueDate(dueDate);
                if (daysPassed > 0) {
                    double fine = 200 * daysPassed;
                    Customer::updateFine(customer,fine);
                }
            }
        }
    }
    for (Employee* employee : employees) {
        for (const string& car : employee->rentedCars) {
            if (car_duedates.find(car) != car_duedates.end()) {
                string dueDate = car_duedates.at(car);
                int daysPassed = daysPassedSinceDueDate(dueDate);
                if (daysPassed > 0) {
                    double fine = 200 * daysPassed;
                    Employee::updateFine(employee,fine);
                }
            }
        }
    }
}

int main(){

    ifstream fcars,fcustomers,femployees,fmanager;
    fcars.open("cars.txt");
    fcustomers.open("customers.txt");
    femployees.open("employees.txt");
    fmanager.open("manager.txt");

    string line;

    vector<Customer*> customers;
    vector<Employee*> employees;
    vector<Manager*> managers;
    vector<Car*> cars;
    unordered_map<string,string> car_duedates;

    fcustomers.seekg(0, ios::beg);
    
    while (getline(fcustomers, line)) {     
        string name = line;
        string id;
        string password;
        double fine_due, record;

        unordered_set<string> rented_cars;
        vector<string> carDue;
        vector<string> due_dates;

        getline(fcustomers, line);
        id = line;
        getline(fcustomers, line);
        password = line;
        getline(fcustomers, line);
        string car;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                rented_cars.insert(car);
                carDue.push_back(car);
                car = "";
            } else {
                car += line[i];
            }
        }
        getline(fcustomers, line);
        string duedate;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                due_dates.push_back(duedate);
                duedate = "";
            } else {
                duedate += line[i];
            }
        }

        if(carDue.size()!=due_dates.size()){
            cout<<"number of Due dates should be in correspndence to number of cars for a customer"<<endl;
            return 0;
        }else{
            for(int i=0;i<due_dates.size();i++){
                car_duedates[carDue[i]]=due_dates[i];
            }            
        }

        getline(fcustomers, line);
        if (!line.empty()) {
            fine_due = stoi(line);
        } else {
            fine_due=0;
        }
        getline(fcustomers, line);
        record = stoi(line);

        Customer* new_customer = Customer::addCustomer(name, id, password, rented_cars, fine_due, record, car_duedates);
        customers.push_back(new_customer);
    }

    while (getline(femployees, line)) {     
        string name = line;
        string id;
        string password;
        double fine_due, record;
        unordered_set<string> rented_cars;

        getline(femployees, line);
        id = line;
        getline(femployees, line);
        password = line;
        getline(femployees, line);
        string car;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                rented_cars.insert(car);
                car = "";
            } else {
                car += line[i];
            }
        }
        getline(femployees, line);
        fine_due = stoi(line);
        getline(femployees, line);
        record = stoi(line);

        Employee* new_employee = Employee::addEmployee(name, id, password, rented_cars, fine_due, record);
        employees.push_back(new_employee);
    }

    while (getline(fmanager, line)) {     
        string name = line;
        string id;
        string password;

        getline(fmanager, line);
        id = line;
        getline(fmanager, line);
        password = line;

        Manager* new_manager = new Manager(name, id, password);
        managers.push_back(new_manager);
    }
    
    while (getline(fcars, line)) { 

        string name = line;
        string model;
        string details;
        double renting_price,condition;

        getline(fcars, line);
        model = line;
        getline(fcars, line);
        condition = stoi(line);
        getline(fcars, line);
        renting_price = stoi(line); 
        getline(fcars, line);
        details = line;        

        Car* new_car = Car::addcar(name, model, condition,renting_price, details);
        cars.push_back(new_car);
    }

    updateFines(customers,employees,car_duedates);

    string post,name,password,id;
    int temp=1;

    Customer* customer;
    Employee* employee;
    Manager* manager;
    
    while(temp){
        cout<<"Enter Login Credentials :"<<endl;
        cout << "Enter 'Customer', 'Employee', or 'Manager' for the respective post you want to login: ";
        cin >> post;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter ID: ";
        cin>> id;
        cout << "Enter Password: ";
        cin >> password;

        if(post == "Customer"){
            for(Customer* it_customer : customers) {
                if(it_customer->name == name && it_customer->ID == id && it_customer->password == password) {
                    cout << "\nCustomer logged in successfully!\n" << endl;
                    temp = 0;
                    customer=it_customer;
                    break;
                }
            }
            if(temp)
                cout << "Invalid credentials. Please try again." << endl;
        }else if(post == "Employee"){
            for(Employee* it_employee : employees) {
                if(it_employee->name == name && it_employee ->ID == id && it_employee->password == password) {
                    cout << "\nEmployee logged in successfully!\n" << endl;
                    temp = 0;
                    employee=it_employee;
                    break;
                }
            }
            if(temp)
                cout << "Invalid credentials. Please try again." << endl;
        }else if(post == "Manager"){
            for(Manager* it_manager : managers) {
                if(it_manager->name == name && it_manager ->ID == id && it_manager->password == password) {
                    cout << "\nManager logged in successfully!\n" << endl;
                    temp = 0;
                    manager=it_manager;
                    break;
                }
            }
            if(temp)
                cout << "Invalid credentials. Please try again." << endl;
        }else{
            cout<<"Enter Valid Post";
        }
    }

    int task=1,inp;

    while(task){
        if(post=="Customer"){

            cout<<"Press integer corresponding to task You want to Perform"<<endl;            
            cout << "1. View Available Cars" << endl;
            cout << "2. View Rented Cars"<<endl;
            cout << "3. Check Fine Due"<< endl;
            cout << "4. Logout"<< endl;
            
            temp=1;
            while(temp){
                cout << "Enter input integer in the range [1,4]: ";
                cin>>inp;
                if (inp == 1 || inp == 2 || inp == 3 || inp == 4 ) {
                    temp=0;
                } else {
                    cout<<"Enter Valid Input"<<endl;
                }
            }
            
            if(inp==1){
                Car::showAvailableCars(cars);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }
            }else if(inp==2){

                Customer::showRentedCar(customers,customer->name, customer->ID);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==3){
                cout<< Customer::checkFine(customer) <<endl;
                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }
            }else{
                task=0;
            }

        }else if(post=="Employee"){

            cout<<"Press integer corresponding to task You want to Perform"<<endl;            
            cout << "1. View Available Cars" << endl;
            cout << "2. View Rented Cars"<<endl;
            cout << "3. Check Fine Due"<< endl;
            cout << "4. Rent Car"<< endl;
            cout << "5. Return Car"<< endl;
            cout << "6. Logout"<< endl;
            
            temp=1;
            while(temp){
                cout << "Enter input integer in the range [1,6]: ";
                cin>>inp;
                if (inp == 1 || inp == 2 || inp == 3 || inp == 4 || inp==5 || inp==6) {
                    temp=0;
                } else {
                    cout<<"Enter Valid Input"<<endl;
                }
            }
            
            if(inp==1){

                Car::showAvailableCars(cars);
                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==2){

                Employee::showRentedCar(employees,employee->name,employee->ID);
                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==3){
                
                cout<<Employee::checkFine(employee)<<endl;
                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==4){

                if(cars.size()==0){
                    cout<<"No Car Available for Renting !"<<endl;
                }
                else{
                    string Customername,CustomerId,Carname,Carmodel,due_date;

                    cout<<"Enter Customer Details: "<<endl;
                    cout<<"Enter Customer Name: ";
                    cin >>Customername;
                    cout<<"Enter Customer Id: ";
                    cin >>CustomerId;

                    if(Customer::searchCustomer(customers,Customername,CustomerId) !=nullptr){
                        double fine=Customer::checkFine(Customer::searchCustomer(customers,Customername,CustomerId));
                        if(fine>0){
                            cout<<"Please return previous rented Cars and pay fine of "<<fine<< "Rs as due date is already crossed"<<endl;
                        }else if(Customer::getCustomerRecord(Customer::searchCustomer(customers,Customername,CustomerId))<5){
                            cout<<"Your Previous Record is not so good we can't rent you a car"<<endl;
                        }else{
                            cout<<"Enter Car Details: "<<endl;
                            cout<<"Enter Car Name: ";
                            cin>>Carname;
                            cout<<"Enter Car Model: ";
                            cin>>Carmodel;
                            cout<<"Enter Car Due Date as 'YYYY-MM-DD': ";
                            cin>>due_date;
                            while(!isValidDateFormat(due_date)){
                                cout<<"Please Enter Valid Due date: ";
                                cin>>due_date;
                            }
                            if(Car::rentCar(cars, Carname, Carmodel)){
                                Customer::searchCustomer(customers,Customername,CustomerId)->rentedCars.insert(Carname);
                                car_duedates[Carname]=due_date;
                                employee->rentedCars.insert(Carname);
                                updateFines(customers,employees,car_duedates);
                            }
                        }
                    }else{
                        cout<<"Customer is not Registered !"<<endl;
                        cout<<"First Ask Manager to Register Customer"<<endl;
                    }

                    cout <<endl;
                    cout<<"Want to Perform Next Task Enter 1 else 0: ";
                    cin>>inp;
                    if(inp!=1){
                        task=0;
                    }
                } 
            }else if(inp==5){

                string Customername,CustomerId,Carname,Carmodel,details;
                double car_condition,car_price;

                cout<<"Enter Customer Details: "<<endl;
                cout<<"Enter Customer Name: ";
                cin >>Customername;
                cout<<"Enter Customer Id: ";
                cin >>CustomerId;
                if(Customer::searchCustomer(customers,Customername,CustomerId) !=nullptr){
                    cout<<"Enter Car Details: "<<endl;
                    cout<<"Enter Car Name: ";
                    cin>>Carname;
                    cout<<"Enter Car Model: ";
                    cin>>Carmodel;
                    cout<<"Enter Car Current Condition: ";
                    cin>>car_condition;
                    cout<<"Enter Car Rental Price: ";
                    cin>>car_price;
                    cin.ignore();
                    cout<<"Car Updated Other Details: ";
                    getline(cin, details);

                    Car* new_car=Car::addcar(Carname, Carmodel, car_condition,car_price, details);
                    cars.push_back(new_car);
                    Customer* cust=Customer::searchCustomer(customers, Customername, CustomerId);

                    if(car_condition<5){
                        if(Customer::getCustomerRecord(cust)>2){
                            Customer::updateCustomerRecord(customer,Customer::getCustomerRecord(customer)-2);
                        }else{
                            Customer::updateCustomerRecord(customer,0);
                        }
                        if(Employee::getEmployeeRecord(employee)>1){
                            Employee::updateEmployeeRecord(employee,Employee::getEmployeeRecord(employee)-1);                    
                        }else{
                            Employee::updateEmployeeRecord(employee,0); 
                        }
                    }

                    if(Customer::checkFine(cust)>0){
                        if(Customer::getCustomerRecord(cust)>1){
                            Customer::updateCustomerRecord(customer,Customer::getCustomerRecord(customer)-1);
                        }else{
                            Customer::updateCustomerRecord(customer,0);
                        }
                    }else if(Customer::checkFine(cust)>1000){
                        if(Customer::getCustomerRecord(cust)>2){
                            Customer::updateCustomerRecord(customer,Customer::getCustomerRecord(customer)-2);
                        }else{
                            Customer::updateCustomerRecord(customer,0);
                        }
                        if(Employee::getEmployeeRecord(employee)>1){
                            Employee::updateEmployeeRecord(employee,Employee::getEmployeeRecord(employee)-1);                    
                        }else{
                            Employee::updateEmployeeRecord(employee,0); 
                        }
                    }

                    Car::updateCar(cars,Carname, Carmodel, 10 ,car_price, details);
                    
                    cust->rentedCars.erase(cust->rentedCars.find(Carname));
                    employee->rentedCars.erase(employee->rentedCars.find(Carname));                

                }else{
                    cout<<"Customer is not Registered !"<<endl;
                    cout<<"First Ask Manager to Register Customer"<<endl;
                }

                cout <<endl;
                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }                 
            }else{

                task=0;

            }

        }else{
            cout<<"Press integer corresponding to task You want to Perform"<<endl;  
            cout << "0. Logout"<<endl;          
            cout << "1. Add Customer" << endl;
            cout << "2. Update Customer" << endl;
            cout << "3. Delete Customer"<< endl;
            cout << "4. Add Employee"<< endl;
            cout << "5. Update Employee" << endl;
            cout << "6. Delete Employee"<< endl;
            cout << "7. Add Car"<< endl;
            cout << "8. Update Car" << endl;
            cout << "9. Delete Car"<< endl;
            cout << "10. All Cars Details"<<endl;

            temp=1;
            while(temp){
                cout << "Enter input integer in the range [0,10]: ";
                cin>>inp;
                if (inp==0 || inp == 1 || inp == 2 || inp == 3 || inp == 4 || inp == 5 || inp == 6 || inp == 7 || inp == 8 || inp==9 || inp==10) {
                    temp=0;
                } else {
                    cout<<"Enter Valid Input"<<endl;
                }
            }
            
            if(inp==0){
                task=0;
            }else if(inp==1){
                string customerName,customerId,customerRecord;
                unordered_map<string,string> cars_dates;
                unordered_set<string> cars_add;
                cout<<"Enter Customer Name: ";
                cin>>customerName;
                cout<<"Enter Customer ID: ";
                cin>>customerId;
                cout<<"Enter Customer password: ";
                cin>>password;
                
                Customer* new_customer = Customer::addCustomer(customerName, customerId, password, cars_add, 0 ,5,cars_dates);
                customers.push_back(new_customer);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==2){
                string customerName,customerId;
                double customerRecord;
                int fine;
                cout<<"Enter Customer Name: ";
                cin>>customerName;
                cout<<"Enter Customer ID: ";
                cin>>customerId;
                cout<<"Updated Fine due: ";
                cin>>fine;
                cout<<"Updated Customer Record: ";
                cin>>customerRecord;    

                Customer::updateCustomer(customers,customerName,customerId,fine,customerRecord);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==3){
                string customerName,customerId;
                cout<<"Enter Customer Name: ";
                cin>>customerName;
                cout<<"Enter Customer ID: ";
                cin>>customerId;

                Customer::deleteCustomer(customers,customerName,customerId);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==4){
                string employeeName,employeeId,employeeRecord;
                int fine;
                unordered_set<string> cars_add;
                cout<<"Enter Employee Name: ";
                cin>>employeeName;
                cout<<"Enter Employee ID: ";
                cin>>employeeId;
                cout<<"Enter Employee password: ";
                cin>>password;
                
                Employee* new_employee = Employee::addEmployee(employeeName,employeeId,password,cars_add,0,5);
                employees.push_back(new_employee); 

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==5){
                string employeeName,employeeId;
                double employeeRecord;
                int fine;
                cout<<"Enter Employee Name: ";
                cin>>employeeName;
                cout<<"Enter Employee ID: ";
                cin>>employeeId;
                cout<<"Updated Fine due: ";
                cin>>fine;
                cout<<"Updated Employee Record: ";
                cin>>employeeRecord;    

                Employee::updateEmployee(employees,employeeName,employeeId,fine,employeeRecord);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==6){
                string employeeName,employeeId;
                cout<<"Enter Employee Name: ";
                cin>>employeeName;
                cout<<"Enter Employee ID: ";
                cin>>employeeId;

                Employee::deleteEmployee(employees,employeeName,employeeId);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==7){
                string name,model,details;
                double renting_price,condition;
                cout<<"Enter New Car Details: "<<endl;
                cout<<"Car Name: ";
                cin>>name;
                cout<<"Car Model: ";
                cin>>model;
                cout<<"Enter Renting Price: ";
                cin>>renting_price;
                cin.ignore();
                cout<<"Car Other Details: ";
                getline(cin, details);

                Car* new_car = Car::addcar(name, model, 10,renting_price, details);
                cars.push_back(new_car);     

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==8){

                string name,model,details;
                double renting_price,condition;
                cout<<"Enter Updated Car Details: "<<endl;
                cout<<"Car Name: ";
                cin>>name;
                cout<<"Car Model: ";
                cin>>model;
                cout<<"Car updated renting price : ";
                cin>>renting_price;
                cin.ignore();
                cout<<"Car Updated Other Details: ";
                getline(cin, details);

                Car::updateCar(cars,name, model, 10, renting_price, details);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==9){
                string name,model;
                cout<<"Enter Car Details To Remove that Car: "<<endl;
                cout<<"Car Name: ";
                cin>>name;
                cout<<"Car Model: ";
                cin>>model;   

                Car::deleteCar(cars,name,model);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==10){
                Car::showAvailableCars(cars);
                Customer::showAllRentedCar(customers);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }
            }
        }
    } 

    ofstream f1customers,f1managers,f1employees,f1cars;
    f1customers.open("customers.txt");
    f1managers.open("managers.txt");
    f1employees.open("employees.txt");
    f1cars.open("cars.txt");

    for(int i=0;i<(customers).size();i++){
        f1customers<<(customers[i])->name<<"\n";
        f1customers<<(customers[i])->ID<<"\n";
        f1customers<<(customers[i])->password<<"\n";
        for(auto x:(customers[i])->rentedCars){
            f1customers<<x<<",";
        }
        f1customers<<"\n";
        for(auto x:(customers[i])->rentedCars){
            f1customers<<car_duedates[x]<<",";
        }
        f1customers<<"\n";
        f1customers<<Customer::checkFine(Customer::searchCustomer(customers,(customers[i])->name,(customers[i])->ID))<<"\n";
        f1customers<<Customer::getCustomerRecord(Customer::searchCustomer(customers,(customers[i])->name,(customers[i])->ID))<<"\n";
    }
    for(int i=0;i<(employees).size();i++){
        f1employees<<(employees[i])->name<<"\n";
        f1employees<<(employees[i])->ID<<"\n";
        f1employees<<(employees[i])->password<<"\n";
        for(auto x:(employees[i])->rentedCars){
            f1employees<<x<<",";
        }
        f1employees<<"\n";
        f1employees<<Employee::checkFine(Employee::searchEmployee(employees, (employees[i])->name,(employees[i])->ID))<<"\n";
        f1employees<<Employee::getEmployeeRecord(Employee::searchEmployee(employees, (employees[i])->name,(employees[i])->ID))<<"\n";
    }

    for(int i=0;i<(managers).size();i++){
        f1managers<<(managers[i])->name<<"\n";
        f1managers<<(managers[i])->ID<<"\n";
        f1managers<<(managers[i])->password<<"\n";
    }

    for(int i=0;i<(cars).size();i++){
        f1cars<<Car::getName(cars[i])<<"\n";
        f1cars<<Car::getModel(cars[i])<<"\n";
        f1cars<<Car::getCondition(cars[i])<<"\n";
        f1cars<<Car::getPrice(cars[i])<<"\n";
        f1cars<<Car::getDetails(cars[i])<<"\n";
    }

    f1employees.close();f1customers.close();f1managers.close();f1cars.close();
    return 0;

}
