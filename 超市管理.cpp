//程序包含easyX图形库，缺少会导致程序无法运行
//程序测试运行环境： Visual Studio 2022
#include <iostream>
#include<graphics.h>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<easyx.h>
#include<cstdio>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Creator {//程序设计创作声明
public:
    void drawMyName(int windowwidth,int windowheight)//绘制名称与学号
    {
        string Design = "程序作者：李阳";
        string MyNumber = "学号：2104240523";
        int Textwidth = ::textwidth(Design.c_str());
        int Textheight = ::textheight(Design.c_str());
        outtextxy(windowwidth - Textwidth, windowheight - 2 * Textheight, Design.c_str());
        outtextxy(windowwidth - ::textwidth(MyNumber.c_str()), windowheight - Textheight, MyNumber.c_str());
    }
    void drawMyTitle(int windowwidth, int windowheight)//绘制标题
    {
        string Title = "超市商品信息管理系统";
        int text_width= ::textwidth(Title.c_str());
        int text_height = ::textheight(Title.c_str());
        outtextxy(windowwidth / 2 - text_width / 2, text_height, Title.c_str());
    }
};
class RunManage {
public:
    void run();//程序运行
public:
    enum operate
    {
        Mean,//主菜单                           0
        BuyGoods, //购买商品                    1
        Manage,//管理商品                       2
        ExitSystem,//退出系统                   3
        Life_Goods,//购买日用品                 4
        Cosmetics_Goods,//购买化妆品            5
        Foods_Goods,//购买食品                  6
        Drinks_Goods,//购买饮料                 7
        Add_Goods,//商品增加                    8
        Dele_Goods,//商品删除                   9
        Search_Goods,//商品查询                 10
        Modify_Goods,//商品修改                 11
        Summary_Goods,//商品统计                12
        SaleSummary_Goods,//用户购买信息统计    13
        Return_Goods,//用户退货                 14
        LookLife_Goods,//查询日用品             15
        LookCosmetics_Goods,//查询化妆品        16
        LookFoods_Goods,//查询食品              17
        LookDrinks_Goods,//查询饮料             18

    };

};
class Goods {//商品类，代表一个商品所具有的属性
public:
    Goods() {};    
    string formatInfo();//格式化数据
    string foematInfo_unEndl();//没有enl换行的格式化数据
    string formatInfo_space();//空格为分割的格式化数据
    string formatInfo_log();//带有售出数量的格式化数据
    void setn(int n) { sale = n; }
    bool operator==(Goods tmp);
public:
    unsigned number;
    string name;
    string manufacturer;
    double price;
    int  stock;
    string brand;
    string category;
    double inprice;
    int sale;
};
static vector<Goods> vec_god;//数据
static vector<Goods> vec_log;//售出数据

class File {//文件类，完成文件的读写
public:
    File(){}
    File(string filename) { fileName = filename; }
    void readFile(const string& fileName);
    void saveFile(const std::string& fileName);
    void savelog(const string& fileName,int n,Goods God);
    void readlog(const string& fileName);
    void saveFileLog(const string& Name);
    string readAdmin(const string& fileName);
    void saveAdmin(const string& fileName,string ad);
private:
    string fileName;
    string m_header;//表头   
    string admin;
};
string File::readAdmin(const string& fileName)
{
    

        ifstream read(fileName.c_str());
        if (!read.is_open())
        {
            cout << "file open error";
            return 0;
        }
       
        string Adm;
        read >>Adm;
        cout << Adm;
  
    
    read.close();
    return Adm;
}
void File::saveAdmin(const string& fileName,string ad)
{
    fstream write(fileName, ios::out | ios::trunc);//写入文件，如果不存在就创建一个文件
    write.write(ad.c_str(),ad.size());
    write.close();
}

string Goods::formatInfo_space()
{
    stringstream ss;
    ss << number << " " << name << " " << manufacturer << " " << price << " " << stock << " " << brand << " " << category << " " << inprice;
    return ss.str();//转成字符串返回
}
string Goods::formatInfo_log()
{
    stringstream ss;
    ss << number << " " << name << " " << manufacturer << " " << price << " " << stock << " " << brand << " " << category << " " << inprice<<" "<<sale<<endl;
    return ss.str();//转成字符串返回
   // return string();
}
bool Goods::operator==(Goods tmp)
{
    if (this->number == tmp.number && this->name == tmp.name && this->manufacturer == tmp.manufacturer && this->brand == tmp.brand)
        return true;
    return false;
}
string Goods::foematInfo_unEndl()
{
    stringstream ss;
    ss << number << "\t" << name << "\t" << manufacturer << "\t" << price << "\t" << stock << "\t" << brand << "\t" << category << "\t" << inprice ;
    return ss.str();//转成字符串返回
}
string Goods::formatInfo()
{
    stringstream ss;
    ss << number << "\t" << name << "\t" << manufacturer << "\t" << price << "\t" << stock << "\t" << brand<<"\t"<<category<<"\t" <<inprice<< endl;
    return ss.str();//转成字符串返回
}

void File::readlog(const string& fileName)
{
  
    fstream read(fileName, ios::in);
  
    if (!read.is_open())
    {
        cout << "file open error";
        return;
    }
  
    Goods god;
   
    //读取数据

    while (!read.eof())
    {
        char data[1024] = { 0 };
        read.getline(data, 1024);
        //跳过空行
        if (strlen(data) == 0)
            break;
        //格式化读取
        stringstream ss(data);//流类
        if (ss >> god.number >> god.name >> god.manufacturer >> god.price >> god.stock >> god.brand >> god.category >> god.inprice>>god.sale)
        {
            vec_log.push_back(god);
           // cout << god.number << " " << god.name << " " << god.manufacturer << " " << god.price << " " << god.stock << " " << god.brand << " " << god.category << " " << god.inprice << endl;
        }
        else
            break;
    }
    read.close();


}
void File::saveFileLog(const string& Name)
{
    fstream write(Name, ios::out | ios::trunc);//写入文件，如果不存在就创建一个文件

    for (int i = 0; i < vec_log.size(); i++)
    {
        string info = vec_log[i].formatInfo_log();
        write.write(info.c_str(), info.size());
    }
    write.close();
}
void File::saveFile(const string& fileName)
{    
    fstream write(fileName, ios::out | ios::trunc);//写入文件，如果不存在就创建一个文件 
    for (int i=0;i<vec_god.size();i++)
    {
        string info =vec_god[i].formatInfo();
        write.write(info.c_str(), info.size());
    }
    write.close();
}
void File::readFile(const string& fileName)
{
    fstream read(fileName, ios::in);
    if (!read.is_open())
    {
        cout << "file open error";//后台输出提示
        return ;
    }
    Goods god;
       while (!read.eof())//读取数据
        { 
            char data[1024] = { 0 };
            read.getline(data, 1024);           
            if (strlen(data) == 0)//跳过空行
                break;
            //格式化读取
            stringstream ss(data);//流类
            if (ss >> god.number >> god.name >> god.manufacturer >> god.price >> god.stock >> god.brand >> god.category>>god.inprice)
            {
                vec_god.push_back(god);               
            }
            else
                break;
        }
    read.close();
}


class Window {//窗口类 完成界面的基本设置与功能
public:
    Window(int w=960, int h=720, int flag = 0);
    void setWindowText(string title);//窗口标题设置
    void setBackGround();//窗口背景图片设置
    int getwidth();//获取窗口宽度
    int getheight();//获取窗口高度
    static void beginWidow();//开始绘制
    static void flushWindow();//“缓冲绘图”
    static void endWindow();//结束绘制
   
private:
    int m_width;//宽
    int m_height;//高
    IMAGE imag;//图片变量
    HWND handle;//窗口句柄
    
};
class Button//按钮类，设计各类按钮完成界面交互
{
public:
    Button(){}
    Button( int x, int y, int width, int height,string text = "Buttom")
 { this->text = text; m_x = x, m_y = y, chang = width, kuan = height; }//绘制按钮的位置初始坐标
    int getx() { return m_x; }
    int gety() { return m_y; }
    int getwidth() { return chang; }
    int getheight() { return kuan; }
    void changecolor() { cur = color1; }
    void backcolor() { cur = color0; }
    void drawButton();
    bool isIn(ExMessage msg);//判断鼠标是否在按钮上，用于按钮变色反馈
    bool isClick(ExMessage msg);//判断按钮是否被点击
    COLORREF getclor() { return cur; }//获取当前按钮颜色
    ~Button();
private:
    int m_x;//按钮坐标
    int m_y;
    int chang;//按钮尺寸
    int kuan;
    string text;//按钮文本信息
   // ExMessage m_msg;
    COLORREF color0 = RGB(232, 232, 236);//初始颜色
    COLORREF cur = RGB(232, 232, 236);//当前颜色初始化为初始颜色
    COLORREF color1 = RGB(168, 168, 168);//鼠标触碰按钮时颜色
};

void Button::drawButton()
{
    setfillcolor(cur);
    ::fillroundrect(m_x,m_y,m_x+chang,m_y+kuan, 10, 10);//圆角矩形
    settextcolor(BLACK);
    //文字居中显示在按钮中间
    int tx = m_x + (chang - textwidth(text.c_str())) / 2;
    int ty = m_y + (kuan - textheight(text.c_str())) / 2;

    ::outtextxy(tx, ty, text.c_str());
}

bool Button::isIn(ExMessage msg)
{
    if (msg.x > m_x && msg.x<m_x + chang && msg.y>m_y && msg.y < m_y + kuan)
    {
       /* changecolor();
        drawButton();*/
        return true;
    }
    else
    {
        backcolor();
        drawButton();return false;
    }
    
}

