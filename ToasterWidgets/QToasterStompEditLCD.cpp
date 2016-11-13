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
#include "QToasterStompEditLCD.h"
#include "ui_QToasterStompEditLCD.h"
#include "QToasterLCD.h"
#include "CtxMenuProvider.h"

QToasterStompEditLCD::QToasterStompEditLCD(QWidget *parent)
  : QToasterLCD(parent)
  , ui(new Ui::QToasterStompEditLCD)
{
  ui->setupUi(this);
  setFonts();
  createSkin();

  ui->stompAEdit->setText("-");
  ui->stompBEdit->setText("-");
  ui->stompCEdit->setText("-");
  ui->stompDEdit->setText("-");
  ui->stompXEdit->setText("-");
  ui->stompModEdit->setText("-");
  ui->reverbEdit->setText("REV");
  ui->delayEdit->setText("DLY");
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
  updatePageInfo();
}

QToasterStompEditLCD::~QToasterStompEditLCD()
{
  if(ui != nullptr)
    delete ui;
}

QString QToasterStompEditLCD::stompInstance() const
{
  return ui->stompInstance->text();
}

QString QToasterStompEditLCD::stompName() const
{
  return ui->stompTypeName->text();
}

QString QToasterStompEditLCD::value1Title() const
{
  return ui->val01Title->text();
}

QString QToasterStompEditLCD::value2Title() const
{
  return ui->val02Title->text();
}

QString QToasterStompEditLCD::value3Title() const
{
  return ui->val03Title->text();
}

QString QToasterStompEditLCD::value4Title() const
{
  return ui->val04Title->text();
}

QString QToasterStompEditLCD::value5Title() const
{
  return ui->val05Title->text();
}

QString QToasterStompEditLCD::value6Title() const
{
  return ui->val06Title->text();
}

QString QToasterStompEditLCD::value7Title() const
{
  return ui->val07Title->text();
}

QString QToasterStompEditLCD::value8Title() const
{
  return ui->val08Title->text();
}

QString QToasterStompEditLCD::value9Title() const
{
  return ui->val09Title->text();
}

QString QToasterStompEditLCD::value10Title() const
{
  return ui->val10Title->text();
}

QString QToasterStompEditLCD::value11Title() const
{
  return ui->val11Title->text();
}

QString QToasterStompEditLCD::value12Title() const
{
  return ui->val12Title->text();
}

QString QToasterStompEditLCD::value13Title() const
{
  return ui->val13Title->text();
}

QString QToasterStompEditLCD::value14Title() const
{
  return ui->val14Title->text();
}

QString QToasterStompEditLCD::value15Title() const
{
  return ui->val15Title->text();
}

QString QToasterStompEditLCD::value16Title() const
{
  return ui->val16Title->text();
}

QString QToasterStompEditLCD::value17Title() const
{
  return ui->val17Title->text();
}

QString QToasterStompEditLCD::value18Title() const
{
  return ui->val18Title->text();
}

QString QToasterStompEditLCD::value19Title() const
{
  return ui->val19Title->text();
}

QString QToasterStompEditLCD::value20Title() const
{
  return ui->val20Title->text();
}

QString QToasterStompEditLCD::value21Title() const
{
  return ui->val21Title->text();
}

QString QToasterStompEditLCD::value22Title() const
{
  return ui->val22Title->text();
}

QString QToasterStompEditLCD::value23Title() const
{
  return ui->val23Title->text();
}

QString QToasterStompEditLCD::value24Title() const
{
  return ui->val24Title->text();
}

QString QToasterStompEditLCD::value25Title() const
{
  return ui->val25Title->text();
}

QString QToasterStompEditLCD::value26Title() const
{
  return ui->val26Title->text();
}

QString QToasterStompEditLCD::value27Title() const
{
  return ui->val27Title->text();
}

QString QToasterStompEditLCD::value28Title() const
{
  return ui->val28Title->text();
}

QString QToasterStompEditLCD::value29Title() const
{
  return ui->val29Title->text();
}

QString QToasterStompEditLCD::value30Title() const
{
  return ui->val30Title->text();
}

QString QToasterStompEditLCD::value31Title() const
{
  return ui->val31Title->text();
}

QString QToasterStompEditLCD::value32Title() const
{
  return ui->val32Title->text();
}

QString QToasterStompEditLCD::value33Title() const
{
  return ui->val33Title->text();
}

