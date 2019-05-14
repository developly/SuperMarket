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
protected:
    string name;              //商品名字
    int quantity;             //现有数量
    int year;                 //商品生产日期
    int month;
    int day;
    double price;             //价格
public:
    //构造函数
    Goods() { }

    Goods(string _name,int _quantity,int _year,int _month,int _day,double _price)
    {
        name=_name;
        quantity=_quantity;
        year=_year;
        month=_month;
        day=_day;
        price=_price;
    }

    virtual void display()
    {
        cout<<"category: Goods"<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"quantity: "<<quantity<<endl;
        cout<<"production_date: "<<year<<"/"<<month<<"/"<<day<<endl;
        cout<<"price: "<<price<<endl;
        cout<<endl;
    }
    friend class Supermarket;
};

class Food;
class DailyGoods;
class ElectricalAppliance;

//派生日常用品类
class DailyGoods: public Goods
{
public:
    DailyGoods(){}
    DailyGoods(string _name,int _quantity,int _year,int _month,int _day,double _price):Goods(_name,_quantity,_year,_month,_day,_price)
    {
        price=_price;
    }

    void display()
    {
        cout<<"category: DailyGoods"<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"quantity: "<<quantity<<endl;
        cout<<"production_date: "<<year<<"/"<<month<<"/"<<day<<endl;
        cout<<"price: "<<price<<endl;
        cout<<endl;
    }

    friend istream& operator >> (istream& in, DailyGoods &dailyGoods);
    friend ostream& operator << (ostream& out, const DailyGoods &dailyGoods);
    friend double operator +(const DailyGoods& dailyGoods,const Food& food);
    friend double operator +(const DailyGoods& dailyGoods,const ElectricalAppliance& electricalAppliance);
    friend double operator *(const DailyGoods& dailyGoods,int num);
    friend class Supermarket;
};

//派生食物类
class Food: public Goods
{
private:
    int guaranteeperiod;      //保质期
public:
    Food(){};

    Food(string _name,int _quantity,int _year,int _month,int _day,double _price, int _guaranteeperiod):Goods(_name,_quantity,_year,_month,_day,_price)
    {
        guaranteeperiod=_guaranteeperiod;
    }

    void display()
    {
        cout<<"category: food"<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"quantity: "<<quantity<<endl;
        cout<<"production_date: "<<year<<"/"<<month<<"/"<<day<<endl;
        cout<<"guarantee_period: "<<guaranteeperiod<<endl;
        cout<<"price: "<<price<<endl;
        cout<<endl;
    }

    friend istream& operator >> (istream& in, Food &food);
    friend ostream& operator << (ostream& out, const Food &food);
    friend double operator +(const DailyGoods& dailyGoods,const Food& food);
    friend double operator +(const Food& food,const ElectricalAppliance& electricalAppliance);
    friend double operator *(const Food& food,int num);
    friend class Supermarket;
};

//派生家电类
class ElectricalAppliance: public Goods
{
private:
    string color;             //颜色
    int maintenanceperiod;    //保修时间

public:
    ElectricalAppliance() {}
    ElectricalAppliance(string _name,int _quantity,int _year,int _month,int _day,double _price, string _color,int _maintenanceperiod):Goods(_name,_quantity,_year,_month,_day,_price)
    {
        color=_color;
        maintenanceperiod=_maintenanceperiod;
    }

    void display()
    {
        cout<<"category: ElectricalAppliance"<<endl;
        cout<<"name: "<<name<<endl;
        cout<<"quantity: "<<quantity<<endl;
        cout<<"production_date: "<<year<<"/"<<month<<"/"<<day<<endl;
        cout<<"color: "<<color<<endl;
        cout<<"maintenance_period: "<<maintenanceperiod<<endl;
        cout<<"price: "<<price<<endl;
        cout<<endl;
    }
    friend istream& operator >> (istream& in, ElectricalAppliance &electricalAppliance);
    friend ostream& operator << (ostream& out, const ElectricalAppliance &electricalAppliance);
    friend double operator +(const DailyGoods& dailyGoods,const ElectricalAppliance& electricalAppliance);
    friend double operator +(const Food& food,const ElectricalAppliance& electricalAppliance);
    friend double operator *(const ElectricalAppliance& electricalAppliance,int num);
    friend class Supermarket;
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

//重载"+" "*"
double operator +(const DailyGoods& dailyGoods,const Food& food)
{
    return dailyGoods.price+food.price;
}

double operator +(const DailyGoods& dailyGoods,const ElectricalAppliance& electricalAppliance)
{
    return dailyGoods.price+electricalAppliance.price;
}

double operator +(const Food& food,const ElectricalAppliance& electricalAppliance)
{
    return food.price+electricalAppliance.price;
}

double operator *(const DailyGoods& dailyGoods,int num)
{
    return num+dailyGoods.price;
}

double operator *(const Food& food,int num)
{
    return num*food.price;
}

double operator *(const ElectricalAppliance& electricalAppliance,int num)
{
    return num*electricalAppliance.price;
}

#endif //SUPERMARKET_GOODS_H
