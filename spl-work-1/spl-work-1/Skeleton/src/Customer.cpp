#include "../include/Customer.h"
#include <iostream>
#include <string>
#include <vector>

Customer:: Customer(int id, const string &name, int locationDistance, int maxOrders)
    : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders),ordersId(),ordersLeft(maxOrders) { 
        std::cout<<"customer maxordEs "+std::to_string(maxOrders);
    }

const string &Customer:: getName() const{
    return name;
}
int Customer:: getId() const{
    return id;
}
int Customer:: getCustomerDistance() const{
    return locationDistance;
}
int Customer:: getMaxOrders() const{
    return maxOrders;
}
int Customer:: getNumOrders() const{
    return ordersId.size();
}
bool Customer:: canMakeOrder() const{
    std::cout<<"\n can make order? " + std::to_string(ordersLeft);
    return (ordersLeft>0);
}
 const vector<int> &Customer:: getOrdersIds() const{
    return ordersId;
 }
 int Customer:: addOrder(int orderId){
    if(canMakeOrder()){
        ordersId.push_back(orderId);
        ordersLeft--;
        return orderId;
    }
    else
        return -1;
 }

 //soldier customer
 SoldierCustomer:: SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders)
    : Customer(id, name, locationDistance, maxOrders) {}


SoldierCustomer* SoldierCustomer::clone() const {
    return new SoldierCustomer(*this);
}


//civilian customer
CivilianCustomer:: CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders)
    : Customer(id, name, locationDistance, maxOrders) {}


CivilianCustomer* CivilianCustomer::clone() const {
    return new CivilianCustomer(*this);
}

