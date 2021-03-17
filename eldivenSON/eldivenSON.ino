/*SOL EL KONFÜGİRASYONU*/

#include <Wire.h>
#include <IRremote.h>
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();
IRsend irsend;
double X,Y,Z,Xn,Yn,Zn;
int led =6;
void setup(void) 
{
   Serial.begin(9600);  
   if(!accel.begin())
   {
      Serial.println(" ADXL345 bulunamadı.");
      while(1);
   }
   pinMode(led,OUTPUT);
}
void loop(void) 
{
   analogWrite(led,20);
   
   delay(1500); //genel delay

   
   sensors_event_t event; 
   accel.getEvent(&event);
   X=event.acceleration.x;
   Y=event.acceleration.y;
   Z=event.acceleration.z;

   if(Z>=9){
    Serial.print("\nAvuc ici assagida\n");
    //delay(1000);
    TVackapa();
   }


   if(Z<=-9){
    Serial.print("\nAvuc ici yukarida\n");
    //delay(1000);
     while(1){
    Serial.print("\nMenu\n");
    
   sensors_event_t event; 
   accel.getEvent(&event);
   
    Zn=event.acceleration.z;
    if(Zn>-8){
    break;
    }
    else{
      MenuOkMute();
    }
    }
   }


   if(X>=6.5 && X<=9){
    Serial.print("\nKanal yukari yonde degisecek\n");
    irsend.sendNEC(0x20DF00FF, 32);
  
    //delay(1000);
   }


   if(X<=-7.5 && X>-9){
    Serial.print("\nKanal assagi yonde degisecek\n");
    irsend.sendNEC(0x20DF807F, 32);
 
    //delay(1000);
   }



   if(Y<=-9){ // Ses açma / kapama modu
    while(1){
   sensors_event_t event; 
   accel.getEvent(&event);
   Zn=event.acceleration.z;

   if(Zn<=-6.5){
    //Serial.print("\nSes kisilacak\n");
    irsend.sendNEC(0x20DFC03F, 32);
    delay(250);
   }
   if(Zn>=6.5 && Zn<9){
    //Serial.print("\nSes acilacak\n");
    irsend.sendNEC(0x20DF40BF, 32);
    delay(250);
   }
   if(Zn>=9 || Zn<=-9.5){
    break;
   }
    }
    
   }



   if(X>=9.5){                             // Sayı girme modu
    while(1){
    Serial.print("\nSayılar giriliyor\n");
    
   sensors_event_t event; 
   accel.getEvent(&event);
   
    Xn=event.acceleration.x;
    if(Xn<9){
    break;
    }
    else{
      sayilar();
    }
    }
   }
}
   






void sayilar(){

//serce = A0 , yuzuk = A1 , orta = A2 , isaret = A3
int serce,yuzuk,orta,isaret ;

serce=0;
yuzuk=0;
orta=0;
isaret=0;

delay(1000); // delay degeri secilecek

   


if(analogRead(A0)<600){
   serce =1;}
   else{
   serce=0;}
if(analogRead(A1)<600){
   yuzuk=1;}
   else{
   yuzuk=0;}
if(analogRead(A2)<600){
   orta=1;}
   else{
   orta=0;}
if(analogRead(A3)<600){
   isaret=1;}
   else{
   isaret=0;}

//degerler atandı , simdi islenecek


if( serce && !yuzuk && !orta && !isaret){
//1
 irsend.sendNEC(0x20DF8877, 32);
     
}
if( !serce && yuzuk && !orta && !isaret){
//2
irsend.sendNEC(0x20DF48B7, 32);
    
}
if( !serce && !yuzuk && orta && !isaret){
//3  
irsend.sendNEC(0x20DFC837, 32);
    
}
if( !serce && !yuzuk && !orta && isaret){
//4
 irsend.sendNEC(0x20DF28D7, 32);  
 
}
if( serce && !yuzuk && !orta && isaret){
//5
irsend.sendNEC(0x20DFA857, 32);    

}
if( !serce && yuzuk && !orta && isaret){
//6
irsend.sendNEC(0x20DF6897, 32);    

}
if( !serce && !yuzuk && orta && isaret){
//7
irsend.sendNEC(0x20DFE817, 32);    

}
if( !serce && yuzuk && orta && isaret){
//8
 irsend.sendNEC(0x20DF18E7, 32);  
  
}
if( serce && yuzuk && orta && isaret){
//9
 irsend.sendNEC(0x20DF9867, 32);  
 
}
if( serce && yuzuk && orta && !isaret){
//0
 irsend.sendNEC(0x20DF08F7, 32);    
 
}
if(serce && yuzuk && !orta && !isaret){
  //okey
  irsend.sendNEC(0x20DF22DD, 32);
 
}
}


