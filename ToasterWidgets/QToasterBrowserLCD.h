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
#ifndef QTOASTERBROWSERLCD_H
#define QTOASTERBROWSERLCD_H
#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"
#include "QToasterLCD.h"

namespace Ui {
  class QToasterBrowserLCD;
}

class TOASTERWIDGETS_EXPORT QToasterBrowserLCD : public QToasterLCD
{
  Q_OBJECT
public:
  explicit QToasterBrowserLCD(QWidget *parent = 0);
  ~QToasterBrowserLCD();


  QStringList getBrowserModeViews();

signals:
  void browserModeViewChanged(int view);

public slots:
  void setColor(Color color);

  void setStompFXType(StompInstance stompInstance, FXType fxType);
  void setStompAFXType(FXType fxType);
  void setStompBFXType(FXType fxType);
  void setStompCFXType(FXType fxType);
  void setStompDFXType(FXType fxType);
  void setStompXFXType(FXType fxType);
  void setStompModFXType(FXType fxType);
  void setStompDelayFXType(FXType fxType);

  void setStompEnabled(StompInstance stompInstance, bool enabled);
  void setStompAEnabled(bool enabled);
  void setStompBEnabled(bool enabled);
  void setStompCEnabled(bool enabled);
  void setStompDEnabled(bool enabled);
  void setStompXEnabled(bool enabled);
  void setStompModEnabled(bool enabled);
  void setDelayEnabled(bool enabled);
  void setReverbEnabled(bool enabled);

  void setBrowserModeBassValueText(const QString& value);
  void setBrowserModeMiddleValueText(const QString& value);
  void setBrowserModeTrebleValueText(const QString& value);
  void setBrowserModePresenceValueText(const QString& value);

  void setBrowserModeRigName(const QString& value);
  void setBrowserModeRigAuthor(const QString& value);
  void setBrowserModeAmpName(const QString& value);

  void setBrowserModeView(int view);

protected:
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);
  void setFonts();

private slots:
  void on_browserViewComboBox_currentIndexChanged(int index);

private:
  Ui::QToasterBrowserLCD *ui;


};

#endif // QTOASTERBROWSERLCD_H
