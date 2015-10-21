#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "QToasterStompEditLCD.h"
#include "ui_QToasterStompEditLCD.h"
#include "QToasterLCD.h"
#include "CtxMenuProvider.h"

QToasterStompEditLCD::QToasterStompEditLCD(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::QToasterStompEditLCD)
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

QToasterStompEditLCD::~QToasterStompEditLCD()
{
  delete ui;
}

void QToasterStompEditLCD::createSkin()
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

void QToasterStompEditLCD::setColor(QToasterStompEditLCD::Color color)
{
  mColor = color;
  update();
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

void QToasterStompEditLCD::setStompAEnabled(bool enabled)
{
  setEnabled(*ui->stompAEdit, enabled);
}

void QToasterStompEditLCD::setStompBEnabled(bool enabled)
{
  setEnabled(*ui->stompBEdit, enabled);
}

void QToasterStompEditLCD::setStompCEnabled(bool enabled)
{
  setEnabled(*ui->stompCEdit, enabled);
}

void QToasterStompEditLCD::setStompDEnabled(bool enabled)
{
  setEnabled(*ui->stompDEdit, enabled);
}

void QToasterStompEditLCD::setStompXEnabled(bool enabled)
{
  setEnabled(*ui->stompXEdit, enabled);
}

void QToasterStompEditLCD::setStompModEnabled(bool enabled)
{
  setEnabled(*ui->stompModEdit, enabled);
}

void QToasterStompEditLCD::setDelayEnabled(bool enabled)
{
  setEnabled(*ui->delayEdit, enabled);
}

void QToasterStompEditLCD::setReverbEnabled(bool enabled)
{
  setEnabled(*ui->reverbEdit, enabled);
}

void QToasterStompEditLCD::setEnabled(QWidget& w, bool enabled)
{
  if(enabled)
    w.setStyleSheet(ENABLED);
  else
    w.setStyleSheet(DISABLED);
}
