#include "../include/Volunteer.h"
#include <string>
#include <vector>
#include <string>

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
    if(order1.getStatus()==OrderStatus::COLLECTING&&getTimeLeft()==0){
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
    bool busy=(timeLeft!=0);
    string s1= "name: " + getName() + "volunteerID: " + std::to_string(getId()) + " isBusy: " + std::to_string(busy)+ " orderID: ";
    if(busy){
        s1+=activeOrderId;
    }
    else{
        s1+="None";
    }
    s1+=" ordersLeft: No Limit";

    return s1;
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
    if(hasOrdersLeft()&&order.getStatus()==OrderStatus::PENDING&&getTimeLeft()==0){
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
    string s1= "name: " + getName() + "volunteerID: " + std::to_string(getId()) + " isBusy: " + std::to_string(busy)+ " orderID: ";
    if(isBusy()){
        s1+=activeOrderId;
    }
    else{
        s1+="None";
    }
    s1+=" ordersLeft: "+getNumOrdersLeft();

    return s1;
}

//driverVolunteer

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
    distanceLeft--;
    return (distanceLeft<=0);
}
bool DriverVolunteer:: hasOrdersLeft() const{
    return true;
}
bool DriverVolunteer:: canTakeOrder(const Order &order) const{
        if(order.getStatus()==OrderStatus::COLLECTING&&getDistanceLeft()==0){
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
    string s1= "name: " + getName() + "volunteerID: " + std::to_string(getId()) + " isBusy: " + std::to_string(busy)+ " orderID: ";
    if(isBusy()){
        s1+=activeOrderId;
    }
    else{
        s1+="None";
    }
    s1+=" ordersLeft: No Limit";

    return s1;
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
    if(hasOrdersLeft()&&order.getStatus()==OrderStatus::COLLECTING&&getDistanceLeft()==0){
        return true;
    }
    else return false;
}
void LimitedDriverVolunteer:: acceptOrder(const Order &order){
    DriverVolunteer::acceptOrder(order); // Call the acceptOrder of the base class
    ordersLeft--; // Decrease the number of orders left
}
string LimitedDriverVolunteer:: toString() const{
    string s1= "name: " + getName() + "volunteerID: " + std::to_string(getId()) + " isBusy: " + std::to_string(busy)+ " orderID: ";
    if(isBusy()){
        s1+=activeOrderId;
    }
    else{
        s1+="None";
    }
    s1+=" ordersLeft: "+ getNumOrdersLeft();

    return s1;
}
