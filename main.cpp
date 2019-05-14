#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Goods.h"
#include "Order.h"
using namespace std;

//当前日期
time_t t=time(0);
tm* now =localtime(&t);

//用于生成订单
int buyGoodsNum=1;
int Buy_class[10],Buy_goods[10],Buy_quantity[10];
string Buy_name[10];
double Buy_price[10];

//用于退货订单
int returnGoodsNum=1;
string Return_name[10];
int Return_class[10],Return_quantity[10];
double Return_price[10];

//超市类
class Supermarket
{
public:
    string name;              //超市名字
    int cashold,cashnew;                 //现金
    Food *foods[20];          //商品
    DailyGoods *dailyGoods[20];
    ElectricalAppliance *electricalAppliance[20];
    int FoodNum,DailyGoodsNum,ElectricalApplianceNum;//商品数量
    Purchaseorder *purchaseorder[10];//进货单
    Returnorder *returnorder[10];//退货单
    int PurchaseOrderNum,ReturnOrderNum;//购货单，退货单数量
public:
    //初始化函数
    Supermarket()
    {
        fstream io_file("/Users/FrankLi/Desktop/code/C++/SuperMarket/market_in.txt",ios::in|ios::out);
        if(io_file.fail())
        {
            cout<<"cannot open this file"<<endl;
        }
        else
        {
            string temp;
            io_file>>temp>>name;
            io_file>>temp>>cashold;
            string category;
            FoodNum=DailyGoodsNum=ElectricalApplianceNum=1;
            while(!io_file.eof())
            {
                io_file>>temp>>category;
                if(category == "food")
                {
                    Food temp;
                    io_file>>temp;
                    foods[FoodNum]=new Food(temp);
                    FoodNum++;
                }
                else if(category=="DailyGoods")
                {
                    DailyGoods temp;
                    io_file>>temp;
                    dailyGoods[DailyGoodsNum]=new DailyGoods(temp);
                    DailyGoodsNum++;
                }
                else if(category=="ElectricalAppliance")
                {
                    ElectricalAppliance temp;
                    io_file>>temp;
                    electricalAppliance[ElectricalApplianceNum]=new ElectricalAppliance(temp);
                    ElectricalApplianceNum++;
                }
            }
            for(int m=FoodNum;m<20;m++)
            {
                foods[m]= nullptr;
            }
            for(int m=DailyGoodsNum;m<20;m++)
            {
                dailyGoods[m]= nullptr;
            }
            for(int m=ElectricalApplianceNum;m<20;m++)
            {
                electricalAppliance[m]= nullptr;
            }
            for(int m=0;m<10;m++)
            {
                purchaseorder[m]= nullptr;
                returnorder[m]=nullptr;
            }
            PurchaseOrderNum=ReturnOrderNum=1;
        }
    }

    //析构函数
    ~Supermarket()
    {
        for(int i=1;i<FoodNum;i++)
        {
            delete foods[i];
        }
        for(int i=1;i<DailyGoodsNum;i++)
        {
            delete dailyGoods[i];
        }
        for(int i=1;i<ElectricalApplianceNum;i++)
        {
            delete electricalAppliance[i];
        }
        for(int i=1;i<PurchaseOrderNum;i++)
        {
            delete purchaseorder[i];
        }
        for (int i=1;i<ReturnOrderNum;i++) 
        {
            delete returnorder[i];
        }
    }