QString QToasterStompEditLCD::value34Title() const
{
  return ui->val34Title->text();
}

QString QToasterStompEditLCD::value35Title() const
{
  return ui->val35Title->text();
}

QString QToasterStompEditLCD::value36Title() const
{
  return ui->val36Title->text();
}

QString QToasterStompEditLCD::value37Title() const
{
  return ui->val37Title->text();
}

QString QToasterStompEditLCD::value38Title() const
{
  return ui->val38Title->text();
}

QString QToasterStompEditLCD::value39Title() const
{
  return ui->val39Title->text();
}

QString QToasterStompEditLCD::value40Title() const
{
  return ui->val40Title->text();
}

QString QToasterStompEditLCD::value41Title() const
{
  return ui->val41Title->text();
}

QString QToasterStompEditLCD::value42Title() const
{
  return ui->val42Title->text();
}

QString QToasterStompEditLCD::value43Title() const
{
  return ui->val43Title->text();
}

QString QToasterStompEditLCD::value44Title() const
{
  return ui->val44Title->text();
}

QString QToasterStompEditLCD::value45Title() const
{
  return ui->val45Title->text();
}

QString QToasterStompEditLCD::value46Title() const
{
  return ui->val46Title->text();
}

QString QToasterStompEditLCD::value47Title() const
{
  return ui->val47Title->text();
}

QString QToasterStompEditLCD::value48Title() const
{
  return ui->val48Title->text();
}

double QToasterStompEditLCD::eqBand1Value() const
{
  return getEqBandValue(ui->eqBand1Widget);
}

double QToasterStompEditLCD::eqBand2Value() const
{
  return getEqBandValue(ui->eqBand2Widget);
}

double QToasterStompEditLCD::eqBand3Value() const
{
  return getEqBandValue(ui->eqBand3Widget);
}

double QToasterStompEditLCD::eqBand4Value() const
{
  return getEqBandValue(ui->eqBand4Widget);
}

double QToasterStompEditLCD::eqBand5Value() const
{
  return getEqBandValue(ui->eqBand5Widget);
}

double QToasterStompEditLCD::eqBand6Value() const
{
  return getEqBandValue(ui->eqBand6Widget);
}

double QToasterStompEditLCD::eqBand7Value() const
{
  return getEqBandValue(ui->eqBand7Widget);
}

double QToasterStompEditLCD::eqBand8Value() const
{
  return getEqBandValue(ui->eqBand8Widget);
}

QToasterStompEditLCD::ScaleView QToasterStompEditLCD::scaleView() const
{
  return (ScaleView) ui->scaleWidget->currentIndex();
}

bool QToasterStompEditLCD::stompsAndAmpHidden() const
{
  return ui->stompsAndAmpWidget->isHidden();
}

void QToasterStompEditLCD::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = sSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
}

void QToasterStompEditLCD::contextMenuEvent(QContextMenuEvent * cme)
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

void QToasterStompEditLCD::setColor(Color color)
{
  QToasterLCD::setColor(color);
  QString colorStyleSheet = sColor2StyleSheetsMap[color];
  ui->pageInfo->setStyleSheet(colorStyleSheet);
  ui->stompInstance->setStyleSheet(colorStyleSheet);
  ui->stompTypeName->setStyleSheet(colorStyleSheet);
  update();
}

void QToasterStompEditLCD::setCurrentPage(Page page)
{
  QToasterLCD::setCurrentPage(page);
  ui->valWidget1->setCurrentIndex((int)mCurrentPage);
  ui->valWidget2->setCurrentIndex((int)mCurrentPage);
  updatePageInfo();
}

void QToasterStompEditLCD::setMaxPage(Page page)
{
  QToasterLCD::setMaxPage(page);
  updatePageInfo();
}


void QToasterStompEditLCD::setStompInstance(QString stompInstance)
{
  ui->stompInstance->setText(stompInstance);
}

void QToasterStompEditLCD::setStompName(QString stompName)
{
  ui->stompTypeName->setText(stompName);
}

void QToasterStompEditLCD::setValue1Title(QString title)
{
  ui->val01Title->setText(title);
  if(title.isEmpty())
    ui->val01->setText("");
}

void QToasterStompEditLCD::setValue2Title(QString title)
{
  ui->val02Title->setText(title);
  if(title.isEmpty())
    ui->val02->setText("");
}

