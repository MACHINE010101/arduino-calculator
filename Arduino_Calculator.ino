#include "Display.h"

const int BUTTON = 8;
const int LED_GREEN = 5;
const int LED_RED = 4;
const int POTMETER = 14;

int num_1;
int num_2;
int mode = 0;
int val;
char opr; 
bool last_btn_state = HIGH;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(POTMETER, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  bool btn_press = false;
  bool btn_state = digitalRead(BUTTON);

  if(btn_state != last_btn_state)
  {
    delay(50);
    btn_state = digitalRead(BUTTON);
    
    if(btn_state == LOW)
    {
      btn_press = true;
      }
    last_btn_state = btn_state;
  }

  if(mode == 0)
  {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    
    Display.show("----");
    delay(3000);

    mode = 1;
    }
  else if(mode == 1)
  {
    val = analogRead(POTMETER);
    num_1 = map(val, 0, 1023, -20, 20);
    Display.show(num_1);
    if(btn_press == true)
    mode = 2;
    }
  else if(mode == 2)
  {
    val = analogRead(POTMETER);
    val = map(val, 0, 1023, 0, 100);
    
    if(val <= 25)
    {
      Display.show("a");
      opr = '+';
      }
    else if(val <= 50 && val > 25)
    {
      Display.show("s");
      opr = '-';
      }
    else if(val <= 75 && val > 50)
    {
      Display.show("t");
      opr = '*';
      }
    else if(val <= 100 && val > 50)
    {
      Display.show("d");
      opr = '/';
      }

    if(btn_press)
      mode = 3;   
    }
   else if(mode == 3)
   {
    val = analogRead(POTMETER);
    num_2 = map(val, 0, 1023, -20, 20);
    Display.show(num_2);
    if(btn_press == true)
    mode = 4;
    }
    else if(mode == 4)
    {
      float result;

      if(opr == '+')
      {
        result = num_1 + num_2;
      Display.show(result);
      digitalWrite(LED_GREEN, HIGH);
      
        }
        else if(opr == '-')
        {
        result = num_1 - num_2;
      Display.show(result);
      digitalWrite(LED_GREEN, HIGH);
      
        }
        else if(opr == '*')
        {
        int result1 = num_1 * num_2;
      Display.show(result1);
      digitalWrite(LED_GREEN, HIGH);
     
        }
        else if(opr == '/')
        {
          if(num_2 == 0)
          {
            Display.show("Err");
          digitalWrite(LED_RED, HIGH);
          
            }
            else
            {
              float result = (float)num_1 / (float)num_2;
              Display.show(result);
              digitalWrite(LED_GREEN, HIGH);
      
              }
                            
                  
          }
      if(btn_press)
          {mode = 0; }
    }  
}
