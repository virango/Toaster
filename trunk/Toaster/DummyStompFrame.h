#ifndef DUMMYSTOMPFRAME_H
#define DUMMYSTOMPFRAME_H

#include <QWidget>
#include "StompEditorPage.h"

namespace Ui {
class DummyStompFrame;
}

class Stomp;

class DummyStompFrame : public QWidget, public IStompEditorPage
{
  Q_OBJECT

public:
  explicit DummyStompFrame(QWidget *parent = 0);
  ~DummyStompFrame();

  // IStompEditorPage
  virtual void activate(Stomp& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual void setStompType(StompInstance stompInstance, FXType fxType);
  virtual void setStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void setAmpName(const QString&  ampName);

private:
  Ui::DummyStompFrame *ui;

  Stomp* mpStomp;
};

#endif // DUMMYSTOMPFRAME_H
