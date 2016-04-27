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
#ifndef QTOASTERSTOMPEDITLCD_H
#define QTOASTERSTOMPEDITLCD_H

#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"
#include "QToasterLCD.h"

namespace Ui {
  class QToasterStompEditLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterStompEditLCD : public QToasterLCD
{
  Q_OBJECT
  Q_ENUMS(ScaleView)
  Q_PROPERTY(QString stompInstance READ stompInstance WRITE setStompInstance)
  Q_PROPERTY(QString stompName READ stompName WRITE setStompName)
  Q_PROPERTY(QString value1Title READ value1Title WRITE setValue1Title)
  Q_PROPERTY(QString value2Title READ value2Title WRITE setValue2Title)
  Q_PROPERTY(QString value3Title READ value3Title WRITE setValue3Title)
  Q_PROPERTY(QString value4Title READ value4Title WRITE setValue4Title)
  Q_PROPERTY(QString value5Title READ value5Title WRITE setValue5Title)
  Q_PROPERTY(QString value6Title READ value6Title WRITE setValue6Title)
  Q_PROPERTY(QString value7Title READ value7Title WRITE setValue7Title)
  Q_PROPERTY(QString value8Title READ value8Title WRITE setValue8Title)
  Q_PROPERTY(QString value9Title READ value9Title WRITE setValue9Title)
  Q_PROPERTY(QString value10Title READ value10Title WRITE setValue10Title)
  Q_PROPERTY(QString value11Title READ value11Title WRITE setValue11Title)
  Q_PROPERTY(QString value12Title READ value12Title WRITE setValue12Title)
  Q_PROPERTY(QString value13Title READ value13Title WRITE setValue13Title)
  Q_PROPERTY(QString value14Title READ value14Title WRITE setValue14Title)
  Q_PROPERTY(QString value15Title READ value15Title WRITE setValue15Title)
  Q_PROPERTY(QString value16Title READ value16Title WRITE setValue16Title)
  Q_PROPERTY(QString value17Title READ value17Title WRITE setValue17Title)
  Q_PROPERTY(QString value18Title READ value18Title WRITE setValue18Title)
  Q_PROPERTY(QString value19Title READ value19Title WRITE setValue19Title)
  Q_PROPERTY(QString value20Title READ value20Title WRITE setValue20Title)
  Q_PROPERTY(QString value21Title READ value21Title WRITE setValue21Title)
  Q_PROPERTY(QString value22Title READ value22Title WRITE setValue22Title)
  Q_PROPERTY(QString value23Title READ value23Title WRITE setValue23Title)
  Q_PROPERTY(QString value24Title READ value24Title WRITE setValue24Title)
  Q_PROPERTY(QString value25Title READ value25Title WRITE setValue25Title)
  Q_PROPERTY(QString value26Title READ value26Title WRITE setValue26Title)
  Q_PROPERTY(QString value27Title READ value27Title WRITE setValue27Title)
  Q_PROPERTY(QString value28Title READ value28Title WRITE setValue28Title)
  Q_PROPERTY(QString value29Title READ value29Title WRITE setValue29Title)
  Q_PROPERTY(QString value30Title READ value30Title WRITE setValue30Title)
  Q_PROPERTY(QString value31Title READ value31Title WRITE setValue31Title)
  Q_PROPERTY(QString value32Title READ value32Title WRITE setValue32Title)
  Q_PROPERTY(QString value33Title READ value33Title WRITE setValue33Title)
  Q_PROPERTY(QString value34Title READ value34Title WRITE setValue34Title)
  Q_PROPERTY(QString value35Title READ value35Title WRITE setValue35Title)
  Q_PROPERTY(QString value36Title READ value36Title WRITE setValue36Title)
  Q_PROPERTY(QString value37Title READ value37Title WRITE setValue37Title)
  Q_PROPERTY(QString value38Title READ value38Title WRITE setValue38Title)
  Q_PROPERTY(QString value39Title READ value39Title WRITE setValue39Title)
  Q_PROPERTY(QString value40Title READ value40Title WRITE setValue40Title)
  Q_PROPERTY(QString value41Title READ value41Title WRITE setValue41Title)
  Q_PROPERTY(QString value42Title READ value42Title WRITE setValue42Title)
  Q_PROPERTY(QString value43Title READ value43Title WRITE setValue43Title)
  Q_PROPERTY(QString value44Title READ value44Title WRITE setValue44Title)
  Q_PROPERTY(QString value45Title READ value45Title WRITE setValue45Title)
  Q_PROPERTY(QString value46Title READ value46Title WRITE setValue46Title)
  Q_PROPERTY(QString value47Title READ value47Title WRITE setValue47Title)
  Q_PROPERTY(QString value48Title READ value48Title WRITE setValue48Title)
  Q_PROPERTY(double eqBand1Value READ eqBand1Value WRITE setEqBand1Value)
  Q_PROPERTY(double eqBand2Value READ eqBand2Value WRITE setEqBand2Value)
  Q_PROPERTY(double eqBand3Value READ eqBand3Value WRITE setEqBand3Value)
  Q_PROPERTY(double eqBand4Value READ eqBand4Value WRITE setEqBand4Value)
  Q_PROPERTY(double eqBand5Value READ eqBand5Value WRITE setEqBand5Value)
  Q_PROPERTY(double eqBand6Value READ eqBand6Value WRITE setEqBand6Value)
  Q_PROPERTY(double eqBand7Value READ eqBand7Value WRITE setEqBand7Value)
  Q_PROPERTY(double eqBand8Value READ eqBand8Value WRITE setEqBand8Value)
  Q_PROPERTY(ScaleView scaleView READ scaleView WRITE setScaleView)
  Q_PROPERTY(bool stompsAndAmpHidden READ stompsAndAmpHidden WRITE setStompsAndAmpHidden)

public:
  explicit QToasterStompEditLCD(QWidget *parent = 0);
  ~QToasterStompEditLCD();

