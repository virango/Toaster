#ifndef QTOASTERTUNERLCD_H
#define QTOASTERTUNERLCD_H

#include <QWidget>
#include "Commons.h"
#include "QToasterLCD.h"

namespace Ui {
  class QToasterTunerLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterTunerLCD : public QToasterLCD
{
  Q_OBJECT


public:
  explicit QToasterTunerLCD(QWidget *parent = 0);
  ~QToasterTunerLCD();


public slots:
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
