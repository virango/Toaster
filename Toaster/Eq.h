#ifndef EQ_H
#define EQ_H
#include <QObject>
#include "EqMidi.h"

class Eq : public QObject, public EqMidi
{
  Q_OBJECT
public:
  Eq();
  ~Eq();


  void requestAllValues();

signals:
  void onOffReceived(bool onOff);
  void bassReceived(double bass);
  void middleReceived(double middle);
  void trebleReceived(double treble);
  void presenceReceived(double presence);

public slots:
  void applyOnOff(bool onOff);
  void applyBassReceived(double bass);
  void applyMiddleReceived(double middle);
  void applyTrebleReceived(double treble);
  void applyPresenceReceived(double presence);

protected:
  // EqMidi
  virtual void midiOnOffReceived(unsigned short rawVal);
  virtual void midiBassReceived(unsigned short rawVal);
  virtual void midiMiddleReceived(unsigned short rawVal);
  virtual void midiTrebleReceived(unsigned short rawVal);
  virtual void midiPresenceReceived(unsigned short rawVal);
};

#endif // EQ_H
