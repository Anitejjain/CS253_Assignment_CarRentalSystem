Car Rental Management System

**Functionalities**:
The Car Rental Management System is a software application designed to manage the rental operations of a car rental company. It can perform the management of customer, employee, manager, and car data. It also updates fine on rented car by taking due date and current date from system imposing 200 Rs fine on each extra day. It also updates Record of Customer and Employees dynamically on returning of Car if Car Condition gets Depleted then There will be decrease in customer record and employee record also on late returning it happens.

**Features**:

**Customers**:
1. **View Available Cars for Renting**
2. **View Rented Cars by Himself**
3. **Check Fine Due**

**Employees**:
1. **View Available Cars for Renting**
2. **View Rented Cars by Himself**
3. **Check Fine Due on His Rented Car**
4. **Rent Car to Customer**
5. **Return Car from Customer**

**Managers**:
1. **Add Customer**
2. **Update Customer**
3. **Delete Customer**
4. **Add Employee**
5. **Update Employee**
6. **Delete Employee**
7. **Add Car**
8. **Update Car**
9. **Delete Car**
10. **All Cars Details Rented or Not Rented**

**Technologies Used**:
- **C++**
- **Object-Oriented Programming**
- **File I/O**
- **Standard Template Library (STL)**

**Input Files**:
1. **customers.txt**:
   - Input Format:
     1. Customer Name (string)
     2. Customer ID (string)
     3. Customer Password (string)
     4. Customer Rented Cars Separated by Comma without spaces ending with comma like audi,ford,
     5. Customer Rented Cars due dates (Format: "YYYY-MM-DD") Separated by Comma without spaces ending with comma like 2024-03-05,2024-04-01,
     6. Customer Fine (Double)
     7. Customer Record (integer ranging 0-10)

2. **employees.txt**:
   - Input Format:
     1. Employee Name (string)
     2. Employee ID (string)
     3. Employee Password (string)
     4. Employee Rented Cars Separated by Comma without spaces ending with comma like audi,ford,
     5. Employee Rented Cars Fine Due (Double)
     6. Employee record (integer ranging 0-10)

3. **manager.txt**:
   - Input Format:
     1. Manager Name (string)
     2. Manager ID (string)
     3. Manager Password (string)

4. **cars.txt**:
   - Input Format:
     1. Car Name (string)
     2. Car Number/Model (string)
     3. Car Condition (integer ranging 1-10) { Initially Before renting assume to be 10}
     4. Car Price (double)
     5. Car Other details
