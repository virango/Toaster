#ifndef QCHICKENHEADDIAL_H
#define QCHICKENHEADDIAL_H
#include <QWidget>
#include <QPixmap>
#include "ToasterWidgetsLib.h"

class TOASTERWIDGETS_EXPORT QChickenHeadDial : public QWidget
{
  Q_OBJECT

public:
  QChickenHeadDial(QWidget *parent = 0);

  enum State
  {
    Off = 0,
    Tuner = 1,
    Browser = 2,
    Perform = 3,
    Profiler = 4
  };

signals:
  void valueChanged(QChickenHeadDial::State);

public slots:
  void setState(State state);

protected:
  void createKnobSkin();
  void paintEvent(QPaintEvent* pe);
  void wheelEvent(QWheelEvent* we);
  void mousePressEvent(QMouseEvent* me);
  //void mouseReleaseEvent(QMouseEvent* me);
  void mouseMoveEvent(QMouseEvent* me);


  void stateUp();
  void stateDown();

private:
  QList<QPixmap> mKnobSkinPixmaps;

  State mCurrState;

  int   mMouseY;

  static const int mKnobSkinNoOfFrames = 5;
};

#endif
