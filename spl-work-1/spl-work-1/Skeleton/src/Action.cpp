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
    string output = std::to_string(numOfSteps) + "actions completed";
    return output;
}


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
        newCustomer = new SoldierCustomer(idnew, customerName, distance, maxOrders);//we need to check how to delete this in the end becuase its in the heap
    else
        newCustomer = new CivilianCustomer(idnew, customerName, distance, maxOrders);//we need to check how to delete this in the end becuase its in the heap
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
        s1+=" Soldier ";
    }
    else{
        s1+=" Civilian ";
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
        }
        else{
            cout <<"CustomerID:" <<currentCustomer->getId();
            vector<int> orderIDS = currentCustomer->getOrdersIds();
            for(int orderID: orderIDS){
                cout<<"OrderID: "<< orderID;
                if(wareHouse.getOrder(orderID).getStatus()==OrderStatus::PENDING){
                    cout<<"OrderStatus: Pending";
                }
                if(wareHouse.getOrder(orderID).getStatus()==OrderStatus::COMPLETED){
                    cout<<"OrderStatus: Completed";
                }
                if(wareHouse.getOrder(orderID).getStatus()==OrderStatus::DELIVERING){
                    cout<<"OrderStatus: Delivering";
                }
                if(wareHouse.getOrder(orderID).getStatus()==OrderStatus::COLLECTING){
                    cout<<"OrderStatus: Collecting";
                }
            cout<< "numOrdersLeft: "<<currentCustomer->getMaxOrders() - currentCustomer->getNumOrders();
            }
            complete();
        }
    
    
    wareHouse.addAction(this);
}
PrintCustomerStatus* PrintCustomerStatus::clone() const {
    return new PrintCustomerStatus(*this);
}
string PrintCustomerStatus:: toString() const{
    string s1="";
    if(getStatus()==ActionStatus::COMPLETED){
        s1+="status: Completed";
    }
    else{
        s1+="status: Error \n";
        s1+= "errorMsg: " + getErrorMsg()+"\n";
    }
    s1+= "customerID: "+ std::to_string(customerId) + "\n";
    return s1;
}
string PrintOrderStatus:: toString() const{
    string s1;
    if(getStatus()==ActionStatus::COMPLETED){
        s1+="status: Completed";
    }
    else{
        s1+="status: Error \n";
        s1+= "errorMsg: " + getErrorMsg()+"\n";
    }
    s1+="\n" ;
    s1+= "orderID: "+ std::to_string(orderId) + "\n";
    return s1;
}
//PrintOrderStatus
PrintOrderStatus::PrintOrderStatus(int id):orderId(id){}
void PrintOrderStatus::act(WareHouse &wareHouse){
    Order o1 = wareHouse.getOrder(orderId);
    if(o1.getId()==-1){
        error("Order doesn't exist");
    }
    else{
        complete();
        cout<<"orderID:"+std::to_string(orderId)+"\n";
                
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
        cout<< "\n";
        cout<<"CustomerId: "+std::to_string(o1.getCustomerId());
        if(o1.getCollectorId()==-1){
            cout<<"CollectorID: None";
        }
        else{
            cout<<"CollectorID: "+std::to_string(o1.getCollectorId());
        }
        if(o1.getDriverId()==-1){
            cout<<"DriverID: None";
        }
        else{
            cout<<"DriverID: "+std::to_string(o1.getDriverId());
        }
    }
    wareHouse.addAction(this);
}
PrintOrderStatus* PrintOrderStatus::clone() const {
    return new PrintOrderStatus(*this);
}
string PrintOrderStatus:: toString() const{
    string s1="";
    if(getStatus()==ActionStatus::COMPLETED){
        s1+="status: Completed";
    }
    else{
        s1+="status: Error \n";
        s1+= "errorMsg: " + getErrorMsg()+"\n";
    }
    s1+="\n" ;
    s1+= "OrderID: "+ std::to_string(orderId) + "\n";
    return s1;
}
//PrintVolunteerStatus
PrintVolunteerStatus::PrintVolunteerStatus(int id):volunteerId(id){

}
void PrintVolunteerStatus:: act(WareHouse &wareHouse){
    if(volunteerId>wareHouse.getVolunteerCounter()){
        error("Volunteer Doesn't exist");
    }
    else{
        Volunteer *v=&wareHouse.getVolunteer(volunteerId);
        if(v->getId()==-1){
            error("Volunteer Doesn't exist");
        }
        else{
            cout<< v->toString();
            complete();
            wareHouse.addAction(this);
        }
    }
}
PrintVolunteerStatus* PrintVolunteerStatus::clone() const {
    return new PrintVolunteerStatus(*this);
}
string PrintVolunteerStatus:: toString() const{
    string s1;
    if(getStatus()==ActionStatus::COMPLETED){
        s1+="status: Completed";
    }
    else{
        s1+="status: Error \n";
        s1+= "errorMsg: " + getErrorMsg()+"\n";
    }
    s1+="\n" ;
    s1+= "VolunteerID: "+ std::to_string(volunteerId) + "\n";
    return s1;
}

//PrintActionsLog

PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(WareHouse &wareHouse){
    for (BaseAction *ba : wareHouse.getActions()) {
            cout<<ba->toString();
    }
    complete();
    wareHouse.addAction(this);
}
PrintActionsLog* PrintActionsLog::clone() const {
    return new PrintActionsLog(*this);
}
string PrintActionsLog:: toString() const{
    return "PrintActionLog: Completed";
}

//BackupWareHouse
BackupWareHouse::BackupWareHouse(){}
void BackupWareHouse::act(WareHouse &wareHouse){
    backup=new WareHouse(wareHouse);
    complete();
    wareHouse.addAction(this);
}
BackupWareHouse* BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}
string BackupWareHouse:: toString() const{
    return "Backup: Completed";
}
