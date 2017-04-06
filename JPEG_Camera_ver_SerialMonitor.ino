byte incomingbyte;
int a=0x0000,j=0,k=0,count=0;     //Read Starting address       
uint8_t MH,ML;
boolean EndFlag=0;
                               
void SendResetCmd();              //Set the cmd func.
void SendTakePhotoCmd();
void SendReadDataCmd();
void StopTakePhotoCmd();

int ZERO = 0x00;

void setup()
{ 
  Serial.begin(115200);            //set uart data
  Serial3.begin(38400);
  
  SendResetCmd();                 //reset camera
  delay(4000);
}

void loop() 
{
            SendTakePhotoCmd();              //send takeing picture cmd
            
            delay(100);
      
            while(Serial3.available()>0)      //read finished cmd
            {
              incomingbyte=Serial3.read();    
            }   
      
            byte a[32];
            
            while(!EndFlag)      
            {  
               j=0;
               k=0;
               count=0;
               SendReadDataCmd();            //send reading data cmd
      
               delay(25);
               while(Serial3.available()>0)
               {
                     incomingbyte=Serial3.read();   //read data
                     k++;
                     if((k>5)&&(j<32)&&(!EndFlag))
                     {
                       a[j]=incomingbyte;
                       if((a[j-1]==0xFF)&&(a[j]==0xD9))      //Check if the picture translation is over
                       EndFlag=1;                           
                       j++;
        	       count++;
                     }
               }
               
                for(j=0;j<count;j++)
                {  
                    if(a[j]<0x10)
                    Serial.print("0");
                    Serial.print(a[j],HEX);
                   // Serial.print(" ");
                }                                       //Send jpeg picture over the serial port
                Serial.println();
            }
            while(true);
            //digitalWrite(resetPin, LOW);               //reset to wait for the taking-picture command again
}
//Send Reset command
void SendResetCmd()
{
      Serial3.write(0x56);
      Serial3.write(ZERO);
      Serial3.write(0x26);
      Serial3.write(ZERO);
}
//Send take picture command
void SendTakePhotoCmd()
{
      Serial3.write(0x56);
      Serial3.write(ZERO);
      Serial3.write(0x36);
      Serial3.write(0x01);
      Serial3.write(ZERO);  
}
//Read data cmd
void SendReadDataCmd()
{
      MH=a/0x100;
      ML=a%0x100;
      Serial3.write(0x56);
      Serial3.write(ZERO);
      Serial3.write(0x32);
      Serial3.write(0x0c);
      Serial3.write(ZERO); 
      Serial3.write(0x0a);
      Serial3.write(ZERO);
      Serial3.write(ZERO);
      Serial3.write(MH);
      Serial3.write(ML);   
      Serial3.write(ZERO);
      Serial3.write(ZERO);
      Serial3.write(ZERO);
      Serial3.write(0x20);
      Serial3.write(ZERO);  
      Serial3.write(0x0a);
      a+=0x20;             
}
//stop taking picture cmd
void StopTakePhotoCmd()
{
      Serial3.write(0x56);
      Serial3.write(ZERO);
      Serial3.write(0x36);
      Serial3.write(0x01);
      Serial3.write(0x03);        
}










