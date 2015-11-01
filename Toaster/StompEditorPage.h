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
  virtual void setStompType(StompInstance stompInstance, FXType fxType) = 0;
  virtual void setStompEnabled(StompInstance stompInstance, bool enabled) = 0;
  virtual void setDelayEnabled(bool enabled) = 0;
  virtual void setReverbEnabled(bool enabled) = 0;
  virtual void setAmpName(const QString&  ampName) = 0;
  virtual FXType getFXType() const = 0;
};

#endif // STOMPEDITORPAGE