    //主菜单及界面
    void Menu()
    {
        cout<<"****************************超市管理系统****************************"<<endl;
        cout<<"                       created by Frank Li"<<endl;
        cout<<"****************************超市管理系统****************************"<<endl;
        cout<<"                             "<<(now->tm_year)+1900<<"-"<<(now->tm_mon)+1<<"-"<<now->tm_mday<<endl;
        cout<<"                              菜单栏"<<endl;
        cout<<"                          1.查询商品信息"<<endl;
        cout<<"                            2.增加商品"<<endl;
        cout<<"                            3.购买商品"<<endl;
        cout<<"                            4.退换商品"<<endl;
        cout<<"                         5.查询当日营业额"<<endl;
        cout<<"                            6.退出系统"<<endl;
        cout<<"                         您要选择的操作是? "<<endl;
        int choose;
        cin>>choose;
        switch (choose)
        {
            case 1:
                displayAllGoods();
                break;
            case 2:
                addGoods();
                break;
            case 3:
                saleGoods();
                break;
            case 4:
                returnGoods();
                break;
            case 5:
                cout<<"当日营业额为："<<cashnew-cashold<<endl;
                break;
            case 6:
                return;

        }
    }

    //返回上一级
    void back()
    {
        cout<<"                         是否返回上一级?（Y/N)"<<endl;
        char choose;
        cin>>choose;
        switch (choose)
        {
            case 'Y':
            case 'y':
                Menu();
                break;
            case 'N':
            case 'n':
                return;
        }
    }

    //显示所有商品信息
    void displayAllGoods()
    {
        for(int i=1;i<FoodNum;i++)
        {
            cout<<*foods[i];
        }
        for(int i=1;i<DailyGoodsNum;i++)
        {
            cout<<*dailyGoods[i];
        }
        for(int i=1;i<ElectricalApplianceNum;i++)
        {
            cout<<*electricalAppliance[i];
        }
        back();
    }

    //增加商品
    void addGoods()
    {
        int choose;
        cout<<"请输入您想要增加的产品："<<endl
            <<"1.food"<<endl
            <<"2.DailyGoods"<<endl
            <<"3.ElectricalAppliance"<<endl
            <<"输入您的选择（数字）"<<endl;
        cin>>choose;
        while (!(choose==1||choose==2||choose==3))
        {
            cout<<"请重新输入数字"<<endl;
            cin>>choose;
        }
        string name,color;
        int quantity,maintenance_period;
        int year,month,day;
        char symbol;
        int guarantee_period;
        double price;
        if(choose==1)
        {
            cout<<"请输入名称"<<endl;
            cin>>name;
            cout<<"请输入数量"<<endl;
            cin>>quantity;
            cout<<"请输入生产日期（以年/月/日的格式）"<<endl;
            cin>>year>>symbol>>month>>symbol>>day;
            cout<<"请输入保质期"<<endl;
            cin>>guarantee_period;
            cout<<"请输入价格"<<endl;
            cin>>price;
            foods[FoodNum]=new Food(name,quantity,year,month,day,price,guarantee_period);
            FoodNum++;
        }
        else if(choose==2)
        {
            cout<<"请输入名称"<<endl;
            cin>>name;
            cout<<"请输入数量"<<endl;
            cin>>quantity;
            cout<<"请输入生产日期（以年/月/日的格式）"<<endl;
            cin>>year>>symbol>>month>>symbol>>day;
            cout<<"请输入价格"<<endl;
            cin>>price;
            dailyGoods[DailyGoodsNum]=new DailyGoods(name,quantity,year,month,day,price);
            DailyGoodsNum++;
        }
        else if(choose==3)
        {
            cout<<"请输入名称"<<endl;
            cin>>name;
            cout<<"请输入数量"<<endl;
            cin>>quantity;
            cout<<"请输入生产日期（以年/月/日的格式）"<<endl;
            cin>>year>>symbol>>month>>symbol>>day;
            cout<<"请输入颜色"<<endl;
            cin>>color;
            cout<<"请输入保修期"<<endl;
            cin>>maintenance_period;
            cout<<"请输入价格"<<endl;
            cin>>price;
            electricalAppliance[ElectricalApplianceNum]=new ElectricalAppliance(name,quantity,year,month,day,price,color,maintenance_period);
            ElectricalApplianceNum++;
        }
        back();
    }

