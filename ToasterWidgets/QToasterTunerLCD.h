#ifndef QTOASTERTUNERLCD_H
#define QTOASTERTUNERLCD_H

#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"

namespace Ui {
  class QToasterTunerLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterTunerLCD : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  explicit QToasterTunerLCD(QWidget *parent = 0);
  ~QToasterTunerLCD();

  enum Color
  {
    Standard    = 0,
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

  Color color() const { return mColor; }
  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

public slots:
  void setColor(QToasterTunerLCD::Color color);
  void setIndexPosition(int position);
  void setNote(QString note);
  void setOctave(QString octave);

protected:
  void createSkin();
  void createIndexSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

private:
  Ui::QToasterTunerLCD *ui;

  QList<QPixmap> mSkinPixmaps;
  Color mColor;

  QList<QPixmap> mIndexPixmaps;

  ICtxMenuProvider* mpCtxMenuProvider;
};

#endif // QTOASTERTUNERLCD_H
