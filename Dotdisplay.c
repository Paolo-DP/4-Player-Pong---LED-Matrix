char dot_display[10] = {0x0F,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,'\n','\0'};
int i=0, pucktest=0;
char temp[3];
char tempin[20];
char extra=0;
char sendHEXdata[21];

//player input vairables
char player1_btns[3] = {0,0,0}, player2_btns[3] = {0,0,0};
char player34_inputs=0;
char p34_delimiter[5] = {':', 'E', 'N', 'D', '\0'};
char puck1 = 0x1c, puck2 = 0x38, puck3=1, puck4=6;

//game variables
char ball_xspeed=0, ball_yspeed=0, ball_xposition = 0x20, ball_yposition=1;
int paddlespeed = 1220/10;
int puckspeed = 1220/6;
char serve=0;

char p1=0, p2=0, p3=0, p4=0;  //player enables
char mode=0;
/*
0 = player select
1 = playmode
*/
char auto_mode=0;

//control variables
int tmr0_i=0, count=0, tmr0_mark=1221;

void output_to_dot_display();
void updategame();
void drawPucks();
void puckupdate();
void movePlayerPucks();
void getPlayerInputs();

void player_select();
void playerselecttimer();

void game();

void interrupt(){

     if(intcon.tmr0if){
         if(mode==0){
             player_select();
         }
         else if(mode==1){
             game();
         }
         if(tmr0_i%40==0){
             strcpy(sendHEXdata,"DOT:");
             for(i=0; i<8; i++){
                 ByteToHex(dot_display[i], temp);
                 strcat(sendHEXdata, temp);
             }
             uart1_write_text(sendHEXdata);

              if(uart1_data_ready()){
                   player34_inputs = uart1_read();
              }


         }
         tmr0_i++;
         intcon.tmr0if = 0;
     }
}

void game(){
     if(tmr0_i%paddlespeed==0){
          movePlayerPucks();
     }
     if(tmr0_i%puckspeed==0){
         puckupdate();
     }
     if(tmr0_i==1220){

          tmr0_i=0;
     }
     else if(tmr0_i%20==0){ //60Hz refresh
         updategame();
         getPlayerInputs();
         
         if((portb.f1 && portb.f0 && portb.f2)
          || (portb.f3 && portb.f4 && portb.f5)
          || ((player34_inputs&0x07)==0x07)
          || ((player34_inputs&0x38)==0x38)){
             mode=0;
             p1=0;
             p2=0;
             p3=0;
             p4=0;

          }
     }
}

void player_select(){
     if(tmr0_i%80==0){

         //drawPucks();
         if(p1)
             dot_display[0]=0x81;
         else
             dot_display[0]=0xff;
         if(p2)
             dot_display[7]=0x81;
         else
             dot_display[7]=0xff;

         extra = 0xff;
         if(p3==1)
             extra-=0x80;
         if(p4==1)
             extra-=0x01;
         for(i=1;i<7;i++){
             dot_display[i]=extra;
         }
         //if(tmr0_i!=1220)
             playerselecttimer();
     }
     if(tmr0_i%304==0){

     }
     if(tmr0_i%20==0){
         if(p1)
             p1=(!portb.f0);
         else
             p1=portb.f2;
         if(p2)
             p2=(!portb.f5);
         else
             p2=portb.f3;
         if(p3)
             p3=((player34_inputs&0x08)==0);
         else
             p3=((player34_inputs&0x20)!=0);

         if(p4)
             p4=((player34_inputs&0x01)==0);
         else
             p4=((player34_inputs&0x04)!=0);

         if(!((portb.f1) || (portb.f4) || ((player34_inputs&0x12)!=0)))
             count=0;


     }
     if(tmr0_i==1220){
         /*for(i=0;i<8;i++){
             dot_display[i]=0xff;
         }*/
         tmr0_i=0;
         //playerselecttimer();
         if(count==4){
             ball_xspeed=0;
             ball_yspeed=0;
             mode=1;
             count=0;
             tmr0_mark=1221;
              if(p1){
                  serve=1;
                  ball_yposition=1;
              }
              else if(p2){
                  serve=2;
                  ball_yposition=6;
              }
              else if(p3){
                  serve=3;
                  ball_xposition=0x40;
              }
              else if(p4){
                  serve=4;
                  ball_xposition=0x02;
              }
         }
         else
             count++;

     }
}

void playerselecttimer(){
     switch(count){
         case 4:
             dot_display[3]-=0x10;
         case 3:
             dot_display[4]-=0x10;
         case 2:
             dot_display[4]-=0x08;
         case 1:
             dot_display[3]-=0x08;
             break;
     }

}

void main() {
     trisa=0;
     trisd=0;
     trisc=0x80;
     trisb=0xff;

     intcon = 0xA0;
     option_reg = 0xC3;
     porta.f1=0;
     porta.f1=1;
     uart1_init(9600);
     for(i=0; i<8; i++){
         dot_display[i]=0xff;
     }
     while(1){
         output_to_dot_display();
     }
}

void updategame(){
     for(i=0; i<8; i++){
         dot_display[i] = 0xff;
     }
     dot_display[ball_yposition]-=ball_xposition;
     drawPucks();
}

void drawPucks(){
     dot_display[0]-=puck1*p1;
     dot_display[7]-=puck2*p2;

     if(p3){
         dot_display[puck3-1] -= (dot_display[puck3-1]>0x80)*0x80;
         dot_display[puck3] -= 0x80;
         dot_display[puck3+1] -= (dot_display[puck3+1]>0x80)*0x80;
     }
     if(p4){
         dot_display[puck4-1] -= ((dot_display[puck4-1]&0x01)!=0)*0x01;
         dot_display[puck4] -= 0x01;
         dot_display[puck4+1] -= ((dot_display[puck4+1]&0x01)!=0)*0x01;
     }
}

