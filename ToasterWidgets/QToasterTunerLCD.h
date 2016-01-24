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
#ifndef QTOASTERTUNERLCD_H
#define QTOASTERTUNERLCD_H

#include <QWidget>
#include "Commons.h"
#include "QToasterLCD.h"

namespace Ui {
  class QToasterTunerLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterTunerLCD : public QToasterLCD
{
  Q_OBJECT


public:
  explicit QToasterTunerLCD(QWidget *parent = 0);
  ~QToasterTunerLCD();

signals:
  void signalMuted(bool muted);

public slots:
  void setIndexPosition(int position);
  void setNote(const QString& note);
  void setOctave(const QString& octave);
  void setMasterTuneValue(const QString& masterTune);
  void setMuted(bool muted);

protected:
  void createIndexSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

private slots:
  void on_muteCheckBox_clicked(bool checked);

private:
  Ui::QToasterTunerLCD *ui;

  QList<QPixmap> mIndexPixmaps;
};

#endif // QTOASTERTUNERLCD_H
