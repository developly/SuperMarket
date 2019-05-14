//
// Created by Frank Li on 2019-05-10.
//

#ifndef SUPERMARKET_ORDER_H
#define SUPERMARKET_ORDER_H

#include <string>
#include <ctime>
#include <fstream>
using namespace std;

//当前日期
time_t _t=time(0);
tm* _now =localtime(&_t);

//订单号
char pnum[10]="A00000001";
char rnum[10]="B00000001";

//订单类
class Order
{
protected:
    int year,month,day;
    struct goods
    {
        string category;
        string name;
        int quantity;
        double price;
    }goods[10];
    int Num;
public:
    Order() {};
    Order(int Array_class[],string Array_name[],double Array_price[],int Array_quantity[],int _Num)
    {
        year=_now->tm_year;
        month=_now->tm_mon;
        day=_now->tm_mday;
        Num=_Num;
        for(int j=1;j<Num;j++)
        {
            if(Array_class[j]==1)
            {
                goods[j].category="food";
                goods[j].name=Array_name[j];
                goods[j].price=Array_price[j];
                goods[j].quantity=Array_quantity[j];
            }
            else if(Array_class[j]==2)
            {
                goods[j].category="DailyGoods";
                goods[j].name=Array_name[j];
                goods[j].price=Array_price[j];
                goods[j].quantity=Array_quantity[j];
            }
            else if(Array_class[j]==3)
            {
                goods[j].category="ElectricalAppliance";
                goods[j].name=Array_name[j];
                goods[j].price=Array_price[j];
                goods[j].quantity=Array_quantity[j];
            }
        }
    }

    friend class Supermarket;
};

//购货单
class Purchaseorder:public Order
{
private:
    string ID;
    double total_price;
public:
    Purchaseorder(int Array_class[],string Array_name[],double Array_price[],int Array_quantity[],int buyGoodsNum,
                  double _total_price)
    :Order(Array_class,Array_name,Array_price,Array_quantity,buyGoodsNum)
    {
        ID=pnum;
        pnum[9]++;
        total_price=_total_price;
    }

    //展示订单
    void showOrder()
    {
        cout<<*this;
    }

    //存储定单
    void saveOrder()
    {
        fstream io_file("/Users/FrankLi/Desktop/code/C++/SuperMarket/PurchaseOrder.txt",ios::in|ios::out);
        io_file<<"ID:"<<ID<<endl;
        io_file<<"Time:"<<(_now->tm_year)+1900<<"-"<<(_now->tm_mon)+1<<"-"<<_now->tm_mday<<endl;
        io_file<<endl;
        for(int i=1;i<Num;i++)
        {
            io_file<<"Category:"<<goods[i].category<<endl;
            io_file<<"Name:"<<goods[i].name<<endl;
            io_file<<"Quantity:"<<goods[i].quantity<<endl;
            io_file<<"Price:"<<goods[i].price<<endl<<endl;
        }
        io_file<<"Total price:"<<total_price<<endl;
    }

    friend ostream& operator <<(ostream& out,const Purchaseorder& purchaseorder);
    friend class Supermarket;
};

//退货单
class Returnorder:public Order
{
private:
    string pID;
    string rID;
    string reason;
    double total_price;
public:
    Returnorder(string _pID,string _reason,int Array_class[],string Array_name[],double Array_price[],int Array_quantity[],int returnGoodsNum,double _total_price)
    :Order(Array_class, Array_name, Array_price, Array_quantity, returnGoodsNum)
    {
        pID=_pID;
        reason=_reason;
        rID=rnum;
        rnum[9]++;
        total_price=_total_price;
    }

    //展示退货单
    void showOrder()
    {
        cout<<*this;
    }

    //存储定单
    void saveOrder()
    {
        fstream io_file("/Users/FrankLi/Desktop/code/C++/SuperMarket/ReturnOrder.txt",ios::in|ios::out);
        io_file<<"Purchase ID:"<<pID<<endl;
        io_file<<"Return ID:"<<rID<<endl;
        io_file<<"Reason:"<<reason<<endl;
        io_file<<"Time:"<<(_now->tm_year)+1900<<"-"<<(_now->tm_mon)+1<<"-"<<_now->tm_mday<<endl;
        io_file<<endl;
        for(int i=1;i<Num;i++)
        {
            io_file<<"Category:"<<goods[i].category<<endl;
            io_file<<"Name:"<<goods[i].name<<endl;
            io_file<<"Quantity:"<<goods[i].quantity<<endl;
            io_file<<"Price:"<<goods[i].price<<endl<<endl;
        }
        io_file<<"Total price:"<<total_price<<endl;
    }

    friend ostream& operator <<(ostream& out,const Returnorder& returnorder);
    friend class Supermarket;
};

//重载"<<" ">>"
ostream& operator <<(ostream& out,const Purchaseorder& purchaseorder)
{
    out<<"订单编号为："<<purchaseorder.ID<<endl;
    out<<"当前日期为："<<(_now->tm_year)+1900<<"-"<<(_now->tm_mon)+1<<"-"<<_now->tm_mday<<endl;
    out<<"所购买的产品有:"<<endl<<endl;
    for(int i=1;i<purchaseorder.Num;i++)
    {
        out<<"category:"<<purchaseorder.goods[i].category<<endl;
        out<<"name:"<<purchaseorder.goods[i].name<<endl;
        out<<"quantity:"<<purchaseorder.goods[i].quantity<<endl;
        out<<"price:"<<purchaseorder.goods[i].price<<endl<<endl;
    }
    out<<"total price:"<<purchaseorder.total_price<<endl;
    return out;
}

ostream& operator <<(ostream& out,const Returnorder& returnorder)
{
    out<<"购货编号为："<<returnorder.pID<<endl;
    out<<"退货编号为："<<returnorder.rID<<endl;
    out<<"退货原因为："<<returnorder.reason<<endl;
    out<<"当前日期为："<<(_now->tm_year)+1900<<"-"<<(_now->tm_mon)+1<<"-"<<_now->tm_mday<<endl;
    out<<"所退掉的产品有:"<<endl<<endl;
    for(int i=1;i<returnorder.Num;i++)
    {
        out<<"category:"<<returnorder.goods[i].category<<endl;
        out<<"name:"<<returnorder.goods[i].name<<endl;
        out<<"quantity:"<<returnorder.goods[i].quantity<<endl;
        out<<"price:"<<returnorder.goods[i].price<<endl<<endl;
    }
    out<<"total price:"<<returnorder.total_price<<endl;
    return out;
}

#endif //SUPERMARKET_ORDER_H
