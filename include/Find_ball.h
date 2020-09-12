#include "vex.h"
#include <queue>
using namespace vex;
event Blue_Ball = event();
event Red_Ball = event();


class DrawRectangle{
    public:
        std::queue<int> x;
        std::queue<int> y;
        std::queue<int> width;
        std::queue<int> height;
        std::queue<vex::color> color;
        
        void Add(int x_,int y_,int w_,int h_,vex::color c_){
            x.push(x_);
            y.push(y_);
            width.push(w_);
            height.push(h_);
            color.push(c_);
        }

        void Draw(){
            Brain.Screen.clearScreen();

            while (!x.empty())
            {
                int x_ = x.front(),y_ = y.front(),w_ = width.front(),h_ = height.front();

                if(w_*h_>200){
                    Brain.Screen.setPenColor(color.front());
                    Brain.Screen.drawRectangle(x_,y_,w_,h_);
                }

                x.pop();
                y.pop();
                width.pop();
                height.pop();
                color.pop();
            }
            
            
        }
};

DrawRectangle draw;

void BLUE_BALL_callback(){

    Vision.takeSnapshot(Vision__BLUEBALL);
    int len = 0;
    int x,y,width,height;

    if(Vision.objectCount > 0){
        len = Vision.objectCount;
        for(int i = 0;i<=len-1;i++){
            width = Vision.objects[i].width;
            height = Vision.objects[i].height;
            x = Vision.objects[i].centerX - (width/2);
            y = Vision.objects[i].centerY - (height/2);
            draw.Add(x,y,width,height,blue);
        }
        
    }
}

void RED_BALL_callback(){

    Vision.takeSnapshot(Vision__REDBALL);
    int len = 0;
    int x,y,width,height;

    if(Vision.objectCount > 0){
        len = Vision.objectCount;
        for(int i = 0;i<=len-1;i++){
            width = Vision.objects[i].width;
            height = Vision.objects[i].height;
            x = Vision.objects[i].centerX - (width/2);
            y = Vision.objects[i].centerY - (height/2);
            draw.Add(x,y,width,height,red);
        }
        
    }
}

void Find_Ball(){

// Brain.Screen.setPenColor(blue);
//                 Brain.Screen.drawRectangle(10,10,10,10);

    Blue_Ball(BLUE_BALL_callback);
    Red_Ball(RED_BALL_callback);

    // Red_Ball(Red_callback);
    while (1){
        
        Blue_Ball.broadcastAndWait();
        Red_Ball.broadcastAndWait();
        //Red_Object.broadcastAndWait();
        draw.Draw();
    }
}