#include <QPainter>
#include "qmulticolorled.h"

QList<QPixmap> QMultiColorLed::sSkinPixmaps;

QMultiColorLed::QMultiColorLed(QWidget *parent) :
  QWidget(parent)
{
  createSkin();
}

void QMultiColorLed::createSkin()
{
  if(sSkinPixmaps.isEmpty())
  {
    QString skin = ":/resources/KPA_Stomp_Led.png";

    QPixmap masterPixmap(skin);

    int width = masterPixmap.width();
    int height = masterPixmap.height() / (NoOfColors);

    if(!masterPixmap.isNull())
    {
      int x = 0;
      int y = 0;
      for(int i = 0; i < NoOfColors; i++)
      {
        y = i * height;
        sSkinPixmaps.insert(i, masterPixmap.copy(x, y, width, height));
      }
    }
  }
}

void QMultiColorLed::paintEvent(QPaintEvent* /*pe*/)
{
  QPainter painter(this);
  if(mColor < NoOfColors)
  {
    QPixmap pm = sSkinPixmaps[mColor];
    painter.setWindow(0, 0, pm.width(), pm.height());
    painter.drawPixmap(0, 0, pm);
  }
}
