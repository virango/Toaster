#ifndef QTOASTERENUMDIAL_H
#define QTOASTERENUMDIAL_H
#include <QWidget>
#include <QPixmap>
#include <QMap>
#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

class TOASTERWIDGETS_EXPORT QToasterEnumDial : public QWidget
{
  Q_OBJECT
  Q_ENUMS(KnobSize)
  Q_PROPERTY(KnobSize knobSize READ knobSize WRITE setKnobSize)
  Q_PROPERTY(QStringList values READ values WRITE setValues)
  Q_PROPERTY(bool isActive READ isActive WRITE setIsActive)
public:
  QToasterEnumDial(QWidget *parent = 0);

  enum KnobSize
  {
    Big, Small
  };

  KnobSize knobSize() const { return mKnobSize; }
  QStringList values() const { return mValues; }
  bool isActive() const { return mIsActive; }

  unsigned int valueIndex() const { return mCurrValueIndex; }

signals:
  void valueChanged(int valueIndex);
  void valueChanged(const QString&);

public slots:
  void setKnobSize(KnobSize knobSize);
  void setValues(QStringList values);
  void setIsActive(bool enabled) { mIsActive = enabled; }
  //void setValue(const QString& value);
  void setValue(int value);

protected:
  void createKnobSkin();
  void paintEvent(QPaintEvent* pe);
  void wheelEvent(QWheelEvent* we);
  void mousePressEvent(QMouseEvent* me);
  void mouseMoveEvent(QMouseEvent* me);

  void enterEvent(QEvent* event);
  void leaveEvent(QEvent* event);

  void update(int deltaSteps);
  void updateValueText();
  void showValueTooltip();

private:
  QList<QPixmap> mKnobSkinPixmaps;
  int mCurrKnobFrameNo;

  KnobSize mKnobSize;

  int mMouseY;

  int               mCurrValueIndex;
  QString           mCurrValueText;

  bool              mIsActive;

  QStringList mValues;

  QMap<KnobSize, QString> mKnobSkins;
  static const int mKnobSkinNoOfFrames = 40;
};

#endif
