#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
  // Costruttore
  Display();
  
  void set();

  // Metodo per stampare il valore sul display
  void print(int angle, char* state);

};

#endif  // DISPLAY_H 