    //展示商品类别，用于出售商品函数
    int diaplayGoodsClass()
    {
        int choose;
        cout<<"                     现有如下商品种类"<<endl;
        cout<<"                        1.食物类"<<endl;
        cout<<"                       2.日常用品类"<<endl;
        cout<<"                         3.家电类"<<endl;
        cout<<"输入您的选择（数字）"<<endl;
        cin>>choose;
        while (!(choose==1||choose==2||choose==3))
        {
            cout<<"请重新输入数字"<<endl;
            cin>>choose;
        }
        if(choose==1)
        {
            cout<<"现有食品类商品库存:"<<endl;
            for (int i = 1; i < FoodNum; i++)
            {
                cout<<"["<<i<<"]"
                    <<"食品名称:"<<foods[i]->name<<'\t'
                    <<"现存数量:"<<foods[i]->quantity<<'\t'
                    <<"保质期:"<<foods[i]->guaranteeperiod<<endl;
                cout<<"----------------------------------------------------"<<endl;
            }
        }
        else if(choose==2)
        {
            cout<<"现有日常商品库存:"<<endl;
            for (int i = 1; i < DailyGoodsNum; i++)
            {
                cout<<"["<<i<<"]"
                    <<"商品名称:"<<dailyGoods[i]->name<<'\t'
                    <<"现存数量:"<<dailyGoods[i]->quantity<<endl;
                cout<<"----------------------------------------------------"<<endl;
            }
        }
        else if(choose==3)
        {
            cout<<"现有家电类商品库存::"<<endl;
            for (int i = 1; i < ElectricalApplianceNum; i++)
            {
                cout<<"["<<i<<"]"
                    <<"商品名称:"<<electricalAppliance[i]->name<<'\t'
                    <<"现存数量:"<<electricalAppliance[i]->quantity<<'\t'
                    <<"颜色:"<<electricalAppliance[i]->color<<endl;
                cout<<"----------------------------------------------------"<<endl;
            }
        }
        return choose;
    }

    //核查库存是否足够
    bool checkQuantity(int choose_class,int choose_goods,int num)
    {
        if(choose_class==1)
        {
            if(checkGuaranteePeriod(choose_goods))
            {
                if(foods[choose_goods]->quantity<num)
                {
                    cout << "库存不足，无法出售" << endl;
                    return false;
                }
            }
        }
        else if(choose_class==2)
        {
            if(dailyGoods[choose_goods]->quantity<num)
            { 
                cout << "库存不足，无法出售" << endl;
                return false;
            }
        }
        else if(choose_class==3)
        {
            if(electricalAppliance[choose_goods]->quantity<num)
            {
                cout << "库存不足，无法出售" << endl;
                return false;
            }
        }
        return true;
    }
    
    //检查食物的保质期
    bool checkGuaranteePeriod(int choose_goods)
    {
        int DaysPerMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
        int sumdays_food=0,sumdays_now,i;
        //计算生产日期到1年的天数
        for (i = 1; i < foods[choose_goods]->year; i++)
        {
            if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
                sumdays_food += 366;
            else
                sumdays_food += 365;
        }
        if (foods[choose_goods]->year % 4 == 0 && foods[choose_goods]->year % 100 != 0 || foods[choose_goods]->year % 400 == 0)
            DaysPerMonth[2] = 29;
        for (i = 1; i < foods[choose_goods]->month; i++)
        {
            sumdays_food += DaysPerMonth[i];
        }
        sumdays_food += foods[choose_goods]->day;
        DaysPerMonth[2] = 28;
        //计算现在到1年的天数
        for (i = 1; i < now->tm_year; i++)
        {
            if (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)
                sumdays_now += 366;
            else
                sumdays_now += 365;
        }
        if (now->tm_year % 4 == 0 && now->tm_year % 100 != 0 || now->tm_year % 400 == 0)
            DaysPerMonth[2] = 29;
        for (i = 1; i < now->tm_mon; i++)
        {
            sumdays_food += DaysPerMonth[i];
        }
        sumdays_now+=now->tm_mday;
        int existDays=sumdays_now-sumdays_food;
        if(existDays>foods[choose_goods]->guaranteeperiod)
        {
            //cout<<"食品过期，无法出售"<<endl;
            return false;
        }
        return true;
    }
    
