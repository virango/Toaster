/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
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

bool Midi::openPorts(const QString& inPort, const QString& outPort)
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

  if(mMidiIn.isPortOpen())
  {
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

    if(mMidiOut.isPortOpen())
      return true;

    mMidiIn.closePort();
  }
  return false;
}

void Midi::closePorts()
{
  mMidiIn.closePort();
  mMidiOut.closePort();
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

const QStringList Midi::getInPorts()
{
  mInPorts.clear();

  for(unsigned int i = 0; i < mMidiIn.getPortCount(); ++i)
    mInPorts.append(QString(mMidiIn.getPortName(i).c_str()));

  return mInPorts;
}

const QStringList Midi::getOutPorts()
{
  mOutPorts.clear();

  for(unsigned int i = 0; i < mMidiOut.getPortCount(); ++i)
    mOutPorts.append(QString(mMidiOut.getPortName(i).c_str()));

  return mOutPorts;
}

void Midi::sendCmd(ByteArray cmd)
{
  if(cmd.size() > 0 && mMidiOut.isPortOpen())
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
