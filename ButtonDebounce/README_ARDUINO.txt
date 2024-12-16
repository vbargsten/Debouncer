The MIT License (MIT)

Copyright (c) 2014-2016

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Original author Trent Cleghorn 
https://github.com/tcleg/Button_Debouncer

Adapted for Arduino by 
Louis Bertrand <louis.bertrand@durhamcollege.ca>
March 2016

Modifications:
* Used only C++ implementation
* Renamed files from button_debounce.* to ButtonDebounce.*
* Created Arduino keywords.txt file

Warning! The Arduino IDE Library Manager now has a library called ButtonDebounce
by Maykon L. Capellari https://github.com/maykon/ButtonDebounce
To avoid a naming conflict you need to rename the folder and the two C++ files,
and also edit the #include in the renamed cpp file.
Personally, I renamed the files to the same as the class name:
    Debouncer.h and Debouncer.cpp .

You should be able to copy the folder ButtonDebounce into 
your Arduino working folder typically 
 C:\My Documents\Arduino\libraries\
and use the library in your sketch. 

1. Restart the IDE.
2. Import the library:
   Sketch > Import Library...
   (this will create a line 
    #include <ButtonDebounce.h>
3. Instantiate one or more Debouncer variables
   /* Use BUTTON_PIN_0 if the switch is active-low
    * BUTTON_PIN_0 is declared in ButtonDebounce.h
    * Arduino readDigital() reads only pin 0.
    */
   Debouncer port1(BUTTON_PIN_0);
4. Read switch digital 2 periodically in loop() and process the value
   port1.ButtonProcess(digitalRead(2));
5. Button debounced state is available on demand
   if ( port1.ButtonPressed(BUTTON_PIN_0) ) {
     // do something
   }
