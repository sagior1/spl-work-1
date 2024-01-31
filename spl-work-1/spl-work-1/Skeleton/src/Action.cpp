#include "../include/Action.h"
#include <iostream>
#include "../include/Volunteer.h"
#include <string>
#include <vector>
#include "../include/WareHouse.h"
#include "../include/Customer.h"
using std::string;
using std::vector; 
using namespace std; 


//global variable backup
extern WareHouse* backup;


//BaseAction
BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::COMPLETED) {}

ActionStatus BaseAction::getStatus() const {
    return status;
}
void BaseAction:: error(string errorMSG){
    errorMsg = errorMSG;
    status = ActionStatus::ERROR;
}
string BaseAction:: getErrorMsg() const{
    return errorMsg;
}
void BaseAction:: complete(){
    status = ActionStatus::COMPLETED;
}

//close
Close::Close(){}

void Close ::act(WareHouse &wareHouse){
    wareHouse.printAllOrders();
    complete();
    wareHouse.addAction(this);
    wareHouse.close();
}


Close *Close::clone() const {
    return new Close(*this);
}

string Close::toString() const{
    string output = "WareHouse is closed!";
    return output;
}


//simulate step
SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps){}

void SimulateStep::act(WareHouse &wareHouse) {
    for(int i=0; i < numOfSteps; i++){
        wareHouse.step();
    }
    complete();
    wareHouse.addAction(this);
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

string SimulateStep::toString() const{
    string output ="simulateStep "+ std::to_string(numOfSteps) + " COMPLETED";
    return output;
}

//AddOrder  
AddOrder::AddOrder(const int customerId) : customerId(customerId){}

void AddOrder::act(WareHouse &wareHouse){
    Customer &customer1 = (wareHouse.getCustomer(customerId));
    if(customer1.getId()==-1){
        error("Cannot place this order");
        cout<<getErrorMsg();
    }
    else{
        int customer_distance = customer1.getCustomerDistance();
        Order *order1 = new Order(wareHouse.getOrderCounter(), customerId, customer_distance);
        if(customer1.canMakeOrder()){
            customer1.addOrder(order1->getId());
            wareHouse.addOrder(order1);
            complete();
        }
        else {
            error("Cannot place this order");
            cout<<getErrorMsg();
        }
    } 
    wareHouse.addAction(this);
} 

string AddOrder:: toString() const{
    string s1= "order " + customerId ;
    if(getStatus() == ActionStatus::COMPLETED){
        s1+=" Completed";
    }
    else{ 
        s1+=" Error";
    }
    return s1;
}

AddOrder *AddOrder::clone() const {
    return new AddOrder(*this);
}

//addCustomer

AddCustomer::AddCustomer(string customerName1, string customerType1, int distance1, int maxOrders1) 
    : customerName(customerName1), 
      customerType(customerType1 == "soldier" ? CustomerType::Soldier : CustomerType::Civilian), 
      distance(distance1), 
      maxOrders(maxOrders1) {}
void AddCustomer::act(WareHouse &wareHouse) {
    int idnew = wareHouse.getcustomerCounter() + 1;
    Customer* newCustomer;
    if((int)customerType==0)// i dont know if this is ok
        newCustomer = new SoldierCustomer(idnew, customerName, distance, maxOrders);
    else
        newCustomer = new CivilianCustomer(idnew, customerName, distance, maxOrders);
    wareHouse.addCustomer(newCustomer);
    complete();
    wareHouse.addAction(this);
}

AddCustomer *AddCustomer::clone() const {
    return new AddCustomer(*this);
}
string AddCustomer::toString() const{
    string s1;
    s1+="Customer " + customerName;
    if(customerType==CustomerType::Soldier){
        s1+="Soldier ";
    }
    else{
        s1+="Civilian ";
    }
    s1+=distance +" "+ maxOrders;
    return s1;
}


//print customer status
PrintCustomerStatus:: PrintCustomerStatus(int cID):customerId(cID){}

void PrintCustomerStatus::act(WareHouse &wareHouse) {
        Customer *currentCustomer = &wareHouse.getCustomer(customerId);
        if(currentCustomer->getId()==-1){
            error("Customer Doesn't exist");
            cout<<"\n"<<getErrorMsg();
        }
        else{
            vector<int> orderIDS = currentCustomer->getOrdersIds();
            for(int orderID: orderIDS){
                cout<<"\n orderId: "<< std::to_string(orderID);

                Order o1=wareHouse.getOrder(orderID);
                if(o1.getStatus()==OrderStatus::PENDING){
                    cout<<"OrderStatus: Pending";
                }
                if(o1.getStatus()==OrderStatus::COMPLETED){
                    cout<<"OrderStatus: Completed";
                }
                if(o1.getStatus()==OrderStatus::DELIVERING){
                    cout<<"OrderStatus: Delivering";
                }
                if(o1.getStatus()==OrderStatus::COLLECTING){
                    cout<<"OrderStatus: Collecting";
                }
            }
            cout<< "\nnumOrdersLeft: "<<std::to_string(currentCustomer->getOrdersLeft());
            complete();
        }
    
    
    wareHouse.addAction(this);
}
PrintCustomerStatus* PrintCustomerStatus::clone() const {
    return new PrintCustomerStatus(*this);
}
string PrintCustomerStatus:: toString() const{
    string s1="CustomerStatus "+customerId;
    if(getStatus()==ActionStatus::COMPLETED){
        s1+=" Completed";
    }
    else{
        s1+=" Error";
    }
    return s1;
}

//PrintVolunteerStatus
PrintVolunteerStatus::PrintVolunteerStatus(int id):volunteerId(id){

}
void PrintVolunteerStatus:: act(WareHouse &wareHouse){

    Volunteer *v=&wareHouse.getVolunteer(volunteerId);
    if(v->getId()==-1){
        error("Volunteer Doesn't exist");
        cout<<"\n"<<getErrorMsg();
    }
    else{
        cout<< v->toString();
        complete();
        wareHouse.addAction(this);
    }
}
PrintVolunteerStatus* PrintVolunteerStatus::clone() const {
    return new PrintVolunteerStatus(*this);
}
string PrintVolunteerStatus:: toString() const{
    string s1="volunteerStatus "+ volunteerId;
    if(getStatus()==ActionStatus::COMPLETED){
        s1+=" Completed";
    }
    else{
        s1+=" Error";
    }
    return s1;
}
//PrintOrderStatus
PrintOrderStatus::PrintOrderStatus(int id):orderId(id){}
void PrintOrderStatus::act(WareHouse &wareHouse){
    Order o1 = wareHouse.getOrder(orderId);
    if(o1.getId()==-1){
        error("Order doesn't exist");
        cout<<"\n"<<getErrorMsg();
    }
    else{
        complete();
        cout<<"\n"<<o1.toString();
    }
    wareHouse.addAction(this);
}
PrintOrderStatus* PrintOrderStatus::clone() const {
    return new PrintOrderStatus(*this);
}
string PrintOrderStatus:: toString() const{
    string s1="orderStatus "+ orderId;
    if(getStatus()==ActionStatus::COMPLETED){
        s1+=" Completed";
    }
    else{
        s1+=" Error";
    }
    return s1;
}
//PrintActionsLog

PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(WareHouse &wareHouse){
    
    wareHouse.printAllActions();
    
    complete();
    wareHouse.addAction(this);
    cout<<"\n"<<toString();
}
PrintActionsLog* PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}
string PrintActionsLog:: toString() const{
    return "Log Completed ";
}

//BackupWareHouse
BackupWareHouse::BackupWareHouse(){}

void BackupWareHouse::act(WareHouse &wareHouse){
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }

    backup = new WareHouse(wareHouse);
    complete();
    wareHouse.addAction(this);
}
BackupWareHouse* BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}
string BackupWareHouse:: toString() const{
    return "Backup: Completed";
}

//restore wareHouse
RestoreWareHouse::RestoreWareHouse(){}

void RestoreWareHouse::act(WareHouse &wareHouse){
    if(backup == nullptr){
        error("No backup available");
        cout<<this->toString();
    }
    else{
        wareHouse=*backup;
    }
    complete();
    wareHouse.addAction(this);
}

RestoreWareHouse* RestoreWareHouse::clone() const {
    return new RestoreWareHouse(*this);
}

string RestoreWareHouse:: toString() const{
    return "Restore: Completed";
}