bool Button::isClick(ExMessage msg)
{
    if (msg.x > m_x && msg.x<m_x + chang && msg.y>m_y && msg.y < m_y + kuan)
    {
        changecolor();
        drawButton();
        if (msg.message == WM_LBUTTONDOWN)//左键点击
        {
            return true;
        }
    }
    else
    backcolor();
    drawButton();
    return false;
}

Button::~Button()
{


}

const vector<string> split(string str, char separator)//分割字符
{
    vector<string> res;

    for (size_t pos = 0; pos != string::npos; )
    {
        //查找指定分割字符的位置
        pos = str.find(separator);//find 找到'\t' 的位置
        //取出字符串 
        res.push_back(str.substr(0, pos));
        //把剩下的字符串保存到str
        str = string(str.c_str() + pos + 1);
    }
    return res;
}
bool AllisNum(string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        int tmp = (int)str[i];
        if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}
 bool upprice(const Goods& element1, const Goods& element2)
{
    return element1.price <  element2.price;
}
 bool downprice(const Goods& element1, const Goods& element2)
{
    return element1.price > element2.price ;
}
 bool upmanf(const Goods& element1, const Goods& element2)
{
    return element1.manufacturer <  element2.manufacturer;
}
 bool downmanf(const Goods& element1, const Goods& element2)
{
    return element1.manufacturer > element2.manufacturer;
}
 bool upstock(const Goods& element1, const Goods& element2)
{
    return element1.stock <element2.stock;
}
 bool downstock(const Goods& element1, const Goods& element2)
{
    return element1.stock > element2.stock;
}
 bool upsale(const Goods& element1, const Goods& element2)
{
    return element1.sale < element2.sale;
}
 bool downsale(const Goods& element1, const Goods& element2)
{
    return element1.sale > element2.sale;
}



Window::Window(int w, int h, int flag)
{
    m_width = w;
    m_height = h;
    initgraph(w, h, flag);
    ::setbkmode(TRANSPARENT);//背景透明
}

void Window::setWindowText(string title)
{
    handle = GetHWnd();
    SetWindowText(handle,title.c_str());
}

void Window::setBackGround()
{
    loadimage(&imag, "./imag/bk.jpg");
    putimage(0, 0, &imag);
}

int Window::getwidth()
{
    return m_width;
}

int Window::getheight()
{
    return m_height;
}

void Window::beginWidow()
{
    BeginBatchDraw();
}

void Window::flushWindow()
{
    FlushBatchDraw();
}

void Window::endWindow()
{
    EndBatchDraw();
}

