#include "../include/WareHouse.h"
#include <iostream>

using namespace std;

WareHouse* backup = nullptr;

int main(int argc, char** argv){
//    if(argc!=2){
//        std::cout << "usage: warehouse <config_path>" << std::endl;
//        return 0;
//    }
    //tests
    cout << "its happaning" << endl;
    //tests
    
    
    string configurationFile = "C:\\Users\\rotem\\rotem\\SPLwork1\\configFileExample.txt";
    //string configurationFile = argv[1];
    WareHouse wareHouse(configurationFile);
    wareHouse.start();
    
    //tests
    PrintCustomerStatus customerMoshe(0);
    Order* o1 = new Order(1, 0, 3);
    Order* o2 = new Order(2, 0, 3);
    Order* o3 = new Order(3, 0, 3);
    wareHouse.addOrder(o1);
    wareHouse.addOrder(o2);
    wareHouse.addOrder(o3);
    customerMoshe.act(&wareHouse);
    //here the program should throw an error because the first customer has only 2 orders (moshe)
    cout << "\n good" << endl;
    
    
    //tests
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
