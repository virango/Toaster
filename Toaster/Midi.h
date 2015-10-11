#ifndef MIDICLIENT_H
#define MIDICLIENT_H
#include <vector>
#include <list>
#include <QString>
#include <RtMidi.h>
#include <QStringList>

using namespace std;

typedef vector<unsigned char> ByteArray;


class Midi
{
public:
  class IMidiConsumer
  {
  public:
    virtual void consume(ByteArray* msg) = 0;
    virtual unsigned char getStatusByte() = 0;
  };

private:
  Midi();
  ~Midi();

public:
  static Midi& get();

  bool openPorts(const QString& inPort, const QString& outPort);
  void closePorts();

  void processMidiInput(ByteArray* msg);

  const QStringList getInPorts();
  const QStringList getOutPorts();

  void sendCmd(ByteArray cmd);

  void addConsumer(IMidiConsumer* consumer);
  void removeConsumer(IMidiConsumer* consumer);

private:
  string          mName;
  RtMidiIn        mMidiIn;
  RtMidiOut       mMidiOut;

  QList<QString>  mInPorts;
  QList<QString>  mOutPorts;

  list<IMidiConsumer*> mConsumer;
};

#endif // MIDICLIENT_H
