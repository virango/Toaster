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
  , mMaxPage(Page2)
  , mCurrentPage(Page1)
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

void QToasterStompEditLCD::setCurrentPage(Page page)
{
  if(page <= mMaxPage)
  {
    mCurrentPage = page;
    ui->valWidget1->setCurrentIndex((int)page);
    ui->valWidget2->setCurrentIndex((int)page);
    updatePageInfo();
  }
}

void QToasterStompEditLCD::setMaxPage(Page page)
{
  mMaxPage = page;
  updatePageInfo();
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

void QToasterStompEditLCD::setAmpName(const QString &ampName)
{
  ui->ampNameEdit->setText(ampName);
}

void QToasterStompEditLCD::setEnabled(QWidget& w, bool enabled)
{
  if(enabled)
    w.setStyleSheet(ENABLED);
  else
    w.setStyleSheet(DISABLED);
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
