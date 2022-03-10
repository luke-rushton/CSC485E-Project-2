#include <LiquidCrystal.h>
#include <Stepper.h>

#define STEPS 180
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int buttonState = 0;
bool runDataSet = false;
bool isReset = false;
int iterator = 0;
Stepper stepperLeft(STEPS, 13, 9, 10, 8);
Stepper stepperRight(STEPS, 7, A0, 6, A1);
double CSCPercentage [] = {0.05, 0.24, 0.44, 0.55, 0.70, 0.83, 0.89, 0.95, 0.95, 0.98};
double HumanitiesPercentage [] = {0.37, 0.30, 0.28, 0.30, 0.24, 0.17, 0.20, 0.21, 0.14};
String year [] = {"2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019", "2020", "2021"};


void setup() {
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(9600);
}

void loop() {
  buttonState= digitalRead(A2);
  if(buttonState == HIGH){
      runDataSet = true;
  }
  Serial.print(buttonState);
  if (runDataSet) {
    if (isReset){
      lcd.clear();
      
      for (int i = (2500 * CSCPercentage[iterator]); i >0; i = i - 1){
        stepperRight.step(-1);
        delay(5);
      }
      for (int i = (2500 * HumanitiesPercentage[iterator]); i > 0; i = i - 1){
        stepperLeft.step(-1);
        delay(5);
      }

      delay(500);
      isReset = false;
      runDataSet = false;
      iterator++;
    } else {
      lcd.clear();
      lcd.print(year[iterator]);
      
      for (int i = 0; i < (2500 * CSCPercentage[iterator]); i++){
        stepperRight.step(1);
        delay(5);
      }
      for (int i = 0; i < (2500 * HumanitiesPercentage[iterator]); i++){
        stepperLeft.step(1);
        delay(5);
      }
      
      delay(500);
      isReset = true;
      runDataSet = false;
    }
  }
  if(iterator > 9){
    iterator = 0;
  }
}
 
