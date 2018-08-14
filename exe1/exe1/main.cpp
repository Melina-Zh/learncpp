//
//  main.cpp
//  exe1
//
//  Created by Melina on 2018/8/14.
//  Copyright © 2018年 Melina. All rights reserved.
//

//:: 叫作用域区分符，指明一个函数属于哪个类或一个数据属于哪个类。
//:: 可以不跟类名，表示全局数据或全局函数（即非成员函数）。
#include <iostream>

using namespace std;

class Box
{
private:
    double length;   // 长度
    double breadth;  // 宽度
    double height;   // 高度
    
public:
    void setbread(double bread){
        breadth=bread;
    }
    void setheight(double hei){
        height=hei;
    }
    void setLength(double);//必须先有成员函数的声明
    double getVolume(void)
    {
        return length * breadth * height;
    }
    //void setLength(double);//必须先有成员函数的声明
};
void Box::setLength( double len )//在类外定义
{
    length = len;
}
int main( )
{
    Box Box1;        // 声明 Box1，类型为 Box
    Box Box2;        // 声明 Box2，类型为 Box
    //double volume = 0.0;     // 用于存储体积
    
    // box 1 详述
    Box1.setLength(0.3);
    Box1.setbread(0.3);
    Box1.setheight(0.3);
    
    Box2.setLength(0.3);
    Box2.setbread(0.3);
    Box2.setheight(0.3);
    
    
    // box 1 的体积
    //volume = Box1.height * Box1.length * Box1.breadth;
    cout << "Box1 的体积：" << Box1.getVolume() <<endl;

    // box 2 的体积
    //volume = Box2.height * Box2.length * Box2.breadth;
    cout << "Box2 的体积：" << Box2.getVolume() <<endl;
    return 0;
}