    //出售商品
    void saleGoods()
    {
        int choose_class = diaplayGoodsClass();
        int choose_goods,num;
        cout << "请输入您想要购买的产品序号:" << endl;
        cin >> choose_goods;
        cout<<"请输入您想要购买的数量:"<<endl;
        cin>>num;
        saveToOrder(choose_class,choose_goods,num);
        bool check_one=checkQuantity(choose_class,choose_goods,num);
        bool check_two=checkGuaranteePeriod(choose_goods);
        bool isBuy=false;
        if(choose_class==1)
        {
            if(!check_two)
                cout<<"食品过期，无法出售"<<endl;
            else if(check_one)
            {
                cout<<"库存足够，购买成功"<<endl;
                isBuy= true;
            }
        }
        else
        {
            if(check_one)
            {
                cout<<"库存足够，购买成功"<<endl;
                isBuy= true;
            }
        }
        if(isBuy)
        {

            if(choose_class==1)
            {
                foods[choose_goods]->quantity-=num;
            }
            else if(choose_class==2)
            {
                dailyGoods[choose_goods]->quantity-=num;
            }
            else if(choose_class==3)
            {
                electricalAppliance[choose_goods]->quantity-=num;
            }
        }
        againBuyGoods();
    }
    
    //将所购买的商品存入数组方便生成订单
    void saveToOrder(int choose_class,int choose_goods,int num)
    {
        Buy_class[buyGoodsNum]=choose_class;
        Buy_goods[buyGoodsNum]=choose_goods;
        if(Buy_class[buyGoodsNum]==1)
        {
            Buy_name[buyGoodsNum]=foods[Buy_goods[buyGoodsNum]]->name;
            Buy_price[buyGoodsNum]=foods[Buy_goods[buyGoodsNum]]->price;
        }
        else if(Buy_class[buyGoodsNum]==2)
        {
            Buy_name[buyGoodsNum]=dailyGoods[Buy_goods[buyGoodsNum]]->name;
            Buy_price[buyGoodsNum]=dailyGoods[Buy_goods[buyGoodsNum]]->price;
        }
        else if(Buy_class[buyGoodsNum]==3)
        {
            Buy_name[buyGoodsNum]=electricalAppliance[Buy_goods[buyGoodsNum]]->name;
            Buy_price[buyGoodsNum]=electricalAppliance[Buy_goods[buyGoodsNum]]->price;
        }
        Buy_quantity[buyGoodsNum]=num;
        buyGoodsNum++;
    }

    //继续购买其他商品
    void againBuyGoods()
    {
        cout<<"        是否购买其他商品(Y/N)"<<endl;
        char choose;
        cin>>choose;
        if(choose=='Y'||choose=='y')
            saleGoods();
        else if(choose=='N'||choose=='n')
        {
            double total_price=0;
            for(int i=1;i<buyGoodsNum;i++)
            {
                total_price+=Buy_quantity[i]*Buy_price[i];
            }
            cashnew+=total_price;
            purchaseorder[PurchaseOrderNum]=new Purchaseorder(Buy_class,Buy_name,Buy_price,Buy_quantity,buyGoodsNum,total_price);
            purchaseorder[PurchaseOrderNum]->showOrder();
            purchaseorder[PurchaseOrderNum]->saveOrder();
            PurchaseOrderNum++;
            cout<<"        是否返回主菜单(Y/N)"<<endl;
            cin>>choose;
            if(choose=='Y'||choose=='y')
                Menu();
            else if(choose=='N'||choose=='n')
                return;
        }
    }

