#include <QPainter>
#include <QPaintEvent>
#include <QWheelEvent>
#include <QToolTip>
#include <math.h>
#include "QToasterLookUpTableDial.h"

#define DEFAULT_SKIN

QToasterLookUpTableDial::QToasterLookUpTableDial(QWidget *parent)
  : QWidget(parent)
  , mCurrKnobFrameNo()
  , mCurrLEDRingFrameNo()
  , mKnobSize(Big)
  , mLEDRingType(Uni)
  , mMouseY(0)
  , mMinValue(0)
  , mMaxValue(0)
  , mCurrValue(0)
  , mCurrValueText("<0.0>")
  , mUnit("")
  , mIsActive(true)
  , mLookUpTable(nullptr)
{
  MAP_INSERT(mKnobSkins, Big,   ":/resources/BigDial.png");
  MAP_INSERT(mKnobSkins, Small, ":/resources/SmallDial.png");

  MAP_INSERT(mLEDRingSkins, Uni, ":/resources/LEDRingUni.png");
  MAP_INSERT(mLEDRingSkins, Bi,  ":/resources/LEDRingBi.png");
  createKnobSkin();
  createLEDRingSkin();
}

void QToasterLookUpTableDial::createKnobSkin()
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

void QToasterLookUpTableDial::createLEDRingSkin()
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

void QToasterLookUpTableDial::setLookUpTable(QVector<QPair<int,QString>>* lookUpTable)
{
  mLookUpTable = lookUpTable;
  if(mLookUpTable != nullptr)
  {
    mMinValue = 0;
    mMaxValue = mLookUpTable->size() - 1;
  }
}

void QToasterLookUpTableDial::update(int deltaSteps)
{
  if(mLookUpTable != nullptr)
  {
    // update value
    int newValue = mCurrValue + deltaSteps;
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
      emit valueChanged(mLookUpTable->at(mCurrValue).first);
  }
}

void QToasterLookUpTableDial::updateValueText()
{
  if(mLookUpTable != nullptr)
  {
    mCurrValueText = mLookUpTable->at((int)mCurrValue).second + " " + mUnit;

    if(mCurrValueText.startsWith("0.0") && mMinValue < 0)
      mCurrValueText = "<" + mCurrValueText + ">";

    if(mIsActive)
      emit valueChanged(mCurrValueText);
  }
}

void QToasterLookUpTableDial::setKnobSize(KnobSize knobSize)
{
  mKnobSize = knobSize;
  createKnobSkin();
}

void QToasterLookUpTableDial::setLEDRingType(LEDRingType ledRingType)
{
  mLEDRingType = ledRingType;
  createLEDRingSkin();
}

void QToasterLookUpTableDial::setValue(int value)
{
  if(mLookUpTable != nullptr && mIsActive)
  {
    for(int i = 0; i < mLookUpTable->size(); ++i)
    {
      if(mLookUpTable->at(i).first > value)
        break;
      mCurrValue = i;
    }
    if(mCurrValue > mMaxValue)
      mCurrValue = mMaxValue;

    updateValueText();
    updateLEDRing();
  }
}

void QToasterLookUpTableDial::setUnit(QString unit)
{
  mUnit = unit;
}

void QToasterLookUpTableDial::paintEvent(QPaintEvent* /* pe */)
{
  QPainter painter(this);
  QPixmap& pmKnob = mKnobSkinPixmaps[mCurrKnobFrameNo];
  painter.setWindow(0, 0, pmKnob.width(), pmKnob.height());
  if(!mLEDRingSkinPixmaps.isEmpty())
    painter.drawPixmap(0,0, mLEDRingSkinPixmaps[mCurrLEDRingFrameNo]);
  painter.drawPixmap(0, 0, pmKnob);
}

void QToasterLookUpTableDial::wheelEvent(QWheelEvent* we)
{
  we->accept();
  int delta = we->delta()/120;
  update(delta);
}

void QToasterLookUpTableDial::mousePressEvent(QMouseEvent* me)
{
  if(me->button() == Qt::LeftButton)
  {
    me->accept();
    mMouseY = me->y();
  }
  else
    me->ignore();
}

void QToasterLookUpTableDial::mouseMoveEvent(QMouseEvent* me)
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

void QToasterLookUpTableDial::enterEvent(QEvent* event)
{
  event->accept();
  showValueTooltip();
}

void QToasterLookUpTableDial::leaveEvent(QEvent* event)
{
  event->accept();
  QToolTip::hideText();
}

void QToasterLookUpTableDial::showValueTooltip()
{
  if(mIsActive)
  {
    QPoint pos = mapToGlobal(QPoint(this->width()/2, this->height()/2));
    QToolTip::showText(pos, mCurrValueText, this);
  }
}

void QToasterLookUpTableDial::updateLEDRing()
{
  if(mLEDRingType != None && mIsActive)
  {
    double step = (mMaxValue - mMinValue) / (mLEDRingSkinNoOfFrames - 1);
    double offset = mMinValue * (-1);
    double value =  (mCurrValue + offset) / step;
    mCurrLEDRingFrameNo = (int) floor(value + 0.5);
  }
}
