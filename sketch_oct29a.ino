#define Trig 2 //引脚Tring 连接 IO D2
#define Echo 3 //引脚Echo 连接 IO D3 
#include<Servo.h>
#include <SCoop.h>
#include <Chrono.h>
Servo my;
int pin = A0; //定义引脚为D2
double duration=0; //定义duration变量为无符号长整数型变量
Chrono chronoB;

float cm; //距离变量
float temp; // 
int R=4;
int G=5;
int B=8;
int pos=0;
int port=10;
int port1=11;
int port3=6;
int port4=7;
char ch;
int state;
int flag=0;
unsigned long timee;
void setup()
{
     Serial.begin(9600);
       //超声波   
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(port, OUTPUT);
  pinMode(port1, OUTPUT);
  pinMode(port3, OUTPUT);
  pinMode(port4, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(G, OUTPUT);
  //my.attach(9);
}


//超声波测距
int distance()
{

   //给Trig发送一个低高低的短时间脉冲,触发测距
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  
  
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,
  //pulseIn函数会等待引脚变为HIGH,开始计算时间,再等待变为LOW并停止计时
  //返回脉冲的长度
  
  //声速是:340m/1s 换算成 34000cm / 1000000μs => 34 / 1000
  //因为发送到接收,实际是相同距离走了2回,所以要除以2
  //距离(厘米)  =  (回波时间 * (34 / 1000)) / 2
  //简化后的计算公式为 (回波时间 * 17)/ 1000
  
  cm = (temp * 17 )/1000; //把回波时间换算成cm
  /*Serial.print("Echo =");
  Serial.println(temp);//串口输出等待时间的原始数据
  Serial.print(" | | Distance = ");
  Serial.print(cm);//串口输出距离换算成cm的结果
  Serial.print("cm");*/
  delay(500);
  return cm;
}

void stops()
{
  Serial.println("stop");
       digitalWrite(port1,LOW);
       digitalWrite(port,LOW);
       digitalWrite(port3,LOW);
       digitalWrite(port4,LOW);
   
}
 
void loop() {
  
  
   state=analogRead(A0);
  
 if ( chronoB.hasPassed(1000) )
   { 
   
   // 如果自启动以来已经超过1000毫秒，则返回true
    chronoB.restart(); // 重新启动crono，以便稍后再次触发
     for(int i=0;i<3;i++)
  {
    duration= duration+ pulseIn(pin, LOW);
  }
   duration= duration/3;
     Serial.print("speed=");
    duration=duration/10000;
     Serial.print(21/duration);
     Serial.println("cm/s");
    }

  
 cm=distance();
 ch=Serial.read();
Serial.print("cm=============");
Serial.println(cm);
//Serial.println(analogRead(A0));
 if(cm<80)
      {
        //Serial.println("ppppppppppppppppppppppp");
         stops();
        
      }
   if(ch=='w')
   {  
    //Serial.println("wwwwwwwwwwwwwwwwwwwwww");
     digitalWrite(14,LOW);
      digitalWrite(port,HIGH);
      digitalWrite(port1,LOW);
      digitalWrite(port4,HIGH);
      digitalWrite(port3,LOW);
  }
 else if(ch=='s')
   {
    digitalWrite(14,HIGH);
    ///Serial.println("sssssssss");
    digitalWrite(port1,HIGH);
      digitalWrite(port,LOW);
       digitalWrite(port3,HIGH);
      digitalWrite(port4,LOW);     
  }
 else if(ch=='a')
   {
    digitalWrite(14,HIGH);
   // Serial.println("10+8+L   9-11-L");
    digitalWrite(port1,HIGH);
      digitalWrite(port,LOW);
       digitalWrite(port3,LOW);
      digitalWrite(port4,HIGH);   
  }
 else if(ch=='d')
   {
    digitalWrite(14,HIGH);
    //Serial.println("10+8+L   9-11-L");
      digitalWrite(port1,LOW);
      digitalWrite(port,HIGH);
       digitalWrite(port3,HIGH);
      digitalWrite(port4,LOW);
     
  }
 else if(ch=='p')
   {  
    stops();
   }  
   else if(ch=='m')
   {    
      digitalWrite(4,LOW);
      delay(500);
      digitalWrite(4,HIGH);
     
   }  
  }



