#ifndef STOMPEDITORPAGE
#define STOMPEDITORPAGE
#include "Commons.h"

class Stomp;
class QString;

struct IStompEditorPage
{
  virtual void activate(Stomp& stomp) = 0;
  virtual void deactivate() = 0;
  virtual bool isActive() = 0;
  virtual FXType getFXType() const = 0;
  virtual void setFXType(FXType fxType) = 0;

  virtual void displayStompType(StompInstance stompInstance, FXType fxType) = 0;
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled) = 0;
  virtual void displayDelayEnabled(bool enabled) = 0;
  virtual void displayReverbEnabled(bool enabled) = 0;
  virtual void displayAmpName(const QString&  ampName) = 0;

};

#endif // STOMPEDITORPAGE

