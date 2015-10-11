#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "QToasterLCD.h"
#include "ui_QToasterLCD.h"
#include "CtxMenuProvider.h"

QToasterLCD::FXType2ShortNameMap QToasterLCD::sFXType2ShortNameMap;

#define ENABLED "background-color: rgb(50,50,50);color: rgb(255, 255, 255);border-color: rgb(0, 0, 0);border-radius: 3px;"
#define DISABLED "background-color: rgb(128,128,128);color: rgb(192, 192, 192);border-color: rgb(0, 0, 0);border-radius: 3px;"

/*
background-color: rgb(50,50,50);
color: rgb(255, 255, 255);
border-color: rgb(0, 0, 0);
border-radius: 3px;
*/

QToasterLCD::QToasterLCD(QWidget *parent)
  : QStackedWidget(parent)
  , ui(new Ui::QToasterLCD)
  , mMode(Browser)
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

QToasterLCD::~QToasterLCD()
{
  delete ui;
}

void QToasterLCD::createSkin()
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

void QToasterLCD::paintEvent(QPaintEvent* pe)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = mSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
  if(mMode == Browser)
    setCurrentIndex(0);
  else if(mMode == Perform)
    setCurrentIndex(1);
}

void QToasterLCD::contextMenuEvent(QContextMenuEvent * cme)
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

void QToasterLCD::setMode(QToasterLCD::Mode mode)
{
  mMode = mode;
  update();
}

void QToasterLCD::setColor(QToasterLCD::Color color)
{
  mColor = color;
  update();
}

void QToasterLCD::setBrowserModeBassValueText(const QString& value)
{
  ui->bassValueLabel->setText(value);
}

void QToasterLCD::setBrowserModeMiddleValueText(const QString& value)
{
  ui->middleValueLabel->setText(value);
}

void QToasterLCD::setBrowserModeTrebleValueText(const QString& value)
{
  ui->trebleValueLabel->setText(value);
}

void QToasterLCD::setBrowserModePresenceValueText(const QString& value)
{
  ui->presenceValueLabel->setText(value);
}

void QToasterLCD::setBrowserModeRigName(const QString& value)
{
  ui->rigNameEdit->setText(value);
  ui->rigNameEdit->setCursorPosition(0);
}

void QToasterLCD::setBrowserModeRigAuthor(const QString& value)
{
  ui->rigAuthorEdit->setText(value);
  ui->rigAuthorEdit->setCursorPosition(0);
}

void QToasterLCD::setBrowserModeAmpName(const QString& value)
{
  ui->ampNameEdit->setText(value);
  ui->ampNameEdit->setCursorPosition(0);
}

void QToasterLCD::setBrowserModeView(int view)
{
  ui->browserViewComboBox->setCurrentIndex(view);
}


void QToasterLCD::setStompAFXType(FXType fxType)
{
  ui->stompAEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompBFXType(FXType fxType)
{
  ui->stompBEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompCFXType(FXType fxType)
{
  ui->stompCEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompDFXType(FXType fxType)
{
  ui->stompDEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompXFXType(FXType fxType)
{
  ui->stompXEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompModFXType(FXType fxType)
{
  ui->stompModEdit->setText(sFXType2ShortNameMap[fxType]);
}

void QToasterLCD::setStompAEnabled(bool enabled)
{
  setEnabled(*ui->stompAEdit, enabled);
}

void QToasterLCD::setStompBEnabled(bool enabled)
{
  setEnabled(*ui->stompBEdit, enabled);
}

void QToasterLCD::setStompCEnabled(bool enabled)
{
  setEnabled(*ui->stompCEdit, enabled);
}

void QToasterLCD::setStompDEnabled(bool enabled)
{
  setEnabled(*ui->stompDEdit, enabled);
}

void QToasterLCD::setStompXEnabled(bool enabled)
{
  setEnabled(*ui->stompXEdit, enabled);
}

void QToasterLCD::setStompModEnabled(bool enabled)
{
  setEnabled(*ui->stompModEdit, enabled);
}

void QToasterLCD::setDelayEnabled(bool enabled)
{
  setEnabled(*ui->delayEdit, enabled);
}

void QToasterLCD::setReverbEnabled(bool enabled)
{
  setEnabled(*ui->reverbEdit, enabled);
}

void QToasterLCD::setEnabled(QWidget& w, bool enabled)
{
  if(enabled)
    w.setStyleSheet(ENABLED);
  else
    w.setStyleSheet(DISABLED);
}

void QToasterLCD::on_browserViewComboBox_currentIndexChanged(int index)
{
  emit browserModeViewChanged(index);
}

QStringList QToasterLCD::getBrowserModeViews()
{
  QStringList list;
  for(int i = 0; i < ui->browserViewComboBox->count(); i++)
    list.append(ui->browserViewComboBox->itemText(i));
  return list;
}
