#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include "qchickenheaddial.h"

QChickenHeadDial::QChickenHeadDial(QWidget *parent)
  : QWidget(parent)
  , mCurrState(Browser)
  , mMouseY(0)
{
  createKnobSkin();
}

void QChickenHeadDial::createKnobSkin()
{
  if(!mKnobSkinPixmaps.isEmpty())
    mKnobSkinPixmaps.clear();

  QString skin = ":/resources/ChickenHeadBlack.png";

  QPixmap masterPixmap(skin);

  int width = masterPixmap.height();
  int height = masterPixmap.height();

  width = masterPixmap.width() / mKnobSkinNoOfFrames;

  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < mKnobSkinNoOfFrames; i++)
    {
      x = i * width;
      mKnobSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }
}

void QChickenHeadDial::setState(State state)
{
  mCurrState = state;
}

void QChickenHeadDial::stateDown()
{
  switch(mCurrState)
  {
    case Tuner:
      mCurrState = Browser;
      break;
      /*
    case Browser:
      mCurrState = Perform;
      break;
    case Perform:
      mCurrState = Profiler;
      break;
      */
  }
}

void QChickenHeadDial::stateUp()
{
  switch (mCurrState) {
    /*
    case Profiler:
      mCurrState = Perform;
      break;
    case Perform:
      mCurrState = Browser;
      break;
      */
    case Browser:
      mCurrState = Tuner;
      break;
  }
}

void QChickenHeadDial::paintEvent(QPaintEvent* /* pe */)
{
  QPainter painter(this);
  QPixmap& pmKnob = mKnobSkinPixmaps[mCurrState];
  painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
  painter.drawPixmap(0, 0, pmKnob);
}

void QChickenHeadDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta();
  if(delta < 0)
    stateDown();
  else
    stateUp();
  emit valueChanged(mCurrState);
  update();
}

void QChickenHeadDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QChickenHeadDial::mouseMoveEvent(QMouseEvent* me)
{
  if(me->buttons() == Qt::LeftButton)
  {
    me->accept();
    int delta = mMouseY - me->y();
    mMouseY = me->y();
    if(delta < 0)
      stateDown();
    else
      stateUp();
    emit valueChanged(mCurrState);
    update();
  }
  else
    me->ignore();
}
