#ifndef QTOASTERTUNERLCD_H
#define QTOASTERTUNERLCD_H

#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"
#include "QToasterLCD.h"

namespace Ui {
  class QToasterTunerLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterTunerLCD : public QWidget, public QToasterLCD
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  explicit QToasterTunerLCD(QWidget *parent = 0);
  ~QToasterTunerLCD();

  Color color() const { return mColor; }
  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

public slots:
  void setColor(Color color);
  void setIndexPosition(int position);
  void setNote(QString note);
  void setOctave(QString octave);

protected:
  void createIndexSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

private:
  Ui::QToasterTunerLCD *ui;

  QList<QPixmap> mIndexPixmaps;
};

#endif // QTOASTERTUNERLCD_H
