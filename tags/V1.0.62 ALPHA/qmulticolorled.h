#ifndef QMULTICOLORLED_H
#define QMULTICOLORLED_H
#include <QWidget>
#include "ToasterWidgetsLib.h"
#include "Commons.h"

class TOASTERWIDGETS_EXPORT QMultiColorLed : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  enum Color
  {
    Off    = 0,
    Orange      = 1,
    Red         = 2,
    Yellow      = 3,
    Cyan        = 4,
    Blue        = 5,
    Purple      = 6,
    White       = 7,
    Green       = 8,
    NoOfColors  = 9      // must be always last
  };

  QMultiColorLed(QWidget *parent = 0);
  ~QMultiColorLed() {}

  Color color() const { return mColor; }

public slots:
  void setColor(Color color) { mColor = color; }

protected:
  void paintEvent(QPaintEvent*);
  void createSkin();

  Color mColor;

  static QList<QPixmap> sSkinPixmaps;
};

#endif
