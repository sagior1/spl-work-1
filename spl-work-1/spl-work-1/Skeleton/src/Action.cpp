#include "../include/Action.h"
#include <iostream>
#include <string>
#include <vector>
#include "../include/WareHouse.h"
#include "../include/Customer.h"
using std::string;
using std::vector; 
using namespace std; 

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
string AddCustomer::toString() const{//need to check the what is needed in this toString
    return "AddCustomer: " + customerName;
}


//print customer status
PrintCustomerStatus:: PrintCustomerStatus(int cID):customerId(cID){}

void PrintCustomerStatus::act(WareHouse &wareHouse) {
    if(customerId>wareHouse.getcustomerCounter()){
        error("Customer Doesn't exist");
    }
    else{
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

