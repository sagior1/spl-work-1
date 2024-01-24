
#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"
#include "WareHouse.h"
#include "Volunteer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include<iterator> 
#include<vector> 
using namespace std;

//adding a new customer to WareHouse
void WareHouse:: addCustomer(Customer* newCustomer){
    customers.push_back(newCustomer);
    customerCounter + 1;
}

//geting a customer by ID
Customer& WareHouse:: getCustomer(int cID) const{
    for (auto &customer : customers) {
        if (customer->getId() == cID) {
            return *customer;
        }
    }
}

void WareHouse:: step(){
    pendingOrdersStep();
    //processOrdersStep();
}

//function isExist - helps us understand the people type by a keyword
bool isExist(string line, string toFind){
    size_t place = line.find(toFind);
    bool ExistsInLine = (place != std::string::npos);
    return ExistsInLine;
}


void configFilePath(){
    string line;
    fstream MYfile;
    //here you insert the file path
    //***TODO***  - check how todo it by name
    MYfile.open("C:\\Users\\rotem\\rotem\\SPLwork1\\RotemsFile.txt", ios::in);
    //initial all the relevant data types.
    string customer, volunteer, name, cType, vType;
    int customer_distance, max_orders, volunteer_coolDown, volunteer_maxDistance, distance_per_step;
    //starts the loop that reads the file
    while (getline(MYfile, line)){
        //dont read the comments in the file, in or out the lines
        size_t place = line.find('#');
        if (line.empty() || line[0] == '#'){
            continue;
        }
        string line2;
        if (place != std::string::npos){
            line2 = line.substr(0, place);
        }
        else (line2=line);
        
        //recognize the type of the person (costumer / volenteer) and also the inner types (collector / limited_collector exc) 
        //inside the "if", seperate the line to the relevant variabels and initiate the person in the wearhouse
        if (isExist(line2, "customer")){
            cout << "customer"<< endl;
             std::istringstream checked_line(line2);
             checked_line >> customer >> name >> cType >> customer_distance >> max_orders;
             cout << customer << ", " << name << ", " << cType << ", " << customer_distance << ", " << max_orders << endl;
            
        }
        else if (isExist(line2, "limited_collector")){
            cout << "limited_collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown >> max_orders;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << ", " << max_orders << endl;
        }
        else if (isExist(line2, "collector")){
            cout << "collector" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_coolDown;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_coolDown << endl;
        }
        else if (isExist(line2, "limited_driver")){
            cout << "limited_driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step >> max_orders;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << ", " << max_orders << endl;
        }
        else if (isExist(line2, "driver")){
            cout << "driver" << endl;
            std::istringstream checked_line(line2);
            checked_line >> volunteer >> name >> vType >> volunteer_maxDistance >> distance_per_step;
            cout << volunteer << ", " << name << ", " << vType << ", " << volunteer_maxDistance << ", " << distance_per_step << endl;
        }
    }
    
    MYfile.close();

}

//**NEW** function - simulate step2
void step2() {

for (Volunteer *currentVol : volunteers){
    if (*currentVol.isBusy()){
        if (*currentVol.type = CollectorVolunteer){
            if (*currentVol.decreaseCoolDown()){
                *currentVol.restoreTimeLeft();
            }
            //there is no need to call for decreaseCoolDown() again, because the function already decreesed the timeleft by 1.
        }
        else if (*currentVol.type = LimitedCollectorVolunteer){
            if (*currentVol.decreaseCoolDown()){
                *currentVol.restoreTimeLeft();
                if (!(hasOrdersLeft())){
                    //******DELETE*****
                }
        }
    }

    }
}