void RunManage::run()
{
    Window w;
    File f;
    int Flag = 0;
    f.readFile("goods.txt");
    f.readlog("log.txt");
    w.setWindowText("超市管理系统");
    ::settextstyle(32, 0, "楷体");
    int Administer = 0;
    string admin = f.readAdmin("admin.txt");

    //   char admin[128] = "123456";//管理员密码设置
    int cur_page = 0;//当前页数
    Button buy(w.getwidth() / 2 - 100, w.getheight() / 4 - 75, 200, 70, "购买商品");
    Button manage(buy.getx(), buy.gety() + 150, 200, 70, "管理商品");
    Button Exit(manage.getx(), manage.gety() + 150, 200, 70, "退出系统");
    Button Save(Exit.getx(), Exit.gety() + 150, 200, 70, "信息保存");
    ExMessage msg;
    int op = Mean;//主菜单
    Creator Li;
    while (true)
    {
        ::cleardevice();
        w.setBackGround();
        Sleep(15);
        peekmessage(&msg, 1 | 2);
        if (msg.vkcode == VK_ESCAPE)
        {
            op = Mean;
        }
        if (op == Mean)
        {
            Li.drawMyName(w.getwidth(), w.getheight());
            Li.drawMyTitle(w.getwidth(), w.getheight());
            buy.drawButton();
            manage.drawButton();
            Exit.drawButton();
            Save.drawButton();
            //鼠标移动到按钮上变色
            if (msg.x > buy.getx() && msg.x<buy.getx() + buy.getwidth() && msg.y>buy.gety() && msg.y < buy.gety() + buy.getheight())
            {
                buy.changecolor();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = BuyGoods;//购买商品
                }
            }
            else
            {
                buy.backcolor();
            }

            if (msg.x > manage.getx() && msg.x<manage.getx() + manage.getwidth() && msg.y>manage.gety() && msg.y < manage.gety() + manage.getheight())
            {
                manage.changecolor();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = Manage;//管理商品
                }
            }
            else
            {
                manage.backcolor();
            }

            if (msg.x > Exit.getx() && msg.x<Exit.getx() + Exit.getwidth() && msg.y>Exit.gety() && msg.y < Exit.gety() + Exit.getheight())
            {
                Exit.changecolor();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = ExitSystem;//退出系统
                }
            }
            else
            {
                Exit.backcolor();
            }

            if (msg.x > Save.getx() && msg.x<Save.getx() + Save.getwidth() && msg.y>Save.gety() && msg.y < Save.gety() + Save.getheight())
            {
                Save.changecolor();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    char code[128];

                    HWND handle = GetHWnd();

                    if (Administer == 0)//没有输入密码
                    {
                        int tips = MessageBox(handle, "请输入管理员密码", "初始密码 123456", MB_OK);
                        InputBox(code, 128, nullptr, "输入管理员密码");
                        if (strcmp(code, admin.c_str()) == 0)
                        {
                            //int tips = MessageBox(handle, "密码正确", "信息保存", MB_OK);
                            Administer = 1;
                        }
                        else
                        {
                            int tips = MessageBox(handle, "密码错误", "信息保存", MB_ICONHAND);
                            op = Mean;
                        }
                    }
                    if (Administer == 1)
                    {
                        f.saveFile("goods.txt");
                        f.saveFileLog("log.txt");
                        //  f.savelog();
                        int tips = MessageBox(handle, "保存成功", "信息保存", MB_OK);
                    }

                }
            }
            else
            {
                Save.backcolor();
            }
        }//op=0 end

        Window::beginWidow();
        if (peekmessage(&msg, 1 | 2))
        {

            switch (msg.message)
            {//按esc退出操作，返回主界面
            case WM_KEYDOWN:     //按键按下
                if (msg.vkcode == VK_ESCAPE)
                {
                    op = Mean;
                }
                break;

            default:std::cout << op << " 鼠标信息接收\n ";//鼠标操作
                //eventLoop();
                break;
            }
        }

        switch (op)
        {
        case BuyGoods://购买商品
        {//日用品，化妆品，食品，饮料
            w.setBackGround();
            Button Life(w.getwidth() / 2 - 100, w.getheight() / 4 - 125, 200, 70, "日用品");
            Button Cosmetics(Life.getx(), Life.gety() + 175, 200, 70, "化妆品");
            Button Food(Cosmetics.getx(), Cosmetics.gety() + 175, 200, 70, "食品");
            Button Drinks(Food.getx(), Food.gety() + 175, 200, 70, "饮料");
            Life.drawButton(); Cosmetics.drawButton(); Food.drawButton(); Drinks.drawButton();
            //  peekmessage(&msg, 1 | 2);
            if (msg.vkcode == VK_ESCAPE)
            {
                op = Mean;
            }
            if (msg.x >= Life.getx() && msg.x<Life.getx() + Life.getwidth() && msg.y>Life.gety() && msg.y < Life.gety() + Life.getheight())
            {

                Life.changecolor();
                Life.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = Life_Goods;//购买日用品
                    cout << op;
                }
            }
            else
            {
                Life.backcolor();
            }

            if (msg.x >= Cosmetics.getx() && msg.x<Cosmetics.getx() + Cosmetics.getwidth() && msg.y>Cosmetics.gety() && msg.y < Cosmetics.gety() + Cosmetics.getheight())
            {

                Cosmetics.changecolor();
                Cosmetics.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = Cosmetics_Goods;//购买化妆品
                    std::cout << op << endl;

                }
            }
            else
            {
                Cosmetics.backcolor();
            }
            if (msg.x >= Food.getx() && msg.x<Food.getx() + Food.getwidth() && msg.y>Food.gety() && msg.y < Food.gety() + Food.getheight())
            {

                Food.changecolor();
                Food.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = Foods_Goods;//购买食品
                    cout << op << endl;
                }
            }
            else
            {
                Food.backcolor();
            }
            if (msg.x >= Drinks.getx() && msg.x<Drinks.getx() + Drinks.getwidth() && msg.y>Drinks.gety() && msg.y < Drinks.gety() + Drinks.getheight())
            {

                Drinks.changecolor();
                Drinks.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    op = Drinks_Goods;//购买饮料
                    cout << op;

                }
            }
            else
            {
                Drinks.backcolor();
            }
            Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = 0;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }


        }break;
        case Manage://管理商品
        {

            char code[128];

            HWND handle = GetHWnd();

            if (Administer == 0)//没有输入密码
            {
                int tips = MessageBox(handle, "请输入管理员密码", "初始密码 123456", MB_OK);
                InputBox(code, 128, nullptr, "输入管理员密码");
                if (strcmp(code, admin.c_str()) == 0)
                {
                    int tips = MessageBox(handle, "密码正确", "商品管理", MB_OK);
                    Administer = 1;
                    op = Manage;
                }
                else
                {
                    int tips = MessageBox(handle, "密码错误", "商品管理", MB_ICONHAND);
                    op = Mean;
                }
            }
            if (Administer == 1)
            {
                //  peekmessage(&msg, 1 | 2);
                ::settextstyle(28, 0, "楷体");//字体设置
                int Button_width = 230;//按钮长度设置
                int Button_height = 58;//按钮宽度设置
                Button Add(150, 75, Button_width, Button_height, "增加商品");//增        8  
                Button Dele(w.getwidth() - Add.getx() - Button_width, 75, Button_width, Button_height, "删除商品");//删 先输入类别 再输入商品名称 9
                Button Search(Add.getx(), Add.gety() + 3 * Button_height, Button_width, Button_height, "查询商品");//查找    10
                Button Change(Dele.getx(), Dele.gety() + 3 * Button_height, Button_width, Button_height, "修改商品");//改     11
                Button Summary(Search.getx(), Search.gety() + 3 * Button_height, Button_width, Button_height, "统计商品");//库存信息统计 按价格 库存 厂家 从大到小排序  12
                Button Log(Change.getx(), Change.gety() + 3 * Button_height, Button_width, Button_height, "用户购买记录");//日志 用户购买记录统计   13
                Button ReGoods(Summary.getx(), Summary.gety() + 3 * Button_height, Button_width, Button_height, "商品退货");//退货   14
                Button RePassword(Log.getx(), Log.gety() + 3 * Button_height, Button_width, Button_height, "修改密码");
                ::settextstyle(32, 0, "楷体");//字体还原

                Add.drawButton();
                Dele.drawButton();
                Search.drawButton();
                Change.drawButton();
                Summary.drawButton();
                Log.drawButton();
                ReGoods.drawButton();
                RePassword.drawButton();
                //鼠标移动到按钮上变色

                if (msg.x > Add.getx() && msg.x<Add.getx() + Add.getwidth() && msg.y>Add.gety() && msg.y < Add.gety() + Add.getheight())
                {
                    Add.changecolor();
                    Add.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Add_Goods;//商品增加
                    }
                }
                else
                {
                    Add.backcolor();
                    Add.drawButton();
                }

                if (msg.x > Dele.getx() && msg.x<Dele.getx() + Dele.getwidth() && msg.y>Dele.gety() && msg.y < Dele.gety() + Dele.getheight())
                {
                    Dele.changecolor();
                    Dele.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Dele_Goods;//商品删除
                    }
                }
                else
                {
                    Dele.backcolor();
                    Dele.drawButton();
                }

                if (msg.x > Search.getx() && msg.x<Search.getx() + Search.getwidth() && msg.y>Search.gety() && msg.y < Search.gety() + Search.getheight())
                {
                    Search.changecolor();
                    Search.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Search_Goods;//商品查找
                    }
                }
                else
                {
                    Search.backcolor();
                    Search.drawButton();
                }

                if (msg.x > Change.getx() && msg.x<Change.getx() + Change.getwidth() && msg.y>Change.gety() && msg.y < Change.gety() + Change.getheight())
                {
                    Change.changecolor();
                    Change.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Modify_Goods;//商品修改
                    }
                }
                else
                {
                    Change.backcolor();
                    Change.drawButton();
                }

                if (msg.x > Summary.getx() && msg.x<Summary.getx() + Summary.getwidth() && msg.y>Summary.gety() && msg.y < Summary.gety() + Summary.getheight())
                {
                    Summary.changecolor();
                    Summary.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Summary_Goods;//商品统计
                    }
                }
                else
                {
                    Summary.backcolor();
                    Summary.drawButton();
                }

                if (msg.x > Log.getx() && msg.x<Log.getx() + Log.getwidth() && msg.y>Log.gety() && msg.y < Log.gety() + Log.getheight())
                {
                    Log.changecolor();
                    Log.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = SaleSummary_Goods;//用户购买记录统计
                    }
                }
                else
                {
                    Log.backcolor();
                    Log.drawButton();
                }

                if (msg.x > ReGoods.getx() && msg.x<ReGoods.getx() + ReGoods.getwidth() && msg.y>ReGoods.gety() && msg.y < ReGoods.gety() + ReGoods.getheight())
                {
                    ReGoods.changecolor();
                    ReGoods.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {
                        op = Return_Goods;//商品退货
                    }
                }
                else
                {
                    ReGoods.backcolor();
                    ReGoods.drawButton();
                }

                if (msg.x > RePassword.getx() && msg.x<RePassword.getx() + RePassword.getwidth() && msg.y>RePassword.gety() && msg.y < RePassword.gety() + RePassword.getheight())
                {

                    RePassword.changecolor();
                    RePassword.drawButton();
                    if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                    {

                        int tips = MessageBox(handle, "请输入需要修改的密码(可区分大小写字母)", "修改管理员密码", MB_OK);

                        InputBox(code, 128, nullptr, "输入想要修改的密码");
                        admin = code;
                        f.saveAdmin("admin.txt", admin);
                        tips = MessageBox(handle, "密码修改成功", "修改管理员密码", MB_OK);
                        Administer = 0;
                        op = Mean;
                    }
                }
                else
                {
                    RePassword.backcolor();
                    RePassword.drawButton();
                }
                //返回键
                /*Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
                if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
                {
                    Return.changecolor();
                    Return.drawButton();
                    if (Return.isClick(msg))      op = 0;
                }
                else
                {
                    Return.backcolor();
                    Return.drawButton();
                }*/


            }



        }break;
        case ExitSystem://退出系统
        {
            f.saveFile("goods.txt");
            f.saveFileLog("log.txt");
            vec_god.clear();
            vec_log.clear();
            exit(0);
        }break;
        case Life_Goods://购买日用品
        {
            File L;

            int r = 0;
            string buffer;
            Button Buy(w.getwidth() / 2 - 75, w.getheight() - 100, 150, 50, "购买");
            Buy.drawButton();
            settextstyle(25, 0, "宋体");

            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");

            for (int i = 0; i < vec_god.size(); i++)
            {

                if (vec_god[i].category == "日用品" && op == 4)
                {
                    r++;

                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());

                }
            }

            settextstyle(32, 0, "楷体");//恢复字体设置


            if (msg.x >= Buy.getx() && msg.x<Buy.getx() + Buy.getwidth() && msg.y>Buy.gety() && msg.y < Buy.gety() + Buy.getheight())
            {

                Buy.changecolor();
                Buy.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    HWND handle = GetHWnd();
                    int tips = MessageBox(handle, "请输入商品名称", "商品购买", MB_OK);
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到用户想要购买的商品
                    //string Name;//储存用户输入的商品名称
                    string Num;//存储用户购买的数量
                    InputBox(name, 128, nullptr, "日用品购买名称输入");
                    std::cout << name;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == name)
                        {
                            flag = 1;
                            tips = MessageBox(handle, "成功找到该商品，请输入需要购买的数量", " ", MB_OK);

                            InputBox(num, 64, nullptr, "日用品购买数量输入");
                            Num = num;//Num是string ; num 是char[ ]
                            if (AllisNum(Num))//判断用户输入是否为纯数字
                            {
                                int int_num = stoi(Num);//字符串转int
                                cout << int_num;
                                if (vec_god[i].stock >= int_num)
                                {
                                    vec_god[i].stock -= int_num;
                                    vec_god[i].setn(int_num);

                                    vec_log.push_back(vec_god[i]);

                                    f.saveFile("goods.txt");
                                    f.saveFileLog("log.txt");

                                    tips = MessageBox(handle, "购买成功", " ", MB_OK);
                                }
                                else
                                {
                                    tips = MessageBox(handle, "库存不足,购买失败", NULL, MB_ICONHAND);
                                }
                            }
                            else //如果不是纯数字
                            {
                                tips = MessageBox(handle, "输入有误，请输入正确的数字", " ", MB_ICONHAND);
                            }
                        }
                    }
                    if (flag == 0)
                        tips = MessageBox(handle, "没有找到该商品", NULL, MB_ICONHAND);
                    //  flag = 0;//复位
                    break;
                }
            }
            else
            {
                Buy.backcolor();
            }
            Buy.drawButton();
            Button Return(0, 0, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = BuyGoods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }


        }break;
        case Cosmetics_Goods://购买化妆品
        {
            File L;
            int r = 0;
            string buffer;
            Button Buy(w.getwidth() / 2 - 75, w.getheight() - 100, 150, 50, "购买");
            Buy.drawButton();
            settextstyle(25, 0, "宋体");

            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            //输出商品信息
            //cout << vec_god.size();
            for (int i = 0; i < vec_god.size(); i++)
            {

                if (vec_god[i].category == "化妆品")
                {
                    r++;

                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());

                }
            }

            settextstyle(32, 0, "楷体");//恢复字体设置


            if (msg.x >= Buy.getx() && msg.x<Buy.getx() + Buy.getwidth() && msg.y>Buy.gety() && msg.y < Buy.gety() + Buy.getheight())
            {

                Buy.changecolor();
                Buy.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    HWND handle = GetHWnd();
                    int tips = MessageBox(handle, "请输入商品名称", "商品购买", MB_OK);
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到用户想要购买的商品
                    //string Name;//储存用户输入的商品名称
                    string Num;//存储用户购买的数量
                    InputBox(name, 128, nullptr, "化妆品购买名称输入");
                    std::cout << name;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == name && op == Cosmetics_Goods)
                        {
                            flag = 1;
                            tips = MessageBox(handle, "成功找到该商品，请输入需要购买的数量", " ", MB_OK);

                            InputBox(num, 64, nullptr, "化妆品购买数量输入");
                            Num = num;//Num是string ; num 是char[ ]
                            if (AllisNum(Num))//判断用户输入是否为纯数字
                            {
                                int int_num = stoi(Num);//字符串转int
                                cout << int_num;
                                if (vec_god[i].stock >= int_num)
                                {
                                    vec_god[i].stock -= int_num;


                                    vec_god[i].setn(int_num);

                                    vec_log.push_back(vec_god[i]);

                                    f.saveFile("goods.txt");
                                    f.saveFileLog("log.txt");

                                    tips = MessageBox(handle, "购买成功", " ", MB_OK);
                                }
                                else
                                {
                                    tips = MessageBox(handle, "库存不足,购买失败", NULL, MB_ICONHAND);
                                }
                            }
                            else //如果不是纯数字
                            {
                                tips = MessageBox(handle, "输入有误，请输入正确的数字", " ", MB_ICONHAND);
                            }
                        }
                    }
                    if (flag == 0)
                        tips = MessageBox(handle, "没有找到该商品", NULL, MB_ICONHAND);


                }

            }
            Button Return(0, 0, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = BuyGoods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
        }break;
        case Foods_Goods://购买食品
        {

            File L;
            int r = 0;
            string buffer;
            Button Buy(w.getwidth() / 2 - 75, w.getheight() - 100, 150, 50, "购买");
            Buy.drawButton();
            settextstyle(25, 0, "宋体");

            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            //输出商品信息
            //cout << vec_god.size();

            for (int i = 0; i < vec_god.size(); i++)
            {

                if (vec_god[i].category == "食品" && op == 6)
                {

                    r++;

                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());

                }
            }

            settextstyle(32, 0, "楷体");//恢复字体设置


            if (msg.x >= Buy.getx() && msg.x<Buy.getx() + Buy.getwidth() && msg.y>Buy.gety() && msg.y < Buy.gety() + Buy.getheight())
            {

                Buy.changecolor();
                Buy.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    HWND handle = GetHWnd();
                    int tips = MessageBox(handle, "请输入商品名称", "商品购买", MB_OK);
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到用户想要购买的商品
                    //string Name;//储存用户输入的商品名称
                    string Num;//存储用户购买的数量
                    InputBox(name, 128, nullptr, "食品购买名称输入");
                    std::cout << name;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == name)
                        {
                            flag = 1;
                            tips = MessageBox(handle, "成功找到该商品，请输入需要购买的数量", " ", MB_OK);

                            InputBox(num, 64, nullptr, "食品购买数量输入");
                            Num = num;//Num是string ; num 是char[ ]
                            if (AllisNum(Num))//判断用户输入是否为纯数字
                            {
                                int int_num = stoi(Num);//字符串转int
                                cout << int_num;
                                if (vec_god[i].stock >= int_num)
                                {
                                    vec_god[i].stock -= int_num;

                                    tips = MessageBox(handle, "购买成功", " ", MB_OK);
                                    vec_god[i].setn(int_num);


                                    vec_log.push_back(vec_god[i]);

                                    f.saveFile("goods.txt");
                                    f.saveFileLog("log.txt");
                                }
                                else
                                {
                                    tips = MessageBox(handle, "库存不足,购买失败", NULL, MB_ICONHAND);
                                }
                            }
                            else //如果不是纯数字
                            {
                                tips = MessageBox(handle, "输入有误，请输入正确的数字", " ", MB_ICONHAND);
                            }
                        }
                    }
                    if (flag == 0)
                        tips = MessageBox(handle, "没有找到该商品", NULL, MB_ICONHAND);
                    //  flag = 0;//复位
                }
            }
            Button Return(0, 0, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = BuyGoods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
        }break;
        case Drinks_Goods://购买饮料
        {
            File L;
            int r = 0;
            string buffer;
            Button Buy(w.getwidth() / 2 - 75, w.getheight() - 100, 150, 50, "购买");
            Buy.drawButton();
            settextstyle(25, 0, "宋体");

            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(12 + 70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            //输出商品信息
            //cout << vec_god.size();

            for (int i = 0; i < vec_god.size(); i++)
            {

                if (vec_god[i].category == "饮料" && op == Drinks_Goods)
                {
                    r++;

                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(12 + 70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());

                }
            }

            settextstyle(32, 0, "楷体");//恢复字体设置


            if (msg.x >= Buy.getx() && msg.x<Buy.getx() + Buy.getwidth() && msg.y>Buy.gety() && msg.y < Buy.gety() + Buy.getheight())
            {

                Buy.changecolor();
                Buy.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    HWND handle = GetHWnd();
                    int tips = MessageBox(handle, "请输入商品名称", "商品购买", MB_OK);
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到用户想要购买的商品
                    //string Name;//储存用户输入的商品名称
                    string Num;//存储用户购买的数量
                    InputBox(name, 128, nullptr, "饮料购买名称输入");
                    std::cout << name;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == name)
                        {
                            flag = 1;
                            tips = MessageBox(handle, "成功找到该商品，请输入需要购买的数量", " ", MB_OK);

                            InputBox(num, 64, nullptr, "饮料购买数量输入");
                            Num = num;//Num是string ; num 是char[ ]
                            if (AllisNum(Num))//判断用户输入是否为纯数字
                            {
                                int int_num = stoi(Num);//字符串转int
                                cout << int_num;
                                if (vec_god[i].stock >= int_num)
                                {
                                    vec_god[i].stock -= int_num;

                                    tips = MessageBox(handle, "购买成功", " ", MB_OK);
                                    vec_god[i].setn(int_num);

                                    vec_log.push_back(vec_god[i]);

                                    f.saveFile("goods.txt");
                                    f.saveFileLog("log.txt");
                                }
                                else
                                {
                                    tips = MessageBox(handle, "库存不足,购买失败", NULL, MB_ICONHAND);
                                }
                            }
                            else //如果不是纯数字
                            {
                                tips = MessageBox(handle, "输入有误，请输入正确的数字", " ", MB_ICONHAND);
                            }
                        }
                    }
                    if (flag == 0)
                        tips = MessageBox(handle, "没有找到该商品", NULL, MB_ICONHAND);
                    //  flag = 0;//复位

                }
            }
            Button Return(0, 0, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = BuyGoods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
        }break;
        case Add_Goods://商品增加
        {
            HWND handle = GetHWnd();
            char goods_msg[1024];
            string tmp;
            Goods buf;
            string text1 = "商品信息输入";
            string text2 = "返回";
            int text_height = textheight("字");
            int len_text1 = textwidth(text1.c_str());
            int len_text2 = textwidth(text2.c_str());
            Button add_goods(w.getwidth() / 2 - len_text1 - 50, 150, len_text1 + 40, text_height + 30, text1.c_str());
            Button confirm(w.getwidth() - add_goods.getx() - len_text1 + 40, 150, len_text1 + 40, text_height + 30, text2.c_str());
            add_goods.drawButton();
            confirm.drawButton();
            ::settextstyle(25, 0, "楷体");
            outtextxy(18, add_goods.gety() - 50, "依次输入商品编号,名称,生产厂家,价格,库存,品牌,类别,进价,用空格隔开");
            ::settextstyle(32, 0, "楷体");
            if (msg.x >= add_goods.getx() && msg.x<add_goods.getx() + add_goods.getwidth() && msg.y>add_goods.gety() && msg.y < add_goods.gety() + add_goods.getheight())
            {

                add_goods.changecolor();
                add_goods.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    InputBox(goods_msg, 128, nullptr, "输入添加的商品信息");
                    if (strcmp(goods_msg, " ") == 0)
                        int tips = MessageBox(handle, "输入为空 ", "商品添加", MB_OK);
                    else
                    {
                        Flag++;
                        tmp = goods_msg;
                        tmp += "\n";
                        stringstream s(tmp);
                        s >> buf.number >> buf.name >> buf.manufacturer >> buf.price >> buf.stock >> buf.brand >> buf.category >> buf.inprice;
                        vec_god.push_back(buf);

                        cout << vec_god[vec_god.size() - 1].name;//后台查看是否添加
                        int tips = MessageBox(handle, "商品添加成功", "商品添加", MB_OK);

                    }



                }
            }
            else
            {
                add_goods.backcolor();
                add_goods.drawButton();
            }

            if (msg.x >= confirm.getx() && msg.x<confirm.getx() + confirm.getwidth() && msg.y>confirm.gety() && msg.y < confirm.gety() + confirm.getheight())
            {

                confirm.changecolor();
                confirm.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    op = Manage;
                }
            }
            else
            {
                confirm.backcolor();
                confirm.drawButton();
            }



        }break;
        case Dele_Goods://商品删除
        {
            int flag = 0;
            HWND handle = GetHWnd();
            char goods_msg[1024];
            Button Life(w.getwidth() / 2 - 100, w.getheight() / 4 - 125, 200, 70, "日用品");
            Button Cosmetics(Life.getx(), Life.gety() + 175, 200, 70, "化妆品");
            Button Food(Cosmetics.getx(), Cosmetics.gety() + 175, 200, 70, "食品");
            Button Drinks(Food.getx(), Food.gety() + 175, 200, 70, "饮料");
            Life.drawButton(); Cosmetics.drawButton(); Food.drawButton(); Drinks.drawButton();
            Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Manage;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
            if (msg.x >= Life.getx() && msg.x<Life.getx() + Life.getwidth() && msg.y>Life.gety() && msg.y < Life.gety() + Life.getheight())
            {

                Life.changecolor();
                Life.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    InputBox(goods_msg, 128, nullptr, "输入删除的商品名称");
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (strcmp(goods_msg, vec_god[i].name.c_str()) == 0)
                        {
                            flag = 1;
                            string buffer;
                            string Tip = "商品查询成功，是否删除该商品(名称 品牌 价格)？\n";
                            buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buffer = buffer.substr(0, buffer.length() - 4);
                            Tip = Tip + vec_god[i].name.c_str() + " " + vec_god[i].brand + " " + buffer;
                            int tips = MessageBox(handle, Tip.c_str(), "商品删除", MB_YESNO);
                            cout << endl << tips << endl;//YES=6 NO=7
                            if (tips == 6)
                            {
                                vec_god.erase(vec_god.begin() + i);//删除查找到的元素 
                                tips = MessageBox(handle, "商品删除成功", "商品删除", MB_OK);

                            }
                            if (tips == 7)
                            {
                                tips = MessageBox(handle, "已取消删除", "商品删除", MB_OK);
                            }

                        }
                    }
                    if (flag)
                        int tips = MessageBox(handle, "未查询到相关商品", "商品删除", MB_OK);
                }
            }
            else
            {
                Life.backcolor();
                Life.drawButton();
            }

            if (msg.x >= Cosmetics.getx() && msg.x<Cosmetics.getx() + Cosmetics.getwidth() && msg.y>Cosmetics.gety() && msg.y < Cosmetics.gety() + Cosmetics.getheight())
            {

                Cosmetics.changecolor();
                Cosmetics.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    InputBox(goods_msg, 128, nullptr, "输入删除的商品名称");
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (strcmp(goods_msg, vec_god[i].name.c_str()) == 0)
                        {
                            flag = 1;
                            string buffer;
                            string Tip = "商品查询成功，是否删除该商品(名称 品牌 价格)？\n";
                            buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buffer = buffer.substr(0, buffer.length() - 4);
                            Tip = Tip + vec_god[i].name.c_str() + " " + vec_god[i].brand + " " + buffer;
                            int tips = MessageBox(handle, Tip.c_str(), "商品删除", MB_YESNO);
                            // cout << endl << tips << endl;//YES=6 NO=7
                            if (tips == 6)
                            {
                                vec_god.erase(vec_god.begin() + i);//删除查找到的元素 
                                tips = MessageBox(handle, "商品删除成功", "商品删除", MB_OK);

                            }
                            if (tips == 7)
                            {
                                tips = MessageBox(handle, "已取消删除", "商品删除", MB_OK);
                            }
                            flag = 0;
                        }
                    }
                    if (flag)
                        int tips = MessageBox(handle, "未查询到相关商品", "商品删除", MB_OK);

                }
            }
            else
            {
                Cosmetics.backcolor();
                Cosmetics.drawButton();
            }

            if (msg.x >= Food.getx() && msg.x<Food.getx() + Food.getwidth() && msg.y>Food.gety() && msg.y < Food.gety() + Food.getheight())
            {

                Food.changecolor();
                Food.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    InputBox(goods_msg, 128, nullptr, "输入删除的商品名称");
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (strcmp(goods_msg, vec_god[i].name.c_str()) == 0)
                        {
                            flag = 1;
                            string buffer;
                            string Tip = "商品查询成功，是否删除该商品(名称 品牌 价格)？\n";
                            buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buffer = buffer.substr(0, buffer.length() - 4);
                            Tip = Tip + vec_god[i].name.c_str() + " " + vec_god[i].brand + " " + buffer;
                            int tips = MessageBox(handle, Tip.c_str(), "商品删除", MB_YESNO);
                            cout << endl << tips << endl;//YES=6 NO=7
                            if (tips == 6)
                            {
                                vec_god.erase(vec_god.begin() + i);//删除查找到的元素 
                                tips = MessageBox(handle, "商品删除成功", "商品删除", MB_OK);

                            }
                            if (tips == 7)
                            {
                                tips = MessageBox(handle, "已取消删除", "商品删除", MB_OK);
                            }
                            flag = 0;
                        }
                    }
                    if (flag)
                        int tips = MessageBox(handle, "未查询到相关商品", "商品删除", MB_ICONHAND);
                }
            }
            else
            {
                Food.backcolor();
                Food.drawButton();
            }

            if (msg.x >= Drinks.getx() && msg.x<Drinks.getx() + Drinks.getwidth() && msg.y>Drinks.gety() && msg.y < Drinks.gety() + Drinks.getheight())
            {

                Drinks.changecolor();
                Drinks.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    InputBox(goods_msg, 128, nullptr, "输入删除的商品名称");
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (strcmp(goods_msg, vec_god[i].name.c_str()) == 0)
                        {
                            flag = 1;
                            string buffer;
                            string Tip = "商品查询成功，是否删除该商品(名称 品牌 价格)？\n";
                            buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buffer = buffer.substr(0, buffer.length() - 4);
                            Tip = Tip + vec_god[i].name.c_str() + " " + vec_god[i].brand + " " + buffer;
                            int tips = MessageBox(handle, Tip.c_str(), "商品删除", MB_YESNO);
                            cout << endl << tips << endl;//YES=6 NO=7
                            if (tips == 6)
                            {
                                vec_god.erase(vec_god.begin() + i);//删除查找到的元素 
                                tips = MessageBox(handle, "商品删除成功", "商品删除", MB_OK);

                            }
                            if (tips == 7)
                            {
                                tips = MessageBox(handle, "已取消删除", "商品删除", MB_OK);
                            }
                            flag = 0;
                        }
                    }
                    if (flag)
                        int tips = MessageBox(handle, "未查询到相关商品", "商品删除", MB_ICONHAND);
                }
            }
            else
            {
                Drinks.backcolor();
                Drinks.drawButton();
            }
            break;
        }break;
        case Search_Goods://商品信息查询
        {
            HWND handle = GetHWnd();
            int Button_width = 250;//按钮长度设置
            int Button_height = 58;//按钮宽度设置
            //类别查询，商品名称查询，生产厂家查询
            Button SeaLife(150, 100, Button_width, Button_height, "日用品查询");//日用品查询
            Button SeaCos(w.getwidth() - SeaLife.getx() - Button_width, 100, Button_width, Button_height, "化妆品查询");//化妆品查询
            Button SeaFood(SeaLife.getx(), SeaLife.gety() + 4 * Button_height, Button_width, Button_height, "食品查询");//食品查询
            Button SeaDrink(SeaCos.getx(), SeaCos.gety() + 4 * Button_height, Button_width, Button_height, "饮料查询");//饮料查询
            Button SeaName(SeaFood.getx(), SeaFood.gety() + 4 * Button_height, Button_width, Button_height, "商品名查询");//商品名称查询
            Button SeaManf(SeaDrink.getx(), SeaDrink.gety() + 4 * Button_height, Button_width, Button_height, "生产厂家查询");//生产厂家查询

            SeaLife.drawButton();
            SeaCos.drawButton();
            SeaFood.drawButton();
            SeaDrink.drawButton();
            SeaName.drawButton();
            SeaManf.drawButton();
            //peekmessage(&msg, 1 | 2);
            /*if (SeaLife.isIn(msg))SeaLife.changecolor(); else SeaLife.backcolor(); SeaLife.drawButton();
            if (SeaCos.isIn(msg))SeaCos.changecolor(); else SeaCos.backcolor(); SeaCos.drawButton();
            if (SeaFood.isIn(msg))SeaFood.changecolor(); else SeaFood.backcolor(); SeaFood.drawButton();
            if (SeaDrink.isIn(msg))SeaDrink.changecolor(); else SeaDrink.backcolor(); SeaDrink.drawButton();*/
            //按钮变色
            if (msg.x > SeaLife.getx() && msg.x<SeaLife.getx() + SeaLife.getwidth() && msg.y>SeaLife.gety() && msg.y < SeaLife.gety() + SeaLife.getheight())
            {

                SeaLife.changecolor();
                SeaLife.drawButton();
                if (SeaLife.isClick(msg))     op = LookLife_Goods;//输出日用品
            }
            else
            {
                SeaLife.backcolor();
            }
            SeaLife.drawButton();
            if (msg.x > SeaCos.getx() && msg.x<SeaCos.getx() + SeaCos.getwidth() && msg.y>SeaCos.gety() && msg.y < SeaCos.gety() + SeaCos.getheight())
            {
                SeaCos.changecolor();
                SeaCos.drawButton();
                if (SeaCos.isClick(msg))      op = LookCosmetics_Goods;//输出化妆品
            }
            else
            {
                SeaCos.backcolor();
                SeaCos.drawButton();
            }

            if (msg.x > SeaFood.getx() && msg.x<SeaFood.getx() + SeaFood.getwidth() && msg.y>SeaFood.gety() && msg.y < SeaFood.gety() + SeaFood.getheight())
            {
                SeaFood.changecolor();
                SeaFood.drawButton();
                if (SeaFood.isClick(msg))     op = LookFoods_Goods;//输出食品
            }
            else
            {
                SeaFood.backcolor();
                SeaFood.drawButton();
            }

            if (msg.x > SeaDrink.getx() && msg.x<SeaDrink.getx() + SeaDrink.getwidth() && msg.y>SeaDrink.gety() && msg.y < SeaDrink.gety() + SeaDrink.getheight())
            {



                SeaDrink.changecolor();

                SeaDrink.drawButton();
                if (SeaDrink.isClick(msg))    op = LookDrinks_Goods;//输出饮料
            }
            else
            {
                SeaDrink.backcolor();
                SeaDrink.drawButton();
            }



            if (msg.x > SeaName.getx() && msg.x<SeaName.getx() + SeaName.getwidth() && msg.y>SeaName.gety() && msg.y < SeaName.gety() + SeaName.getheight())
            {
                SeaName.changecolor();
                SeaName.drawButton();
                if (SeaName.isClick(msg))
                {

                    string buf_price;
                    string buf_inprice;
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到商品

                    InputBox(name, 128, nullptr, "商品名称输入");
                    string Name = name;
                    string content = "编号 名称 生产厂家 价格 库存 品牌 分类 进价\n";
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == Name)
                        {
                            flag = 1;
                            
                            buf_price = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buf_price = buf_price.substr(0, buf_price.length() - 4);
                            buf_inprice = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                            buf_inprice = buf_inprice.substr(0, buf_inprice.length() - 4);
                            content += to_string(vec_god[i].number) + " " + vec_god[i].name + " " + vec_god[i].manufacturer + " " + buf_price + " " + to_string(vec_god[i].stock) + " " + vec_god[i].brand + " " + vec_god[i].category + " " + buf_inprice+"\n";
                            
                        }
                    }
                    if(flag==1)int tips = MessageBox(handle, content.c_str(), "商品名查询商品", MB_OK);
                    if (flag == 0) int tips = MessageBox(handle, "没有查询到您输入的商品信息", "商品名查询商品", MB_ICONHAND);
                }
            }
            else
            {
                SeaName.backcolor();
                SeaName.drawButton();
            }

            if (msg.x > SeaManf.getx() && msg.x<SeaManf.getx() + SeaManf.getwidth() && msg.y>SeaManf.gety() && msg.y < SeaManf.gety() + SeaManf.getheight())
            {
                SeaManf.changecolor();
                SeaManf.drawButton();
                if (SeaManf.isClick(msg))
                {

                    string buf_price;
                    string buf_inprice;
                    char name[1024] = { 0 };
                    char num[64] = { 0 };
                    int flag = 0;//作标记量，标记是否找到商品
                    string content = "编号 名称 生产厂家 价格 库存 品牌 分类 进价\n";
                    InputBox(name, 128, nullptr, "生产厂家输入");
                    string Name = name;//Name 存放厂家名称
                    for (int i = 0; i < vec_god.size(); i++)
                    {

                        if (vec_god[i].manufacturer == Name)
                        {

                            flag = 1;

                            buf_price = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                            buf_price = buf_price.substr(0, buf_price.length() - 4);
                            buf_inprice = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                            buf_inprice = buf_inprice.substr(0, buf_inprice.length() - 4);
                            content += to_string(vec_god[i].number) + " " + vec_god[i].name + " " + vec_god[i].manufacturer + " " + buf_price + " " + to_string(vec_god[i].stock) + " " + vec_god[i].brand + " " + vec_god[i].category + " " + buf_inprice + "\n";



                        }
                    }
                    if (flag == 1)
                    {
                        int tips = MessageBox(handle, content.c_str(), "生产厂家查询商品", MB_OK);
                    }
                    if (flag == 0) int tips = MessageBox(handle, "没有查询到您输入的商品信息", "生产厂家查询商品", MB_ICONHAND);

                }
            }
            else
            {
                SeaManf.backcolor();
                SeaManf.drawButton();
            }

            Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Manage;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
        }break;
        case Modify_Goods://商品信息修改
        {
            int flag = 0;
            HWND handle = GetHWnd();
            char goods_msg[1024];
            string tmp;
            Goods buf;
            string text1 = "商品信息输入";
            string text2 = "返回";
            int text_height = textheight("字");
            int len_text1 = textwidth(text1.c_str());
            int len_text2 = textwidth(text2.c_str());
            Button add_goods(w.getwidth() / 2 - len_text1 - 50, 150, len_text1 + 40, text_height + 30, text1.c_str());
            Button confirm(w.getwidth() - add_goods.getx() - len_text1 + 40, 150, len_text1 + 40, text_height + 30, text2.c_str());
            Button PriceChange(add_goods.getx(), add_goods.gety() + 175, len_text1 + 40, text_height + 30, "价格修改");
            Button StockChange(confirm.getx(), confirm.gety() + 175, len_text1 + 40, text_height + 30, "库存修改");

            add_goods.drawButton();
            confirm.drawButton();
            PriceChange.drawButton();
            StockChange.drawButton();

            ::settextstyle(20, 0, "楷体");
            outtextxy(18, add_goods.gety() - 50, "依次输入商品编号,名称,生产厂家,价格,库存,品牌,类别,进价,用空格或制表位隔开");
            ::settextstyle(32, 0, "楷体");
            if (msg.x >= add_goods.getx() && msg.x<add_goods.getx() + add_goods.getwidth() && msg.y>add_goods.gety() && msg.y < add_goods.gety() + add_goods.getheight())
            {

                add_goods.changecolor();
                add_goods.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    InputBox(goods_msg, 128, nullptr, "输入要修改的商品信息");

                    tmp = goods_msg;
                    tmp += "\n";
                    stringstream s(tmp);
                    s >> buf.number >> buf.name >> buf.manufacturer >> buf.price >> buf.stock >> buf.brand >> buf.category >> buf.inprice;

                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == buf.name && vec_god[i].number == buf.number && vec_god[i].manufacturer == buf.manufacturer && vec_god[i].price == buf.price)
                        {
                            flag = 1;//代表找到了
                            InputBox(goods_msg, 128, nullptr, "输入修改后的商品信息");

                            tmp = goods_msg;
                            tmp += "\n";
                            stringstream s(tmp);
                            s >> buf.number >> buf.name >> buf.manufacturer >> buf.price >> buf.stock >> buf.brand >> buf.category >> buf.inprice;
                            vec_god[i].number = buf.number;
                            vec_god[i].name = buf.name;
                            vec_god[i].manufacturer = buf.manufacturer;
                            vec_god[i].price = buf.price;
                            vec_god[i].stock = buf.stock;
                            vec_god[i].brand = buf.brand;
                            vec_god[i].category = buf.category;
                            vec_god[i].inprice = buf.inprice;
                            int tips = MessageBox(handle, "商品修改成功", "商品修改", MB_OK);
                        }
                    }
                    if (flag == 0)
                        int tips = MessageBox(handle, "商品修改失败，未查询到您所输入的商品", "商品修改", MB_ICONHAND);

                }
            }
            else
            {
                add_goods.backcolor();
                add_goods.drawButton();
            }

            if (msg.x >= confirm.getx() && msg.x<confirm.getx() + confirm.getwidth() && msg.y>confirm.gety() && msg.y < confirm.gety() + confirm.getheight())
            {

                confirm.changecolor();
                confirm.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {

                    op = Manage;
                }
            }
            else
            {
                confirm.backcolor();
                confirm.drawButton();
            }

            if (msg.x >=  PriceChange.getx() && msg.x< PriceChange.getx() +  PriceChange.getwidth() && msg.y> PriceChange.gety() && msg.y <  PriceChange.gety() +  PriceChange.getheight())
            {

                 PriceChange.changecolor();
                 PriceChange.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    char temp[1024];
                    string Temp;
                    InputBox(temp, 128, nullptr, "输入要修改的商品名称");
                    Temp = temp;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == Temp)
                        {
                            InputBox(temp, 128, nullptr, "成功找到该商品，请输入修改后的商品价格");   
                            stringstream s(temp);
                            double a;
                            s >> a;
                            vec_god[i].price = a;
                        }                    
                    }
                   
                }
            }
            else
            {
                 PriceChange.backcolor();
                 PriceChange.drawButton();
            }
      
            if (msg.x >= StockChange.getx() && msg.x< StockChange.getx() + StockChange.getwidth() && msg.y> StockChange.gety() && msg.y < StockChange.gety() + StockChange.getheight())
            {

                StockChange.changecolor();
                StockChange.drawButton();
                if (msg.message == WM_LBUTTONDOWN)//如果鼠标左键点击
                {
                    char temp[1024];
                    string Temp;
                    InputBox(temp, 128, nullptr, "输入要修改的商品名称");
                    Temp = temp;
                    for (int i = 0; i < vec_god.size(); i++)
                    {
                        if (vec_god[i].name == Temp)
                        {
                            InputBox(temp, 128, nullptr, "成功找到该商品，请输入修改后的商品库存");
                            stringstream s(temp);
                            int  a;
                            s >> a;
                            vec_god[i].stock = a;
                        }
                    }

                }
            }
            else
            {
                StockChange.backcolor();
                StockChange.drawButton();
            }
        }break;
        case Summary_Goods://商品信息统计
        {

            /*for (int i = 0; i < vec_god.size(); i++)
            {
                cout << vec_god[i].name<<" "<<vec_god[i].price<<endl;
            }
            cout << endl << endl;*/

            settextstyle(25, 0, "宋体");
            //要求输出当前库存商品总数及其详细信息，按商品价格，库存，生产厂家进行统计，从大到小排序
            //int FLAG ;//作为点击标志
            int btn_width = textwidth("生产厂家升序") + 25;
            int btn_height = textheight("字") + 20;//按钮大小设置
            int m_x = 100;//第一个按钮的横坐标
            int m_y = 25;//第一个按钮的纵坐标
            Button Priceup(m_x, m_y, btn_width, btn_height, "价格升序");//升序，从小到大
            Button Pricedown(Priceup.getx(), Priceup.gety() + 1.5 * btn_height, btn_width, btn_height, "价格降序");//降序，从大到小
            Button Stockup(w.getwidth() / 2 - btn_width / 2, m_y, btn_width, btn_height, "库存升序");
            Button Stockdown(Stockup.getx(), Stockup.gety() + 1.5 * btn_height, btn_width, btn_height, "库存降序");
            Button Manfup(w.getwidth() - m_x - btn_width, m_y, btn_width, btn_height, "生产厂家升序");
            Button Manfdown(Manfup.getx(), Manfup.gety() + 1.5 * btn_height, btn_width, btn_height, "生产厂家降序");//生产厂家排序
            //绘制按钮
            Priceup.drawButton();
            Pricedown.drawButton();
            Stockup.drawButton();
            Stockdown.drawButton();
            Manfup.drawButton();
            Manfdown.drawButton();
            //返回键
            Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Manage;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }


            //按钮点击操作
            //价格升序按钮
            if (msg.x > Priceup.getx() && msg.x<Priceup.getx() + Priceup.getwidth() && msg.y>Priceup.gety() && msg.y < Priceup.gety() + Priceup.getheight())
            {

                Priceup.changecolor();
                Priceup.drawButton();
                if (Priceup.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), upprice);//价格升序
                }
            }
            else
            {
                Priceup.backcolor();
            }
            Priceup.drawButton();

            if (msg.x > Pricedown.getx() && msg.x<Pricedown.getx() + Pricedown.getwidth() && msg.y>Pricedown.gety() && msg.y < Pricedown.gety() + Pricedown.getheight())
            {

                Pricedown.changecolor();
                Pricedown.drawButton();
                if (Pricedown.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), downprice);//价格降序
                }
            }
            else
            {
                Pricedown.backcolor();
            }
            Pricedown.drawButton();

            if (msg.x > Stockup.getx() && msg.x<Stockup.getx() + Stockup.getwidth() && msg.y>Stockup.gety() && msg.y < Stockup.gety() + Stockup.getheight())
            {

                Stockup.changecolor();
                Stockup.drawButton();
                if (Stockup.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), upstock);//库存升序
                }
            }
            else
            {
                Stockup.backcolor();
            }
            Stockup.drawButton();

            if (msg.x > Stockdown.getx() && msg.x<Stockdown.getx() + Stockdown.getwidth() && msg.y>Stockdown.gety() && msg.y < Stockdown.gety() + Stockdown.getheight())
            {

                Stockdown.changecolor();
                Stockdown.drawButton();
                if (Stockdown.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), downstock);//库存降序
                }
            }
            else
            {
                Stockdown.backcolor();
            }
            Stockdown.drawButton();

            if (msg.x > Manfup.getx() && msg.x<Manfup.getx() + Manfup.getwidth() && msg.y>Manfup.gety() && msg.y < Manfup.gety() + Manfup.getheight())
            {

                Manfup.changecolor();
                Manfup.drawButton();
                if (Manfup.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), upmanf);//生产厂家升序
                }
            }
            else
            {
                Manfup.backcolor();
            }
            Manfup.drawButton();

            if (msg.x > Manfdown.getx() && msg.x<Manfdown.getx() + Manfdown.getwidth() && msg.y>Manfdown.gety() && msg.y < Manfdown.gety() + Manfdown.getheight())
            {

                Manfdown.changecolor();
                Manfdown.drawButton();
                if (Manfdown.isClick(msg))
                {
                    sort(vec_god.begin(), vec_god.end(), downmanf);//生产厂家降序
                }
            }
            else
            {
                Manfdown.backcolor();
            }
            Manfdown.drawButton();

            //设定输出数据的初始位置
            int text_x = Pricedown.getx();
            int text_y = Pricedown.gety() + 1.5 * btn_height;
            outtextxy(text_x + 100 * 0, text_y, "编号");
            outtextxy(text_x + 100 * 1, text_y, "名称");
            outtextxy(text_x + 100 * 2, text_y, "生产厂家");
            outtextxy(text_x + 100 * 4, text_y, "价格");
            outtextxy(text_x + 100 * 5, text_y, "库存");
            outtextxy(text_x + 100 * 6, text_y, "品牌");
            outtextxy(text_x + 100 * 7, text_y, "进价");

            string buffer;
            //设计翻页功能 
            Button upPage(text_x, text_y * 4, btn_width / 2, btn_height / 2, "上一页"); upPage.drawButton();
            Button downPage(upPage.getx() + upPage.getwidth(), upPage.gety(), btn_width / 2, btn_height / 2, "下一页"); downPage.drawButton();
            //peekmessage(&msg, 1 | 2);

            int rowcount = 13;//设置一页显示多少行数据                            
            int max_page = vec_god.size() / rowcount;//总页数
            if (vec_god.size() % rowcount == 0)
                max_page--;
            int extra = vec_god.size() % rowcount;//如果不是整数页，那么保存一下最后一页有多少条数据
            if (rowcount >= vec_god.size())//如果数据过少，一页的显示内容大于总数据
            {
                max_page = 0;
                extra = vec_god.size();
            }
            else
            {
                extra = vec_god.size() % rowcount;	//计算余下多少条数据
                max_page = vec_god.size() / rowcount;
            }

            if (msg.vkcode == VK_NEXT)//下一页
                if (cur_page < max_page)
                {
                    cur_page++;
                }

            if (msg.x > downPage.getx() && msg.x<downPage.getx() + downPage.getwidth() && msg.y>downPage.gety() && msg.y < downPage.gety() + downPage.getheight())
            {
                downPage.changecolor();
                downPage.drawButton();
                if (downPage.isClick(msg))//下一页
                {
                    if (cur_page < max_page)
                    {
                        cur_page++;
                    }
                }
            }
            else
            {
                downPage.backcolor();
            }
            downPage.drawButton();

            if (msg.vkcode == VK_PRIOR)//上一页
                if (cur_page == 0)
                {
                    cur_page = 0;
                }
                else
                {
                    cur_page--;
                }
            if (msg.x > upPage.getx() && msg.x<upPage.getx() + upPage.getwidth() && msg.y>upPage.gety() && msg.y < upPage.gety() + upPage.getheight())
            {

                upPage.changecolor();
                upPage.drawButton();
                if (upPage.isClick(msg))//上一页
                {
                    if (cur_page == 0)
                    {
                        cur_page = 0;
                    }
                    else
                    {
                        cur_page--;
                    }
                }
            }
            else
            {
                upPage.backcolor();
            }
            upPage.drawButton();

            //防止越界
            if (rowcount > vec_god.size() && vec_god.size() != 0)
            {
                rowcount = vec_god.size();
            }
            text_y += 50;
            int i = 0, ro = 0, j = 0;
            if (cur_page != max_page)
                for (ro = 0, i = cur_page * rowcount; j < rowcount; j++, ro++, i++)
                {   //信息输出         
                    if (vec_god[i].stock != 0)
                    {
                        outtextxy(text_x + 100 * 0, text_y + ro * 30, to_string(vec_god[i].number).c_str());
                        outtextxy(text_x + 100 * 1, text_y + ro * 30, vec_god[i].name.c_str());
                        outtextxy(text_x + 100 * 2, text_y + ro * 30, vec_god[i].manufacturer.c_str());
                        buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’保留两位小数
                        buffer = buffer.substr(0, buffer.length() - 4);
                        outtextxy(text_x + 100 * 4, text_y + ro * 30, buffer.c_str());
                        outtextxy(text_x + 100 * 5, text_y + ro * 30, to_string(vec_god[i].stock).c_str());
                        outtextxy(text_x + 100 * 6, text_y + ro * 30, vec_god[i].brand.c_str());
                        buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                        buffer = buffer.substr(0, buffer.length() - 4);
                        outtextxy(text_x + 100 * 7, text_y + ro * 30, buffer.c_str());
                    }

                }
            if (cur_page == max_page)//最后一页数据输出
            {
                int j = 0;
                for (ro = 0, i = cur_page * rowcount; j < extra; j++, i++, ro++)
                {
                    if (vec_god[i].stock != 0)
                    {
                        outtextxy(text_x + 100 * 0, text_y + ro * 30, to_string(vec_god[i].number).c_str());
                        outtextxy(text_x + 100 * 1, text_y + ro * 30, vec_god[i].name.c_str());
                        outtextxy(text_x + 100 * 2, text_y + ro * 30, vec_god[i].manufacturer.c_str());
                        buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                        buffer = buffer.substr(0, buffer.length() - 4);
                        outtextxy(text_x + 100 * 4, text_y + ro * 30, buffer.c_str());
                        outtextxy(text_x + 100 * 5, text_y + ro * 30, to_string(vec_god[i].stock).c_str());
                        outtextxy(text_x + 100 * 6, text_y + ro * 30, vec_god[i].brand.c_str());
                        buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                        buffer = buffer.substr(0, buffer.length() - 4);
                        outtextxy(text_x + 100 * 7, text_y + ro * 30, buffer.c_str());
                    }
                }
            }

            int total = 0;
            for (int i = 0; i < vec_god.size(); i++)
            {
                total += vec_god[i].stock;
            }
            string all = "商品库存总数：";
            all += to_string(total);
            all += " 件";
            outtextxy(downPage.getx() + 100, downPage.gety(), all.c_str());

            settextstyle(32, 0, "楷体");//恢复字体设置

        }break;
        case SaleSummary_Goods://用户购买信息统计
        {
            // f.readlog("log.txt");//数据读入，数据更新
            settextstyle(20, 0, "宋体");


            //相同数据合并
            for (int i = 0; i < vec_log.size(); i++)
            {
                for (int j = i + 1; j < vec_log.size(); j++)
                {
                    if (vec_log[i] == vec_log[j])
                    {
                        vec_log[i].sale = vec_log[i].sale + vec_log[j].sale;
                        vec_log.erase(vec_log.begin() + j);
                    }
                }
            }


            int btn_width = textwidth("已售商品价格升序") + 25;
            int btn_height = textheight("字") + 20;//按钮大小设置
            int m_x = 150;//第一个按钮的横坐标
            int m_y = 25;//第一个按钮的纵坐标
            Button upPrice(m_x, m_y, btn_width, btn_height, "已售商品价格升序");
            Button upSale(w.getwidth() - m_x - btn_width, m_y, btn_width, btn_height, "已售商品数量升序");
            Button downPrice(upPrice.getx(), upPrice.gety() + 1.5 * btn_height, btn_width, btn_height, "已售商品价格降序");
            Button downSale(upSale.getx(), upSale.gety() + 1.5 * btn_height, btn_width, btn_height, "已售商品数量降序");

            upPrice.drawButton();
            upSale.drawButton();
            downPrice.drawButton();
            downSale.drawButton();

            Button Return(w.getwidth() - 70, w.getheight() - 43, 70, 43, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Manage;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }

            if (msg.x > upPrice.getx() && msg.x<upPrice.getx() + upPrice.getwidth() && msg.y>upPrice.gety() && msg.y < upPrice.gety() + upPrice.getheight())
            {

                upPrice.changecolor();
                upPrice.drawButton();
                if (upPrice.isClick(msg))
                {
                    Flag = 1;

                }
            }
            else
            {
                upPrice.backcolor();
            }
            upPrice.drawButton();

            if (msg.x > downPrice.getx() && msg.x<downPrice.getx() + downPrice.getwidth() && msg.y>downPrice.gety() && msg.y < downPrice.gety() + downPrice.getheight())
            {

                downPrice.changecolor();
                downPrice.drawButton();
                if (downPrice.isClick(msg))
                {
                    Flag = 2;

                }
            }
            else
            {
                downPrice.backcolor();
            }
            downPrice.drawButton();

            if (msg.x > upSale.getx() && msg.x<upSale.getx() + upSale.getwidth() && msg.y>upSale.gety() && msg.y < upSale.gety() + upSale.getheight())
            {

                upSale.changecolor();
                upSale.drawButton();
                if (upSale.isClick(msg))
                {
                    Flag = 3;

                }
            }
            else
            {
                upSale.backcolor();
            }
            upSale.drawButton();

            if (msg.x > downSale.getx() && msg.x<downSale.getx() + downSale.getwidth() && msg.y>downSale.gety() && msg.y < downSale.gety() + downSale.getheight())
            {

                downSale.changecolor();
                downSale.drawButton();
                if (downSale.isClick(msg))
                {
                    Flag = 4;

                }
            }
            else
            {
                downSale.backcolor();
            }
            downSale.drawButton();

            if (Flag == 1)
                sort(vec_log.begin(), vec_log.end(), upprice);//价格升序
            if (Flag == 2)
                sort(vec_log.begin(), vec_log.end(), downprice);//价格降序
            if (Flag == 3)
                sort(vec_log.begin(), vec_log.end(), upsale);//售出升序
            if (Flag == 4)
                sort(vec_log.begin(), vec_log.end(), downsale);//售出降序





            string buffer;
            int r = 0;
            outtextxy(70 + 100 * 0, 200, "编号");
            outtextxy(70 + 100 * 1, 200, "名称");
            outtextxy(70 + 100 * 2, 200, "生产厂家");
            outtextxy(70 + 100 * 4, 200, "价格");
            outtextxy(70 + 100 * 5, 200, "库存");
            outtextxy(70 + 100 * 6, 200, "品牌");
            outtextxy(70 + 100 * 7, 200, "进价");
            outtextxy(70 + 100 * 8, 200, "售出数量");
            for (int i = 0; i < vec_log.size(); i++)
            {
                if (vec_log[i].sale != 0)
                {
                    r++;
                    outtextxy(70 + 100 * 0, 200 + r * 30, to_string(vec_log[i].number).c_str());
                    outtextxy(70 + 100 * 1, 200 + r * 30, vec_log[i].name.c_str());
                    outtextxy(70 + 100 * 2, 200 + r * 30, vec_log[i].manufacturer.c_str());
                    buffer = to_string(vec_log[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 200 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 200 + r * 30, to_string(vec_log[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 200 + r * 30, vec_log[i].brand.c_str());
                    buffer = to_string(vec_log[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 7, 200 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 8, 200 + r * 30, to_string(vec_log[i].sale).c_str());
                }
            }
            string T = "总计盈利：";
            double total = 0;
            for (int i = 0; i < vec_log.size(); i++)
            {
                total += (vec_log[i].price - vec_log[i].inprice) * vec_log[i].sale;
            }
            buffer = to_string(total);
            buffer = buffer.substr(0, buffer.length() - 4);
            T += buffer + "元";

            outtextxy(70, downPrice.gety() + downPrice.getheight() + 25, T.c_str());

            settextstyle(32, 0, "楷体");//恢复字体设置

            //   settextstyle(32, 0, "楷体");
        }break;
        case Return_Goods://用户退货
        {
            HWND handle = GetHWnd();
            int flag = 0;
            int index;
            //  f.readlog("log.txt");//数据更新
            char goods_msg[1024];
            string goodsName;
            string goodsNum;
            InputBox(goods_msg, 128, nullptr, "输入退货商品名称");
            goodsName = goods_msg;
            for (int i = 0; i < vec_log.size(); i++)
            {
                if (goodsName == vec_log[i].name)
                {
                    flag = 1;
                    index = i;
                }
            }
            if (flag == 1)
            {
                InputBox(goods_msg, 128, nullptr, "输入退货数量");
                goodsNum = goods_msg;
                if (AllisNum(goodsNum))//判断用户输入是否为纯数字
                {
                    int int_num = stoi(goodsNum);//字符串转int
                    if (vec_log[index].sale >= int_num)
                    {
                        vec_log[index].sale -= int_num;
                        for (int i = 0; i < vec_god.size(); i++)
                        {
                            if (vec_god[i].name == goodsName)
                            {
                                vec_god[i].stock += int_num;

                                int tips = MessageBox(handle, "退货成功", " ", MB_OK);
                                op = Manage;
                            }
                        }

                    }
                    else
                    {
                        int tips = MessageBox(handle, "商品售出数量小于退货数量，请检查输入是否正确", NULL, MB_ICONHAND);
                    }
                }
                else //如果不是纯数字
                {
                    int tips = MessageBox(handle, "输入有误，请输入正确的数字", " ", MB_ICONHAND);
                }
            }
            else
            {
                int tips = MessageBox(handle, "未查询到相关信息", "商品退货", MB_ICONHAND);
                op = Manage;
            }


        }break;
        case LookLife_Goods://查询日用品信息
        {
            File L;
            int r = 0;
            string buffer;
            settextstyle(25, 0, "宋体");
            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            for (int i = 0; i < vec_god.size(); i++)
            {
                if (vec_god[i].category == "日用品")
                {
                    r++;
                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());
                }
            }

            Button Return(w.getwidth() - 80, w.getheight() - 53, 80, 53, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Search_Goods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            } settextstyle(32, 0, "楷体");//恢复字体设置
        }break;
        case LookCosmetics_Goods://查询化妆品
        {
            File L;
            int r = 0;
            string buffer;
            settextstyle(25, 0, "宋体");
            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            for (int i = 0; i < vec_god.size(); i++)
            {
                if (vec_god[i].category == "化妆品")
                {
                    r++;
                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());
                }
            }
            Button Return(w.getwidth() - 80, w.getheight() - 53, 80, 53, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Search_Goods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
            settextstyle(32, 0, "楷体");//恢复字体设置
        }break;
        case LookFoods_Goods://查询食品
        {
            File L;
            int r = 0;
            string buffer;
            settextstyle(25, 0, "宋体");
            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            for (int i = 0; i < vec_god.size(); i++)
            {
                if (vec_god[i].category == "食品")
                {
                    r++;
                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());
                }
            }
            Button Return(w.getwidth() - 80, w.getheight() - 53, 80, 53, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Search_Goods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
            settextstyle(32, 0, "楷体");//恢复字体设置
        }break;
        case LookDrinks_Goods://查询饮料
        {
            File L;
            int r = 0;
            string buffer;
            settextstyle(25, 0, "宋体");
            outtextxy(70 + 100 * 0, 30, "编号");
            outtextxy(70 + 100 * 1, 30, "名称");
            outtextxy(70 + 100 * 2, 30, "生产厂家");
            outtextxy(70 + 100 * 4, 30, "价格");
            outtextxy(70 + 100 * 5, 30, "库存");
            outtextxy(70 + 100 * 6, 30, "品牌");
            for (int i = 0; i < vec_god.size(); i++)
            {
                if (vec_god[i].category == "饮料")
                {
                    r++;
                    outtextxy(70 + 100 * 0, 30 + r * 30, to_string(vec_god[i].number).c_str());
                    outtextxy(70 + 100 * 1, 30 + r * 30, vec_god[i].name.c_str());
                    outtextxy(70 + 100 * 2, 30 + r * 30, vec_god[i].manufacturer.c_str());
                    buffer = to_string(vec_god[i].price);//double转换为字符串，去掉精度后的‘0’
                    buffer = buffer.substr(0, buffer.length() - 4);
                    outtextxy(70 + 100 * 4, 30 + r * 30, buffer.c_str());
                    outtextxy(70 + 100 * 5, 30 + r * 30, to_string(vec_god[i].stock).c_str());
                    outtextxy(70 + 100 * 6, 30 + r * 30, vec_god[i].brand.c_str());
                    //buffer = to_string(vec_god[i].inprice);//double转换为字符串，去掉精度后的‘0’
                    //buffer = buffer.substr(0, buffer.length() - 4);
                    //outtextxy(70 + 100 * 7, 30 + r * 30, buffer.c_str());
                }
            }
            Button Return(w.getwidth() - 80, w.getheight() - 53, 80, 53, "返回");
            if (msg.x > Return.getx() && msg.x<Return.getx() + Return.getwidth() && msg.y>Return.gety() && msg.y < Return.gety() + Return.getheight())
            {
                Return.changecolor();
                Return.drawButton();
                if (Return.isClick(msg))      op = Search_Goods;
            }
            else
            {
                Return.backcolor();
                Return.drawButton();
            }
            settextstyle(32, 0, "楷体");//恢复字体设置
        }break;
        default:
            Window::flushWindow();
            break;
        }
        //   w.setBackGround();
        Window::flushWindow();
    }

    Window::endWindow();
}


int main()
{
    RunManage me;
    me.run();

    return getchar();
}