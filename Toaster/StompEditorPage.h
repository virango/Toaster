#ifndef STOMPEDITORPAGE
#define STOMPEDITORPAGE
#include "Commons.h"

class Stomp;
class QString;

struct IStompEditorPage
{
  virtual void activate(QObject& stomp) = 0;
  virtual void deactivate() = 0;
  virtual bool isActive() = 0;
  virtual QObject* getStomp() = 0;

  virtual void displayStompType(StompInstance stompInstance, FXType fxType) = 0;
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled) = 0;
  virtual void displayDelayEnabled(bool enabled) = 0;
  virtual void displayReverbEnabled(bool enabled) = 0;
  virtual void displayAmpName(const QString&  ampName) = 0;

};

#endif // STOMPEDITORPAGE

