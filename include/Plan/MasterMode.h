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

struct CoverData
{
    int x;
    int y;
    int width;
    int height;
    int Center_x;
    int Center_y;
    double CoverPercent;
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

    Log_data ToSquireData(Log_data Object)
    {
        Log_data Out;
        Out.x = Object.x - (Object.width / 2);
        Out.y = Object.y - (Object.height / 2);
        Out.width = Object.width;
        Out.height = Object.height;
        Out.area = Object.area;

        return Out;
    }

    CoverData Cover(Log_data O, int x, int y, int w, int h)
    {
        Log_data Object = ToSquireData(O);
        CoverData Data;
        if (Object.x < x)
            Data.x = x;
        else
            Data.x = Object.x;

        if (Object.y < y)
            Data.y = y;
        else
            Data.y = Object.y;

        if (Object.x + Object.width < x + w)
            Data.width = Object.width;
        else
            Data.width = w;

        if (Object.y + Object.height < y + h)
            Data.height = Object.height;
        else
            Data.height = h;

        Data.Center_x = Object.x + (Object.width / 2);
        Data.Center_y = Object.y + (Object.height / 2);

        Data.CoverPercent = (double(Data.width) * double(Data.height)) / (double(w) * double(h));

        return Data;
    }

    int FindMaxCoverd(int x, int y, int w, int h)
    {
        int Index = 0;
        double Max = 0;
        for (int i = 0; i <= Count; i++)
        {
            CoverData F = Cover(Data[i],x,y,w,h);
            if(F.CoverPercent > Max){
                Max = F.CoverPercent;
                Index = i;
            }
        }
        return Index;
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
            Red.Clean();
            Red_Ball.broadcastAndWait();
            break;

        case 6:
            Blue.Clean();
            Blue_Ball.broadcastAndWait();
            break;
        }
    }

} // namespace Find_Balls

namespace Tools
{
    Log_data ToSquireData(Log_data Object)
    {
        Log_data Out;
        Out.x = Object.x - (Object.width / 2);
        Out.y = Object.y - (Object.height / 2);
        Out.width = Object.width;
        Out.height = Object.height;
        Out.area = Object.area;

        return Out;
    }

    CoverData Cover(Log_data O, int x, int y, int w, int h)
    {
        Log_data Object = ToSquireData(O);
        CoverData Data;
        if (Object.x < x)
            Data.x = x;
        else
            Data.x = Object.x;

        if (Object.y < y)
            Data.y = y;
        else
            Data.y = Object.y;

        if (Object.x + Object.width < x + w)
            Data.width = Object.width;
        else
            Data.width = w;

        if (Object.y + Object.height < y + h)
            Data.height = Object.height;
        else
            Data.height = h;

        Data.Center_x = Object.x + (Object.width / 2);
        Data.Center_y = Object.y + (Object.height / 2);

        Data.CoverPercent = (double(Data.width) * double(Data.height)) / (double(w) * double(h));

        return Data;
    }

    void GoNear()
    {
        int Index;
        Log_data MaxObject;
        Index = Find_Balls::Red.FindMaxCoverd(80, 100, 160, 111);
        MaxObject = Find_Balls::Red.DataFromId(Index);
        Brain.Screen.setFont(mono40);
        Brain.Screen.clearLine(1,black);
        Brain.Screen.setCursor(Brain.Screen.row(),1);
        Brain.Screen.setCursor(1,1);
        Brain.Screen.print(MaxObject.x);

        Brain.Screen.setFont(mono40);
        Brain.Screen.clearLine(2,black);
        Brain.Screen.setCursor(Brain.Screen.row(),1);
        Brain.Screen.setCursor(2,1);
        Brain.Screen.print(MaxObject.y);
        // CoverData First = Cover(item, 80, 100, 160, 50);
        // CoverData Second = Cover(item, 80, 150, 160, 61);
    }
} // namespace Tools

namespace AiCube
{
    void InitAll()
    {
        Find_Goals::Init();
        Find_Balls::Init();
    }

    void AiRun()
    {
        while (true)
        {
            Tools::GoNear();
            wait(100, msec);
        }
    }
} // namespace AiCube

namespace MasterMode
{
    void cycle()
    {
        AiCube::InitAll();

        AiCube::AiRun();
    }
} // namespace MasterMode

#endif;