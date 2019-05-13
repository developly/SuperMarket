//
// Created by Frank Li on 2019-05-10.
//

#ifndef SUPERMARKET_GOODS_H
#define SUPERMARKET_GOODS_H

#include <string>
using namespace std;

//商品类
class Goods
{
public:
    string name;              //商品名字
    int quantity;             //现有数量
    int year;                 //商品生产日期
    int month;
    int day;
    double price;             //价格
public:
    //构造函数
    Goods() { }

    Goods(string _name,int _quantity,int _year,int _month,int _day)
    {
        name=_name;
        quantity=_quantity;
        year=_year;
        month=_month;
        day=_day;
    }
};

//派生日常用品类
class DailyGoods: public Goods
{
public:
    DailyGoods(){}
    DailyGoods(string _name,int _quantity,int _year,int _month,int _day,double _price):Goods(_name,_quantity,_year,_month,_day)
    {
        price=_price;
    }

    friend istream& operator >> (istream& in, DailyGoods &dailyGoods);
    friend ostream& operator << (ostream& out, const DailyGoods &dailyGoods);
};

//派生食物类
class Food: public Goods
{
public:
    int guaranteeperiod;      //保质期
public:
    Food(){};

    Food(string _name,int _quantity,int _year,int _month,int _day,double _price, int _guaranteeperiod):Goods(_name,_quantity,_year,_month,_day)
    {
        guaranteeperiod=_guaranteeperiod;
    }

    friend istream& operator >> (istream& in, Food &food);
    friend ostream& operator << (ostream& out, const Food &food);
};

//派生家电类
class ElectricalAppliance: public Goods
{
public:
    string color;             //颜色
    int maintenanceperiod;    //保修时间

public:
    ElectricalAppliance() {}
    ElectricalAppliance(string _name,int _quantity,int _year,int _month,int _day,double _price, string _color,int _maintenanceperiod):Goods(_name,_quantity,_year,_month,_day)
    {
        color=_color;
        maintenanceperiod=_maintenanceperiod;
    }

    friend istream& operator >> (istream& in, ElectricalAppliance &electricalAppliance);
    friend ostream& operator << (ostream& out, const ElectricalAppliance &electricalAppliance);
};

//重载"<<" ">>"
istream& operator >> (istream& in, DailyGoods& dailyGoods)
{
    string string1;
    char symbol;
    in>>string1>>dailyGoods.name;
    in>>string1>>dailyGoods.quantity;
    in>>string1>>dailyGoods.year>>symbol>>dailyGoods.month>>symbol>>dailyGoods.day;
    in>>string1>>dailyGoods.price;
    return in;
}

istream& operator >> (istream& in, Food &food)
{
    string string1;
    char symbol;
    in>>string1>>food.name;
    in>>string1>>food.quantity;
    in>>string1>>food.year>>symbol>>food.month>>symbol>>food.day;
    in>>string1>>food.guaranteeperiod;
    in>>string1>>food.price;
    return in;
}

istream& operator >> (istream& in, ElectricalAppliance &electricalAppliance)
{
    string string1;
    char symbol;
    in>>string1>>electricalAppliance.name;
    in>>string1>>electricalAppliance.quantity;
    in>>string1>>electricalAppliance.year>>symbol>>electricalAppliance.month>>symbol>>electricalAppliance.day;
    in>>string1>>electricalAppliance.color;
    in>>string1>>electricalAppliance.maintenanceperiod;
    in>>string1>>electricalAppliance.price;
    return in;
}

ostream& operator << (ostream& out, const DailyGoods &dailyGoods)
{
    out<<"category: DailyGoods"<<endl;
    out<<"name: "<<dailyGoods.name<<endl;
    out<<"quantity: "<<dailyGoods.quantity<<endl;
    out<<"production_date: "<<dailyGoods.year<<"/"<<dailyGoods.month<<"/"<<dailyGoods.day<<endl;
    out<<"price: "<<dailyGoods.price<<endl;
    out<<endl;
    return out;
}

ostream& operator << (ostream& out, const Food &food)
{
    out<<"category: food"<<endl;
    out<<"name: "<<food.name<<endl;
    out<<"quantity: "<<food.quantity<<endl;
    out<<"production_date: "<<food.year<<"/"<<food.month<<"/"<<food.day<<endl;
    out<<"guarantee_period: "<<food.guaranteeperiod<<endl;
    out<<"price: "<<food.price<<endl;
    out<<endl;
    return out;
}

ostream& operator << (ostream& out, const ElectricalAppliance &electricalAppliance)
{
    out<<"category: ElectricalAppliance"<<endl;
    out<<"name: "<<electricalAppliance.name<<endl;
    out<<"quantity: "<<electricalAppliance.quantity<<endl;
    out<<"production_date: "<<electricalAppliance.year<<"/"<<electricalAppliance.month<<"/"<<electricalAppliance.day<<endl;
    out<<"color: "<<electricalAppliance.color<<endl;
    out<<"maintenance_period: "<<electricalAppliance.maintenanceperiod<<endl;
    out<<"price: "<<electricalAppliance.price<<endl;
    out<<endl;
    return out;
}

#endif //SUPERMARKET_GOODS_H
