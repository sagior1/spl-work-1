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
WareHouse::WareHouse(const string &configFilePath): isOpen(false), // or whatever default value it should have
      actionsLog(),
      volunteers(),
      pendingOrders(),
      inProcessOrders(),
      completedOrders(), 
      customers(),
      customerCounter(0),
      volunteerCounter(0),
      ordersCounter(0){
   FileTOCode(configFilePath); 
   start();
}

WareHouse::~WareHouse() {
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    volunteers.clear();
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
    for (BaseAction* action : actionsLog) {
        delete action;
    }
    actionsLog.clear();
}
// Copy assignment operator
WareHouse& WareHouse::operator=(const WareHouse& other) {
    for (Customer* customer : customers) {
        delete customer;
    }
    customers.clear();
    for (Volunteer* volunteer : volunteers) {
        delete volunteer;
    }
    volunteers.clear();
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
    for (BaseAction* action : actionsLog) {
        delete action;
    }
    actionsLog.clear();


        // 2: allocate new memory and copy the elements
        for(auto *action : other.actionsLog)
            actionsLog.push_back(action->clone());
        for(auto *volunteer : other.volunteers)
            volunteers.push_back(volunteer->clone());
        for(auto *order : other.pendingOrders)
            pendingOrders.push_back(order->clone());
        for(auto *order : other.inProcessOrders)
            inProcessOrders.push_back(order->clone());
        for(auto *order : other.completedOrders)
            completedOrders.push_back(order->clone());
        for(auto *customer : other.customers)
            customers.push_back(customer->clone());

        // 3: assign the other members
        isOpen = other.isOpen;
        customerCounter = other.customerCounter;
        volunteerCounter = other.volunteerCounter;
        ordersCounter=other.ordersCounter;
    
    return *this;
}


// Copy constructor
WareHouse::WareHouse(const WareHouse& other) 
    : isOpen(other.isOpen), 
      actionsLog(),
      volunteers(),
      pendingOrders(),
      inProcessOrders(),
      completedOrders(),
      customers(), 
      customerCounter(other.customerCounter), 
      volunteerCounter(other.volunteerCounter),
      ordersCounter(other.ordersCounter)
{
    // Deep copy each vector
    for(auto *action : other.actionsLog)
        actionsLog.push_back(action->clone());
    for(auto *volunteer : other.volunteers)
        volunteers.push_back(volunteer->clone());
    for(auto *order : other.pendingOrders)
        pendingOrders.push_back(order->clone());
    for(auto *order : other.inProcessOrders)
        inProcessOrders.push_back(order->clone());
    for(auto *order : other.completedOrders)
        completedOrders.push_back(order->clone());
    for(auto *customer : other.customers)
        customers.push_back(customer->clone());
}

// Move constructor
WareHouse::WareHouse(WareHouse&& other) noexcept
    : isOpen(std::move(other.isOpen)),
      actionsLog(std::move(other.actionsLog)),
      volunteers(std::move(other.volunteers)),
      pendingOrders(std::move(other.pendingOrders)),
      inProcessOrders(std::move(other.inProcessOrders)),
      completedOrders(std::move(other.completedOrders)),
      customers(std::move(other.customers)),
      customerCounter(other.customerCounter),
      volunteerCounter(other.volunteerCounter),
      ordersCounter(other.ordersCounter) {
}

// Move assignment operator
WareHouse& WareHouse::operator=(WareHouse&& other) noexcept {
    if (this != &other) {
        // Free up any resources that 'this' is holding before taking ownership of 'other'
        actionsLog.clear();
        volunteers.clear();
        pendingOrders.clear();
        inProcessOrders.clear();
        completedOrders.clear();
        customers.clear();

        // Transfer ownership of 'other' to 'this'
        isOpen = std::move(other.isOpen);
        actionsLog = std::move(other.actionsLog);
        volunteers = std::move(other.volunteers);
        pendingOrders = std::move(other.pendingOrders);
        inProcessOrders = std::move(other.inProcessOrders);
        completedOrders = std::move(other.completedOrders);
        customers = std::move(other.customers);
        customerCounter = std::move(other.customerCounter);
        volunteerCounter = std::move(other.volunteerCounter);
        ordersCounter = std::move(other.ordersCounter);

        // Invalidate the data in 'other'
        other.actionsLog.clear();
        other.volunteers.clear();
        other.pendingOrders.clear();
        other.inProcessOrders.clear();
        other.completedOrders.clear();
        other.customers.clear();
    }
    return *this;
}


void WareHouse:: start(){
     open();
     cout<<"Warehouse is open!";
    string command;
    //int num, maxOrders;
    while (isOpen){
        cout << "\nInsert your next command:" << endl;
        string input, command;
        getline(cin, input);  // Read the entire line of input
        std::istringstream input2(input);
        input2 >> command;
        if (command == "customer"){
            string type, name;
            int num, maxOrders;
            input2 >> name >> type >> num >> maxOrders;
            cout << name << ", " << type << ", " << to_string(num) << ", " << to_string(maxOrders) <<endl;
            AddCustomer *c1= new AddCustomer(name, type, num, maxOrders);
            c1->act(*this);
        }
        if (command == "order"){
            int num;
            input2 >> num;
            AddOrder *o1= new AddOrder(num);
            o1->act(*this);
        }
        else if (command == "orderStatus"){
            int num;
            input2 >> num;
            PrintOrderStatus *p1=new PrintOrderStatus(num);
            p1->act(*this);
        }
        else if (command == "step"){
            int num;
            input2 >> num;
            SimulateStep *s1=new SimulateStep(num);
            s1->act(*this);
        }
        else if (command == "volunteerStatus"){
            int id;
            input2 >> id;
            PrintVolunteerStatus *v1= new PrintVolunteerStatus(id);
            v1->act(*this);
        }
        else if (command == "customerStatus"){
            int num;
            input2 >> num;
            PrintCustomerStatus *c1=new PrintCustomerStatus(num);
            c1->act(*this);
        }
        else if (command == "log"){
            PrintActionsLog *cl1= new PrintActionsLog();
            cl1->act(*this);
        }  
        else if (command == "close"){
            Close *cl1= new Close();
            cl1->act(*this);
        }
        else if (command == "backup"){
            BackupWareHouse *bu1= new BackupWareHouse();
            bu1->act(*this);
        }
        else if (command == "restore"){
            RestoreWareHouse *res1= new RestoreWareHouse();
            res1->act(*this);
        }    

    }
 }