  enum ScaleView
  {
    Empty = 0,
    GraphicEq = 1,
    StompValue = 2
  };

  QString stompInstance() const;
  QString stompName() const;
  QString value1Title() const;
  QString value2Title() const;
  QString value3Title() const;
  QString value4Title() const;
  QString value5Title() const;
  QString value6Title() const;
  QString value7Title() const;
  QString value8Title() const;
  QString value9Title() const;
  QString value10Title() const;
  QString value11Title() const;
  QString value12Title() const;
  QString value13Title() const;
  QString value14Title() const;
  QString value15Title() const;
  QString value16Title() const;
  QString value17Title() const;
  QString value18Title() const;
  QString value19Title() const;
  QString value20Title() const;
  QString value21Title() const;
  QString value22Title() const;
  QString value23Title() const;
  QString value24Title() const;
  QString value25Title() const;
  QString value26Title() const;
  QString value27Title() const;
  QString value28Title() const;
  QString value29Title() const;
  QString value30Title() const;
  QString value31Title() const;
  QString value32Title() const;
  QString value33Title() const;
  QString value34Title() const;
  QString value35Title() const;
  QString value36Title() const;
  QString value37Title() const;
  QString value38Title() const;
  QString value39Title() const;
  QString value40Title() const;
  QString value41Title() const;
  QString value42Title() const;
  QString value43Title() const;
  QString value44Title() const;
  QString value45Title() const;
  QString value46Title() const;
  QString value47Title() const;
  QString value48Title() const;

  double eqBand1Value() const;
  double eqBand2Value() const;
  double eqBand3Value() const;
  double eqBand4Value() const;
  double eqBand5Value() const;
  double eqBand6Value() const;
  double eqBand7Value() const;
  double eqBand8Value() const;

  ScaleView scaleView() const;

