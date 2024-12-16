//*********************************************************************************
// Copyright (C) 2014 Trent Cleghorn , <trentoncleghorn@gmail.com>
// 
//                                  MIT License
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//*********************************************************************************

//*********************************************************************************
// Headers
//*********************************************************************************
#include "Debouncer.h"

//*********************************************************************************
// Class Functions
//*********************************************************************************
Debouncer::
Debouncer(uint8_t pulledUpButtons)
{
    uint8_t i;
    
    index = 0;
    debouncedState = 0x00;
    changed = 0x00;
    pullType = pulledUpButtons;
    
    // Initialize the state array
    for(i = 0; i < NUM_BUTTON_STATES; i++)
    {
        state[i] = 0x00;
    }
}

void Debouncer::
ButtonProcess(uint8_t portStatus)
{
    uint8_t i;
    uint8_t lastDebouncedState = debouncedState;
    
    // If a button is high and is pulled down or
    // if a button is low and is pulled high, use a 1 bit
    // to denote the button has changed state. Else, a 0 bit
    // shows it is in a normal position.
    // Then, save the port status info into the state array
    state[index] = portStatus ^ pullType;
    
    // Debounce the buttons
    uint8_t consistentlyHigh = 0xFF;
    uint8_t consistentlyLow  = 0xFF;
    for(i = 0; i < NUM_BUTTON_STATES; i++)
    {
        consistentlyHigh &=  state[i];
        consistentlyLow  &= ~state[i];
    }
    //  Previous                                           New
    //  debouncedState  consistentlyHigh  consistentlyLow  debouncedState
    //  -               1                 -                1
    //  -               -                 1                0
    //  0               0                 0                0
    //  1               0                 0                1
    debouncedState = consistentlyHigh | (debouncedState & ~consistentlyLow);
    
    // Check to make sure the index hasn't gone over the limit
    index++;
    if(index >= NUM_BUTTON_STATES)
    {
        index = 0;
    }
    
    // Calculate what changed.
    // If the switch was high and is now low, 1 and 0 xORed with
    // each other produces a 1. If the switch was low and is now
    // high, 0 and 1 xORed with each other produces a 1. Otherwise,
    // it is 0
    changed = debouncedState ^ lastDebouncedState;
}

uint8_t Debouncer::
ButtonPressed(uint8_t GPIOButtonPins)
{
    // If the button changed and it changed to a 1, then the
    // user just pressed the button.
    return (changed & debouncedState) & GPIOButtonPins;
}

uint8_t Debouncer:: 
ButtonReleased(uint8_t GPIOButtonPins)
{
    // If the button changed and it changed to a 0, then the
    // user just released the button.
    return (changed & (~debouncedState)) & GPIOButtonPins;
}

uint8_t Debouncer::
ButtonCurrent(uint8_t GPIOButtonPins)
{
    // Current pressed or not pressed states of the buttons expressed
    // as one 8 bit byte. A 0 bit denotes the button is not pressed,
    // and a 1 bit denotes it is being pressed.
    return debouncedState & GPIOButtonPins;
}

