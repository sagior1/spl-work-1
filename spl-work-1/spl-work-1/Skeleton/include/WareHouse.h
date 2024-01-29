#pragma once
#include <string>
#include <vector>

#include "Order.h"
#include "Customer.h"

class BaseAction;
class Volunteer;

//Warehouse responsible for Volunteers, Customers Actions, and Orders.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        void start();
        void addOrder(Order* order);//done
        void addAction(BaseAction* action);//done
        Customer &getCustomer(int customerId) const;//done
        Volunteer &getVolunteer(int volunteerId) const;//done
        Order &getOrder(int orderId) const;//done
        const vector<BaseAction*> &getActions() const;//done
        void close();//done
        void open();//done
        int &getcustomerCounter() const;//done?
        void addCustomer(Customer* newCustomer);//done
        void addVolunteer(Volunteer* newVolunteer);//done
        void deleteVolunteer(int volunteerID);
        int getVolunteerCounter() const;
        void step();
        void pendingOrdersStep();//done
        void step2();
        void isExist();
        void FileTOCode(string configFilePath);
        bool isExist(string line, string toFind);

        void moveBetweenVectors(vector<Order*> vectorToDelete, vector<Order*> vectorToInsert, Order order1);
        void deleteSpecificVolenteer(Volunteer* volToDelete );
        void processOrdersStep(); //delete step2()
        int getOrderCounter() const;
        void printAllOrders(); 

        ~WareHouse(); 
        WareHouse(const WareHouse& other);
        WareHouse& operator=(const WareHouse& other);
        WareHouse(WareHouse&& other) noexcept;
        WareHouse& operator=(WareHouse&& other) noexcept;
        //***new***
    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int ordersCounter; //For assigning unique order IDs
};
