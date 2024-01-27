#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "../include/Action.h"
#include "../include/Volunteer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<iterator> 
#include<vector> 
using namespace std;

//constructor
WareHouse::WareHouse(const string &configFilePath){
   FileTOCode(configFilePath); 
}

//Destructor
WareHouse::~WareHouse() {
    // Delete all dynamically allocated Customers
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();
    // Delete all dynamically allocated Volunteers
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    volunteers.clear();
    // Delete all dynamically allocated Orders
    for (Order* order : pendingOrders) {
        delete order;
    }
    pendingOrders.clear();
        for (Order* order : inProcessOrders) {
        delete order;
    }
    inProcessOrders.clear();
        for (Order* order : completedOrders) {
        delete order;
    }
    completedOrders.clear();
}

//Copy assignment operator
WareHouse& WareHouse::operator=(const WareHouse& other) {
    if (this != &other) { // protect against invalid self-assignment
        // 1: deallocate memory that 'this' used to hold
        for(auto &action : actionsLog)
            delete action;
        for(auto &volunteer : volunteers)
            delete volunteer;
        for(auto &order : pendingOrders)
            delete order;
        for(auto &order : inProcessOrders)
            delete order;
        for(auto &order : completedOrders)
            delete order;
        for(auto &customer : customers)
            delete customer;

        // 2: allocate new memory and copy the elements
        actionsLog = other.actionsLog;
        volunteers = other.volunteers;
        pendingOrders = other.pendingOrders;
        inProcessOrders = other.inProcessOrders;
        completedOrders = other.completedOrders;
        customers = other.customers;

        // 3: assign the other members
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
    }
    // by convention, always return *this
    return *this;
}


// Copy constructor
WareHouse::WareHouse(const WareHouse& other) 
    : isOpen(other.isOpen), 
      customerCounter(other.customerCounter), 
      volunteerCounter(other.volunteerCounter) {
    // Deep copy each vector
    for(BaseAction *action : other.actionsLog)
        actionsLog.push_back(action->clone());
    for(auto *volunteer : other.volunteers)
        volunteers.push_back(volunteer->clone());
    for(auto *order : other.pendingOrders)
        pendingOrders.push_back(new Order(*order));
    for(auto *order : other.inProcessOrders)
        inProcessOrders.push_back(new Order(*order));
    for(auto *order : other.completedOrders)
        completedOrders.push_back(new Order(*order));
    for(auto *customer : other.customers)
        customers.push_back(customer->clone());
}

void WareHouse:: start(){
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


Order &WareHouse:: getOrder(int oID) const{
    static Order invalidOrder(-1,-1,-1);
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
    return invalidOrder;
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
    processOrdersStep();
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
                moveBetweenVectors(pendingOrders,inProcessOrders,*currOrder);
                break;
            }
        }
    }
    
}

//function isExist - helps us understand the people type by a keyword
bool WareHouse::isExist(string line, string toFind){
    size_t place = line.find(toFind);
    bool ExistsInLine = (place != std::string::npos);
    return ExistsInLine;
}

void WareHouse::FileTOCode(string configFilePath){
    string line;
    fstream MYfile;
    //here you insert the file path
    //***TODO***  - check how todo it by name
    MYfile.open(configFilePath, ios::in);
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
        if (isExist(line2, "solider")){
            //cout << "solider"<< endl;
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             SoldierCustomer* SoliderCustomer1 = new SoldierCustomer(getcustomerCounter(),name, customer_distance, max_orders);
             addCustomer(SoliderCustomer1);
             //cout << customer << ", " << name << ", " << cType << ", " << customer_distance << ", " << max_orders << endl;
        }
        if (isExist(line2, "customer")){
            //cout << "customer"<< endl;
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             CivilianCustomer* CivilianCustomer1 = new CivilianCustomer(getcustomerCounter(), name, customer_distance, max_orders);
             addCustomer(CivilianCustomer1);
             //cout << customer << ", " << name << ", " << cType << ", " << customer_distance << ", " << max_orders << endl;
        }
        else if (isExist(line2, "limited_collector")){
            cout << "limited_collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown >> max_orders;
            LimitedCollectorVolunteer* LimitedCollectorVolunteer1 = new LimitedCollectorVolunteer(getVolunteerCounter() ,name, volunteer_coolDown ,max_orders);
            addVolunteer(LimitedCollectorVolunteer1);
            //cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << ", " << max_orders << endl;
        }
        else if (isExist(line2, "collector")){
            cout << "collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown;
            CollectorVolunteer* CollectorVolunteer1 = new CollectorVolunteer(getVolunteerCounter(), name, volunteer_coolDown);
            addVolunteer(CollectorVolunteer1);
            //cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << endl;
        }
        else if (isExist(line2, "limited_driver")){
            cout << "limited_driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step >> max_orders;
            LimitedDriverVolunteer* LimitedDriverVolunteer1= new LimitedDriverVolunteer(getVolunteerCounter(), name, volunteer_maxDistance, distance_per_step, max_orders);
            addVolunteer(LimitedDriverVolunteer1);
            //cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << ", " << max_orders << endl;
        }
        else if (isExist(line2, "driver")){
            cout << "driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step;
            DriverVolunteer* DriverVolunteer1 = new DriverVolunteer(getVolunteerCounter(), name, volunteer_maxDistance, distance_per_step);
            addVolunteer(DriverVolunteer1);
            // << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << endl;
        }
    }
    
    MYfile.close();

}

//***NEW****
void WareHouse::moveBetweenVectors(vector<Order*> vectorToDelete, vector<Order*> vectorToInsert, Order order1){
    Order* pOrder = &order1;
    vectorToInsert.push_back(pOrder);
    
    auto iter = vectorToDelete.begin();
    while (iter != vectorToDelete.end()) {
        if (*iter == pOrder) {
            iter = vectorToDelete.erase(iter);
            break;
        } else {
            ++iter;
        }
        
    }
}

void WareHouse:: deleteSpecificVolenteer(Volunteer* volToDelete ){
    auto iter = volunteers.begin();
    while (iter != volunteers.end()) {
        if (*iter == volToDelete) {
            delete volToDelete;
            iter = volunteers.erase(iter);
            break;
        } else {
            ++iter;
        }
        
    }
}


void WareHouse::processOrdersStep() {

for(auto *currOrder : inProcessOrders){
    if (currOrder->getStatus() == OrderStatus::COLLECTING){
        int volId = currOrder->getCollectorId();
        Volunteer &Volenteer1 = getVolunteer(volId);
        Volenteer1.step();
        if(!(Volenteer1.isBusy())){
            moveBetweenVectors(inProcessOrders, pendingOrders, *currOrder);
        }
        if (!(Volenteer1.hasOrdersLeft())){
            deleteSpecificVolenteer(&Volenteer1);
        }
    }
    
    else {
       int volId = currOrder->getCollectorId();
       Volunteer &Volenteer2 = getVolunteer(volId);
       Volenteer2.step();
       if(!(Volenteer2.isBusy())){
            moveBetweenVectors(inProcessOrders, completedOrders, *currOrder);
        }
        if (!(Volenteer2.hasOrdersLeft())){
            deleteSpecificVolenteer(&Volenteer2);
        }
    }
}    
    

    }
