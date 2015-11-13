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

void QToasterStompEditLCD::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = mSkinPixmaps[mColor];
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
  case StompMOD:
    setStompModFXType(fxType);
    break;
  }
}

void QToasterStompEditLCD::setStompAFXType(FXType fxType)
{
  ui->stompAEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterStompEditLCD::setStompBFXType(FXType fxType)
{
  ui->stompBEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterStompEditLCD::setStompCFXType(FXType fxType)
{
  ui->stompCEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterStompEditLCD::setStompDFXType(FXType fxType)
{
  ui->stompDEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterStompEditLCD::setStompXFXType(FXType fxType)
{
  ui->stompXEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterStompEditLCD::setStompModFXType(FXType fxType)
{
  ui->stompModEdit->setText(sFXType2ShortNameMap[fxType]);
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
  case StompMOD:
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