    //退换商品
    void returnGoods()
    {
        string ID,reason,name;
        int num;
        cout<<"请输入您购货订单号"<<endl;
        cin>>ID;
        cout<<"请输入退货原因"<<endl;
        cin>>reason;
        returnGoodsProcess_one(ID);
        returnGoodsProcess_two(ID,reason);
    }

    //退货流程1
    void returnGoodsProcess_one(string ID)
    {
        int num;
        string name;
        cout<<"您的订单为"<<endl;
        for(int i=1;i<PurchaseOrderNum;i++)
        {
            if(purchaseorder[i]->ID==ID)
            {
                purchaseorder[i]->showOrder();
            }
        }
        cout<<"请输入您想要退的商品的名字"<<endl;
        cin>>name;
        cout<<"请输入您想要退货的数量"<<endl;
        cin>>num;
        Return_name[returnGoodsNum]=name;
        Return_quantity[returnGoodsNum]=num;
        for(int i=1;i<FoodNum;i++)
        {
            if(foods[i]->name==name)
            {
                foods[i]->quantity+=num;
                Return_price[returnGoodsNum]=foods[i]->price;
                Return_class[returnGoodsNum]=1;
            }
        }
        for(int i=1;i<DailyGoodsNum;i++)
        {
            if(dailyGoods[i]->name==name)
            {
                dailyGoods[i]->quantity+=num;
                Return_price[returnGoodsNum]=dailyGoods[i]->price;
                Return_class[returnGoodsNum]=2;
            }
        }
        for(int i=1;i<ElectricalApplianceNum;i++)
        {
            if(electricalAppliance[i]->name==name)
            {
                dailyGoods[i]->quantity+=num;
                Return_price[returnGoodsNum]=electricalAppliance[i]->price;
                Return_class[returnGoodsNum]=3;
            }
        }
        returnGoodsNum++;
    }

    //退货流程2
    void returnGoodsProcess_two(string ID,string reason)
    {
        char choose;
        cout<<"是否要继续退货(Y/N)"<<endl;
        cin>>choose;
        if(choose=='Y'||choose=='y')
            returnGoodsProcess_one(ID);
        else if(choose=='N'||choose=='n')
        {
            double total_price;
            for(int i=1;i<returnGoodsNum;i++)
            {
                total_price+=Return_price[i]*Return_quantity[i];
            }
            cashnew-=total_price;
            returnorder[ReturnOrderNum]=new Returnorder(ID,reason,Return_class,Return_name,Return_price,Return_quantity,returnGoodsNum,total_price);
            returnorder[ReturnOrderNum]->showOrder();
            returnorder[ReturnOrderNum]->saveOrder();
            ReturnOrderNum++;
            cout<<"        是否返回主菜单(Y/N)"<<endl;
            cin>>choose;
            if(choose=='Y'||choose=='y')
                Menu();
            else if(choose=='N'||choose=='n')
                return;
        }
    }

    //储存所有信息 方便下次初始化
    void saveInformation()
    {
        fstream io_file("/Users/FrankLi/Desktop/code/C++/SuperMarket/market_in.txt",ios::in|ios::out);
        if(io_file.fail())
        {
            cout<<"cannot open this file"<<endl;
        }
        io_file<<"Name: "<<name<<endl;
        io_file<<"Cash: "<<cashnew<<endl<<endl;
        for(int i=1;i<FoodNum;i++)
        {
            io_file<<*foods[i];
        }
        for(int i=1;i<DailyGoodsNum;i++)
        {
            io_file<<*dailyGoods[i];
        }
        for(int i=1;i<ElectricalApplianceNum;i++)
        {
            io_file<<*electricalAppliance[i];
        }
        io_file.close();
    }
};

int main()
{
    Supermarket supermarket;
    supermarket.Menu();
    supermarket.saveInformation();
    return 0;
}