void QToasterStompEditLCD::setValue3Title(QString title)
{
  ui->val03Title->setText(title);
  if(title.isEmpty())
    ui->val03->setText("");
}

void QToasterStompEditLCD::setValue4Title(QString title)
{
  ui->val04Title->setText(title);
  if(title.isEmpty())
    ui->val04->setText("");
}

void QToasterStompEditLCD::setValue5Title(QString title)
{
  ui->val05Title->setText(title);
  if(title.isEmpty())
    ui->val05->setText("");
}

void QToasterStompEditLCD::setValue6Title(QString title)
{
  ui->val06Title->setText(title);
  if(title.isEmpty())
    ui->val06->setText("");
}

void QToasterStompEditLCD::setValue7Title(QString title)
{
  ui->val07Title->setText(title);
  if(title.isEmpty())
    ui->val07->setText("");
}

void QToasterStompEditLCD::setValue8Title(QString title)
{
  ui->val08Title->setText(title);
  if(title.isEmpty())
    ui->val08->setText("");
}

void QToasterStompEditLCD::setValue9Title(QString title)
{
  ui->val09Title->setText(title);
  if(title.isEmpty())
    ui->val09->setText("");
}

void QToasterStompEditLCD::setValue10Title(QString title)
{
  ui->val10Title->setText(title);
  if(title.isEmpty())
    ui->val10->setText("");
}

void QToasterStompEditLCD::setValue11Title(QString title)
{
  ui->val11Title->setText(title);
  if(title.isEmpty())
    ui->val11->setText("");
}

void QToasterStompEditLCD::setValue12Title(QString title)
{
  ui->val12Title->setText(title);
  if(title.isEmpty())
    ui->val12->setText("");
}

void QToasterStompEditLCD::setValue13Title(QString title)
{
  ui->val13Title->setText(title);
  if(title.isEmpty())
    ui->val13->setText("");
}

void QToasterStompEditLCD::setValue14Title(QString title)
{
  ui->val14Title->setText(title);
  if(title.isEmpty())
    ui->val14->setText("");
}

void QToasterStompEditLCD::setValue15Title(QString title)
{
  ui->val15Title->setText(title);
  if(title.isEmpty())
    ui->val15->setText("");
}

void QToasterStompEditLCD::setValue16Title(QString title)
{
  ui->val16Title->setText(title);
  if(title.isEmpty())
    ui->val16->setText("");
}

void QToasterStompEditLCD::setValue17Title(QString title)
{
  ui->val17Title->setText(title);
  if(title.isEmpty())
    ui->val17->setText("");
}

void QToasterStompEditLCD::setValue18Title(QString title)
{
  ui->val18Title->setText(title);
  if(title.isEmpty())
    ui->val18->setText("");
}

void QToasterStompEditLCD::setValue19Title(QString title)
{
  ui->val19Title->setText(title);
  if(title.isEmpty())
    ui->val19->setText("");
}

void QToasterStompEditLCD::setValue20Title(QString title)
{
  ui->val20Title->setText(title);
  if(title.isEmpty())
    ui->val20->setText("");
}

void QToasterStompEditLCD::setValue21Title(QString title)
{
  ui->val21Title->setText(title);
  if(title.isEmpty())
    ui->val21->setText("");
}

void QToasterStompEditLCD::setValue22Title(QString title)
{
  ui->val22Title->setText(title);
  if(title.isEmpty())
    ui->val22->setText("");
}

void QToasterStompEditLCD::setValue23Title(QString title)
{
  ui->val23Title->setText(title);
  if(title.isEmpty())
    ui->val23->setText("");
}

void QToasterStompEditLCD::setValue24Title(QString title)
{
  ui->val24Title->setText(title);
  if(title.isEmpty())
    ui->val24->setText("");
}

void QToasterStompEditLCD::setValue25Title(QString title)
{
  ui->val25Title->setText(title);
  if(title.isEmpty())
    ui->val25->setText("");
}

void QToasterStompEditLCD::setValue26Title(QString title)
{
  ui->val26Title->setText(title);
  if(title.isEmpty())
    ui->val26->setText("");
}

void QToasterStompEditLCD::setValue27Title(QString title)
{
  ui->val27Title->setText(title);
  if(title.isEmpty())
    ui->val27->setText("");
}

