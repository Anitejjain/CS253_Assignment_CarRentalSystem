#include<iostream>
#include <fstream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;
 
class User {

    public:
        string name;
        string ID;
        string password;

};

class Customer : public User {
    private:
        string customerRecord;
        string otherDetails;
    public:
        unordered_set<string> rentedCars;
        double fineDue;

        static Customer* addCustomer(string n, string id, string pass, unordered_set<string> cars, double fine, string record){
            Customer* newcustomer = new Customer;
            newcustomer->name = n;
            newcustomer->ID = id;
            newcustomer->password = pass;
            newcustomer->rentedCars = cars;
            newcustomer->fineDue=fine;
            newcustomer->customerRecord=record;
            return newcustomer;           
        }

        static void deleteCustomer(vector<Customer*> customers,string customerName,string customerId){
            for (auto it = customers.begin(); it != customers.end(); ++it) {
                if ((*it)->name == customerName && (*it)->ID == customerId) {
                    delete *it;  
                    customers.erase(it); 
                    cout << "Customer \"" << customerName << " " << customerId << "\" has been deleted." << endl;
                    return ;
                }
            }
            cout << "Employee \"" << customerName << " " << customerId << "\" not Found." << endl;
            return ;            
        } 

        static void updateCustomer(vector<Customer*> customers,string customerName,string customerId,int fine,string record){
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
                        cout << *carIt << ", ";
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
                        cout << *carIt << ", ";
                    }
                    cout << endl;
                }
            }
        }
};

class Employee : public User {

    private:

        unordered_set<string> rentedCars;
        int fineDue;
        string employeeRecord;
        string otherDetails;

    public:

