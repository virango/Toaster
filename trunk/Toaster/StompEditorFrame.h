#ifndef STOMPEDITORFRAME_H
#define STOMPEDITORFRAME_H

#include <QStackedWidget>

namespace Ui {
  class StompEditorFrame;
}

class StompEditorFrame : public QStackedWidget
{
  Q_OBJECT

public:
  explicit StompEditorFrame(QWidget *parent = 0);
  ~StompEditorFrame();

private:
  Ui::StompEditorFrame *ui;
};

#endif // STOMPEDITORFRAME_H
