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
#ifndef EXTPARAM_H
#define EXTPARAM_H

#include <QObject>
#include "ExtParamMidi.h"

#define extParamObj ExtParam::get()

class ExtParam : public QObject, public ExtParamMidi
{
  Q_OBJECT
public:
  static ExtParam& get();

  void requestAllValues();

signals:
  void browserViewReceived(unsigned int view);

public slots:
  void applyBrowserView(unsigned int view);

protected:
  // EqMidi
  virtual void midiBrowserViewReceived(unsigned int rawVal);

private:
  ExtParam();
  ~ExtParam();
};

#endif // EXTPARAM_H
