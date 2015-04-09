#ifndef MIDICLIENT_H
#define MIDICLIENT_H
#include <vector>
#include <list>
#include <QString>
#include <RtMidi.h>

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

  bool openMidiPorts(const string inPort, const string outPort);

  void processMidiInput(ByteArray* msg);

  const vector<string> getInPorts();
  const vector<string> getOutPorts();

  void sendCmd(ByteArray cmd);

  void addConsumer(IMidiConsumer* consumer);
  void removeConsumer(IMidiConsumer* consumer);

private:
  string          mName;
  RtMidiIn        mMidiIn;
  RtMidiOut       mMidiOut;

  vector<string>  mInPorts;
  vector<string>  mOutPorts;

  list<IMidiConsumer*> mConsumer;
};

#endif // MIDICLIENT_H