void WareHouse::addOrder(Order* order){
    pendingOrders.push_back(order);
    ordersCounter++;
}
void WareHouse:: addAction(BaseAction* a1){
    actionsLog.push_back(a1);
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
            delete *it; 
            volunteers.erase(it); // Remove the pointer from the vector
            return; // Exit the function after deleting the volunteer
        }
    }
}


//getting a customer by ID
Customer &WareHouse:: getCustomer(int cID) const{
    static CivilianCustomer invalidCustomer(-1, "Invalid", 0, 0);
    for (auto *customer : customers) {
        if (customer->getId() == cID) {
            return *customer;
        }
    }

    return invalidCustomer; // Return the invalid customer if no match is found
}

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

int WareHouse:: getVolunteerCounter() const{
    return (volunteerCounter);
}

int WareHouse:: getOrderCounter() const{
    return ordersCounter;
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
                    currOrder->setCollectorId(currVol->getId());
                    moveBetweenVectors(pendingOrders,inProcessOrders,*currOrder);
                }
                else{
                    currOrder->setStatus(OrderStatus::DELIVERING);
                    currOrder->setDriverId(currVol->getId());
                    moveBetweenVectors(pendingOrders,inProcessOrders,*currOrder);

                }
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
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             SoldierCustomer* SoliderCustomer1 = new SoldierCustomer(getcustomerCounter(),name, customer_distance, max_orders);
             addCustomer(SoliderCustomer1);
        }
        if (isExist(line2, "customer")){
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             CivilianCustomer* CivilianCustomer1 = new CivilianCustomer(getcustomerCounter(), name, customer_distance, max_orders);
             addCustomer(CivilianCustomer1);
        }
        else if (isExist(line2, "limited_collector")){
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown >> max_orders;
            LimitedCollectorVolunteer* LimitedCollectorVolunteer1 = new LimitedCollectorVolunteer(volunteerCounter ,name, volunteer_coolDown ,max_orders);
            addVolunteer(LimitedCollectorVolunteer1);
        }
        else if (isExist(line2, "collector")){
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown;
            CollectorVolunteer* CollectorVolunteer1 = new CollectorVolunteer(volunteerCounter, name, volunteer_coolDown);
            addVolunteer(CollectorVolunteer1);
        }
        else if (isExist(line2, "limited_driver")){
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step >> max_orders;
            LimitedDriverVolunteer* LimitedDriverVolunteer1= new LimitedDriverVolunteer(volunteerCounter, name, volunteer_maxDistance, distance_per_step, max_orders);
            addVolunteer(LimitedDriverVolunteer1);
        }
        else if (isExist(line2, "driver")){
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step;
            DriverVolunteer* DriverVolunteer1 = new DriverVolunteer(volunteerCounter, name, volunteer_maxDistance, distance_per_step);
            addVolunteer(DriverVolunteer1);
        }
    }
    
    MYfile.close();

}

//***NEW****
void WareHouse::moveBetweenVectors(vector<Order*>& vectorToDelete, vector<Order*>& vectorToInsert, Order& order1){
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
        if (currOrder->getStatus() == OrderStatus::DELIVERING){ 
        int volId = currOrder->getDriverId();
        Volunteer &Volenteer2 = getVolunteer(volId);
        Volenteer2.step();
        if(!(Volenteer2.isBusy())){
                currOrder->setStatus(OrderStatus::COMPLETED);
                moveBetweenVectors(inProcessOrders, completedOrders, *currOrder);
            }
            if (!(Volenteer2.hasOrdersLeft())){
                deleteSpecificVolenteer(&Volenteer2);
            }
        }
    }    
    

}

void WareHouse::printAllOrders(){
    for(auto *currPendingOrder : pendingOrders){
        string orderDitails1 ="Order Id: "+ to_string(currPendingOrder->getId()) + ", "+ to_string(currPendingOrder->getCustomerId()) + ", " + currPendingOrder->orderStatusToString(currPendingOrder->getStatus());
        cout << orderDitails1 << endl;
    }
    for(auto *currInProcessOrder : inProcessOrders){
        string orderDitails2 ="Order Id: "+ to_string(currInProcessOrder->getId()) + ", "+ to_string(currInProcessOrder->getCustomerId()) + ", " + currInProcessOrder->orderStatusToString(currInProcessOrder->getStatus());
        cout << orderDitails2 << endl;
    }
    for(auto *currcompletedOrder : completedOrders){
        string orderDitails3 ="Order Id: "+ to_string(currcompletedOrder->getId()) + ", "+ to_string(currcompletedOrder->getCustomerId()) + ", " + currcompletedOrder->orderStatusToString(currcompletedOrder->getStatus());
        cout << orderDitails3 << endl;
    }
}
void WareHouse::printAllActions(){
        for(auto *action : actionsLog){
        cout << action->toString() << endl;
    }
}
