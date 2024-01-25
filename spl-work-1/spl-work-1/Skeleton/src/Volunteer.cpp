#include "../include/Volunteer.h"
#include <string>
#include <vector>

//constructor
Volunteer:: Volunteer(int id1, const string &name1):id(id1),name(name1){
    completedOrderId=NO_ORDER;
    activeOrderId=NO_ORDER;
};

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

CollectorVolunteer:: CollectorVolunteer(int id1, const string &name1, int coolDown1):id(id1),name(name1),coolDown(coolDown1){
    timeLeft=coolDown1;
    completedOrderId=NO_ORDER;
    activeOrderId=NO_ORDER;
}

CollectorVolunteer* CollectorVolunteer::clone() const {
    return new CollectorVolunteer(*this);
}

//need to add step here

