
    To start, the game has two modes: Idle mode and active mode. 
    Idle mode is activated when no games are currently being played, and is characterized by the leds toggling on and off in a one second interval. 
    Active mode is activated when a game is started or being played, and is characterized by one or two leds blinking.
      as part of the actual simon says game. 
    To switch between active and idle mode, I'm set on the idea that the blue button switches users between the idle and active modes, but its not working.
    Currently, the program is stuck in active mode, and I'll wait to fix that until the actual game is completed.

    In active mode, the game is played and is currently structured with two variables, if statements, and case statements. 
    The two variables are int simon and int light.
    Light determines which of the three non-blue lights are turned on, and which button should be pushed. 
    Simon determines whether the blue led is on or off. If it's on, then simon says. If it's off, then simon does not say.
      Simon is currently a random number between 0 and 4. The intention is to make a 1/4 chance that simon does not say during the loops. 
      To do so, 0 is currently set as the "doesnt say" number because its simple. 
    The code structure of the game is set up in the order of: choose which light light -> determine whether simon says.
