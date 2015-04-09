#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "qtoasterbutton.h"


QToasterButton::QToasterButton(QWidget *parent)
  : QWidget(parent)
  , mType(Small)
  , mTriState(false)
  , mCurrState(Off)
  , mPrevState(Off)
  , mDblClick(false)
  , mAnimLabel(this)
  , mMovie()
{
  mAnimLabel.setMovie(&mMovie);
  mAnimLabel.hide();
  MAP_INSERT(mSkins, Big,      ":/resources/BigButton.png");
  MAP_INSERT(mSkins, Small,    ":/resources/SmallButton.png");

  MAP_INSERT(mAnims, Big,      ":/resources/BigButtonAnim.gif");
  MAP_INSERT(mAnims, Small,    ":/resources/SmallButtonAnim.gif");
  createSkin();

  mSingleClickTimer.setSingleShot(true);
  connect(&mSingleClickTimer, SIGNAL(timeout()), this, SLOT(singleClick()));
}

void QToasterButton::createSkin()
{
  if(!mSkinPixmaps.isEmpty())
    mSkinPixmaps.clear();

  QString skin = mSkins[mType];

  QPixmap masterPixmap(skin);

  int width = masterPixmap.height();
  int height = masterPixmap.height();

  if(mSkinNoOfFrames)
    width = masterPixmap.width() / mSkinNoOfFrames;

  if(!masterPixmap.isNull())
  {
    int x = 0;
    int y = 0;
    for(int i = 0; i < mSkinNoOfFrames; i++)
    {
      x = i * width;
      mSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
    }
  }

  QString anim = mAnims[mType];
  mMovie.setFileName(anim);
}

void QToasterButton::setType(Type type)
{
  mType = type;
  createSkin();
}

void QToasterButton::setTriState(bool triState)
{
  mTriState = triState;
}

void QToasterButton::setState(State state)
{
  mPrevState = mCurrState;
  mCurrState = state;
}

void QToasterButton::singleClick()
{
  toggleOnOff();
  emit valueChanged(mCurrState);
  update();
}

void QToasterButton::paintEvent(QPaintEvent* /* pe */)
{
  QPainter painter(this);
  if(mCurrState < Tri)
  {
    mAnimLabel.hide();
    QPixmap pm = mSkinPixmaps[mCurrState];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
  else
  {
    mAnimLabel.show();
    mAnimLabel.adjustSize();
    mMovie.start();
  }
}

void QToasterButton::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    qDebug() << "mouse press\n";
    me->accept();
  }
  else
    me->ignore();
}

void QToasterButton::mouseReleaseEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    if(mDblClick)
    {
      mCurrState = Tri;
      emit valueChanged(mCurrState);
      mDblClick = false;
      update();
    }
    else
    {
      mSingleClickTimer.start(200);
    }
  }
  else
    me->ignore();
}

void QToasterButton::mouseDoubleClickEvent(QMouseEvent* me)
{
  if((me->button() == Qt::LeftButton) && mTriState)
  {
    mSingleClickTimer.stop();
    mDblClick = true;
    me->accept();
  }
  else
    me->ignore();
}

void QToasterButton::toggleOnOff()
{
  if(mCurrState != Tri)
    mPrevState = mCurrState;

  if(mCurrState == Off)
    mCurrState = On;
  else if(mCurrState == On)
    mCurrState = Off;
  else
    mCurrState = mPrevState;
}
