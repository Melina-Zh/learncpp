//
//  main.cpp
//  modeling
//
//  Created by Melina on 2018/10/6.
//  Copyright © 2018年 Melina. All rights reserved.
//

#include <iostream>
#include "server.h"
#include "customer.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <math.h>
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    double aver_arrive_time,aver_serve_time;
    int customer_num,max_queue_num,queue_num;
    cout << "Plense enter the average arriving time"<< endl;//average 1/lambda
    cin >> aver_arrive_time;
    if(aver_arrive_time<1e-8){
        cout<<"There will never be two persons arriving at bank at the same time"<<endl;
        return 0;
    }
    cout << "Plense enter the average serving time"<< endl;
    cin >> aver_serve_time;
    if(aver_serve_time<1e-8){
        cout<<"We need time to serve each person"<<endl;
        return 0;
    }
    
    cout << "Plense enter the number of customers"<< endl;
    cin >> customer_num;
    
    cout << "Plense enter the maxinum number of one queue"<< endl;
    cin >> max_queue_num;
    
    cout << "Plense enter the number of servers"<< endl;
    cin >> queue_num;
    
    double arrive_time=0.0,serving_time=0.0,lambda_arr=0.0,lambda_ser=0.0,pv=0.0;
    int i=0,j=0,flag=0,k=0;
    int min=0,crowd=0;
    int f=0;
    double min_c,exp_time;
    vector<customer> queue;//the only customer queue
    vector<int> release_server;
    srand((unsigned)time(0));
    server servers[queue_num];
    lambda_ser=1/aver_serve_time;
    lambda_arr=1/aver_arrive_time;
    
    
        
        pv=(double)(rand()%20)/20.0;
        while(pv==0){
           pv=(double)(rand()%20)/20.0;
        }
        serving_time=(-1.0/lambda_ser)*log(1-pv);
        customer cu;
        customer c_ini(arrive_time,serving_time,i);
        if(queue.size()<max_queue_num){
            //cout<<"The No."<<i<<" customer arrives."<<endl;
            queue.push_back(c_ini);
        }
        else{
            cout<<"There is no space for the No."<<i<<" customer. He is furious but he has to leave"<<endl;
        }
        cu=queue[0];
    
            
            while(i<customer_num){
                if(i>=1){
                    pv=(double)(rand()%20)/20.0;
                    while(pv==0){
                        pv=(double)(rand()%20)/20.0;
                    }
                    serving_time=(-1.0/lambda_ser)*log(1-pv);
                    customer c(arrive_time,serving_time,i);
                    if(queue.size()<max_queue_num){
                        //cout<<"The No."<<i<<" customer arrives."<<endl;
                        queue.push_back(c);
                    }
                    else{
                        cout<<"There is no space for the No."<<i<<" customer. He is furious but he has to leave"<<endl;
                    }
                    cu=queue[0];
                }
                
            
            while(j<queue_num){
                if(servers[j].isbusy()&&(cu.get_arr()>servers[j].curr_total_time())){//release
                    release_server.push_back(j);
            }
            j++;
            }
        //release
            while(release_server.size()!=0){
                min=0;
                min_c=servers[release_server[0]].curr_total_time();
                for(k=1;k<release_server.size();k++){
                    if(servers[release_server[k]].curr_total_time()<min_c){
                        min=k;
                        min_c=servers[release_server[k]].curr_total_time();
                    }
                }
                servers[release_server[min]].release();
                vector<int>::iterator iter = release_server.begin()+min;
                release_server.erase(iter);
                if(flag==0){
                    f=min;
                    
                }
                flag=1;
            }
            if(flag==1){
                cout<<"The No."<<i<<" customer arrives."<<endl;
                servers[min].work(cu,min);
            }
            
            
            j=0;
            if(flag==0){
                while(flag==0&&j<queue_num){//let the free court serve the customer.
                    if(!servers[j].isbusy()){
                        cout<<"The No."<<i<<" customer arrives."<<endl;
                        servers[j].work(cu,j);
                        flag=1;
                    }
                    j++;
                }
                if(flag==0){
                    cout<<"The No."<<i<<" customer arrives."<<endl;
                    j=0;
                    min=0;
                    min_c=servers[0].curr_total_time();
                    for(j=1;j<queue_num;j++){
                        if(servers[j].curr_total_time()<min){
                            min=j;
                            min_c=servers[j].curr_total_time();
                        }
                    }
                    cout<<i<<"has to wait"<<endl;
                    if(arrive_time>servers[min].curr_total_time()){
                        crowd=0;
                        servers[min].release();
                        
                        cu.s_wait(servers[min].curr_total_time()-cu.get_arr());
                        servers[min].work(cu,min);
                        flag=1;
                        
                    }
                    else{
                        crowd=1;
                    }
                    
                    
                }
                
               
            }
            if(flag==1){
                vector<customer>::iterator iter = queue.begin();
                queue.erase(iter);
            }
            
        flag=0;
        j=0;
        i++;
                pv=(double)(rand()%20)/20.0;
                while(pv==0||pv==1){
                    pv=(double)(rand()%20)/20.0;
                }
                arrive_time+=(-1.0/lambda_arr)*log(1-pv);
    }
 
        while(queue.size()!=0){//release the queue
          
            
                j=0;
                min=0;
                min_c=servers[0].curr_total_time();
                for(j=1;j<queue_num;j++){
                    if(servers[j].curr_total_time()<min){
                        min=j;
                        min_c=servers[j].curr_total_time();
                    }
                }
            
                    servers[min].release();
                    
                    cu.s_wait(servers[min].curr_total_time()-cu.get_arr());
                    servers[min].work(cu,min);
                    
            
            
                vector<customer>::iterator iter = queue.begin();
                queue.erase(iter);
            
            
            
    }
    //release all servers
    j=0;
    while(j<queue_num){
        if(servers[j].isbusy()){//release
            release_server.push_back(j);
        }
        
        j++;
    }
    //release
    while(release_server.size()!=0){
        min=0;
        min_c=servers[release_server[0]].curr_total_time();
        for(k=1;k<release_server.size();k++){
            if(servers[release_server[k]].curr_total_time()<min_c){
                min=k;
                min_c=servers[release_server[k]].curr_total_time();
            }
        }
        servers[release_server[min]].release();
        vector<int>::iterator iter = release_server.begin()+min;
        release_server.erase(iter);
    }

    cout<<"The End"<<endl;
    return 0;
}