        static Employee* addEmployee(string n, string id, string pass, unordered_set<string> cars, double fine, string record){
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

        static int updateEmployee(vector<Employee*> employees,string employeeName,string employeeId,int fine,string record){
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

        static int deleteEmployee(vector<Employee*> employees,string employeeName,string employeeId){
            for (auto it = employees.begin(); it != employees.end(); ++it) {
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
        string carName;
        string carModel;
        string Conditions;
        string otherDetails;     
    public:

        static Car* addcar(string n, string model, string condition, string details){
            Car* newcar = new Car;
            newcar->carName = n;
            newcar->carModel = model;
            newcar->Conditions = condition;
            newcar->otherDetails = details;  
            return newcar;           
        }

        static void rentCar(vector<Car*>& cars, const string& carName, const string& carModel) {

            for (auto it = cars.begin(); it != cars.end(); ++it) {
                if ((*it)->carName == carName && (*it)->carModel == carModel) {
                    delete *it;  
                    cars.erase(it); 
                    cout << "Car \"" << carName << " " << carModel << "\" has been rented." << endl;
                    return;
                }
            }
            cout << "Car \"" << carName << " " << carModel << "\" not Found." << endl;
            return;
        }

        static void showAvailableCars(const vector<Car*>& cars){
            cout<<"Car Availble for Rent Details: "<<endl;
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                cout<<"Car Name: "<<(*it)->carName<<" Car Model: "<<(*it)->carModel<<endl;
            }
            cout << endl; 
        }

        static void updateCar(vector<Car*> cars,string carName,string carModel,string carCondition,string details){
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                if((*it)->carName == carName && (*it)->carModel == carModel){
                   (*it)->Conditions=carCondition;
                   (*it)->otherDetails=details;
                    cout << "Car \"" << carName << " " << carModel << "\" details has been updated." << endl;
                    return ;
                }
            }
            cout << "Car \"" << carName << " " << carModel << "\" not Found." << endl;
            return ;            
        }   

        static void deleteCar(vector<Car*> cars,string carName,string carModel){
            for (auto it = cars.begin(); it != cars.end(); ++it) {
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

        static void allCarDetails(vector<Car*> cars, vector<Customer*> customers){
            
        }
};

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

    fcustomers.seekg(0, ios::beg);
    
    while (getline(fcustomers, line)) {     
        string name = line;
        string id;
        string password;
        double fine_due;
        string record;
        unordered_set<string> rented_cars;

        getline(fcustomers, line);
        id = line;
        getline(fcustomers, line);
        password = line;
        getline(fcustomers, line);
        string car;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == ',') {
                rented_cars.insert(car);
                car = "";
            } else {
                car += line[i];
            }
        }

        getline(fcustomers, line);
        fine_due = stoi(line);
        getline(fcustomers, line);
        record = line;

        Customer* new_customer = Customer::addCustomer(name, id, password, rented_cars, fine_due, record);
        customers.push_back(new_customer);
    }

    while (getline(femployees, line)) {     
        string name = line;
        string id;
        string password;
        double fine_due;
        string record;
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
        record = line;

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
        string condition;
        string details;

        getline(fcars, line);
        model = line;
        getline(fcars, line);
        condition = line;
        getline(fcars, line);
        details = line;        

        Car* new_car = Car::addcar(name, model, condition, details);
        cars.push_back(new_car);
    }

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
                    cout << "Customer logged in successfully!" << endl;
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
                    cout << "Employee logged in successfully!" << endl;
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
                    cout << "Manager logged in successfully!" << endl;
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
            cout << "3. Rent Car" << endl;
            cout << "4. Check Fine Due"<< endl;
            cout << "5. Logout"<< endl;
            
            temp=1;
            while(temp){
                cout << "Enter input integer in the range [1,5]: ";
                cin>>inp;
                if (inp == 1 || inp == 2 || inp == 3 || inp == 4 || inp==5) {
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

                if(cars.size()==0){
                    cout<<"No Car Available for Renting !"<<endl;
                }
                else{
                    string Carname,Carmodel;
                    cout<<"Enter Car Details: "<<endl;
                    cout<<"Enter Car Name: ";
                    cin>>Carname;
                    cout<<"Enter Car Model: ";
                    cin>>Carmodel;
                    Car::rentCar(cars,Carname,Carmodel);

                    cout <<endl;
                    cout<<"Want to Perform Next Task Enter 1 else 0: ";
                    cin>>inp;
                    if(inp!=1){
                        task=0;
                    }
                }
            }else if(inp==4){
                cout<< customer->fineDue <<endl;
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
            cout << "4. Logout"<< endl;
            
            temp=1;
            while(temp){
                cout << "Enter input integer in the range [1,4]: ";
                cin>>inp;
                if (inp == 1 || inp == 2 || inp == 3 || inp == 4) {
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
                cout << "Enter input integer in the range [1,4]: ";
                cin>>inp;
                if (inp == 1 || inp == 2 || inp == 3 || inp == 4 || inp == 5 || inp == 6 || inp == 7 || inp == 8 || inp==9 || inp==10) {
                    temp=0;
                } else {
                    cout<<"Enter Valid Input"<<endl;
                }
            }
            
            if(inp==0){
                task=0;
            }else if(inp==1){
                string customerName,customerId,customerRecord;
                int fine;
                unordered_set<string> cars_add;
                cout<<"Enter Customer Name: ";
                cin>>customerName;
                cout<<"Enter Customer ID: ";
                cin>>customerId;
                cout<<"Enter Customer password: ";
                cin>>password;
                cout<<"Enter Fine due: ";
                cin>>fine;
                cout<<"Enter Customer  Record: ";
                cin>>customerRecord;
                
                Customer* new_customer = Customer::addCustomer(name, id, password, cars_add, fine, customerRecord);
                customers.push_back(new_customer);

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==2){
                string customerName,customerId,customerRecord;
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

                Employee::deleteEmployee(employees,customerName,customerId);

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
                cout<<"Enter Fine due: ";
                cin>>fine;
                cout<<"Enter Employee Record: ";
                cin>>employeeRecord;
                
                Employee* new_employee = Employee::addEmployee(employeeName,employeeId,password,cars_add,fine,"average");
                employees.push_back(new_employee); 

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==5){
                string employeeName,employeeId,employeeRecord;
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
                string name,model,condition,details;
                cout<<"Enter New Car Details: "<<endl;
                cout<<"Car Name: ";
                cin>>name;
                cout<<"Car Model: ";
                cin>>model;
                cout<<"Car Condition [1,10]: ";
                cin>>condition;
                cout<<"Car Other Details: ";
                cin>>details;

                Car* new_car = Car::addcar(name, model, condition, details);
                cars.push_back(new_car);     

                cout<<"Want to Perform Next Task Enter 1 else 0: ";
                cin>>inp;
                if(inp!=1){
                    task=0;
                }

            }else if(inp==8){

                string name,model,condition,details;
                cout<<"Enter Updated Car Details: "<<endl;
                cout<<"Car Name: ";
                cin>>name;
                cout<<"Car Model: ";
                cin>>model;
                cout<<"Car updated Condition [1,10]: ";
                cin>>condition;
                cout<<"Car Updated Other Details: ";
                cin>>details;

                Car::updateCar(cars,name, model, condition, details);

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
}