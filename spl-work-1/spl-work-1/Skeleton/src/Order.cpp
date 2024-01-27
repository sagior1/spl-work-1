#pragma once

#include <string>
#include <vector>
using std::string;
#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "../include/Volunteer.h"
//#include "WareHouse.h"
//#include "Volunteer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<iterator> 
#include<vector> 
using namespace std;

//Constructor
Order:: Order(int id, int customerId, int distance):id(id),customerId(customerId),distance(distance){
    status=OrderStatus::PENDING;
    collectorId=NO_VOLUNTEER;
    driverId=NO_VOLUNTEER;
}

//Copy Constructor
Order::Order(const Order& other)
    : id(other.id), customerId(other.customerId), distance(other.distance),
      status(other.status), collectorId(other.collectorId), driverId(other.driverId) {
}

int Order:: getId() const{
    return id;
}

int Order:: getCustomerId() const{
    return customerId;
}

int Order:: getDistance() const{
    return distance;
}

void Order:: setStatus(OrderStatus status){
    this->status=status;
}

void Order:: setCollectorId(int collectorId){
    this->collectorId=collectorId;
}

void Order:: setDriverId(int driverId){
    this->driverId=driverId;
}

int Order:: getCollectorId() const{
    return collectorId;
}

int Order:: getDriverId() const{
    return driverId;
}

OrderStatus Order:: getStatus() const{
    return status;
}

//how to do non when there is no collector or no Driver?
string const Order:: toString() const{
    string OrderStat;
    if(status==OrderStatus::PENDING){
        OrderStat ="Pending";
    }
    else if(status==OrderStatus::COMPLETED){
        OrderStat = "Completed";
    }
    if(status==OrderStatus::DELIVERING){
        OrderStat = "Delivering";
    }
    if(status==OrderStatus::COLLECTING){
        OrderStat = "Collecting";
    }

    string orderStatus = "OrderID: " + to_string(id) + "\n" +
                        "OrderStatus: " + OrderStat + 
                        "\n CustomerID: " + to_string(customerId) +
                        "\n Collector: " + to_string(collectorId) +
                        "\n Driver: " + to_string(driverId);
    return orderStatus;
}
