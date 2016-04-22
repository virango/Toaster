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
#ifndef MASTERVOLUME_H
#define MASTERVOLUME_H

#include <QObject>
#include "Global.h"

class MasterVolume : public QObject
{
  Q_OBJECT
public:
  static MasterVolume& get() { return mThis; }

  bool getMainOutputLink() { return mMainOutputLink; }
  bool getMonitoprOutputLink() { return mMonitorOutputLink; }
  bool getDirectOutputLink() { return mDirectOutputLink; }
  bool getHeadphoneOutputLink() { return mHeadphoneOutputLink; }
  bool getSPDIFOutputLink() { return mSPDIFOutputLink; }

  void init();
  void requestValues();

signals:
  void setMasterVolume(double value);
  void setMainOutputVolume(int value);
  void setMonitorOutputVolume(int value);
  void setDirectOutputVolume(int value);
  void setHeadphoneOutputVolume(int value);
  void setSPDIFOutputVolume(int value);

public slots:
  void onMainOutputLink(bool link);
  void onMonitorOutputLink(bool link);
  void onDirectOutputLink(bool link);
  void onHeadPhoneOutputLink(bool link);
  void onSPDIFOutputLink(bool link);
  void onMainOutputVolume(int value);
  void onMonitorOutputVolume(int value);
  void onDirectOutputVolume(int value);
  void onHeadPhoneOutputVolume(int value);
  void onSPDIFOutputVolume(int value);
  void onMasterVolume(double value);

private:
  explicit MasterVolume(QObject *parent = 0);
  ~MasterVolume();

  static MasterVolume mThis;

  Global mGlobal;

  bool mMainOutputLink;
  bool mMonitorOutputLink;
  bool mDirectOutputLink;
  bool mHeadphoneOutputLink;
  bool mSPDIFOutputLink;

  int mMainOutputVolume;
  int mMonitorOutputVolume;
  int mDirectOutputVolume;
  int mHeadphoneOutputVolume;
  int mSPDIFOutputVolume;

  int mMasterVolume;

  // TODO: put this methods in a separate header
  unsigned short phys2Raw(double physVal, double deltaMinMax, double min, unsigned short maxRawVal = 0x3FFF)
  {
    unsigned short rawVal = ((physVal - min) * maxRawVal) / deltaMinMax;
    return rawVal;
  }

  double raw2Phys(unsigned short rawVal, double deltaMinMax, double min)
  {
    double physVal = ((rawVal * deltaMinMax) / 0x3FFF) + min;
    return physVal;
  }
};

#endif // MASTERVOLUME_H