void QToasterStompEditLCD::setValue28Title(QString title)
{
  ui->val28Title->setText(title);
  if(title.isEmpty())
    ui->val28->setText("");
}

void QToasterStompEditLCD::setValue29Title(QString title)
{
  ui->val29Title->setText(title);
  if(title.isEmpty())
    ui->val29->setText("");
}

void QToasterStompEditLCD::setValue30Title(QString title)
{
  ui->val30Title->setText(title);
  if(title.isEmpty())
    ui->val30->setText("");
}

void QToasterStompEditLCD::setValue31Title(QString title)
{
  ui->val31Title->setText(title);
  if(title.isEmpty())
    ui->val31->setText("");
}

void QToasterStompEditLCD::setValue32Title(QString title)
{
  ui->val32Title->setText(title);
  if(title.isEmpty())
    ui->val32->setText("");
}

void QToasterStompEditLCD::setValue33Title(QString title)
{
  ui->val33Title->setText(title);
  if(title.isEmpty())
    ui->val33->setText("");
}

void QToasterStompEditLCD::setValue34Title(QString title)
{
  ui->val34Title->setText(title);
  if(title.isEmpty())
    ui->val34->setText("");
}

void QToasterStompEditLCD::setValue35Title(QString title)
{
  ui->val35Title->setText(title);
  if(title.isEmpty())
    ui->val35->setText("");
}

void QToasterStompEditLCD::setValue36Title(QString title)
{
  ui->val36Title->setText(title);
  if(title.isEmpty())
    ui->val36->setText("");
}

void QToasterStompEditLCD::setValue37Title(QString title)
{
  ui->val37Title->setText(title);
  if(title.isEmpty())
    ui->val37->setText("");
}

void QToasterStompEditLCD::setValue38Title(QString title)
{
  ui->val38Title->setText(title);
  if(title.isEmpty())
    ui->val38->setText("");
}

void QToasterStompEditLCD::setValue39Title(QString title)
{
  ui->val39Title->setText(title);
  if(title.isEmpty())
    ui->val39->setText("");
}

void QToasterStompEditLCD::setValue40Title(QString title)
{
  ui->val40Title->setText(title);
  if(title.isEmpty())
    ui->val40->setText("");
}

void QToasterStompEditLCD::setValue41Title(QString title)
{
  ui->val41Title->setText(title);
  if(title.isEmpty())
    ui->val41->setText("");
}

void QToasterStompEditLCD::setValue42Title(QString title)
{
  ui->val42Title->setText(title);
  if(title.isEmpty())
    ui->val42->setText("");
}

void QToasterStompEditLCD::setValue43Title(QString title)
{
  ui->val43Title->setText(title);
  if(title.isEmpty())
    ui->val43->setText("");
}

void QToasterStompEditLCD::setValue44Title(QString title)
{
  ui->val44Title->setText(title);
  if(title.isEmpty())
    ui->val44->setText("");
}

void QToasterStompEditLCD::setValue45Title(QString title)
{
  ui->val45Title->setText(title);
  if(title.isEmpty())
    ui->val45->setText("");
}

void QToasterStompEditLCD::setValue46Title(QString title)
{
  ui->val46Title->setText(title);
  if(title.isEmpty())
    ui->val46->setText("");
}

void QToasterStompEditLCD::setValue47Title(QString title)
{
  ui->val47Title->setText(title);
  if(title.isEmpty())
    ui->val47->setText("");
}

void QToasterStompEditLCD::setValue48Title(QString title)
{
  ui->val48Title->setText(title);
  if(title.isEmpty())
    ui->val48->setText("");
}


void QToasterStompEditLCD::setValue1(QString value)
{
  ui->val01->setText(value);
}

void QToasterStompEditLCD::setValue2(QString value)
{
  ui->val02->setText(value);
}

void QToasterStompEditLCD::setValue3(QString value)
{
  ui->val03->setText(value);
}

void QToasterStompEditLCD::setValue4(QString value)
{
  ui->val04->setText(value);
}

void QToasterStompEditLCD::setValue5(QString value)
{
  ui->val05->setText(value);
}

void QToasterStompEditLCD::setValue6(QString value)
{
  ui->val06->setText(value);
}

void QToasterStompEditLCD::setValue7(QString value)
{
  ui->val07->setText(value);
}

void QToasterStompEditLCD::setValue8(QString value)
{
  ui->val08->setText(value);
}

