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
  void masterVolumeChanged(int value);
  void mainOutputVolumeChanged(int value);
  void monitorOutputVolumeChanged(int value);
  void directOutputVolumeChanged(int value);
  void headphoneOutputVolumeChanged(int value);
  void spdifOutputVolumeChanged(int value);
  void linksChanged(int noOfLinks);

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
  void onMasterVolume(int value);

private:
  explicit MasterVolume(QObject *parent = 0);
  ~MasterVolume();

  int noOfLinks();

  static MasterVolume mThis;

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
};

#endif // MASTERVOLUME_H
