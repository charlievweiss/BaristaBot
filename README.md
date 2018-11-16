# BaristaBot
Code for BaristaBot, a project for the class Principles of Engineering

## Desired Behavior (in time blocks)
- Dispense cup
- send cup under main house
- AT THE SAME TIME, wet filter and start grinding
- once cup reaches house, pour water
- once water is poured, send cup out.

## These things are real:
  - Main.ino
    - user interface (bean level, water level, cup level)
    - times coffee brewing (sends signal to grind board and pour board)
  - bean_grinding.ino
    - times grinding once high signal received
  - temp_triggerd_pour.ino
    - wets filter, spirals water, dispenses water
  - temp_control.ino
    - reads temp of water and converts in
    - turns coil on and off according to temp
    - sends a signal to the solenoid based on temperature
  
## Boards:
  - Main (user inputs - 3 (size/number cups/strength??)
    - need estop
  - Water pour/spiral
  - Grinding
  - cup dispensing/conveyor
  - temp_control
