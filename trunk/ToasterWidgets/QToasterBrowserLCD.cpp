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
#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "QToasterBrowserLCD.h"
#include "ui_QToasterBrowserLCD.h"
#include "QToasterLCD.h"
#include "CtxMenuProvider.h"

#define BROWSER_VIEW_STYLESHEETS "QComboBox#browserViewComboBox\
{\
%1; \
background-color: rgb(50,50,50);\
border-color: rgb(0, 0, 0);\
border-radius: 3px;\
padding-left:7px;\
padding-bottom: 2px;\
}\
QComboBox::drop-down {width: 0px; border-style: none}"



QToasterBrowserLCD::QToasterBrowserLCD(QWidget *parent)
  : QToasterLCD(parent)
  , ui(new Ui::QToasterBrowserLCD)
{
  ui->setupUi(this);
  createSkin();
  ui->stompAEdit->setText("-");
  ui->stompBEdit->setText("-");
  ui->stompCEdit->setText("-");
  ui->stompDEdit->setText("-");
  ui->stompXEdit->setText("-");
  ui->stompModEdit->setText("-");
  ui->reverbEdit->setText("REV");
  ui->delayEdit->setText("DLY");
  ui->rigNameEdit->setText("-");
  ui->rigAuthorEdit->setText("-");
  ui->rigTypeEdit->setText("Guitar Rig");
  ui->ampNameEdit->setText("-");

  ui->stompAEdit->setStyleSheet("border-radius: 3px");

  setStompAEnabled(false);
  setStompBEnabled(false);
  setStompCEnabled(false);
  setStompDEnabled(false);
  setStompXEnabled(false);
  setStompModEnabled(false);
  setDelayEnabled(false);
  setReverbEnabled(false);

  setColor(mColor);
}

QToasterBrowserLCD::~QToasterBrowserLCD()
{
  delete ui;
}

void QToasterBrowserLCD::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = sSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
}

void QToasterBrowserLCD::contextMenuEvent(QContextMenuEvent * cme)
{
  if(mpCtxMenuProvider)
  {
    QMenu ctxMenu;
    QPoint globalPos = mapToGlobal(cme->pos());
    mpCtxMenuProvider->createMenu(ctxMenu);
    if(!ctxMenu.isEmpty())
      ctxMenu.exec(globalPos);
  }
}

void QToasterBrowserLCD::setColor(QToasterLCD::Color color)
{
  mColor = color;
  QString colorStyleSheet = sColor2StyleSheetsMap[color];
  ui->browserViewComboBox->setStyleSheet(QString(BROWSER_VIEW_STYLESHEETS).arg(colorStyleSheet));
  /*
  ui->stompAEdit->setStyleSheet(colorStyleSheet);
  ui->stompBEdit->setStyleSheet(colorStyleSheet);
  ui->stompCEdit->setStyleSheet(colorStyleSheet);
  ui->stompDEdit->setStyleSheet(colorStyleSheet);
  ui->stompXEdit->setStyleSheet(colorStyleSheet);
  ui->stompModEdit->setStyleSheet(colorStyleSheet);
  ui->delayEdit->setStyleSheet(colorStyleSheet);
  ui->reverbEdit->setStyleSheet(colorStyleSheet);
  */
  ui->rigAuthorEdit->setStyleSheet(colorStyleSheet);
  ui->rigTypeEdit->setStyleSheet(colorStyleSheet);
  update();
}

void QToasterBrowserLCD::setBrowserModeBassValueText(const QString& value)
{
  ui->bassValueLabel->setText(value);
}

void QToasterBrowserLCD::setBrowserModeMiddleValueText(const QString& value)
{
  ui->middleValueLabel->setText(value);
}

void QToasterBrowserLCD::setBrowserModeTrebleValueText(const QString& value)
{
  ui->trebleValueLabel->setText(value);
}

void QToasterBrowserLCD::setBrowserModePresenceValueText(const QString& value)
{
  ui->presenceValueLabel->setText(value);
}

void QToasterBrowserLCD::setBrowserModeRigName(const QString& value)
{
  ui->rigNameEdit->setText(value);
  ui->rigNameEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setBrowserModeRigAuthor(const QString& value)
{
  ui->rigAuthorEdit->setText(value);
  ui->rigAuthorEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setBrowserModeAmpName(const QString& value)
{
  ui->ampNameEdit->setText(value);
  ui->ampNameEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setBrowserModeView(int view)
{
  ui->browserViewComboBox->setCurrentIndex(view);
}

void QToasterBrowserLCD::setStompFXType(StompInstance stompInstance, FXType fxType)
{
  switch(stompInstance)
  {
  case StompA:
    setStompAFXType(fxType);
    break;
  case StompB:
    setStompBFXType(fxType);
    break;
  case StompC:
    setStompCFXType(fxType);
    break;
  case StompD:
    setStompDFXType(fxType);
    break;
  case StompX:
    setStompXFXType(fxType);
    break;
  case StompMOD:
    setStompModFXType(fxType);
    break;
  }
}

void QToasterBrowserLCD::setStompAFXType(FXType fxType)
{
  ui->stompAEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompAEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompBFXType(FXType fxType)
{
  ui->stompBEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompBEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompCFXType(FXType fxType)
{
  ui->stompCEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompCEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompDFXType(FXType fxType)
{
  ui->stompDEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompDEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompXFXType(FXType fxType)
{
  ui->stompXEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompXEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompModFXType(FXType fxType)
{
  ui->stompModEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompModEdit->setCursorPosition(0);
}

void QToasterBrowserLCD::setStompEnabled(StompInstance stompInstance, bool enabled)
{
  switch(stompInstance)
  {
  case StompA:
    setStompAEnabled(enabled);
    break;
  case StompB:
    setStompBEnabled(enabled);
    break;
  case StompC:
    setStompCEnabled(enabled);
    break;
  case StompD:
    setStompDEnabled(enabled);
    break;
  case StompX:
    setStompXEnabled(enabled);
    break;
  case StompMOD:
    setStompModEnabled(enabled);
    break;
  }
}

void QToasterBrowserLCD::setStompAEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompAEdit, enabled);
}

void QToasterBrowserLCD::setStompBEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompBEdit, enabled);
}

void QToasterBrowserLCD::setStompCEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompCEdit, enabled);
}

void QToasterBrowserLCD::setStompDEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompDEdit, enabled);
}

void QToasterBrowserLCD::setStompXEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompXEdit, enabled);
}

void QToasterBrowserLCD::setStompModEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompModEdit, enabled);
}

void QToasterBrowserLCD::setDelayEnabled(bool enabled)
{
  displayStompEnabled(*ui->delayEdit, enabled);
}

void QToasterBrowserLCD::setReverbEnabled(bool enabled)
{
  displayStompEnabled(*ui->reverbEdit, enabled);
}

void QToasterBrowserLCD::on_browserViewComboBox_currentIndexChanged(int index)
{
  emit browserModeViewChanged(index);
}

QStringList QToasterBrowserLCD::getBrowserModeViews()
{
  QStringList list;
  for(int i = 0; i < ui->browserViewComboBox->count(); i++)
    list.append(ui->browserViewComboBox->itemText(i));
  return list;
}
