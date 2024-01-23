
#include <string>
#include <vector>
#include "../include/Order.h"
#include "../include/Customer.h"
#include "../include/WareHouse.h"

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