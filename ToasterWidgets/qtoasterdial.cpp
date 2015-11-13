#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QToolTip>
#include <math.h>
#include "qtoasterdial.h"

#define DEFAULT_SKIN

QToasterDial::QToasterDial(QWidget *parent)
  : QWidget(parent)
  , mCurrKnobFrameNo()
  , mCurrLEDRingFrameNo()
  , mKnobSize(Big)
  , mLEDRingType(Uni)
  , mMouseY(0)
  , mMinValue(0)
  , mMaxValue(100)
  , mStepWidth(1)
  , mPrecision(0)
  , mCurrValue(0)
  , mCurrValueText("<0.0>")
  , mUnit("")
  , mIsActive(true)
{
  MAP_INSERT(mKnobSkins, Big,   ":/resources/BigDial.png");
  MAP_INSERT(mKnobSkins, Small, ":/resources/SmallDial.png");

  MAP_INSERT(mLEDRingSkins, Uni, ":/resources/LEDRingUni.png");
  MAP_INSERT(mLEDRingSkins, Bi,  ":/resources/LEDRingBi.png");
  createKnobSkin();
  createLEDRingSkin();
}

void QToasterDial::createKnobSkin()
{
  if(!mKnobSkinPixmaps.isEmpty())
    mKnobSkinPixmaps.clear();

  QString skin = mKnobSkins[mKnobSize];

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

void QToasterDial::createLEDRingSkin()
{
  if(!mLEDRingSkinPixmaps.isEmpty())
    mLEDRingSkinPixmaps.clear();

  if(mLEDRingType != None)
  {
    QString skin = mLEDRingSkins[mLEDRingType];

    QPixmap masterPixmap(skin);

    int width = masterPixmap.height();
    int height = masterPixmap.height();

    width = masterPixmap.width() / mLEDRingSkinNoOfFrames;

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < mLEDRingSkinNoOfFrames; i++)
      {
        x = i * width;
        mLEDRingSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QToasterDial::update(int deltaSteps)
{
  // update value
  double newValue = mCurrValue + (deltaSteps * mStepWidth);
  double tmp = pow(10, (double)mPrecision);
  newValue = floor(newValue * tmp + 0.5) / tmp;

  if (newValue < mMinValue)
    mCurrValue = mMinValue;
  else if(newValue > mMaxValue)
    mCurrValue = mMaxValue;
  else
    mCurrValue = newValue;

  updateValueText();

  // update knob
  int newKnobFrameNo = mCurrKnobFrameNo + deltaSteps;
  if(newKnobFrameNo < 0)
    mCurrKnobFrameNo = mKnobSkinNoOfFrames + (newKnobFrameNo % mKnobSkinNoOfFrames);
  else if(newKnobFrameNo >= mKnobSkinNoOfFrames)
    mCurrKnobFrameNo = newKnobFrameNo % mKnobSkinNoOfFrames;
  else
    mCurrKnobFrameNo = newKnobFrameNo;

  // update led ring
  updateLEDRing();

  // paint
  QWidget::update();
  showValueTooltip();
  // notify value changed
  if(mIsActive)
    emit valueChanged(mCurrValue);
}

void QToasterDial::updateValueText()
{
  mCurrValueText = "";
  mCurrValueText += QString::number(mCurrValue, 'f', mPrecision) + " " + mUnit;
  if(mCurrValueText.startsWith("0.0") && mMinValue < 0)
    mCurrValueText = "<" + mCurrValueText + ">";

  if(mIsActive)
    emit valueChanged(mCurrValueText);
}

void QToasterDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  createKnobSkin();
}

void QToasterDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  createLEDRingSkin();
}

void QToasterDial::setMinValue(double minValue)
{
  if(minValue < mMaxValue)
  {
    mMinValue = minValue;
  }
  QWidget::update();
}

void QToasterDial::setMaxValue(double maxValue)
{
  if(maxValue > mMinValue)
  {
    mMaxValue = maxValue;
  }
  QWidget::update();
}

void QToasterDial::setStepWidth(double stepWidth)
{
  if(stepWidth < (mMaxValue - mMinValue))
  {
    mStepWidth = stepWidth;
    if(mStepWidth < 1.0 && mPrecision == 0)
      mPrecision = 1;
  }
}

void QToasterDial::setValue(double value)
{
  if(value >= mMinValue && value <= mMaxValue && mIsActive)
  {
    double tmp = pow(10, (double)mPrecision);
    mCurrValue = floor(value * tmp + 0.5) / tmp;
    updateValueText();
    updateLEDRing();
  }
}

void QToasterDial::setUnit(QString unit)
{
  mUnit = unit;
}

void QToasterDial::paintEvent(QPaintEvent* /* pe */)
{
  QPainter painter(this);
  QPixmap& pmKnob = mKnobSkinPixmaps[mCurrKnobFrameNo];
  painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
  if(!mLEDRingSkinPixmaps.isEmpty())
    painter.drawPixmap(0,0, mLEDRingSkinPixmaps[mCurrLEDRingFrameNo]);
  painter.drawPixmap(0, 0, pmKnob);
}

void QToasterDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta()/120;
  update(delta);
}

void QToasterDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QToasterDial::mouseMoveEvent(QMouseEvent* me)
{
  if(me->buttons() == Qt::LeftButton)
  {
    me->accept();
    int delta = mMouseY - me->y();
    mMouseY = me->y();
    update(delta);
  }
  else
    me->ignore();
}

void QToasterDial::enterEvent(QEvent* event)
{
  event->accept();
  showValueTooltip();
}

void QToasterDial::leaveEvent(QEvent* event)
{
  event->accept();
  QToolTip::hideText();
}

void QToasterDial::showValueTooltip()
{
  if(mIsActive)
  {
    QPoint pos = mapToGlobal(QPoint(this->width()/2, this->height()/2));
    QToolTip::showText(pos, mCurrValueText, this);
  }
}

void QToasterDial::updateLEDRing()
{
  if(mLEDRingType != None && mIsActive)
  {
    double step = (mMaxValue - mMinValue) / (mLEDRingSkinNoOfFrames - 1);
    double offset = mMinValue * (-1);
    mCurrLEDRingFrameNo = (int) ((mCurrValue + offset) / step);
  }
}
