#define capPin A3
#define buz 9
#define pulsePin A4
#define led2 2
#define led 10
#define button 4
#define Pin 6

long sumExpect=0; //running sum of 64 sums 
long ignor=0;   //number of ignored sums
long diff=0;        //difference between sum and avgsum
long tempsum=0;
long buzPeriod=0; 
boolean first=true;
int j=0;

void setup() 
{
  Serial.begin(9600);
  pinMode(pulsePin, OUTPUT); 
  digitalWrite(pulsePin, LOW);
  pinMode(capPin, INPUT);  
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  pinMode(led, OUTPUT);
  pinMode(button,INPUT);
  tempsum=0;
}

void loop() 
{
  int minval=99999;
  int maxval=0;
  long int sum=0;

  for (int i=0; i<2000; i++)
  {
    //reset the capacitor
   
    reset();
    applyPulses();
    int val = analogRead(capPin);
    
    
    
    if (diff>200){
      digitalWrite(led,HIGH);
          
    }
    else{
      digitalWrite(led,LOW);
      
      }
      //Serial.println(val); 
    //read the charge of capacitor
     //takes 13x8=104 microseconds
    sum=sum+val;

  //subtract minimum and maximum value to remove spikes
  }
  
  if (j<10) 
  {sumExpect=(sumExpect*j+sum)/(j+1);
  j=j+1;} 
  else{//set sumExpect to expected value 
  tempsum=tempsum+sum;
  diff=sumExpect-sum;
  Serial.println(diff); 
  j=j+1;
  }

  if(abs(diff)>50){tempsum=tempsum-sum; j=j-1;}
  if(j==30){sumExpect=tempsum/20;j=10;tempsum=0;}
  
     
}

void applyPulses()
{
    for (int i=0;i<3;i++) 
    {
      digitalWrite(pulsePin,HIGH); //take 3.5 uS
      delayMicroseconds(3);
      digitalWrite(pulsePin,LOW);  //take 3.5 uS
      delayMicroseconds(3);
    }
      
}
void reset()
{pinMode(Pin,OUTPUT);
 digitalWrite(Pin,LOW);
 delayMicroseconds(5);
 pinMode(Pin,INPUT);
}
