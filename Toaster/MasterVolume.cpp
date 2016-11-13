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
#include "MasterVolume.h"
#include "Settings.h"
#include "Global.h"

MasterVolume MasterVolume::mThis;

MasterVolume::MasterVolume(QObject *parent)
  : QObject(parent)
  , mMainOutputLink(Settings::get().getMainOutputLink())
  , mMonitorOutputLink(Settings::get().getMonitorOutputLink())
  , mDirectOutputLink(Settings::get().getDirectOutputLink())
  , mHeadphoneOutputLink(Settings::get().getHeadphoneOutputLink())
  , mSPDIFOutputLink(Settings::get().getSPDIFOutputLink())
  , mMainOutputVolume(0)
  , mMonitorOutputVolume(0)
  , mDirectOutputVolume(0)
  , mHeadphoneOutputVolume(0)
  , mSPDIFOutputVolume(0)
  , mMasterVolume(Settings::get().getMasterVolume())
{  
}

MasterVolume::~MasterVolume()
{ 
}

void MasterVolume::init()
{
  connect(&globalObj, &Global::mainOutputVolumeReceived, this, &MasterVolume::onMainOutputVolume);
  connect(&globalObj, &Global::monitorOutputVolumeReceived, this, &MasterVolume::onMonitorOutputVolume);
  connect(&globalObj, &Global::directOutputVolumeReceived, this, &MasterVolume::onDirectOutputVolume);
  connect(&globalObj, &Global::headphoneOutputVolumeReceived, this, &MasterVolume::onHeadPhoneOutputVolume);
  connect(&globalObj, &Global::spdifOutputVolumeReceived, this, &MasterVolume::onSPDIFOutputVolume);
  emit masterVolumeChanged(mMasterVolume);
}

void MasterVolume::dispose()
{
  Settings::get().setMasterVolume(mMasterVolume);

  disconnect(&globalObj, &Global::mainOutputVolumeReceived, this, &MasterVolume::onMainOutputVolume);
  disconnect(&globalObj, &Global::monitorOutputVolumeReceived, this, &MasterVolume::onMonitorOutputVolume);
  disconnect(&globalObj, &Global::directOutputVolumeReceived, this, &MasterVolume::onDirectOutputVolume);
  disconnect(&globalObj, &Global::headphoneOutputVolumeReceived, this, &MasterVolume::onHeadPhoneOutputVolume);
  disconnect(&globalObj, &Global::spdifOutputVolumeReceived, this, &MasterVolume::onSPDIFOutputVolume);
}

int MasterVolume::noOfLinks()
{
  int noOfLinks = 0;
  if(mMainOutputLink)
    noOfLinks++;
  if(mMonitorOutputLink)
    noOfLinks++;
  if(mDirectOutputLink)
    noOfLinks++;
  if(mHeadphoneOutputLink)
    noOfLinks++;
  if(mSPDIFOutputLink)
    noOfLinks++;
  return noOfLinks;
}

void MasterVolume::requestValues()
{
  if(mMainOutputLink)
    globalObj.requestMainOutputVolume();

  if(mMonitorOutputLink)
    globalObj.requestMonitorOutputVolume();

  if(mDirectOutputLink)
    globalObj.requestDirectOutputVolume();

  if(mHeadphoneOutputLink)
    globalObj.requestHeadphoneOutputVolume();

  if(mSPDIFOutputLink)
    globalObj.requestSPDIFOutputVlume();

  emit linksChanged(noOfLinks());
  emit masterVolumeChanged(mMasterVolume);
}

void MasterVolume::onMainOutputLink(bool link)
{
  mMainOutputLink = link;
  Settings::get().setMainOutputLink(link);
  if(mMainOutputLink)
    globalObj.requestMainOutputVolume();

  emit linksChanged(noOfLinks());
}

void MasterVolume::onMonitorOutputLink(bool link)
{
  mMonitorOutputLink = link;
  Settings::get().setMonitorOutputLink(link);
  if(mMonitorOutputLink)
    globalObj.requestMonitorOutputVolume();

  emit linksChanged(noOfLinks());
}

void MasterVolume::onDirectOutputLink(bool link)
{
  mDirectOutputLink = link;
  Settings::get().setDirectOutputLink(link);
  if(mDirectOutputLink)
    globalObj.requestDirectOutputVolume();

  emit linksChanged(noOfLinks());
}

void MasterVolume::onHeadPhoneOutputLink(bool link)
{
  mHeadphoneOutputLink = link;
  Settings::get().setHeadphoneOutputLink(link);
  if(mHeadphoneOutputLink)
    globalObj.requestHeadphoneOutputVolume();

  emit linksChanged(noOfLinks());
}

