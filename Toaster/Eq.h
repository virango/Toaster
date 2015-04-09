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
};

#endif // EQ_H
