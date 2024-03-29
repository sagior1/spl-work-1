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
Volunteer::Volunteer(int id1, const string &name1) 
    : completedOrderId(NO_ORDER), activeOrderId(NO_ORDER),id(id1), name(name1) {
}


int Volunteer:: getId() const{
    return id;
}

const string &Volunteer:: getName() const{
    return name;
}

int Volunteer:: getActiveOrderId() const{
    return activeOrderId;
}

int Volunteer:: getCompletedOrderId() const{
    return completedOrderId;
}

bool Volunteer:: isBusy() const{
    return(activeOrderId!=NO_ORDER);
}

//CollectorVolunteer

CollectorVolunteer::CollectorVolunteer(int id1, const string &name1, int coolDown1)
    : Volunteer(id1, name1), coolDown(coolDown1), timeLeft(0){
    completedOrderId=NO_ORDER;//set to -1
    activeOrderId=NO_ORDER;
}

//***NEW***
void CollectorVolunteer::step() {
    timeLeft--; 
    if(timeLeft == 0){
        completedOrderId=activeOrderId;//set completed order id
        activeOrderId = NO_ORDER;
    }
}

CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(*this);
}


int CollectorVolunteer::getCoolDown() const{
    return coolDown;
}
int CollectorVolunteer:: getTimeLeft() const{
    return timeLeft;
}
bool CollectorVolunteer:: decreaseCoolDown(){
    timeLeft--;//decrease timeleft
    if(timeLeft==0){
        completedOrderId=activeOrderId;//set completed order id
        return true;
    }
    else return false;
}
bool CollectorVolunteer::hasOrdersLeft() const{
    return true;
}
bool CollectorVolunteer:: canTakeOrder(const Order &order1) const{//here i put if the order is in collecting phase for the volunteer to be able to take it
    if(order1.getStatus()==OrderStatus::PENDING&&!isBusy()){
        return true;
    }
    else{
        return false;
    }
}
void CollectorVolunteer:: acceptOrder(const Order &order1){// i didnt take time left down here
    timeLeft=coolDown;
    activeOrderId=order1.getId();
}
string CollectorVolunteer:: toString() const{
    string output = "VolunteerID: " + std::to_string(getId()) +
                    "\nisBusy: " + (isBusy() ? "True" : "False") +
                    "\nOrderId: ";
    if(isBusy()){
        output+=to_string(activeOrderId);
        output+="\nTimeLeft: " + to_string(getTimeLeft());
    }
    else{
        output+="None";
        output+="\nTimeLeft: None";
    }
    output+="\nordersLeft: No Limit\n";

    return output;
}

//LimitedCollectorVolunteer

LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, const string &name, int coolDown ,int maxOrders1)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders1), ordersLeft(maxOrders1) {
}

LimitedCollectorVolunteer* LimitedCollectorVolunteer::clone() const {
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer:: hasOrdersLeft() const{
    return ordersLeft>0;
} 
bool LimitedCollectorVolunteer:: canTakeOrder(const Order &order) const{//same note as normal collector
    if(hasOrdersLeft()&&order.getStatus()==OrderStatus::PENDING&&!isBusy()){
        return true;
    }
    else return false;
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
    CollectorVolunteer::acceptOrder(order); // Call the acceptOrder of the base class
    ordersLeft--; // Decrease the number of orders left
}
int LimitedCollectorVolunteer:: getMaxOrders() const{
    return maxOrders;
} 
int LimitedCollectorVolunteer:: getNumOrdersLeft() const{
    return ordersLeft;
}
string LimitedCollectorVolunteer:: toString() const{ 
    string output = "VolunteerID: " + std::to_string(getId()) +
                    "\nisBusy: " + (isBusy() ? "True" : "False") +
                    "\nOrderId: ";
    if(isBusy()){
        output+=to_string(activeOrderId);
        output+="\nTimeLeft: " + to_string(getTimeLeft());
    }
    else{
        output+="None";
        output+="\nTimeLeft: None";
    }
    output+="\nordersLeft: " + to_string(ordersLeft) + "\n";

    return output;
}

//driverVolunteer

void DriverVolunteer::step() {
    distanceLeft = distanceLeft-distancePerStep;
    if(distanceLeft <= 0){
        activeOrderId = NO_ORDER;
    }
}

DriverVolunteer:: DriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep): Volunteer(id, name),maxDistance(maxDistance), distancePerStep(distancePerStep),distanceLeft(0){
}
DriverVolunteer* DriverVolunteer::clone() const {
    return new DriverVolunteer(*this);
}
int DriverVolunteer :: getDistanceLeft() const{
    return distanceLeft;
}
int DriverVolunteer:: getMaxDistance() const{
    return maxDistance;
}
int DriverVolunteer:: getDistancePerStep() const{
    return distancePerStep;
}
bool DriverVolunteer::decreaseDistanceLeft(){
    return (distanceLeft<=0);
}
bool DriverVolunteer:: hasOrdersLeft() const{
    return true;
}
bool DriverVolunteer:: canTakeOrder(const Order &order) const{
        if(order.getStatus()==OrderStatus::COLLECTING&&!isBusy() &&
        getMaxDistance() >= order.getDistance()){
            return true;
        }
        else
            return false;
}
void DriverVolunteer:: acceptOrder(const Order &order){
    distanceLeft=order.getDistance();
    activeOrderId=order.getId();
}
//add step here
string DriverVolunteer:: toString() const{
    string output = "VolunteerID: " + std::to_string(getId()) +
                    "\nisBusy: " + (isBusy() ? "True" : "False") +
                    "\nOrderId: ";
    if(isBusy()){
        output+=to_string(activeOrderId);
        output+="\nDistanceLeft: " + to_string(getDistanceLeft());
    }
    else{
        output+="None";
        output+="\nDistanceLeft: None";
    }
    output+="\nordersLeft: No Limit\n";

    return output;
}

//LimitedDriverVolunteer

LimitedDriverVolunteer:: LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep,int maxOrders):DriverVolunteer(id,name,maxDistance,distancePerStep),maxOrders(maxOrders),ordersLeft(maxOrders){
}
LimitedDriverVolunteer* LimitedDriverVolunteer::clone() const {
    return new LimitedDriverVolunteer(*this);
}
int LimitedDriverVolunteer:: getMaxOrders() const{
    return maxOrders;
}
int LimitedDriverVolunteer:: getNumOrdersLeft() const{
    return ordersLeft;
}
bool LimitedDriverVolunteer:: hasOrdersLeft() const{
    return (ordersLeft>0);
}
bool LimitedDriverVolunteer:: canTakeOrder(const Order &order) const{
    if(hasOrdersLeft()&&order.getStatus()==OrderStatus::COLLECTING&&!isBusy() &&
    getMaxDistance() >= order.getDistance()){
        return true;
    }
    else return false;
}
void LimitedDriverVolunteer:: acceptOrder(const Order &order){
    DriverVolunteer::acceptOrder(order); // Call the acceptOrder of the base class
    ordersLeft--; // Decrease the number of orders left
}
string LimitedDriverVolunteer:: toString() const{
    string output = "VolunteerID: " + std::to_string(getId()) +
                    "\nisBusy: " + (isBusy() ? "True" : "False") +
                    "\nOrderId: ";
    if(isBusy()){
        output+=to_string(activeOrderId);
        output+="\nDistanceLeft: " + to_string(getDistanceLeft());
    }
    else{
        output+="None";
        output+="\nDistanceLeft: None";
    }
    output+="\nordersLeft: " + to_string(getNumOrdersLeft()) + "\n";

    return output;
}
