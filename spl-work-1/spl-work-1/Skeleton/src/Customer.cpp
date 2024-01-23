#include "../include/Customer.h"
#include <iostream>
#include <string>
#include <vector>

Customer:: Customer(int id, const string &name, int locationDistance, int maxOrders)
    : id(id), name(name), locationDistance(locationDistance), maxOrders(maxOrders) {}

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
    return (ordersId.size()<maxOrders);
}
 const vector<int> &Customer:: getOrdersIds() const{
    return ordersId;
 }
 int Customer:: addOrder(int orderId){
    if(canMakeOrder()){
        ordersId.push_back(orderId);
        return orderId;
    }
    else
        return -1;
 }
 
 //soldier customer
 SoldierCustomer:: SoldierCustomer(int id, const string &name, int locationDistance, int maxOrders)// i am intrested why the name is &name
    : Customer(id, name, locationDistance, maxOrders) {}


SoldierCustomer* SoldierCustomer::clone() const {// i am not sure what is the right way to do the clone function
    return new SoldierCustomer(*this);
}

//civilian customer
CivilianCustomer:: CivilianCustomer(int id, const string &name, int locationDistance, int maxOrders)// i am intrested why the name is &name
    : Customer(id, name, locationDistance, maxOrders) {}


CivilianCustomer* CivilianCustomer::clone() const {// i am not sure what is the right way to do the clone function
    return new CivilianCustomer(*this);
}
