#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

String acct = "29 4E 0B 18";
String pass = "Anshika Rawat";
int balance = 1000;
int rate = 300;

void setup() 
{
  Serial.begin(9600);
    SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(" WELCOME ");
  Serial.println("Please scan your card on the reader "); 
}


void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.println();
  Serial.print("\n UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  
   content.toUpperCase();
   if (content.substring(1) == acct) 
   {
       Serial.print("Name = ");
       Serial.println(pass);
       Serial.print("Message : ");
       if (balance >= rate)
       {
              balance -= rate;
              
              Serial.print(" Payment Done");
              delay(1000);
         }
             else
             {
               Serial.print(" Sorry Insufficient Balance");
               delay(1000);
             }
              Serial.println();
              Serial.print("Balance Available = ");
              Serial.print(balance);
              delay(3000);
              return;
    }
  
       else
       {
         Serial.println("Invalid card");
         Serial.println("Please get a valid card");
         delay(3000);
       }
  }   
