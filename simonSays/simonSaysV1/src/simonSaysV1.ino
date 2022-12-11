
int buttonB = D0;    //blue
int ledB = D1;       //blue
int buttonG = D2;    //green
int ledG = D3;       //green
int buttonY = D4;    //yellow
int ledY = D5;       //yellow
int buttonR = D6;    //red
int ledR = A0;       //red

int prevBlue = LOW;  //blue
bool LED_stateB = FALSE;    //blue
int prevGreen = LOW;      //green
bool LED_stateG = FALSE;    //green
int prevYellow = LOW;      //yellow
bool LED_stateY = FALSE;    //yellow
int prevRed = LOW;      //red
bool LED_stateR = FALSE;    //red


// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
    pinMode(ledB, OUTPUT);
    digitalWrite(ledB, LOW);
    pinMode(ledG, OUTPUT);
    digitalWrite(ledG, LOW);
    pinMode(ledY, OUTPUT);
    digitalWrite(ledY, LOW);
    pinMode(ledR, OUTPUT);
    digitalWrite(ledR, LOW);
    
    //timeToToggleLED = millis() + 1000;
    pinMode(buttonB, INPUT_PULLDOWN);
    pinMode(buttonG, INPUT_PULLDOWN);  // INPUT mode with internal pull-down resistor
    pinMode(buttonY, INPUT_PULLDOWN);
    pinMode(buttonR, INPUT_PULLDOWN);
    Serial.begin(9600); 
}

int rounds = 0;
int points = 0;
unsigned long int timeToToggleLED;

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  unsigned long int currentTime = millis();
  int change = 1000;
  int curB = digitalRead(buttonB);
  bool startGame = TRUE;

  if(curB == LOW && startGame == FALSE){     //the idle light sequence while a game is not being played.
    if(currentTime > timeToToggleLED){  
    // Time to Toggle!
    LED_stateB = !LED_stateB;
    digitalWrite(ledB, LED_stateB);
    LED_stateG = !LED_stateG;
    digitalWrite(ledG, LED_stateG);
    LED_stateY = !LED_stateY;
    digitalWrite(ledY, LED_stateY);
    LED_stateR = !LED_stateR;
    digitalWrite(ledR, LED_stateR);

        // Calculate and store the next time to toggle the LED
    timeToToggleLED += change;
    }
    if (curB == HIGH && prevBlue == LOW){
      // a transition happened -- the user has just pressed the button
      Serial.println("Blue button press detected.1 startGame = "  );  //Debugging printout 
      startGame = !startGame;
    }

  } else {
    startGame = TRUE; //to make sure that the if statement directs here when it initially enters this part of the if statement
    int curG = digitalRead(buttonG); //reading button inputs
    int curY = digitalRead(buttonY);
    int curR = digitalRead(buttonR);
    
    
    digitalWrite(ledB, LOW); //keeps all LEDs off for the game to work
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledR, LOW);
    //start the game

    int simon = rand() % 4; //if simon = 0, then simon does not say. Otherwise, he does.
    int light = rand() % 3; //determines which light will be the focus of the round. 0 = green, 1 = yellow, 2 = red
    int points = 0;

    switch(light){
      case 0: 
        // green light
        LED_stateG = !LED_stateG;
        digitalWrite(ledG, HIGH);
        

        if(simon != 0){ 
          //0 is the "simon does not say" condition, 1&2&3 are "simon does say" conditions
          if(curG == HIGH && prevGreen == LOW){ //user presses the green button
          Serial.println("Simon did not say \"Press green.\" No points awarded");  //Debugging printout 
          
          }
        } else { 
          //simon says
          LED_stateB = !LED_stateB;
          digitalWrite(ledB, HIGH);
          if(curG == LOW && prevGreen == LOW){ //user presses the green button
          Serial.println("Simon said \"press green.\" 1 point awarded");  //Debugging printout 
          points++;
          }
        }
        
        break;

      case 1: 
        // yellow light
        LED_stateY = !LED_stateY;
        digitalWrite(ledY, HIGH);
        

        if(simon != 0){ //0 is the "simon does not say" condition, 1&2&3 are "simon does say" conditions
          if(curY == HIGH && prevYellow == LOW){ //user presses the yellow button
          Serial.println("Simon did not say \"Press yellow.\" No points awarded");  //Debugging printout 
          points++;
          }
        } else {
          LED_stateB = !LED_stateB;
          digitalWrite(ledB, HIGH);
          if(curY == HIGH && prevYellow == LOW){ //user presses the yellow button
          Serial.println("Simon said \"press yellow.\" 1 point awarded");  //Debugging printout 
          
          }
        }
        
        break;

      case 2: 
        // red light
        LED_stateR = !LED_stateR;
        digitalWrite(ledR, HIGH);
        

        if(simon != 0){ //0 is the "simon does not say" condition, 1&2&3 are "simon does say" conditions
          if(curR == HIGH && prevRed == LOW){ //user presses the red button
          Serial.println("Simon did not say \"Press red.\" No points awarded");  //Debugging printout 
          
          }
        } else {
          LED_stateB = !LED_stateB;
          digitalWrite(ledB, HIGH);
          if(curR == HIGH && prevRed == LOW){ //user presses the red button
          Serial.println("Simon said \"press red.\" 1 point awarded");  //Debugging printout 
          points++;
          }
        }
        
        break;

        default:
          Serial.println("Something went wrong");
          digitalWrite(ledB, LOW); //keeps all LEDs off for the game to work
          digitalWrite(ledG, LOW);
          digitalWrite(ledY, LOW);
          digitalWrite(ledR, LOW);
          break;

    }
    
    prevGreen = curG;
    prevYellow = curY;
    prevRed = curR;
      
  }


  prevBlue = curB;
}