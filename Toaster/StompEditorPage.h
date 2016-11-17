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
#ifndef STOMPEDITORPAGE
#define STOMPEDITORPAGE
#include "Commons.h"
#include "QToasterLCD.h"

class Stomp;
class QString;

struct IStompEditorPage
{
  virtual ~IStompEditorPage() {}
  virtual void activate(QObject& stomp) = 0;
  virtual void deactivate() = 0;
  virtual bool isActive() = 0;
  virtual QObject* getStomp() = 0;
  virtual QToasterLCD::Page getMaxDisplayPage() = 0;
  virtual QToasterLCD::Page getCurrentDisplayPage() = 0;
  virtual void setCurrentDisplayPage(QToasterLCD::Page page) = 0;

  virtual void displayStompType(StompInstance stompInstance, FXType fxType) = 0;
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled) = 0;
  virtual void displayDelayEnabled(bool enabled) = 0;
  virtual void displayReverbEnabled(bool enabled) = 0;
  virtual void displayAmpName(const QString&  ampName) = 0;

};

#endif // STOMPEDITORPAGE

