#ifndef MASTER_MODE_
#define MASTER_MODE_

#include "vex.h"
#include <algorithm>
#include <queue>

using namespace vex;

// 自定数据结构

struct Log_data
{
    int x;
    int y;
    int width;
    int height;
    int area;
};

namespace Types
{
    int Type_x = 0;
    int Type_y = 1;
    int Type_width = 2;
    int Type_height = 3;
    int Type_area = 4;

    int Red = 5;
    int Blue = 6;
} // namespace Types

// 数据类
class Data
{
private:
    Log_data Data[20];
    int Count = -1;
    int tmp, Index;

    int Get_Type_Data(int type, Log_data data)
    {
        switch (type)
        {
        case 0:
            return data.x;
        case 1:
            return data.y;
        case 2:
            return data.width;
        case 3:
            return data.height;
        case 4:
            return data.area;
        }
    }

public:
    void Clean()
    {
        for (int i = 0; i <= Count; i++)
        {
            Data[i].x = 0;
            Data[i].y = 0;
            Data[i].width = 0;
            Data[i].height = 0;
            Data[i].area = 0;
        }
        Count = -1;
    }

    void Add(int x, int y, int width, int height)
    {
        Count++;
        Data[Count].x = x;
        Data[Count].y = y;
        Data[Count].width = width;
        Data[Count].height = height;
        Data[Count].area = width * height;
    }

    Log_data Find_Min(int type)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Get_Type_Data(type, Data[i]) < Get_Type_Data(type, Data[i + 1]))
            {
                Index = i;
            }
        }
        return Data[Index];
    }

    Log_data Find_Max(int type)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Get_Type_Data(type, Data[i]) < Get_Type_Data(type, Data[i + 1]))
            {
                Index = i;
            }
        }
        return Data[Index];
    }

    int Num()
    {
        return Count + 1;
    }

    Log_data DataFromId(int id)
    {
        return Data[id];
    }
};

// ==========================================================================================

// 找球

namespace Find_Goals
{
    Data data;
    event Green_data = event();
    void Green_data_callback()
    {

        Vision_top.takeSnapshot(Vision_top__GREEN_BIN);
        int len = 0;
        int x, y, width, height;

        if (Vision_top.objectCount > 0)
        {
            len = Vision_top.objectCount;
            for (int i = 0; i <= len - 1; i++)
            {
                width = Vision_top.objects[i].width;
                height = Vision_top.objects[i].height;
                x = Vision_top.objects[i].centerX - (width / 2);
                y = Vision_top.objects[i].centerY - (height / 2);

                data.Add(x, y, width, height);
            }
        }
    }

    void Init()
    {
        Green_data(Green_data_callback);
    }

    void DataConnect()
    {
        data.Clean();
        Green_data.broadcastAndWait();
    }

} // namespace Find_Goals

namespace Find_Balls
{
    Data Blue, Red;
    event Blue_Ball = event();
    event Red_Ball = event();

    void BLUE_BALL_callback()
    {
        Vision_bottom.takeSnapshot(Vision_bottom__BLUEBALL);
        int len = 0;
        int x, y, width, height;

        if (Vision_bottom.objectCount > 0)
        {
            len = Vision_bottom.objectCount;
            for (int i = 0; i <= len - 1; i++)
            {
                width = Vision_bottom.objects[i].width;
                height = Vision_bottom.objects[i].height;
                x = Vision_bottom.objects[i].centerX - (width / 2);
                y = Vision_bottom.objects[i].centerY - (height / 2);
                Blue.Add(x, y, width, height);
            }
        }
    }

    void RED_BALL_callback()
    {
        Vision_bottom.takeSnapshot(Vision_bottom__REDBALL);
        int len = 0;
        int x, y, width, height;

        if (Vision_bottom.objectCount > 0)
        {
            len = Vision_bottom.objectCount;
            for (int i = 0; i <= len - 1; i++)
            {
                width = Vision_bottom.objects[i].width;
                height = Vision_bottom.objects[i].height;
                x = Vision_bottom.objects[i].centerX - (width / 2);
                y = Vision_bottom.objects[i].centerY - (height / 2);
                Red.Add(x, y, width, height);
            }
        }
    }
    void Init()
    {
        Blue_Ball(BLUE_BALL_callback);
        Red_Ball(RED_BALL_callback);
    }

    void DataConnect(int type)
    {
        switch (type)
        {
        case 5:
            Red_Ball.broadcastAndWait();
            break;

        case 6:
            Blue_Ball.broadcastAndWait();
            break;
        }
    }

} // namespace Find_Balls

namespace Tools
{
    struct Advise_flow
    {
        int v_left_plus;
        int v_right_plus;
    };

    bool isInside(Log_data c, int x, int y, int w, int h)
    {
        if (c.x > x && c.y > y && c.width + c.x < x + w && c.height + c.y < y + h)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    double A(double x_)
    {
        return -0.00008 * x_ * x_ + -0.1397 * x_ + 39.405;
    }

    int I(double x_)
    {
        if (x_ > 0)
        {
            return 1;
        }
        else if (x_ < 0)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    double L(double x_)
    {
        return 0.0000008 * x_ * x_ - 0.0272 * x_ + 70.919;
    }

    double F(double x_)
    {
        const int a = 1;
        const int b = 0;
        return a * x_ + b;
    }

    double Add(double x_, double size_)
    {
        const int a = 1;
        int Lx = L(size_);
        int Ax = A(x_);
        int Fx = F(Lx);
        return I(-Ax) * a * Fx * Ax * Ax;
    }

    Advise_flow MasterAdvise(double v_left,double v_right)
    {
        Find_Goals::DataConnect();
        Log_data Data;
        Advise_flow Advise;
        Data = Find_Goals::data.Find_Max(Types::Type_area);
        double Add_ = Add(Data.x,Data.area);

        Advise.v_left_plus = v_left + Add_;
        Advise.v_right_plus = v_right - Add_;

        return Advise;
    }
} // namespace Tools

namespace AiCube
{
    void InitAll()
    {
        Find_Goals::Init();
    }

    void AiRun()
    {
        Tools::Advise_flow Advise;
        while (true){
            Advise = Tools::MasterAdvise(50,50);
            Brain.Screen.clearScreen();
            Brain.Screen.setCursor(0,0);
            Brain.Screen.setFont(vex::mono12);
            Brain.Screen.print(Advise.v_left_plus);

            wait(100,msec);
        }
    }
} // namespace AiCube

namespace MasterMode
{
    void cycle()
    {
        AiCube::InitAll();
        while (true)
        {
            AiCube::AiRun();
        }
    }
} // namespace MasterMode

#endif;