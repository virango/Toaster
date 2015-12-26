#ifndef DUMMYSTOMPFRAME_H
#define DUMMYSTOMPFRAME_H
#include <QWidget>
#include "StompEditorPage.h"
#include "Stomp.h"

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
  virtual void activate(QObject& stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual QObject* getStomp()  { return mpStomp; }

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString&  ampName);


private:
  Ui::DummyStompFrame *ui;

  Stomp* mpStomp;

  FXType mFXType;
};

#endif // DUMMYSTOMPFRAME_H