void QToasterStompEditLCD::setValue9(QString value)
{
  ui->val09->setText(value);
}

void QToasterStompEditLCD::setValue10(QString value)
{
  ui->val10->setText(value);
}

void QToasterStompEditLCD::setValue11(QString value)
{
  ui->val11->setText(value);
}

void QToasterStompEditLCD::setValue12(QString value)
{
  ui->val12->setText(value);
}

void QToasterStompEditLCD::setValue13(QString value)
{
  ui->val13->setText(value);
}

void QToasterStompEditLCD::setValue14(QString value)
{
  ui->val14->setText(value);
}

void QToasterStompEditLCD::setValue15(QString value)
{
  ui->val15->setText(value);
}

void QToasterStompEditLCD::setValue16(QString value)
{
  ui->val16->setText(value);
}

void QToasterStompEditLCD::setValue17(QString value)
{
  ui->val17->setText(value);
}

void QToasterStompEditLCD::setValue18(QString value)
{
  ui->val18->setText(value);
}

void QToasterStompEditLCD::setValue19(QString value)
{
  ui->val19->setText(value);
}

void QToasterStompEditLCD::setValue20(QString value)
{
  ui->val20->setText(value);
}

void QToasterStompEditLCD::setValue21(QString value)
{
  ui->val21->setText(value);
}

void QToasterStompEditLCD::setValue22(QString value)
{
  ui->val22->setText(value);
}

void QToasterStompEditLCD::setValue23(QString value)
{
  ui->val23->setText(value);
}

void QToasterStompEditLCD::setValue24(QString value)
{
  ui->val24->setText(value);
}

void QToasterStompEditLCD::setValue25(QString value)
{
  ui->val25->setText(value);
}

void QToasterStompEditLCD::setValue26(QString value)
{
  ui->val26->setText(value);
}

void QToasterStompEditLCD::setValue27(QString value)
{
  ui->val27->setText(value);
}

void QToasterStompEditLCD::setValue28(QString value)
{
  ui->val28->setText(value);
}

void QToasterStompEditLCD::setValue29(QString value)
{
  ui->val29->setText(value);
}

void QToasterStompEditLCD::setValue30(QString value)
{
  ui->val30->setText(value);
}

void QToasterStompEditLCD::setValue31(QString value)
{
  ui->val31->setText(value);
}

void QToasterStompEditLCD::setValue32(QString value)
{
  ui->val32->setText(value);
}

void QToasterStompEditLCD::setValue33(QString value)
{
  ui->val33->setText(value);
}

void QToasterStompEditLCD::setValue34(QString value)
{
  ui->val34->setText(value);
}

void QToasterStompEditLCD::setValue35(QString value)
{
  ui->val35->setText(value);
}

void QToasterStompEditLCD::setValue36(QString value)
{
  ui->val36->setText(value);
}

void QToasterStompEditLCD::setValue37(QString value)
{
  ui->val37->setText(value);
}

void QToasterStompEditLCD::setValue38(QString value)
{
  ui->val38->setText(value);
}

void QToasterStompEditLCD::setValue39(QString value)
{
  ui->val39->setText(value);
}

void QToasterStompEditLCD::setValue40(QString value)
{
  ui->val40->setText(value);
}

void QToasterStompEditLCD::setValue41(QString value)
{
  ui->val41->setText(value);
}

void QToasterStompEditLCD::setValue42(QString value)
{
  ui->val42->setText(value);
}

void QToasterStompEditLCD::setValue43(QString value)
{
  ui->val43->setText(value);
}

void QToasterStompEditLCD::setValue44(QString value)
{
  ui->val44->setText(value);
}

void QToasterStompEditLCD::setValue45(QString value)
{
  ui->val45->setText(value);
}

void QToasterStompEditLCD::setValue46(QString value)
{
  ui->val46->setText(value);
}

void QToasterStompEditLCD::setValue47(QString value)
{
  ui->val47->setText(value);
}

void QToasterStompEditLCD::setValue48(QString value)
{
  ui->val48->setText(value);
}


