#ifndef MASTER_MODE_
#define MASTER_MODE_

#include "vex.h"
#include <algorithm>
#include <queue>

using namespace vex;

class DrawRectangle
{
public:
    std::queue<int> x;
    std::queue<int> y;
    std::queue<int> width;
    std::queue<int> height;
    std::queue<vex::color> color_;

    void Add(int x_, int y_, int w_, int h_, vex::color c_)
    {
        x.push(x_);
        y.push(y_);
        width.push(w_);
        height.push(h_);
        color_.push(c_);
    }

    void Draw()
    {
        Brain.Screen.clearScreen();

        while (!x.empty())
        {
            int x_ = x.front(), y_ = y.front(), w_ = width.front(), h_ = height.front();

            Brain.Screen.setPenColor(color_.front());
            Brain.Screen.drawRectangle(x_, y_, w_, h_);

            x.pop();
            y.pop();
            width.pop();
            height.pop();
            color_.pop();
        }
    }
};

DrawRectangle draw;

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

    struct DecisionMaking
    {
        int size;
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

    // 最小识别 cx 255 cy 25 w 48 50 h 48 50
    // 右 微 cx 240 241 cy 26 w 48 50 h 52
    // 右 中 cx 222 223 cy 26 w 48 50 h 52
    // 右 大 cx 214 215 cy 26 w 48 50 h 52

    // 左 微 cx 263 264 cy 26 w 50 52 h 30 52
    // 左 中 cx 269 270 cy 26 w 50 52 h 50 52
    // 左 大 cx 281 282 cy 26 w 50 52 h 50 52

    // 标准识别
    // 5 cm
    // cx 239 cy 28 w 46 48 h 56

    // 10 cm
    // cx 239 cy 30 w 42 44 h 59 60

    // 15 cm
    // cx 234 cy 31 w 40 42 h 58 60

    // 20 cm
    // cx 228 229 cy 37 w 38 40 h 54

    // 25 cm
    // cx 225 226 cy 40 w 34 36 h 52

    // 30 cm
    // cx 224 225 cy 42 w 32 34 h 43

    // 35 cm
    // cx 220 221 cy 44 45 w 32 h 44 46

    // 40 cm
    // cx 220 221 cy 47 w 28 30 h 42
    Advise_flow MasterAdvise(DecisionMaking DM)
    {
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