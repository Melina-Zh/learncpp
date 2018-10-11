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
static double wait_t=0;
static double fina_time;
static double fina_ser=0;
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
        wait_t+=current_cu.g_wait();
        //cout<<"wait_t: "<<wait_t;
        fina_time=current_cu.total_time();
        cout<<"the No."<<current_cu.get_id()<<" customer Done!"<<endl;
        busy=0;
    }
    double curr_total_time(){
        return current_cu.total_time();
    }
    void work(customer cu,int i){
        cout<<"The No."<<i<<" server is serving the No."<<cu.get_id()<<" customer."<<endl;
        if(current_cu.total_time()>cu.get_arr()){
            cu.s_wait(current_cu.total_time()-cu.get_arr());
        }
        
        current_cu=cu;
        fina_ser+=current_cu.g_ser();
        busy=1;
    }
    int current_id(){
        return current_cu.get_id();
    }
    double g_w()const{
        return wait_t;
    }
    double g_f()const{
        return fina_time;
    }
    double g_s()const{
        return fina_ser;
    }
    
};

#endif /* server_h */
