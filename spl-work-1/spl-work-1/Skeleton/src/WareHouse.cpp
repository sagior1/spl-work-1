#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<iterator> 
#include<vector> 
using namespace std;

WareHouse::~WareHouse() {
    // Delete all dynamically allocated Customer objects
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();
    // Delete all dynamically allocated Volunteer objects
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    volunteers.clear();
}


void WareHouse:: start(){//i dont know what is needed here
    open();
    cout<<"Warehouse is open!";
}
void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
}
void WareHouse:: addAction(BaseAction* action){
    actionsLog.push_back(action);
}

//adding a new customer to WareHouse
void WareHouse:: addCustomer(Customer* newCustomer){
    customers.push_back(newCustomer);
    customerCounter ++;
}
void WareHouse:: addVolunteer(Volunteer* newVolunteer){
    volunteers.push_back(newVolunteer);
    volunteerCounter++;
}
void WareHouse:: deleteVolunteer(int vID){
    for (auto it = volunteers.begin(); it != volunteers.end(); ++it) {
        if ((*it)->getId() == vID) {
            delete *it; // Delete the dynamically allocated Volunteer
            volunteers.erase(it); // Remove the pointer from the vector
            return; // Exit the function after deleting the volunteer
        }
    }
}

//getting a customer by ID
Customer &WareHouse:: getCustomer(int cID) const{//maybe need here another return if we dont find the customer
    static CivilianCustomer invalidCustomer(-1, "Invalid", 0, 0); // Represents an invalid customer
    for (Customer *customer : customers) {
        if (customer->getId() == cID) {
            return *customer;
        }
    }
    return invalidCustomer; // Return the invalid customer if no match is found
}//need to check if this hirtut is good

Volunteer &WareHouse:: getVolunteer(int vID) const{//maybe need here another return if we dont find the volunteer
    static CollectorVolunteer invalidVolunteer(-1,"Invalid",0);
    for (Volunteer *vol : volunteers) {
        if (vol->getId() == vID) {
            return *vol;
        }
    }
    return invalidVolunteer;
}


Order &WareHouse:: getOrder(int oID) const{//maybe need here another return if we dont find the volunteer
    for (Order *order1 : pendingOrders) {
        if (order1->getId() == oID) {
            return *order1;
        }
    }
        for (Order *order1 : inProcessOrders) {
        if (order1->getId() == oID) {
            return *order1;
        }
    }
        for (Order *order1 : completedOrders) {
        if (order1->getId() == oID) {
            return *order1;
        }
    }
}
const vector<BaseAction*> &WareHouse:: getActions()const{
    return actionsLog;
}
void WareHouse:: close(){
    isOpen=false;
}
void WareHouse:: open(){
    isOpen=true;
}
int &WareHouse:: getcustomerCounter() const{
    return const_cast<int&>(customerCounter); //i dont know if this is right
}

void WareHouse:: step(){
    pendingOrdersStep();
    //processOrdersStep();
}

void WareHouse:: pendingOrdersStep(){
    for (Order *currOrder: pendingOrders)
    {
        for(Volunteer *currVol: volunteers){
            if(currVol->canTakeOrder(*currOrder)){
                currVol->acceptOrder(*currOrder);
                if(currOrder->getStatus()==OrderStatus::PENDING){
                    currOrder->setStatus(OrderStatus::COLLECTING);
                }
                else{
                    currOrder->setStatus(OrderStatus::DELIVERING);
                }
                break;
            }
        }
    }
    
}

//function isExist - helps us understand the people type by a keyword
bool isExist(string line, string toFind){
    size_t place = line.find(toFind);
    bool ExistsInLine = (place != std::string::npos);
    return ExistsInLine;
}

void configFilePath(){
    string line;
    fstream MYfile;
    //here you insert the file path
    //***TODO***  - check how todo it by name
    MYfile.open("C:\\Users\\rotem\\rotem\\SPLwork1\\RotemsFile.txt", ios::in);
    //initial all the relevant data types.
    string customer, volunteer, name, cType, vType;
    int customer_distance, max_orders, volunteer_coolDown, volunteer_maxDistance, distance_per_step;
    //starts the loop that reads the file
    while (getline(MYfile, line)){
        //dont read the comments in the file, in or out the lines
        size_t place = line.find('#');
        if (line.empty() || line[0] == '#'){
            continue;
        }
        string line2;
        if (place != std::string::npos){
            line2 = line.substr(0, place);
        }
        else (line2=line);
        
        //recognize the type of the person (costumer / volenteer) and also the inner types (collector / limited_collector exc) 
        //inside the "if", seperate the line to the relevant variabels and initiate the person in the wearhouse
        if (isExist(line2, "customer")){
            cout << "customer"<< endl;
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             cout << customer << ", " << name << ", " << cType << ", " << customer_distance << ", " << max_orders << endl;
            
        }
        else if (isExist(line2, "limited_collector")){
            cout << "limited_collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown >> max_orders;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << ", " << max_orders << endl;
        }
        else if (isExist(line2, "collector")){
            cout << "collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << endl;
        }
        else if (isExist(line2, "limited_driver")){
            cout << "limited_driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step >> max_orders;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << ", " << max_orders << endl;
        }
        else if (isExist(line2, "driver")){
            cout << "driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << endl;
        }
    }
    
    MYfile.close();

}

//**NEW** function - simulate step2
void WareHouse:: step2() {

for (Volunteer *currentVol : volunteers){
    if (currentVol.isBusy()){
        if (*currentVol.type = CollectorVolunteer){
            if (*currentVol.decreaseCoolDown()){
                *currentVol.restoreTimeLeft();
            }
            //there is no need to call for decreaseCoolDown() again, because the function already decreesed the timeleft by 1.
        }
        else if (*currentVol.type = LimitedCollectorVolunteer){
            if (*currentVol.decreaseCoolDown()){
                *currentVol.restoreTimeLeft();
                if (!(hasOrdersLeft())){
                    //******DELETE*****
                }
        }
    }

    }
}
}
