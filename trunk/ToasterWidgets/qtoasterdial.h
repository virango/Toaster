#ifndef QTOASTERDIAL_H
#define QTOASTERDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>

#define MAP_INSERT(x, y, z) x[y] = z

class QToasterDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_ENUMS(LEDRingType)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(LEDRingType ledRingType READ ledRingType WRITE setLEDRingType)
  Q_PROPERTY(double minValue READ minValue WRITE setMinValue)
  Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue)
  Q_PROPERTY(double stepWidth READ stepWidth WRITE setStepWidth)
  Q_PROPERTY(QString unit READ unit WRITE setUnit)

public:
  QToasterDial(QWidget *parent = 0);

  enum KnobSize
  {
    Big, Small
  };

  enum LEDRingType
  {
    None, Uni, Bi
  };

  KnobSize knobSize() const { return mKnobSize; }
  LEDRingType ledRingType() const { return mLEDRingType; }
  double minValue() const { return mMinValue; }
  double maxValue() const { return mMaxValue; }
  double stepWidth() const { return mStepWidth; }
  QString unit() const { return mUnit; }

signals:
  void valueChanged(double);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setLEDRingType(LEDRingType ledType);
  void setMinValue(double minValue);
  void setMaxValue(double maxValue);
  void setStepWidth(double stepWidth);
  void setValue(double value);
  void setUnit(QString unit);

protected:
  void createKnobSkin();
  void createLEDRingSkin();
  void paintEvent(QPaintEvent* pe);
  void wheelEvent(QWheelEvent* we);
  void mousePressEvent(QMouseEvent* me);
  void mouseMoveEvent(QMouseEvent* me);

  void enterEvent(QEvent* event);
  void leaveEvent(QEvent* event);

  void update(int deltaSteps);
  void showValueTooltip();

  void updateLEDRing();

private:
  QList<QPixmap> mKnobSkinPixmaps;
  QList<QPixmap> mLEDRingSkinPixmaps;
  int mCurrKnobFrameNo;
  int mCurrLEDRingFrameNo;

  KnobSize mKnobSize;
  LEDRingType  mLEDRingType;

  int mMouseY;

  double mMinValue;
  double mMaxValue;
  double mStepWidth;
  double mCurrValue;

  QString mUnit;

  QMap<KnobSize, QString> mKnobSkins;
  QMap<LEDRingType, QString> mLEDRingSkins;
  static const int mKnobSkinNoOfFrames = 40;
  static const int mLEDRingSkinNoOfFrames = 16;
};

#endif