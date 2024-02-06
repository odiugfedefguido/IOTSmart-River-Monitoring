#ifndef DISPLAY_H
#define DISPLAY_H

// Class representing a display
class Display {
public:
    // Constructor
    Display();
  
    // Method to set up the display
    void set();

    // Method to print the value on the display
    void print(int angle, char* state);
};

#endif  // DISPLAY_H 