void MasterVolume::onSPDIFOutputLink(bool link)
{
  mSPDIFOutputLink = link;
  Settings::get().setSPDIFOutputLink(link);
  if(mSPDIFOutputLink)
    globalObj.requestSPDIFOutputVlume();

  emit linksChanged(noOfLinks());
}

void MasterVolume::onMainOutputVolume(int value)
{
  mMainOutputVolume = value;
  if(mMainOutputLink && (mMainOutputVolume == 0x3FFF))
  {
    mMasterVolume = 0x3FFF;
    emit masterVolumeChanged(mMasterVolume);
  }
}

void MasterVolume::onMonitorOutputVolume(int value)
{
  mMonitorOutputVolume = value;
  if(mMonitorOutputLink && (mMonitorOutputVolume == 0x3FFF))
  {
    mMasterVolume = 0x3FFF;
    emit masterVolumeChanged(mMasterVolume);
  }
}

void MasterVolume::onDirectOutputVolume(int value)
{
  mDirectOutputVolume = value;
  if(mDirectOutputLink && (mDirectOutputVolume == 0x3FFF))
  {
    mMasterVolume = 0x3FFF;
    emit masterVolumeChanged(mMasterVolume);
  }
}

void MasterVolume::onHeadPhoneOutputVolume(int value)
{
  mHeadphoneOutputVolume = value;
  if(mHeadphoneOutputLink && (mHeadphoneOutputVolume == 0x3FFF))
  {
    mMasterVolume = 0x3FFF;
    emit masterVolumeChanged(mMasterVolume);
  }
}

void MasterVolume::onSPDIFOutputVolume(int value)
{
  mSPDIFOutputVolume = value;
  if(mSPDIFOutputLink && (mSPDIFOutputVolume == 0x3FFF))
  {
    mMasterVolume = 0x3FFF;
    emit masterVolumeChanged(mMasterVolume);
  }
}

void MasterVolume::onMasterVolume(int value)
{
  int delta = value - mMasterVolume;
  mMasterVolume = value;

  if(mMainOutputLink)
  {
    mMainOutputVolume = mMainOutputVolume + delta > 0x3FFF ? 0x3FFF : mMainOutputVolume + delta;
    globalObj.applyMainOutputVolume(mMainOutputVolume > 0 ? mMainOutputVolume : 0);
    if(mMainOutputVolume == 0x3FFF)
      mMasterVolume = 0x3FFF;

    emit mainOutputVolumeChanged(mMainOutputVolume > 0 ? mMainOutputVolume : 0);
  }

  if(mMonitorOutputLink)
  {
    mMonitorOutputVolume = mMonitorOutputVolume + delta > 0x3FFF ? 0x3FFF : mMonitorOutputVolume + delta;
    globalObj.applyMonitorOutputVolume(mMonitorOutputVolume > 0 ? mMonitorOutputVolume : 0);
    if(mMonitorOutputVolume == 0x3FFF)
      mMasterVolume = 0x3FFF;

    emit monitorOutputVolumeChanged(mMonitorOutputVolume > 0 ? mMonitorOutputVolume : 0);
  }

  if(mDirectOutputLink)
  {
    mDirectOutputVolume = mDirectOutputVolume + delta > 0x3FFF ? 0x3FFF : mDirectOutputVolume + delta;
    globalObj.applyDirectOutputVolume(mDirectOutputVolume > 0 ? mDirectOutputVolume : 0);
    if(mDirectOutputVolume == 0x3FFF)
      mMasterVolume = 0x3FFF;

    emit directOutputVolumeChanged(mDirectOutputVolume > 0 ? mDirectOutputVolume : 0);
  }

  if(mHeadphoneOutputLink)
  {
    mHeadphoneOutputVolume = mHeadphoneOutputVolume + delta > 0x3FFF ? 0x3FFF : mHeadphoneOutputVolume + delta;
    globalObj.applyHeadphoneOutputVolume(mHeadphoneOutputVolume > 0 ? mHeadphoneOutputVolume : 0);
    if(mHeadphoneOutputVolume == 0x3FFF)
      mMasterVolume = 0x3FFF;

    emit headphoneOutputVolumeChanged(mHeadphoneOutputVolume > 0 ? mHeadphoneOutputVolume : 0);
  }

  if(mSPDIFOutputLink)
  {
    mSPDIFOutputVolume = mSPDIFOutputVolume + delta > 0x3FFF ? 0x3FFF : mSPDIFOutputVolume + delta;
    globalObj.applySPDIFOutputVolume(mSPDIFOutputVolume > 0 ? mSPDIFOutputVolume : 0);
    if(mSPDIFOutputVolume  == 0x3FFF)
      mMasterVolume = 0x3FFF;

    emit spdifOutputVolumeChanged(mSPDIFOutputVolume > 0 ? mSPDIFOutputVolume : 0);
  }

  if(mMasterVolume == 0x3FFF)
    emit masterVolumeChanged(mMasterVolume);
}
