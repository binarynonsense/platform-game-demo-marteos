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
--  file: cgame.cpp                                                        --
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

#include "cgame.h"
#include "frames.h"

void CGame :: Init(){

        int ret;                
        
        reset_blocking_mode ();
        set_raw_mode ();
        //ret = init_vga(G640x480x16, VGA, PCI_DEVICE_ID_S3_TRIO64V2);
        //assert (ret == 0);
        //vga_setmode(G320x200x256);
        ret = init_vga(G320x200x256, VGA, PCI_DEVICE_ID_S3_TRIO64V2);

        
        period = 1.0/8.0;
        double_to_timespec(period, &period_ts);
        
        
        #define VGASIZE 320*200
        buffer = (unsigned char *)malloc(VGASIZE);//virtual canvas
        memset(buffer, 0, VGASIZE);

        
        mario= new CSprite(4);
        mario->frames[0].pixelColor=&mario_1;
        mario->frames[1].pixelColor=&mario_2;
        mario->frames[2].pixelColor=&mario_3;
        mario->frames[3].pixelColor=&mario_4;
        mario->frameState[IDLE][0]=0;
        mario->frameState[IDLE][1]=-1;
        mario->frameState[WALKING][0]=0;
        mario->frameState[WALKING][1]=1;
        mario->frameState[WALKING][2]=0;
        mario->frameState[WALKING][3]=2;
        mario->frameState[WALKING][4]=-1;
        mario->frameState[JUMPING][0]=3;
        mario->frameState[JUMPING][1]=-1;
        
        mario->SetPosX(2);
        mario->SetPosY(200-55-16);
        mario->direction=LEFT;
                
        gameOver = 0;
         
        vga_setpalette(0, 0, 0, 0);//black
        vga_setpalette(1, 255, 255, 255);//white
        vga_setpalette(2, 90, 90, 90);//grey
        vga_setpalette(3, 255, 0, 0);//red
        vga_setpalette(4, 0, 0, 175);//dark ble
        vga_setpalette(5, 0, 25, 175);//light blue
}

void CGame :: DrawCanvas(){
    int i,j;
    int color = 17;
    int lines = 1;
//     for(i=0;i<320;i++){
//         for(j=0;j<200;j++){
//             buffer[320*j+i]=1;
//         }
//     }
    
    for(j=0;j<20;j++){
        for(i=0;i<320;i++){
            buffer[320*j+i]=color;
        }
    }
    for(j=20;j<120;j++){
        for(i=0;i<320;i++){
            buffer[320*j+i]=color;
        }
        lines++;
        if (lines == 10){
            lines=1;
            color++;
        }
    }
    for(j=120;j<200;j++){
        for(i=0;i<320;i++){
            buffer[320*j+i]=color;
        }
    }
    
    for(j=(200-16);j<(200-16+2);j++){
        for(i=0;i<320;i++){
            buffer[320*j+i]=(12*16)-1;
        }
    }
    
    for(j=(200-16+2);j<200;j++){
        for(i=0;i<320;i++){
            buffer[320*j+i]=(12*16)-1-6;
        }
    }

    
}

void CGame :: Flip(){
    
    vga_waitretrace();
    vga_drawscansegment(buffer,0,0,VGASIZE);
    
    
}

int CGame :: GameLoop(){

         while(!gameOver){               
                
                mario->CheckForMovement();                
                
                DrawCanvas();
                mario->Draw(buffer);
                Flip();
                
                
                nanosleep(&period_ts, NULL);
        }
        return 0;
}
