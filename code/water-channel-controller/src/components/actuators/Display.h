#ifndef __DISPLAY__
#define __DISPLAY__

enum Message
{
  MSG_AUTOMATIC,
  MSG_MANUAL,
  MSG_INIT
};

class Display
{

public:
  void showText(Message message);
  void setup();
  void turnOff();
  void showText(int percentual);
};

#endif
