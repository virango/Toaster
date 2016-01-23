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

signals:
  void signalMuted(bool muted);

public slots:
  void setIndexPosition(int position);
  void setNote(const QString& note);
  void setOctave(const QString& octave);
  void setMasterTuneValue(const QString& masterTune);
  void setMuted(bool muted);

protected:
  void createIndexSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

private slots:
  void on_muteCheckBox_clicked(bool checked);

private:
  Ui::QToasterTunerLCD *ui;

  QList<QPixmap> mIndexPixmaps;
};

#endif // QTOASTERTUNERLCD_H
