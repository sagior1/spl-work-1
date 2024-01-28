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
//AddOrder  
AddOrder::AddOrder(const int customerId) : customerId(customerId){}

void AddOrder::act(WareHouse &wareHouse){
    Customer &customer1 = (wareHouse.getCustomer(customerId));
    int customer_distance = customer1.getCustomerDistance();
    Order *order1 =new Order(wareHouse.getOrderCounter(), customerId, customer_distance);
    if(customer1.canMakeOrder()){
        cout<<"\n inside AddOrder in action.cpp the customer could make order and we are checking if he can add it \n";
        customer1.addOrder(order1->getId());
        wareHouse.addOrder(order1);
        complete();
    }
    else {
        error("There is no customer with customerID=" + to_string(customerId));
    } 
    wareHouse.addAction(this);
} 

string AddOrder:: toString() const{
    return "AddOrder: Completed";
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
        cout<<"\n entered printCustomerStatus in Action.cpp ";
        Customer *currentCustomer = &wareHouse.getCustomer(customerId);
        if(currentCustomer->getId()==-1){
            error("Customer Doesn't exist");
        }
        else{
            cout<<"\n";
            vector<int> orderIDS = currentCustomer->getOrdersIds();
            for(int orderID: orderIDS){
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
            cout<< " numOrdersLeft: "<<currentCustomer->getMaxOrders() - currentCustomer->getNumOrders();
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

//PrintVolunteerStatus
PrintVolunteerStatus::PrintVolunteerStatus(int id):volunteerId(id){

}
void PrintVolunteerStatus:: act(WareHouse &wareHouse){

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
PrintVolunteerStatus* PrintVolunteerStatus::clone() const {
    return new PrintVolunteerStatus(*this);
}
string PrintVolunteerStatus:: toString() const{
    string s1="";
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
