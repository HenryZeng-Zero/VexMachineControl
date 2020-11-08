#ifndef MASTER_MODE_
#define MASTER_MODE_

#include "../vex.h"
#include <map>

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

class Data
{
private:
    Log_data Data[20];
    int Count = -1;

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

    void Find_Min(int x, int y, int width, int height)
    {
        Count++;
        Data[Count].x = x;
        Data[Count].y = y;
        Data[Count].width = width;
        Data[Count].height = height;
        Data[Count].area = width * height;
    }

    void Find_Max(int x, int y, int width, int height)
    {
        Count++;
        Data[Count].x = x;
        Data[Count].y = y;
        Data[Count].width = width;
        Data[Count].height = height;
        Data[Count].area = width * height;
    }
};

// 找球

namespace Find_Goals
{

    event Green = event();
    void Green_callback()
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
            }
        }
    }

    void Find_Ball()
    {
        // Brain.Screen.setPenColor(blue);
        //                 Brain.Screen.drawRectangle(10,10,10,10);

        Green(Green_callback);

        // Red_Ball(Red_callback);
        while (1)
        {
            Green.broadcastAndWait();
            // Red_Object.broadcastAndWait();
        }
    }

} // namespace Find_Goals

namespace Find_Balls
{
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
            }
        }
    }

    void Find_Ball()
    {
        // Brain.Screen.setPenColor(blue);
        //                 Brain.Screen.drawRectangle(10,10,10,10);

        Blue_Ball(BLUE_BALL_callback);
        Red_Ball(RED_BALL_callback);

        // Red_Ball(Red_callback);
        while (1)
        {
            Blue_Ball.broadcastAndWait();
            Red_Ball.broadcastAndWait();
            // Red_Object.broadcastAndWait();
        }
    }

} // namespace Find_Balls

#endif;