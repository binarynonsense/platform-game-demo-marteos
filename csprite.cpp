/*---------------------------------------------------------------------------
--                            Platform Game Demo                           -- 
-----------------------------------------------------------------------------
--                                                                         --
--  This is an example demo for MaRTE OS.                                  --
--                                                                         --
--  author:   Alvaro Garcia Cuesta                                         --
--  email:    alvaro@binarynonsense.com                                    --
--  website:  www.binarynonsense.com                                       --
--                                                                         --
--  file: csprite.cpp                                                      --
--                                                                         --
--  this file contains [...]                                               --
-----------------------------------------------------------------------------
--                               License                                  -- 
-----------------------------------------------------------------------------
--                                                                         --
-- This is free software; you can redistribute it and/or modify it         --
-- under the terms of the GNU General Public License version 2 as          -- 
-- published by the Free Software Foundation.                              --
-- See COPYING file for more info about the license                        --
--                                                                         --
-----------------------------------------------------------------------------
--                        last update: 08 Oct 09                           --
---------------------------------------------------------------------------*/

#include "csprite.h"

CSprite :: CSprite(){
        numFrames=1;
        frames=new CFrame[numFrames];
        frameNumber=0;
        direction=LEFT;
        
}

CSprite :: CSprite(int nFrames){
        numFrames=nFrames;
        frames=new CFrame[numFrames];
        frameNumber=0;
        direction=LEFT;
        
}

void CSprite :: CheckForMovement (){
    
    char key;
    key=getchar();
    
    switch(state){
        case IDLE:
            if(key=='d' || key=='6'){
                SetPosX(GetPosX()+5);
                state=WALKING;
                direction=RIGHT;
                frameNumber++;
                if(frameState[state][frameNumber]==-1){
                    frameNumber=0;
                }
                
            }else if(key=='a' || key=='4'){
                SetPosX(GetPosX()-5);
                state=WALKING;
                direction=LEFT;
                frameNumber++;
                if(frameState[state][frameNumber]==-1){
                    frameNumber=0;
                }
            }
            else if(key=='w' || key=='8'){
                state=JUMPING;
                jumpDistance=-10;
                frameNumber=0;
                SetPosY(GetPosY()+jumpDistance);
            }
            break;
        case WALKING:
            if(key=='d' || key=='6'){
                SetPosX(GetPosX()+5);
                state=WALKING;
                direction=RIGHT;
                frameNumber++;
                if(frameState[state][frameNumber]==-1){
                    frameNumber=0;
                }
            }else if(key=='a' || key=='4'){
                SetPosX(GetPosX()-5);
                state=WALKING;
                direction=LEFT;
                frameNumber++;
                if(frameState[state][frameNumber]==-1){
                    frameNumber=0;
                }
            }else if(key=='w' || key=='8'){
                state=JUMPING;
                jumpDistance=-10;
                frameNumber=0;
                SetPosY(GetPosY()+jumpDistance);
            }else{
                    state=IDLE;
                    frameNumber=0;
            }
            break;
        case JUMPING:
            if(key=='d' || key=='6'){
                SetPosX(GetPosX()+5);
                direction=RIGHT;
            }else if(key=='a' || key=='4'){
                SetPosX(GetPosX()-5);
                direction=LEFT;
            }
            SetPosY(GetPosY()+jumpDistance);
            jumpDistance+=2;
            if(GetPosY()>=199-16-55){
                SetPosY(200-55-16);
                state=IDLE;
            }
            break;
    }    
        
    //flush keyboard buffer
    while(getchar()!=-1){
    }
}

void CSprite :: Draw (unsigned char *buffer){
    
    int x = GetPosX();
    int y = GetPosY();
    
    int i,j;
    if (direction==RIGHT){
        for(i=0;i<50;i++){
            for(j=0;j<55;j++){
                if( (*frames[frameState[state][frameNumber]].pixelColor)[i][j]>=0){
                    //vga_pixel(conv_to_point(x+i,y+j),(*frames[0].pixelColor)[i][j]);
                    buffer[320*(y+j)+(x+i)]=(*frames[frameState[state][frameNumber]].pixelColor)[i][j];
                }
            }
        }
    }else{
        for(i=0;i<50;i++){
            for(j=0;j<55;j++){
                if( (*frames[frameState[state][frameNumber]].pixelColor)[49-i][j]>=0){
                    //vga_pixel(conv_to_point(x+i,y+j),(*frames[0].pixelColor)[49-i][j]);
                    buffer[320*(y+j)+(x+i)]=(*frames[frameState[state][frameNumber]].pixelColor)[49-i][j];
                }
            }
        }
    }
        
}