void getPlayerInputs(){
     player1_btns[0] = portb.f0;
     player1_btns[1] = portb.f1;
     player1_btns[2] = portb.f2;
     player2_btns[0] = portb.f3;
     player2_btns[1] = portb.f4;
     player2_btns[2] = portb.f5;
}

void movePlayerPucks(){
     if(auto_mode){
         puck1 = ball_xposition + (2*ball_xposition) + (ball_xposition/2);
         puck2=puck1;
         puck3=ball_yposition;
         puck4=puck3;
     }
     else{
         if(p1){
             if(puck1>0x07)
                  puck1/=1+player1_btns[2];
             if(puck1<0xe0)
                  puck1*=1+player1_btns[0];
         }
         if(p2){
             if(puck2>0x07)
                  puck2/=1+player2_btns[2];
             if(puck2<0xe0)
                  puck2*=1+player2_btns[0];
         }
         if(p3){
             if(puck3<6)
                 puck3+=(player34_inputs&0x08)!=0;
             if(puck3>1)
                 puck3-=(player34_inputs&0x20)!=0;
         }
         if(p4){
             if(puck4<6)
                 puck4+=(player34_inputs&0x04)!=0;
             if(puck4>1)
                 puck4-=(player34_inputs&0x01)!=0;
         }
         if(serve!=0)
             puckupdate();
     }
}

void puckupdate(){
     if(serve!=0){
          switch(serve){
              case 1:
                  ball_xposition = puck1 & (puck1*2) & (puck1/2);
                  if(player1_btns[1])
                       ball_yspeed=1;
                  break;
              case 2:
                  ball_xposition = puck2 & (puck2*2) & (puck2/2);
                  if(player2_btns[1])
                       ball_yspeed=-1;
                  break;
              case 3:
                  ball_yposition = puck3;
                  if(player34_inputs & 0x10)
                       ball_xspeed=1;
                  break;
              case 4:
                  ball_yposition = puck4;
                  if(player34_inputs & 0x02)
                       ball_xspeed=-1;
                  break;
          }
          if(ball_xspeed!=0 || ball_yspeed!=0)
              serve=0;
     }
     else{
           switch(ball_yposition){
               case 0:
                    if(!p1){
                        ball_yspeed=1;
                    }
                    else{
                        serve=1;
                        ball_xspeed=0;
                        ball_yspeed=0;
                        ball_yposition=1;
                    }
                    break;
               case 1:
                    if(p1){
                        if((puck1/ball_xposition==1)){
                             ball_yspeed=1;
                             if(ball_xspeed!=1)
                                 ball_xspeed++;
                        }
                        else if((puck1/ball_xposition)==3){
                             ball_yspeed=1;
                        }
                        else if((puck1/ball_xposition)==7){
                             ball_yspeed=1;
                             if(ball_xspeed!=0xff)
                                 ball_xspeed--;
                        }
                    }
                   break;
               case 6:
                    if(p2){
                        if((puck2/ball_xposition==1)){
                             ball_yspeed=-1;
                             if(ball_xspeed!=1)
                                 ball_xspeed++;
                        }
                        else if((puck2/ball_xposition)==3){
                             ball_yspeed=-1;
                        }
                        else if((puck2/ball_xposition)==7){
                             ball_yspeed=-1;
                             if(ball_xspeed!=0xff)
                                 ball_xspeed--;
                        }
                    }
                    break;
               case 7:
                    if(!p2){
                        ball_yspeed=-1;
                    }
                    else{
                        serve=2;
                        ball_xspeed=0;
                        ball_yspeed=0;
                        ball_yposition=6;
                    }
                    break;

           }

           switch(ball_xposition){
               case 1:
                    if(!p4){
                        ball_xspeed=1;
                    }
                    else{
                        serve=4;
                        ball_xspeed=0;
                        ball_yspeed=0;
                        ball_xposition=0x02;
                    }
                    break;
               case 2:
                   if(p4){
                      pucktest = puck4-ball_yposition;
                        if(pucktest==0){
                            ball_xspeed=1;
                        }
                        if(pucktest==1){
                            ball_xspeed=1;
                            if(ball_yspeed!=0xff)
                                 ball_yspeed--;
                        }
                        if(pucktest==-1){
                            ball_xspeed=1;
                            if(ball_yspeed!=1)
                                 ball_yspeed++;;
                        }
                     }
                   break;
               case 0x40:
                     if(p3){
                      pucktest = puck3-ball_yposition;
                        if(pucktest==0){
                            ball_xspeed=-1;
                        }
                        if(pucktest==1){
                            ball_xspeed=-1;
                            if(ball_yspeed!=0xff)
                                 ball_yspeed--;
                        }
                        if(pucktest==-1){
                            ball_xspeed=-1;
                            if(ball_yspeed!=1)
                                 ball_yspeed++;;
                        }
                     }
                    break;

               case 0x80:
                    if(!p3){
                        ball_xspeed=-1;
                    }
                    else{
                        serve=3;
                        ball_xspeed=0;
                        ball_yspeed=0;
                        ball_xposition=0x40;
                    }
                    break;

           }

           ball_yposition += ball_yspeed ;

           if(ball_xspeed==1)
               ball_xposition*=2;
           else if(ball_xspeed==0xff)
               ball_xposition/=2;
     }
}



void output_to_dot_display(){
     //portd=0xff;
     porta.f1=0;
     porta.f1=1;
     portd=dot_display[0];
     //delay_ms(100);
     for(i=1; i<8; i++){
         portd=0xff;
         porta.f0=0;
         porta.f0=1;
         portd=dot_display[i];
         //delay_ms(100);
     }

}