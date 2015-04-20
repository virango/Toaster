#include <jack/jack.h>
#include <jack/midiport.h>
#include <jack/ringbuffer.h>
#include "Midi.h"

void cbProcessMidiInput(double , std::vector<unsigned char> *message, void*)
{
  Midi::get().processMidiInput(message);
}

Midi::Midi()
  : mName("Toaster")
  , mMidiIn(RtMidi::UNSPECIFIED, mName)
  , mMidiOut(RtMidi::UNSPECIFIED, mName)
{
}

Midi::~Midi()
{
  mConsumer.clear();
}

Midi& Midi::get()
{
  static Midi singleton;
  return singleton;
}

bool Midi::openMidiPorts(const string inPort, const string outPort)
{
  int inPortNo = -1;
  int outPortNo = -1;

  getInPorts();
  for(size_t i = 0; i < mInPorts.size(); ++i)
  {
    if(mInPorts[i] == inPort)
    {
      inPortNo = i;
      break;
    }
  }

  if(inPortNo >= 0)
    mMidiIn.openPort(inPortNo, "in");
  else
    mMidiIn.openVirtualPort("in");

  mMidiIn.setCallback(&cbProcessMidiInput);
  mMidiIn.ignoreTypes(false, false, false);

  getOutPorts();
  for(size_t i = 0; i < mOutPorts.size(); ++i)
  {
    if(mOutPorts[i] == outPort)
    {
      outPortNo = i;
      break;
    }
  }

  if(outPortNo >= 0)
    mMidiOut.openPort(outPortNo, "out");
  else
    mMidiOut.openVirtualPort("out");


  return true;
}

void Midi::processMidiInput(ByteArray* msg)
{
  if(msg && msg->size() > 0)
  {
    for(list<IMidiConsumer*>::iterator it = mConsumer.begin(); it != mConsumer.end(); ++it)
    {
      IMidiConsumer* consumer = (*it);
      if((*msg)[0] == consumer->getStatusByte())
        consumer->consume(msg);
    }
  }
}

const vector<string> Midi::getInPorts()
{
  mInPorts.clear();

  for(unsigned int i = 0; i < mMidiIn.getPortCount(); ++i)
    mInPorts.push_back(mMidiIn.getPortName(i));

  return mInPorts;
}

const vector<string> Midi::getOutPorts()
{
  mOutPorts.clear();

  for(unsigned int i = 0; i < mMidiOut.getPortCount(); ++i)
    mOutPorts.push_back(mMidiOut.getPortName(i));

  return mOutPorts;
}

void Midi::sendCmd(ByteArray cmd)
{
  if(cmd.size() > 0)
  {
    if(cmd[0] != 0xB0)
      mMidiOut.sendMessage(&cmd);
    else if(cmd.size()%3 == 0)
    {
      ByteArray::iterator it = cmd.begin();
      for(unsigned int i = 0; i < cmd.size() / 3; ++i)
      {
        ByteArray tmp(it, it + 3);
        mMidiOut.sendMessage(&tmp);
        it += 3;
      }
    }
  }
}

void Midi::addConsumer(IMidiConsumer* consumer)
{
  if(consumer)
    mConsumer.push_back(consumer);
}

void Midi::removeConsumer(IMidiConsumer* consumer)
{
  mConsumer.remove(consumer);
}