void TVackapa(){

 int serce,yuzuk,orta,isaret,counter ;

serce=0;
yuzuk=0;
orta=0;
isaret=0;

delay(1000); // delay degeri secilecek
if(analogRead(A0)<600){
   serce =1;}
   else{
   serce=0;}
if(analogRead(A1)<600){
   yuzuk=1;}
   else{
   yuzuk=0;}
if(analogRead(A2)<600){
   orta=1;}
   else{
   orta=0;}
if(analogRead(A3)<600){
   isaret=1;}
   else{
   isaret=0;} 

   
if( serce && yuzuk && orta && isaret){
//TV aç-kapa
irsend.sendNEC(0x20DF10EF, 32); 

}

if( serce && !yuzuk && !orta && !isaret){
 

//Kumanda kilit
while(1){
serce=0;
yuzuk=0;
orta=0;
isaret=0;
analogWrite(led,LOW);  
delay(1000);
if(analogRead(A0)<600){
   serce =1;}
   else{
   serce=0;}
if(analogRead(A1)<600){
   yuzuk=1;}
   else{
   yuzuk=0;}
if(analogRead(A2)<600){
   orta=1;}
   else{
   orta=0;}
if(analogRead(A3)<600){
   isaret=1;}
   else{
   isaret=0;} 

   sensors_event_t event; 
   accel.getEvent(&event);
   Zn=event.acceleration.z;
   if(Zn>=9){
 if( serce && !yuzuk && !orta && !isaret){
  break;
}     
}
}
}

  
}








void MenuOkMute(){


 int serce,yuzuk,orta,isaret,counter ;

serce=0;
yuzuk=0;
orta=0;
isaret=0;

delay(1000); // delay degeri secilecek
if(analogRead(A0)<600){
   serce =1;}
   else{
   serce=0;}
if(analogRead(A1)<600){
   yuzuk=1;}
   else{
   yuzuk=0;}
if(analogRead(A2)<600){
   orta=1;}
   else{
   orta=0;}
if(analogRead(A3)<600){
   isaret=1;}
   else{
   isaret=0;}



if( !serce && !yuzuk && !orta && isaret){
//yukarı ok

irsend.sendNEC(0x20DF02FD, 32);      
}

if( serce && !yuzuk && !orta && !isaret){
//assagı ok


 irsend.sendNEC(0x20DF827D, 32);   
}
if( !serce && !yuzuk && orta && !isaret){
//sol ok

irsend.sendNEC(0x20DFE01F, 32);    
}
if( !serce && yuzuk && !orta && !isaret){
//sag ok
 
irsend.sendNEC(0x20DF609F, 32); 
}
if( !serce && yuzuk && orta && !isaret){
//menu
  
irsend.sendNEC(0x20DFC23D, 32);
}
if( serce && yuzuk && !orta && !isaret){
//okey
   
irsend.sendNEC(0x20DF22DD, 32); 
}

if( serce && yuzuk && orta && isaret){
 //mute    
irsend.sendNEC(0x20DF906F, 32); 
}   


if( !serce && !yuzuk && orta && isaret){
//geri   
irsend.sendNEC(0x20DF14EB, 32);
}   

if( serce && !yuzuk && !orta && isaret){
//smart menü 
irsend.sendNEC(0x20DF3EC1, 32);
} 


}
