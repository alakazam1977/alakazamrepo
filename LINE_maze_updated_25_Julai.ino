//updated 8.44pm 15 feb


#define motorRightEn 5 // RightEn Pin 5 is connected to EN1 motorRightB
#define motorRightDir 4   //RightDir Pin 4 is connected to DIR1 motorRightA
#define motorLeftEn 6 //LeftEn Pin 6 is connected to EN2 motorLeftB
#define motorLeftDir 7 //LeftDir Pin 7 is connected to DIR2 motorLeftA

//motorLeftA  //value 1 motor kiri pusing belakang;
//motorLeftB // 0 stop motor

//motorRightA // 1 motor kanan pusing belakang;
//motorRightB //0 stop motor

//Pin declaration for LSS05
int senLeft = A1;
int senMLeft = A2;
int senMiddle = A3;
int senMRight = A4;
int senRight = A5;
int senFarLeft = A15;
int senFarRight = A14;
int senBLeft = A12;
int senBRight = A11;

int maxspd = 80; //at full batt power
int turn_spd = 60;
int injin_kereta;

void setup() {

 // Serial.begin(9600);
  
 //Motor Driver Pin Setup
  pinMode(motorRightEn,OUTPUT);
  pinMode(motorRightDir,OUTPUT);
  pinMode(motorLeftEn,OUTPUT);
  pinMode(motorLeftDir,OUTPUT);


// Line Sensor Pin Setup
  pinMode(senLeft,INPUT);
  pinMode(senMLeft,INPUT);
  pinMode(senMiddle,INPUT);
  pinMode(senMRight,INPUT);
  pinMode(senRight,INPUT);
  pinMode(senFarLeft,INPUT);
  pinMode(senFarRight,INPUT);
  pinMode(senBLeft,INPUT);
  pinMode(senBRight,INPUT);
 }

void loop() 

{// start void loop

  
while(injin_kereta == 1){ 



//straight line
if(digitalRead(senMLeft) == 1 || digitalRead(senMiddle)==1 || digitalRead(senMRight)==1)
{
  goto_straight_line();
}//end



  // ------- jumpa selekoh kiri.... ------------------------

if(digitalRead(senFarLeft) == 1 && digitalRead(senFarRight)==0)
  {
   motor(0,0); 
    while (digitalRead(senBLeft)==0)
    {
      motor(50,50);
    }

    motor(0,0);
    kekiri_pusing_bah();
    goto_straight_line();
   }

//-----------end turn left suksess 




// ------- jumpa selekoh kanan atau simpang terus dan kanan |- .... ------------------------

if(digitalRead(senFarLeft) ==0 && digitalRead(senFarRight)==1)
{   
    motor(0,0); 
    while (digitalRead(senBRight)==0)
    {
      motor(50,50);
    }
    motor(0,0);

    if (digitalRead(senMiddle)== 1)//sensor tengah jumpa straight line
    {
      goto_straight_line();
    }
    else //sensor tengah xjumpa line
    {
      kekanan_pusing_bah();
      goto_straight_line();
    }
  
}//end ------- jumpa selekoh kanan atau simpang terus dan kanan |-------------------------



  

// ------- jumpa T atau t atau destinasi.... ------------------------


if(digitalRead(senFarLeft)== 1 && digitalRead(senFarRight)== 1)

//if((digitalRead(senFarLeft)== 1)&&(digitalRead(senLeft)== 1) &&(digitalRead(senMLeft)== 1)&&(digitalRead(senMiddle)== 1) && (digitalRead(senMRight)== 1)&& (digitalRead(senRight)== 1)&& (digitalRead(senFarRight)== 1))
  {
    motor(0,0);
    while ((digitalRead(senBLeft)== 0)&& (digitalRead(senBRight)== 0))
    {
      motor(50,50);
     }//stop dan move depan sikit


    if((digitalRead(senFarLeft)== 1 && digitalRead(senFarRight)== 1) && (digitalRead(senBLeft)== 1)&& (digitalRead(senBRight)== 1))
    {
    motor(0,0);
    injin_kereta =0;
    }//sampai doh ghumoh kitoooo

    else
    {
    kekiri_pusing_bah();
    goto_straight_line();
    }//turn left bro
    
   
  }// ------- end jumpa T atau t.... ------------------------




// ------- found jalan mati.... ------------------------

if((digitalRead(senFarLeft)== 0)&&(digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 0)&& (digitalRead(senFarRight)== 0))
{
  lepak_jap_wei(); //berhenti dan move depan sikit
  
  while (digitalRead(senMRight)== 0)//turn right
          {
               motor(turn_spd, (-1*turn_spd));
          }   //end while turn
          
        motor(0,0); delay(200); 
        goto_straight_line();
        
}//---------------- end jalan mamposs




}//end injin kereta = 0

}//end void loop


