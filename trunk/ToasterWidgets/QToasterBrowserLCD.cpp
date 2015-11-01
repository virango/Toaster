#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "QToasterBrowserLCD.h"
#include "ui_QToasterBrowserLCD.h"
#include "QToasterLCD.h"
#include "CtxMenuProvider.h"

QToasterBrowserLCD::QToasterBrowserLCD(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::QToasterBrowserLCD)
  , mColor(Standard)
  , mpCtxMenuProvider(NULL)
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
}

QToasterBrowserLCD::~QToasterBrowserLCD()
{
  delete ui;
}

void QToasterBrowserLCD::createSkin()
{
  QString skin = ":/resources/LCD.png";

  QPixmap masterPixmap(skin);

  int width = masterPixmap.width();
  int height = masterPixmap.height() / (NoOfColors + 1); // to compansate a bug in JKnobMan:
                                                         // as JKnobMan doesn't create the last frame properly
                                                         // there must be an additional one
  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < NoOfColors; i++)
    {
      y = i * height;
      mSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }
}

void QToasterBrowserLCD::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = mSkinPixmaps[mColor];
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

void QToasterBrowserLCD::setColor(QToasterBrowserLCD::Color color)
{
  mColor = color;
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
}

void QToasterBrowserLCD::setStompBFXType(FXType fxType)
{
  ui->stompBEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterBrowserLCD::setStompCFXType(FXType fxType)
{
  ui->stompCEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterBrowserLCD::setStompDFXType(FXType fxType)
{
  ui->stompDEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterBrowserLCD::setStompXFXType(FXType fxType)
{
  ui->stompXEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterBrowserLCD::setStompModFXType(FXType fxType)
{
  ui->stompModEdit->setText(sFXType2ShortNameMap[fxType]);
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
  setEnabled(*ui->stompAEdit, enabled);
}

void QToasterBrowserLCD::setStompBEnabled(bool enabled)
{
  setEnabled(*ui->stompBEdit, enabled);
}

void QToasterBrowserLCD::setStompCEnabled(bool enabled)
{
  setEnabled(*ui->stompCEdit, enabled);
}

void QToasterBrowserLCD::setStompDEnabled(bool enabled)
{
  setEnabled(*ui->stompDEdit, enabled);
}

void QToasterBrowserLCD::setStompXEnabled(bool enabled)
{
  setEnabled(*ui->stompXEdit, enabled);
}

void QToasterBrowserLCD::setStompModEnabled(bool enabled)
{
  setEnabled(*ui->stompModEdit, enabled);
}

void QToasterBrowserLCD::setDelayEnabled(bool enabled)
{
  setEnabled(*ui->delayEdit, enabled);
}

void QToasterBrowserLCD::setReverbEnabled(bool enabled)
{
  setEnabled(*ui->reverbEdit, enabled);
}

void QToasterBrowserLCD::setEnabled(QWidget& w, bool enabled)
{
  if(enabled)
    w.setStyleSheet(ENABLED);
  else
    w.setStyleSheet(DISABLED);
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
