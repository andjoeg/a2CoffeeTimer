# a2CoffeeTimer
Arduino Code for the Artisans Asylum Coffee Timer

This is the code running on the CoffeeTimer in the Artisan's Asylum MPR1 Kitchen.

I have also included the STL and PDF files for the body and front panel to be 3D-printed and laser cut, respectively. 

I will eventually add a wiring diagram, but the overall system composes of an Arduino Pro Mini, and a 7-segment display, and a button. Follow the comments in the main file to figure out pin wiring. Everything gets assembled into the case, which uses heat-set inserts to allow the front panel to screw in.

The use of the timer is simple - power it via a Mini-USB cable into the Arduino (or any other 5V power supply going into Arduino's RAW and GND pins). Press the button to start or reset the timer. It will count the hours and minutes (up to 99 hours) since the button was last pressed. Whenever a fresh pot is brewed, reset the timer.
