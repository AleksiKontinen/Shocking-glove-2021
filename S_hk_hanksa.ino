/* Setuppi on arduino nanossa. Nappi on GRD D2, Ledit on D3-5, rele on D6
 *  Tnappi on D7, D9 on PWM portti joten laser siihen, VCC vain releeseen. 
 *  Muista 220ohm ressu ledeihin ja 47 ohm ledi jos käytät 3V laseria
 *  Muista releen rämpytys pitää korjata se on paha onglema kun sähköt virtaa. 
 */





const int rele = 11, nappi = 2, led1 = 3, led2 = 4, led3 = 5, led4=6, led5=7, led6=8, Tnappi=10, laser=9;
bool onoff=false, aloituksenesto;
int tila, laserteho=0, x, moodi=1, Tnappitila, lasertila=1;


void setup() {
 pinMode(nappi,INPUT_PULLUP);
 pinMode(led1,OUTPUT);
 pinMode(led2,OUTPUT);
 pinMode(led3,OUTPUT);
 pinMode(led4,OUTPUT);
 pinMode(led5,OUTPUT);
 pinMode(led6,OUTPUT);
 pinMode(rele, OUTPUT);
 digitalWrite(rele,HIGH);
 pinMode(laser,OUTPUT);
 pinMode(Tnappi, INPUT_PULLUP);
//Serial.begin(9600); //muista poistaa lopullisesta
aloituksenesto=false;
}



void loop() 
{
  if(aloituksenesto==false) 
    {
    aloitus();//mennään aloitukseen 
    aloituksenesto=true;//ei jouduta enään aloitukseen ellei määritetä aloituksenestoa pois (false)
    //Serial.println("aloitus saatettu loppuun");
    }

  delay(500); //turha mutta silti siinä vältää ainakin rämppäyksen

  //Serial.println("valikossa");

  tila=digitalRead(nappi);//moodien valikon perusta

    if(moodi>3)
    {
      moodi=1;
    }
    else
    {
      moodi++;
    }


    
switch(moodi)//itse moodi valikko
  {
  case 1:
  peruspainallus();
  break;

  case 2:
  lasermoodi();  
  break;

  case 3:
  showmoodi();
  break;
  }
lopetus();
}






void peruspainallus()//toiminta näppäimestä sähköä
{
digitalWrite(led1,HIGH);
digitalWrite(led2,HIGH);
//Serial.println("valitsit perus tilan");
  do
  {
   Tnappitila=digitalRead(Tnappi);
   if(Tnappitila==LOW)
    {
    digitalWrite(rele,LOW);//rele auki nappia painamalla
    delay(50); 
    }
    else
    {
    digitalWrite(rele,HIGH);
    }
  }
while(digitalRead(nappi)==HIGH);
delay(100);
//Serial.println("poistuit perus tilasta");
lopetus();
return;
}



void lasermoodi()
{
//Serial.println("valitsit laser tilan");
digitalWrite(led3,HIGH);  
digitalWrite(led4,HIGH);
  do{
  Tnappitila=digitalRead(Tnappi);//sama kun muissakin napin tunnistus kohdissa
   
      if(Tnappitila==LOW)
      {
        if(lasertila<3)
        {
          lasertila++;
          delay(500);
        }else{lasertila=1;}
        if(lasertila==1){laserteho=0;} //pois päältä, kissa safe ja full power
        if(lasertila==2){laserteho=5;}
        if(lasertila==3){laserteho=255;}
      //Serial.print(lasertila);
      delay(500);
      analogWrite(laser,laserteho);
      delay(500);
      }
   }while(digitalRead(nappi)==HIGH);
delay(750);
//Serial.println("poistuit laserista");
lopetus();
return;

}
    
     
   
  
void showmoodi()
{
//Serial.println("showmoodissa");
  do
  {
  digitalWrite(led5,HIGH);  
  digitalWrite(led6,HIGH); 
  Tnappitila=digitalRead(Tnappi);
  if(Tnappitila==LOW)
    {
    //Serial.println("painallus");
    for(int x=0; x<=255; x++)
      {
      analogWrite(laser,x);
      //Serial.println(x);
      delay(16);
      }
    digitalWrite(laser,LOW);
    for(int x=0; x<=6; x++)
      {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      delay(200);
      lopetus();
      delay(100);
      }
     digitalWrite(rele,LOW);
     delay(500);
     digitalWrite(rele,HIGH);
    }
  }while(digitalRead(nappi)==HIGH);
  delay(750);
  //Serial.println("poistuit juhlasta");
  lopetus();
  return;
}



  





void aloitus()
{ //aloitus ja päällelaitto
 //Serial.println("aloitus aloitettu");
  do{//tämä pitää tilan koodissa kunnes olet painannut nappia tietyn verran
    tila=digitalRead(nappi);
    if(tila==LOW){
    //Serial.println("painallus");
      for(int x = 0; x <= 100; x++){//lasketaan 100 tietyllä viiveellä
      //Serial.println(x);
      delay(20);
        if(digitalRead(nappi)!=LOW){ //jos keskeytät koko homma keskeytyy
        //Serial.println("pidempää"); // muista nyt sit poistaa
        lopetus();
        break;
       }
        if (x>17){digitalWrite(led1,HIGH);}
        if(x>33){digitalWrite(led2, HIGH);}
        if(x>50){digitalWrite(led3, HIGH);}
        if(x>66){digitalWrite(led4, HIGH);}
        if(x>83){digitalWrite(led5, HIGH);}
        if(x==100){//laskettu 100 vapautetaan tästä nappi tilasta
        onoff=true;
        digitalWrite(led6, HIGH);
        delay(750);
        lopetus();
        }
      }
    }
  //Serial.println(onoff);
  delay(1000);
  }while(onoff==false);
 
digitalWrite(led1, HIGH);//valo tanssi animaatio
delay(500);
digitalWrite(led2, HIGH);
delay(500);
digitalWrite(led3, HIGH);
delay(500);
digitalWrite(led4, HIGH);
delay(500);
digitalWrite(led5, HIGH);
delay(500);
digitalWrite(led6, HIGH);
delay(500);
digitalWrite(led1, LOW);
delay(500);
digitalWrite(led2, LOW);
delay(500);
digitalWrite(led3, LOW);
delay(500);
digitalWrite(led4, LOW);
delay(500);
digitalWrite(led5,LOW);
delay(500);
digitalWrite(led6,LOW);
delay(500);
lopetus();
return 0;//palataan void looppiin
}

void lopetus()
{
int lopetussekvenssi[9]={3,4,5,6,7,8,9  };
for(int x=0; x!=7; x++)
  {
    digitalWrite(lopetussekvenssi[x],LOW);
    //Serial.println(x);
  }
digitalWrite(rele,HIGH);
laserteho=0;
lasertila=1;
//Serial.println("lopetus tehty");
}
//alle 10 bugia kahdessa funktiossa, ihan vitun hyvä suoritus aamulla nähdään toimiiko???


  
