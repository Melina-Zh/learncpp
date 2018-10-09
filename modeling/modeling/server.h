//
//  server.h
//  modeling
//
//  Created by Melina on 2018/10/6.
//  Copyright © 2018年 Melina. All rights reserved.
//

#ifndef server_h
#define server_h
#include <iostream>
#include "customer.h"
using namespace std;
class server{
private:
    int busy;
    customer current_cu;
    //double area;
   // vector<customer> each_queue;
public:
    server(){
        busy=0;
        current_cu=customer();
    }
    bool isbusy(){
        return(busy==0)?false:true;
    }
    void release(){
        
        cout<<"the No."<<current_cu.get_id()<<" customer Done!"<<endl;
        busy=0;
    }
    double curr_total_time(){
        return current_cu.total_time();
    }
    void work(customer cu,int i){
        cout<<"The No."<<i<<" server is serving the No."<<cu.get_id()<<" customer."<<endl;
        current_cu=cu;
        busy=1;
    }
    int current_id(){
        return current_cu.get_id();
    }
    
};

#endif /* server_h */
