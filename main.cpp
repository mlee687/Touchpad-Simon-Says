#include "stdio.h"
#include "mbed.h"
#include "SPI_TFT_ILI9341.h"
#include "GraphicsDisplay.h"
#include "TextDisplay.h"
#include <mpr121.h> // Thanks to Anthony Buckton
#include "Arial12x12.h"
#include "SongPlayer.h"

float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };


DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
  
// Create the interrupt receiver object on pin 26       
InterruptIn interrupt(p26);
 
// Setup the i2c bus on pins 9 and 10                    
I2C i2c(p28, p27);
 
// Setup the Mpr121:
// constructor(i2c object, i2c address of the mpr121)
Mpr121 mpr121(&i2c, Mpr121::ADD_VSS);


SPI_TFT_ILI9341 TFT(p5, p6, p7, p8, p9, p10,"TFT"); // mosi, miso, sclk, cs, reset, dc
int lastpressed=0;
int reset=0;


}
void blink(int i){                  //short blink in order to acknowledge user input
    switch(i){
        case 0:
            wait(0.1);
            TFT.fillrect(10,20,70,70,Red);
            wait(0.1);
            TFT.fillrect(10,20,70,70,Black);
            wait(0.1);
            break;
        case 1:
            wait(0.1);
            TFT.fillrect(90,10,150,70,Red);
            wait(0.1);
            TFT.fillrect(90,10,150,70,Black);
            wait(0.1);
            break;
        case 2:
            wait(0.1);
            TFT.fillrect(170,10,230,70,Red);
            wait(0.1);
            TFT.fillrect(170,10,230,70,Black);
            wait(0.1);
            break;
        case 3:
            wait(0.1);
            TFT.fillrect(250,10,310,70,Red);
            wait(0.1);
            TFT.fillrect(250,10,310,70,Black);
            wait(0.1);
            break;
        case 4:
            wait(0.1);
            TFT.fillrect(10,90,70,150,Red);
            wait(0.1);
            TFT.fillrect(10,90,70,150,Black);
            wait(0.1);
            break;
        case 5:
            wait(0.1);
            TFT.fillrect(90,90,150,150,Red);
            wait(0.1);
            TFT.fillrect(90,90,150,150,Black);
            wait(0.1);
            break;
        case 6:
            wait(0.1);
            TFT.fillrect(170,90,230,150,Red);
            wait(0.1);
            TFT.fillrect(170,90,230,150,Black);
            wait(0.1);
            break;
        case 7:
            wait(0.1);
            TFT.fillrect(250,90,310,150,Red);
            wait(0.1);
            TFT.fillrect(250,90,310,150,Black);
            wait(0.1);
            break;
        case 8:
            wait(0.1);
            TFT.fillrect(10,170,70,230,Red);
            wait(0.1);
            TFT.fillrect(10,170,70,230,Black);
            wait(0.1);   
            break;
        case 9:
            wait(0.1);
            TFT.fillrect(90,170,150,230,Red);
            wait(0.1);
            TFT.fillrect(90,170,150,230,Black);
            wait(0.1);
            break;
        case 10:
            wait(0.1);
            TFT.fillrect(170,170,230,230,Red);
            wait(0.1);
            TFT.fillrect(170,170,230,230,Black);
            wait(0.1); 
            break;
        case 11:
            wait(0.1);
            TFT.fillrect(250,170,310,230,Red);
            wait(0.1);
            TFT.fillrect(250,170,310,230,Black);
            wait(0.1); 
            break;
       
        default:
            break;
       }
}    


