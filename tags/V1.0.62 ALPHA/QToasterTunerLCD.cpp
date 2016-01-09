#include <QPainter>
#include <QMenu>
#include <QMouseEvent>
#include "QToasterTunerLCD.h"
#include "ui_QToasterTunerLCD.h"
#include "CtxMenuProvider.h"

QToasterTunerLCD::QToasterTunerLCD(QWidget *parent)
  : QToasterLCD(parent)
  , ui(new Ui::QToasterTunerLCD)
{
  ui->setupUi(this);
  createSkin();
  createIndexSkin();
  setIndexPosition(100);
}

QToasterTunerLCD::~QToasterTunerLCD()
{
  delete ui;
}

void QToasterTunerLCD::createIndexSkin()
{
  QString skin = ":/resources/Tuner.png";
  QPixmap masterPixmap(skin);
  int width = masterPixmap.width();
  int height = masterPixmap.height()/200;

  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < 200; i++)
    {
      y = i * height;
      mIndexPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }
}

void QToasterTunerLCD::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = sSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
}

void QToasterTunerLCD::contextMenuEvent(QContextMenuEvent * cme)
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

void QToasterTunerLCD::setIndexPosition(int position)
{
  if(position >= 0 && position < 200)
  {
    ui->indexLabel->setPixmap(mIndexPixmaps[position]);
    update();
  }
}

void QToasterTunerLCD::setNote(QString note)
{
  ui->noteLabel->setText(note);
}

void QToasterTunerLCD::setOctave(QString octave)
{
  ui->octaveLabel->setText(octave);
}