void goto_straight_line()// ----------- straight line start 5 sensor used -------suksess -------------------------------
{

if((digitalRead(senLeft)== 0)&& (digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 1) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 0))
        {//00100
          
          motor(maxspd, maxspd);
         }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 1) && (digitalRead(senMiddle)== 1) && (digitalRead(senMRight)== 1)&& (digitalRead(senRight)== 0))
        //01110
        {
          motor(maxspd, maxspd);
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 1) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 0)&&(digitalRead(senRight)== 0))
        //01000
        {
         motor((0.375*maxspd), maxspd);
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 1)&& (digitalRead(senRight)== 0))
        //00010
        {
          motor(maxspd, (0.375*maxspd));
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 1) && (digitalRead(senMiddle)== 1) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 0))
                                   //01100
        {
          motor((0.2*maxspd), maxspd);
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 1) && (digitalRead(senMRight)== 1)&& (digitalRead(senRight)== 0))
                                   //00110
        {
          motor(maxspd, (0.2*maxspd));
        }
    else if((digitalRead(senLeft)== 1) &&(digitalRead(senMLeft)== 1) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 0))
                                   //11000
        {
          motor((0.125*maxspd), maxspd);
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 1)&& (digitalRead(senRight)== 1))
                                   //00011
        {
          motor(maxspd, (0.125*maxspd));
        }
    else if((digitalRead(senLeft)== 1) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 0))
                                   //10000
        {
          motor(0, maxspd);
        }
    else if((digitalRead(senLeft)== 0) &&(digitalRead(senMLeft)== 0) && (digitalRead(senMiddle)== 0) && (digitalRead(senMRight)== 0)&& (digitalRead(senRight)== 1))
                                   //00001
        {
          motor(maxspd, 0);
        }
      
// -------- end straight line ---------------------

}//end goto_straight_line()




void lepak_jap_wei()
{
        motor(0,0);
        delay(100);
         motor(50,50);//move depan sikit
         delay(150); // increase kalau tayar xinline dg line    
       
}



void kekiri_pusing_bah()
{
  while(digitalRead(senMLeft)== 0)//||(digitalRead(senMRight)==0))//turn lft
          {
               motor((-1*turn_spd), turn_spd);
          }   //end while turn lft
      
        motor(0,0); delay(150); motor(maxspd,maxspd);
 }



void kekanan_pusing_bah()
{
   while(digitalRead(senMRight)== 0)//||(digitalRead(senMRight)==0))//turn lft
          {
               motor(turn_spd, (-1*turn_spd));
                                       
           }   //end while turn lft

    motor(0,0); delay(150); motor(maxspd,maxspd);
}



void motor(int speedLM, int speedRM)
{
  int speed, maxSpeed = maxspd;
  
/*Perhatian!!
  motorLeftDir 1 bckwd
  motorLeftDir 0 fwd
  motorRightDir 1 bckwd
  motorRightDir 0 fwd
  */
 
if((speedLM < 0) && (speedRM < 0)){
digitalWrite(motorLeftDir, HIGH); // motor kiri rotate backward
analogWrite(motorLeftEn, (-1*speedLM));// speed left
digitalWrite(motorRightDir, HIGH); // motor kanan rotate backward
analogWrite(motorRightEn, (-1*speedRM));// speed right
}

else if((speedRM > 0) && (speedLM > 0)){
digitalWrite(motorLeftDir, LOW); // motor kiri rotate depan
analogWrite(motorLeftEn, speedLM);// speed left
digitalWrite(motorRightDir, LOW); // right motor rotate fwd
analogWrite(motorRightEn, speedRM);// speed right
}

else if((speedRM < 0) && (speedLM > 0)){
digitalWrite(motorLeftDir, 0); // Left motor rotate fwd
analogWrite(motorLeftEn, speedLM);// speed left
digitalWrite(motorRightDir, 1); // right motor rotate bkwd
analogWrite(motorRightEn, (-1*speedRM));// speed right
}

else if((speedRM > 0) && (speedLM < 0)){
digitalWrite(motorLeftDir, 1); // Left motor rotate bckwd
analogWrite(motorLeftEn, (-1*speedLM));// speed left
digitalWrite(motorRightDir, 0); // right motor rotate fwd
analogWrite(motorRightEn, speedRM);// speed 
}

else if((speedRM == 0) && (speedLM > 0)){
digitalWrite(motorLeftDir, 0); // Left motor rotate bckwd
analogWrite(motorLeftEn, speedLM);// speed left
digitalWrite(motorRightDir, 0); // right motor rotate fwd
analogWrite(motorRightEn, speedRM);// speed 
}

else if((speedRM > 0) && (speedLM == 0)){
digitalWrite(motorLeftDir, 1); // Left motor rotate bckwd
analogWrite(motorLeftEn, speedLM);// speed left
digitalWrite(motorRightDir, 0); // right motor rotate fwd
analogWrite(motorRightEn, speedRM);// speed 
}

else if((speedRM == 0) && (speedLM == 0)){
digitalWrite(motorLeftDir, 1); // Left motor rotate bckwd
analogWrite(motorLeftEn, speedLM);// speed left
digitalWrite(motorRightDir, 1); // right motor rotate backwd
analogWrite(motorRightEn, speedRM);// speed 
}

if(speed > maxSpeed) speed = maxSpeed; // Limit the speed;


}//end int motor