void QToasterStompEditLCD::setEqBand1Value(double value)
{
  setEqBandValue(ui->eqBand1Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand2Value(double value)
{
  setEqBandValue(ui->eqBand2Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand3Value(double value)
{
  setEqBandValue(ui->eqBand3Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand4Value(double value)
{
  setEqBandValue(ui->eqBand4Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand5Value(double value)
{
  setEqBandValue(ui->eqBand5Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand6Value(double value)
{
  setEqBandValue(ui->eqBand6Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand7Value(double value)
{
  setEqBandValue(ui->eqBand7Widget, (int)value);
}

void QToasterStompEditLCD::setEqBand8Value(double value)
{
  setEqBandValue(ui->eqBand8Widget, (int)value);
}

void QToasterStompEditLCD::setScaleView(ScaleView scaleView)
{
  ui->scaleWidget->setCurrentIndex((int)scaleView);
}

void QToasterStompEditLCD::setStompsAndAmpHidden(bool hidden)
{
  if(hidden)
    ui->stompsAndAmpWidget->hide();
  else
    ui->stompsAndAmpWidget->show();
}

void QToasterStompEditLCD::setStompFXType(StompInstance stompInstance, FXType fxType)
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
  case StompMod:
    setStompModFXType(fxType);
    break;
  case StompDelay:
    setStompDelayFXType(fxType);
  }
}

void QToasterStompEditLCD::setStompAFXType(FXType fxType)
{
  ui->stompAEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompAEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompBFXType(FXType fxType)
{
  ui->stompBEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompBEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompCFXType(FXType fxType)
{
  ui->stompCEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompCEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompDFXType(FXType fxType)
{
  ui->stompDEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompDEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompXFXType(FXType fxType)
{
  ui->stompXEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompXEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompModFXType(FXType fxType)
{
  ui->stompModEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->stompModEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompDelayFXType(FXType fxType)
{
  ui->delayEdit->setText(sFXType2ShortNameMap[fxType]);
  ui->delayEdit->setCursorPosition(0);
}

void QToasterStompEditLCD::setStompEnabled(StompInstance stompInstance, bool enabled)
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
  case StompMod:
    setStompModEnabled(enabled);
    break;
  }
}


void QToasterStompEditLCD::setStompAEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompAEdit, enabled);
}

void QToasterStompEditLCD::setStompBEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompBEdit, enabled);
}

void QToasterStompEditLCD::setStompCEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompCEdit, enabled);
}

void QToasterStompEditLCD::setStompDEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompDEdit, enabled);
}

void QToasterStompEditLCD::setStompXEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompXEdit, enabled);
}

void QToasterStompEditLCD::setStompModEnabled(bool enabled)
{
  displayStompEnabled(*ui->stompModEdit, enabled);
}

void QToasterStompEditLCD::setDelayEnabled(bool enabled)
{
  displayStompEnabled(*ui->delayEdit, enabled);
}

void QToasterStompEditLCD::setReverbEnabled(bool enabled)
{
  displayStompEnabled(*ui->reverbEdit, enabled);
}

void QToasterStompEditLCD::setAmpName(const QString &ampName)
{
  ui->ampNameEdit->setText(ampName);
}

void QToasterStompEditLCD::updatePageInfo()
{
  if(mMaxPage != Page1)
  {
    QString text = QString("[Page %1/%2]").arg((int)mCurrentPage+1).arg((int)mMaxPage+1);
    ui->pageInfo->setText(text);
  }
  else
  {
    ui->pageInfo->setText(" ");
  }
}

void QToasterStompEditLCD::setEqBandValue(QWidget* widget, int value)
{
  if(value >= -12 && value <= 12 && widget != nullptr)
  {
    QRect rect = widget->geometry();
    if(value <= 0)
    {
      rect.setY(14);
      rect.setHeight(((-1) * value) + 1);
    }
    else
    {
      rect.setY(14-value);
      rect.setHeight(value + 1);
    }
    widget->setGeometry(rect);
    update();
  }
}

double QToasterStompEditLCD::getEqBandValue(QWidget* widget) const
{
  int val = 0;
  if(widget != nullptr)
  {
    const QRect& rect = widget->geometry();
    val = rect.height() - 1;

    if(rect.y() == 14)
      val *= (-1);
  }
  return (double)val;
}


void QToasterStompEditLCD::setFonts()
{
  QFont font;
  font.setFamily(QStringLiteral("Ubuntu"));
  font.setStretch(95);
  font.setWeight(QFont::Bold);
  font.setPixelSize(13);
  ui->val01Title->setFont(font);
  ui->val02Title->setFont(font);
  ui->val03Title->setFont(font);
  ui->val04Title->setFont(font);
  ui->val05Title->setFont(font);
  ui->val06Title->setFont(font);
  ui->val07Title->setFont(font);
  ui->val08Title->setFont(font);
  ui->val09Title->setFont(font);
  ui->val10Title->setFont(font);
  ui->val11Title->setFont(font);
  ui->val12Title->setFont(font);
  ui->val13Title->setFont(font);
  ui->val14Title->setFont(font);
  ui->val15Title->setFont(font);
  ui->val16Title->setFont(font);
  ui->val17Title->setFont(font);
  ui->val18Title->setFont(font);
  ui->val19Title->setFont(font);
  ui->val20Title->setFont(font);
  ui->val21Title->setFont(font);
  ui->val22Title->setFont(font);
  ui->val23Title->setFont(font);
  ui->val24Title->setFont(font);
  ui->val25Title->setFont(font);
  ui->val26Title->setFont(font);
  ui->val27Title->setFont(font);
  ui->val28Title->setFont(font);
  ui->val29Title->setFont(font);
  ui->val30Title->setFont(font);
  ui->val31Title->setFont(font);
  ui->val32Title->setFont(font);
  ui->val33Title->setFont(font);
  ui->val34Title->setFont(font);
  ui->val35Title->setFont(font);
  ui->val36Title->setFont(font);
  ui->val37Title->setFont(font);
  ui->val38Title->setFont(font);
  ui->val39Title->setFont(font);
  ui->val40Title->setFont(font);
  ui->val41Title->setFont(font);
  ui->val42Title->setFont(font);
  ui->val43Title->setFont(font);
  ui->val44Title->setFont(font);
  ui->val45Title->setFont(font);
  ui->val46Title->setFont(font);
  ui->val47Title->setFont(font);
  ui->val48Title->setFont(font);

  font.setStretch(QFont::Unstretched);
  font.setPixelSize(11);
  ui->stompTypeName->setFont(font);

  font.setPixelSize(10);
  font.setWeight(QFont::Normal);
  ui->val01->setFont(font);
  ui->val02->setFont(font);
  ui->val03->setFont(font);
  ui->val04->setFont(font);
  ui->val05->setFont(font);
  ui->val06->setFont(font);
  ui->val07->setFont(font);
  ui->val08->setFont(font);
  ui->val09->setFont(font);
  ui->val10->setFont(font);
  ui->val11->setFont(font);
  ui->val12->setFont(font);
  ui->val13->setFont(font);
  ui->val14->setFont(font);
  ui->val15->setFont(font);
  ui->val16->setFont(font);
  ui->val17->setFont(font);
  ui->val18->setFont(font);
  ui->val19->setFont(font);
  ui->val20->setFont(font);
  ui->val21->setFont(font);
  ui->val22->setFont(font);
  ui->val23->setFont(font);
  ui->val24->setFont(font);
  ui->val25->setFont(font);
  ui->val26->setFont(font);
  ui->val27->setFont(font);
  ui->val28->setFont(font);
  ui->val29->setFont(font);
  ui->val30->setFont(font);
  ui->val31->setFont(font);
  ui->val32->setFont(font);
  ui->val33->setFont(font);
  ui->val34->setFont(font);
  ui->val35->setFont(font);
  ui->val36->setFont(font);
  ui->val37->setFont(font);
  ui->val38->setFont(font);
  ui->val39->setFont(font);
  ui->val40->setFont(font);
  ui->val41->setFont(font);
  ui->val42->setFont(font);
  ui->val43->setFont(font);
  ui->val44->setFont(font);
  ui->val45->setFont(font);
  ui->val46->setFont(font);
  ui->val47->setFont(font);
  ui->val48->setFont(font);

  ui->ampNameEdit->setFont(font);
  ui->pageInfo->setFont(font);
  ui->stompInstance->setFont(font);

  font.setPixelSize(10);
  font.setWeight(QFont::Light);
  font.setStretch(92);
  ui->stompAEdit->setFont(font);
  ui->stompBEdit->setFont(font);
  ui->stompCEdit->setFont(font);
  ui->stompDEdit->setFont(font);
  ui->stompXEdit->setFont(font);
  ui->stompModEdit->setFont(font);
  ui->delayEdit->setFont(font);
  ui->reverbEdit->setFont(font);


}
