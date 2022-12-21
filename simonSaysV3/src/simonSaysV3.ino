

int buttonB = D0; // blue
int ledB = D1;    // blue
int buttonG = D2; // green
int ledG = D3;    // green
int buttonY = D4; // yellow
int ledY = D5;    // yellow
int buttonR = D6; // red
int ledR = A0;    // red

int prevBlue = LOW;      // blue
bool LED_stateB = FALSE; // blue
int prevGreen = LOW;     // green
bool LED_stateG = FALSE; // green
int prevYellow = LOW;    // yellow
bool LED_stateY = FALSE; // yellow
int prevRed = LOW;       // red
bool LED_stateR = FALSE; // red

int rounds = 0;
int points;
unsigned long int timeToToggleLED;
bool startGame = FALSE;

// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  Particle.variable("intVal", points);

  pinMode(ledB, OUTPUT);
  digitalWrite(ledB, LOW);
  pinMode(ledG, OUTPUT);
  digitalWrite(ledG, LOW);
  pinMode(ledY, OUTPUT);
  digitalWrite(ledY, LOW);
  pinMode(ledR, OUTPUT);
  digitalWrite(ledR, LOW);

  // timeToToggleLED = millis() + 1000;
  pinMode(buttonB, INPUT_PULLDOWN);
  pinMode(buttonG, INPUT_PULLDOWN); // INPUT mode with internal pull-down resistor
  pinMode(buttonY, INPUT_PULLDOWN);
  pinMode(buttonR, INPUT_PULLDOWN);

  Serial.begin(9600);
}

void gameOver() // signals an incorrect input and the resulting game over mode
{
  digitalWrite(ledB, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, HIGH);
  delay(100);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
  delay(100);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, HIGH);
  delay(100);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
  delay(100);
  digitalWrite(ledB, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, HIGH);
  delay(100);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
  delay(100);
}

void startingLights() // signals the start of the game, watch LEDS
{
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
  delay(1000);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, LOW);
  delay(1000);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, HIGH);
  delay(1000);
  digitalWrite(ledB, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledY, HIGH);
  digitalWrite(ledR, HIGH);
  delay(1000);
}

// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  // The core of your code will likely live here.

  unsigned long int currentTime = millis();
  int change = 1000;
  int curB = digitalRead(buttonB);

  if (startGame == FALSE)
  {                                  // the idle light sequence while a game is not being played.
    int curG = digitalRead(buttonG); // reading button inputs
    int curY = digitalRead(buttonY);
    int curR = digitalRead(buttonR);

    if (currentTime > timeToToggleLED)
    {
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
    if (curB == HIGH && prevBlue == LOW)
    {
      // a transition happened -- the user has just pressed the button
      Serial.println("Blue button press detected. Start the game!"); // Debugging printout
      startGame = !startGame;
      prevBlue = curB;

      startingLights();
    }
    if (curG == HIGH || curY == HIGH || curR == HIGH)
    {
      Serial.print("Points = ");
      Serial.println(points);
    }
  }
  else
  {
    startGame = TRUE;
    prevBlue = FALSE;                // to make sure that the if statement directs here when it initially enters this part of the if statement
    int curG = digitalRead(buttonG); // reading button inputs
    int curY = digitalRead(buttonY);
    int curR = digitalRead(buttonR);

    digitalWrite(ledB, LOW); // keeps all LEDs off for the game to work
    digitalWrite(ledG, LOW);
    digitalWrite(ledY, LOW);
    digitalWrite(ledR, LOW);
    delay(500);

    // start the game

    int simon = rand() % 2; // if simon = 0, then simon does not say. Otherwise, he does.
    int light = rand() % 3; // determines which light will be the focus of the round. 0 = green, 1 = yellow, 2 = red

    switch (light)
    {
    case 0:
      // green light

      digitalWrite(ledG, HIGH); // turn on the green LED

      delay(50);
      if (simon == 0) // simon does not say
      {
        Serial.println("Hold the green button.");
        delay(2500); // Gives time for the user to make an appropriate input

        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curG == HIGH || curY == HIGH || curR == HIGH) // user presses any button (they currently should not)
        {
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
        else
        {
          Serial.println(" One point awarded");
          points++;
        }
      }
      else // simon says
      {

        Serial.println("Simon says hold the green button.");
        digitalWrite(ledB, HIGH); // turn on the simon LED

        delay(2500);                 // Gives time for the user to make an appropriate input
        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curG == HIGH && curY == LOW && curR == LOW)
        {                                     // user presses the green button
          Serial.println(" 1 point awarded"); // Debugging printout

          points++;
        }
        else
        {
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
      }
      delay(50);
      break;

    case 1:
      // yellow light
      digitalWrite(ledY, HIGH);
      delay(50);

      if (simon == 0)
      { // 0 is the "simon does not say" condition, 1&2&3 are "simon does say" conditions
        Serial.println("hold the yellow button.");
        delay(2500);

        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curY == HIGH || curG == HIGH || curR == HIGH) // user presses any button (they currently should not)
        {
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
        else
        {
          Serial.println(" One point awarded");
          points++;
        }
      }
      else
      {

        digitalWrite(ledB, HIGH); // turn on the simon LED

        Serial.println("Simon says hold the yellow button.");
        delay(2500);                 // Gives time for the user to make an appropriate input
        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curY == HIGH && curG == LOW && curR == LOW)
        {                                     // user presses the yellow button
          Serial.println(" 1 point awarded"); // Debugging printout
          points++;
        }
        else
        {
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
      }
      delay(100);
      break;

    case 2:
      // red light

      digitalWrite(ledR, HIGH);

      delay(50);
      if (simon == 0)
      { // 0 is the "simon does not say" condition, 1&2&3 are "simon does say" conditions
        Serial.println("Press the red button");
        delay(2500);                 // Gives time for the user to make an appropriate input
        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curR == HIGH || curG == HIGH || curY == HIGH)
        {                                       // user presses the red button
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
        else
        {
          Serial.println(" One point awarded");
          points++;
        }
      }
      else
      {

        digitalWrite(ledB, HIGH); // turning on the simon led

        Serial.println("Simon says hold the red button");
        delay(2500);                 // Gives time for the user to make an appropriate input
        curG = digitalRead(buttonG); // reads all button inputs to make sure only the correct button is/isnt pressed
        curY = digitalRead(buttonY);
        curR = digitalRead(buttonR);

        if (curR == HIGH && curG == LOW && curY == LOW)
        {                                     // user presses the red button
          Serial.println(" 1 point awarded"); // Debugging printout
          points++;
        }
        else
        {
          Serial.println(" No points awarded"); // Debugging printout
          gameOver();
          startGame = !startGame;
        }
      }

      delay(100);
      break;

    default: // turns all LEDS off in case something doesn't work (it shouldn't)
      Serial.println("Something went wrong");
      digitalWrite(ledB, LOW);
      digitalWrite(ledG, LOW);
      digitalWrite(ledY, LOW);
      digitalWrite(ledR, LOW);
      break;
    }

    Serial.println("");
    delay(1000); // A pause in between rounds.
    prevGreen = curG;
    prevYellow = curY;
    prevRed = curR;
  }

  curB = digitalRead(buttonB);
  if (curB == HIGH && prevBlue == LOW) // Push the blue button to switch to idle mode
  {
    // a transition happened -- the user has just pressed the blue button
    Serial.println("Blue button press detected. Enter idle mode"); // Debugging printout
    startGame = !startGame;
  }

  delay(1000);
  prevBlue = curB;
}