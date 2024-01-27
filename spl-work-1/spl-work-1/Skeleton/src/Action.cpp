#include "../include/Action.h"
#include <iostream>
#include <string>
#include <vector>
#include "../include/WareHouse.h"
#include "../include/Customer.h"
using std::string;
using std::vector; 
using namespace std; 




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
        SoldierCustomer* newCustomer = new SoldierCustomer(idnew, customerName, distance, maxOrders);//we need to check how to delete this in the end becuase its in the heap
    else
        CivilianCustomer* newCustomer = new CivilianCustomer(idnew, customerName, distance, maxOrders);//we need to check how to delete this in the end becuase its in the heap
    wareHouse.addCustomer(newCustomer);
    complete();
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
    if(customerId>wareHouse.getcustomerCounter()){
        error("Customer Doesn't exist");
    }
    else{//maybe we can take the tostirng from customer or order
        Customer *currentCustomer = &wareHouse.getCustomer(customerId);
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

        }
        cout<< "numOrdersLeft: "<<currentCustomer->getMaxOrders() - currentCustomer->getNumOrders();
    }
    
        complete();
}
PrintCustomerStatus* PrintCustomerStatus::clone() const {
    return new PrintCustomerStatus(*this);
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

//PrintVolunteerStatus
PrintVolunteerStatus::PrintVolunteerStatus(int id):volunteerId(id){
    
}
