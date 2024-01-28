#include "../include/WareHouse.h"
#include "../include/Action.h"

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
    
    
    string configurationFile = "/home/users/bsc/sagior/Downloads/configFileExample.txt";
    //string configurationFile = argv[1];
    WareHouse wareHouse(configurationFile);
    wareHouse.start();
        //tests
    AddOrder o1(0);
    AddOrder o2(0);
    AddOrder o3(0);
    PrintCustomerStatus customerMoshe(0);
    o1.act(wareHouse);
    o2.act(wareHouse);
    customerMoshe.act(wareHouse);

    PrintOrderStatus pos(0);
    pos.act(wareHouse);
    // o3.act(wareHouse);
    // customerMoshe.act(wareHouse);

    //here the program should throw an error because the first customer has only 2 orders (moshe)
    cout << "\n good" << endl;
    
    
    //tests
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    return 0;
}
