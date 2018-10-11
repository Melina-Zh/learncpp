//
//  main.cpp
//  modeling
//
//  Created by Melina on 2018/10/6.
//  Copyright © 2018年 Melina. All rights reserved.
//

#include <iostream>
#include <stdio.h>
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
    
    printf("Plense enter the average arriving time\n");//average 1/lambda
    scanf("%lf",&aver_arrive_time);
    
    if(aver_arrive_time<1e-8){
        cout<<"There will never be two persons arriving at bank at the same time"<<endl;
        return 0;
    }
    cout << "Plense enter the average serving time"<< endl;
    scanf("%lf",&aver_serve_time);
    if(aver_serve_time<1e-8){
        cout<<"We need time to serve each person"<<endl;
        return 0;
    }
    
    cout << "Plense enter the number of customers"<< endl;
    scanf("%d",&customer_num);
    
    
    cout << "Plense enter the maxinum number of one queue"<< endl;
    //cin >> max_queue_num;
    scanf("%d",&max_queue_num);
    cout << "Plense enter the number of servers"<< endl;
    //cin >> queue_num;
    scanf("%d",&queue_num);
    double arrive_time=0.0,serving_time=0.0,lambda_arr=0.0,lambda_ser=0.0,pv=0.0;
    int i=0,j=0,flag=0,k=0;
    int min=0;
    double min_c;
    int f=0,t=0;
    int cu_delay=0;
    vector<customer> queue;//the only customer queue
    vector<int> release_server;
    srand((unsigned)time(0));
    server servers[queue_num];
    lambda_ser=1/aver_serve_time;
    lambda_arr=1/aver_arrive_time;

        customer cu;
   
    
            
        while(i<customer_num){
            
            t=0;
            pv=(double)(rand()%20)/20.0;
            while(pv==0||pv==1){
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
                
                i++;
                
                continue;
            }
            
            j=0;
            while(j<queue_num){
                
                if(servers[j].isbusy()&&(c.get_arr()>servers[j].curr_total_time())){//release
                    release_server.push_back(j);
                }
                j++;
            }
            //release
            while(release_server.size()!=0){
                t=0;
                min=0;
                min_c=servers[release_server[0]].curr_total_time();
                for(k=1;k<release_server.size();k++){
                    if(servers[release_server[k]].curr_total_time()<min_c){
                        min=k;
                        min_c=servers[release_server[k]].curr_total_time();
                        
                    }
                }
                f=release_server[min];
                servers[release_server[min]].release();
                vector<int>::iterator iter = release_server.begin()+min;
                release_server.erase(iter);
                if(queue.size()!=0){
                    if(queue[t].get_id()==i){
                        cout<<"The No."<<i<<" customer arrives."<<endl;
                        flag=1;
                    }
                    
                    
                    servers[f].work(queue[t],f);
                    vector<customer>::iterator iter = queue.begin();
                    queue.erase(iter);
                    t++;
                }
                
                
            }
            
            
            j=0;
            while(flag==0&&j<queue_num){//let the free court serve the customer.
                if(!servers[j].isbusy()){
                    if(queue.size()!=0){
                        if(queue[t].get_id()==i){
                            cout<<"The No."<<i<<" customer arrives."<<endl;
                            flag=1;
                        }
                        servers[j].work(queue[t],j);
                        vector<customer>::iterator iter = queue.begin();
                        queue.erase(iter);
                        t++;
                    }
                    
                }
                j++;
            }
            
                    //cu=queue[0];
           
           
           
                if(flag==0){
                    cout<<"The No."<<i<<" customer arrives."<<endl;
                    cu_delay++;
                    cout<<i<<" has to wait"<<endl;
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
          
            cu=queue[0];
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

    cout<<"***********The End**********"<<endl;
    cout<<"The measurement indicators:"<<endl;
    if(cu_delay==0){
        cout<<"There is no delay in the queue."<<endl;
    }
    else{
        cout<<"The average delay in the queue: "<<wait_t/cu_delay<<endl;
    }
    
    cout<<"The average number of customers in queue: "<<wait_t/fina_time<<endl;
    //cout<<fina_ser<<"      "<<fina_time<<endl;
    cout<<"The average utilisation of servers: "<<fina_ser/(fina_time*queue_num)<<endl;
    
    return 0;
}
