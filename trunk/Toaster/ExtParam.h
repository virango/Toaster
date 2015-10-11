#ifndef EXTPARAM_H
#define EXTPARAM_H

#include <QObject>
#include "ExtParamMidi.h"

class ExtParam : public QObject, public ExtParamMidi
{
  Q_OBJECT
public:
  explicit ExtParam(QObject *parent = 0);
  ~ExtParam();

  void requestAllValues();

signals:
  void browserViewReceived(unsigned int view);

public slots:
  void applyBrowserView(unsigned int view);

protected:
  // EqMidi
  virtual void midiBrowserViewReceived(unsigned int rawVal);
};

#endif // EXTPARAM_H