  bool stompsAndAmpHidden() const;

  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

public slots:
  virtual void setColor(Color color);
  void setStompInstance(QString stompInstance);
  void setStompName(QString stompName);
  void setValue1Title(QString title);
  void setValue2Title(QString title);
  void setValue3Title(QString title);
  void setValue4Title(QString title);
  void setValue5Title(QString title);
  void setValue6Title(QString title);
  void setValue7Title(QString title);
  void setValue8Title(QString title);
  void setValue9Title(QString title);
  void setValue10Title(QString title);
  void setValue11Title(QString title);
  void setValue12Title(QString title);
  void setValue13Title(QString title);
  void setValue14Title(QString title);
  void setValue15Title(QString title);
  void setValue16Title(QString title);
  void setValue17Title(QString title);
  void setValue18Title(QString title);
  void setValue19Title(QString title);
  void setValue20Title(QString title);
  void setValue21Title(QString title);
  void setValue22Title(QString title);
  void setValue23Title(QString title);
  void setValue24Title(QString title);
  void setValue25Title(QString title);
  void setValue26Title(QString title);
  void setValue27Title(QString title);
  void setValue28Title(QString title);
  void setValue29Title(QString title);
  void setValue30Title(QString title);
  void setValue31Title(QString title);
  void setValue32Title(QString title);
  void setValue33Title(QString title);
  void setValue34Title(QString title);
  void setValue35Title(QString title);
  void setValue36Title(QString title);
  void setValue37Title(QString title);
  void setValue38Title(QString title);
  void setValue39Title(QString title);
  void setValue40Title(QString title);
  void setValue41Title(QString title);
  void setValue42Title(QString title);
  void setValue43Title(QString title);
  void setValue44Title(QString title);
  void setValue45Title(QString title);
  void setValue46Title(QString title);
  void setValue47Title(QString title);
  void setValue48Title(QString title);

  void setValue1(QString value);
  void setValue2(QString value);
  void setValue3(QString value);
  void setValue4(QString value);
  void setValue5(QString value);
  void setValue6(QString value);
  void setValue7(QString value);
  void setValue8(QString value);
  void setValue9(QString value);
  void setValue10(QString value);
  void setValue11(QString value);
  void setValue12(QString value);
  void setValue13(QString value);
  void setValue14(QString value);
  void setValue15(QString value);
  void setValue16(QString value);
  void setValue17(QString value);
  void setValue18(QString value);
  void setValue19(QString value);
  void setValue20(QString value);
  void setValue21(QString value);
  void setValue22(QString value);
  void setValue23(QString value);
  void setValue24(QString value);
  void setValue25(QString value);
  void setValue26(QString value);
  void setValue27(QString value);
  void setValue28(QString value);
  void setValue29(QString value);
  void setValue30(QString value);
  void setValue31(QString value);
  void setValue32(QString value);
  void setValue33(QString value);
  void setValue34(QString value);
  void setValue35(QString value);
  void setValue36(QString value);
  void setValue37(QString value);
  void setValue38(QString value);
  void setValue39(QString value);
  void setValue40(QString value);
  void setValue41(QString value);
  void setValue42(QString value);
  void setValue43(QString value);
  void setValue44(QString value);
  void setValue45(QString value);
  void setValue46(QString value);
  void setValue47(QString value);
  void setValue48(QString value);

  void setEqBand1Value(double value);
  void setEqBand2Value(double value);
  void setEqBand3Value(double value);
  void setEqBand4Value(double value);
  void setEqBand5Value(double value);
  void setEqBand6Value(double value);
  void setEqBand7Value(double value);
  void setEqBand8Value(double value);

  void setScaleView(ScaleView scaleView);
  void setStompsAndAmpHidden(bool hidden);

  virtual void setCurrentPage(Page page);
  virtual void setMaxPage(Page page);

  void setStompFXType(StompInstance stompInstance, FXType fxType);
  void setStompAFXType(FXType fxType);
  void setStompBFXType(FXType fxType);
  void setStompCFXType(FXType fxType);
  void setStompDFXType(FXType fxType);
  void setStompXFXType(FXType fxType);
  void setStompModFXType(FXType fxType);

  void setStompEnabled(StompInstance stompInstance, bool enabled);
  void setStompAEnabled(bool enabled);
  void setStompBEnabled(bool enabled);
  void setStompCEnabled(bool enabled);
  void setStompDEnabled(bool enabled);
  void setStompXEnabled(bool enabled);
  void setStompModEnabled(bool enabled);
  void setDelayEnabled(bool enabled);
  void setReverbEnabled(bool enabled);

  void setAmpName(const QString& ampName);

protected:
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);
  void updatePageInfo();

  void setEqBandValue(QWidget* widget, int value);
  double getEqBandValue(QWidget* widget) const;

  void setFonts();

private:
  Ui::QToasterStompEditLCD *ui;
};

#endif // QTOASTERSTOMPEDITLCD_H