void blink_long(int i){                 //long blink for users to see 
   switch(i){
        case 0:
            wait(0.5);
            TFT.fillrect(10,20,70,70,Blue);
            wait(0.5);
            TFT.fillrect(10,20,70,70,Black);
            wait(0.5);
            break;
        case 1:
            wait(0.5);
            TFT.fillrect(90,10,150,70,Blue);
            wait(0.5);
            TFT.fillrect(90,10,150,70,Black);
            wait(0.5);
            break;
        case 2:
            wait(0.5);
            TFT.fillrect(170,10,230,70,Blue);
            wait(0.5);
            TFT.fillrect(170,10,230,70,Black);
            wait(0.5);
            break;
        case 3:
            wait(0.5);
            TFT.fillrect(250,10,310,70,Blue);
            wait(0.5);
            TFT.fillrect(250,10,310,70,Black);
            wait(0.5);
            break;
        case 4:
            wait(0.5);
            TFT.fillrect(10,90,70,150,Blue);
            wait(0.5);
            TFT.fillrect(10,90,70,150,Black);
            wait(0.5);
            break;
        case 5:
            wait(0.5);
            TFT.fillrect(90,90,150,150,Blue);
            wait(0.5);
            TFT.fillrect(90,90,150,150,Black);
            wait(0.5);
            break;
        case 6:
            wait(0.5);
            TFT.fillrect(170,90,230,150,Blue);
            wait(0.5);
            TFT.fillrect(170,90,230,150,Black);
            wait(0.5);
            break;
        case 7:
            wait(0.5);
            TFT.fillrect(250,90,310,150,Blue);
            wait(0.5);
            TFT.fillrect(250,90,310,150,Black);
            wait(0.5);
            break;
        case 8:
            wait(0.5);
            TFT.fillrect(10,170,70,230,Blue);
            wait(0.5);
            TFT.fillrect(10,170,70,230,Black);
            wait(0.5);   
            break;
        case 9:
            wait(0.5);
            TFT.fillrect(90,170,150,230,Blue);
            wait(0.5);
            TFT.fillrect(90,170,150,230,Black);
            wait(0.5);
            break;
        case 10:
            wait(0.5);
            TFT.fillrect(170,170,230,230,Blue);
            wait(0.5);
            TFT.fillrect(170,170,230,230,Black);
            wait(0.5); 
            break;
        case 11:
            wait(0.5);
            TFT.fillrect(250,170,310,230,Blue);
            wait(0.5);
            TFT.fillrect(250,170,310,230,Black);
            wait(0.5); 
            break;
        default:
            break;
       }
}    

void fallInterrupt() {          //interrupt code to input from touchpad
    int key_code=0;
    int i=0;
    int value=mpr121.read(0x00);
    value +=mpr121.read(0x01)<<8;
    // LED demo mod
    i=0;
    // puts key number out to LEDs for demo
    for (i=0; i<12; i++) {
    if (((value>>i)&0x01)==1) key_code=i;
    }
    reset=0;
    led4=key_code & 0x01;
    led3=(key_code>>1) & 0x01;
    led2=(key_code>>2) & 0x01;
    led1=(key_code>>3) & 0x01;
    lastpressed = (led4)+2*(led3)+4*(led2)+8*(led1);
}


int main()
{

//////////////////////////Initializing the background color, and rectangles on the screen//////////////////////   
    SongPlayer Speaker(p25);     //need to add speaker interface and music thread

    int game_array[10];
    reset=1;
    TFT.claim(stdout);      // send stdout to the TFT display
    //TFT.claim(stderr);      // send stderr to the TFT display
    TFT.set_orientation(1);
    TFT.background(White);    // set background to black
    TFT.foreground(Black);
    TFT.cls();
    TFT.set_font((unsigned char*) Arial12x12);
    int rounds=1;
    int cur_round=0;
    int win=1;
    wait(2);
    
    interrupt.fall(&fallInterrupt);
    interrupt.mode(PullUp); 
    TFT.locate(120,120);
    TFT.printf("Begin Game!");
    Speaker.PlaySong(note,duration);
    wait(7);
    TFT.cls();
    TFT.fillrect(10,20,70,70,Black);
    TFT.fillrect(90,10,150,70,Black);
    TFT.fillrect(170,10,230,70,Black);
    TFT.fillrect(250,10,310,70,Black);
    TFT.fillrect(10,90,70,150,Black);
    TFT.fillrect(90,90,150,150,Black);
    TFT.fillrect(170,90,230,150,Black);
    TFT.fillrect(250,90,310,150,Black);
    TFT.fillrect(10,170,70,230,Black);
    TFT.fillrect(90,170,150,230,Black);
    TFT.fillrect(170,170,230,230,Black);
    TFT.fillrect(250,170,310,230,Black);
    
    while(1){
        TFT.locate(5,5);
        TFT.printf("Round %d",rounds);
        for(int i=0;i<rounds;i++){
            game_array[i]=rand()%12;
        }
        for(int i=0;i<rounds;i++){

            blink_long(game_array[i]);
        }
        while(1){
            if(reset==0){
             
                if(game_array[cur_round]!=lastpressed){
                     win=0;
                     break;
                }
                else{
                    blink(lastpressed);
                    reset++;
                    cur_round++;
                    if(cur_round==rounds) break;
                        
                } 
            }   
        }
        if(win==0||rounds==10) break;
            
        else{
            rounds++;
            cur_round=0;
        }    
    }
    if(win==1){
        for(int i=0;i<12;i++) {
            blink(i);
        }
        TFT.cls();
        TFT.locate(120,120);
        TFT.printf("You Win!");
        Speaker.PlaySong(note,duration);
        wait(7);
        }
    else{
         for(int i=0;i<12;i++) {
            blink(11-i);
        }
        TFT.cls();
        TFT.locate(120,120);
        TFT.printf("You lose!");
        Speaker.PlaySong(note,duration);
        wait(7);
    }
}
