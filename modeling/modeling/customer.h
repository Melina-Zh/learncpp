//
//  customer.h
//  modeling
//
//  Created by Melina on 2018/10/6.
//  Copyright © 2018年 Melina. All rights reserved.
//

#ifndef customer_h
#define customer_h
class customer{
private:
    double arrive_time;
    double serving_time;
    double waiting_time=0;
    int i_d;
public:
    customer(){}
    customer(double arrive_time,double serving_time,int i_d):
    arrive_time(arrive_time),serving_time(serving_time),i_d(i_d){}
    double get_arr()const{
        return arrive_time;
    }
    int get_id()const{
        return i_d;
    }
    void s_wait(double time){
        waiting_time+=time;
    }
    double total_time(){
        return arrive_time+serving_time+waiting_time;
    }
};

#endif /* customer_h */
