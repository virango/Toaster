#ifndef QTOASTERLOOKUPTABLEDIAL_H
#define QTOASTERLOOKUPTABLEDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

class TOASTERWIDGETS_EXPORT QToasterLookUpTableDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_ENUMS(LEDRingType)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(LEDRingType ledRingType READ ledRingType WRITE setLEDRingType)
  Q_PROPERTY(QString unit READ unit WRITE setUnit)
  Q_PROPERTY(bool isActive READ isActive WRITE setIsActive)

public:
  QToasterLookUpTableDial(QWidget *parent = 0);

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
  QString unit() const { return mUnit; }
  bool isActive() const { return mIsActive; }

  void setLookUpTable(QVector<QPair<int, QString> >* lookUpTable);

signals:
  void valueChanged(int value);
  void valueChanged(const QString&);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setLEDRingType(LEDRingType ledType);
  void setValue(int value);
  void setUnit(QString unit);
  void setIsActive(bool active) { mIsActive = active; }

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
  void updateValueText();
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

  int      mMinValue;
  int      mMaxValue;
  int      mCurrValue;
  QString  mCurrValueText;
  QString  mUnit;
  bool     mIsActive;

  QVector<QPair<int,QString>>* mLookUpTable;

  QMap<KnobSize, QString> mKnobSkins;
  QMap<LEDRingType, QString> mLEDRingSkins;
  static const int mKnobSkinNoOfFrames = 40;
  static const int mLEDRingSkinNoOfFrames = 15;
};

#endif
