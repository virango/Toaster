#ifndef CAB_H
#define CAB_H
#include <QObject>
#include "CabMidi.h"

class Cab : public QObject, public CabMidi
{
  Q_OBJECT
public:
  Cab();
  ~Cab();

  void requestValues();
  
signals:
  void onOffReceived(bool onOff);  
};

#endif // CAB_H
