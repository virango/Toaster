#ifndef STOMPEDITORFRAME_H
#define STOMPEDITORFRAME_H

#include <QStackedWidget>
#include "Commons.h"

namespace Ui {
  class StompEditorFrame;
}

class Stomp;

class StompEditorFrame : public QStackedWidget
{
  Q_OBJECT

public:
  explicit StompEditorFrame(QWidget *parent = 0);
  ~StompEditorFrame();

  void attach(Stomp& stomp);
  void detach();

private slots:
  void onStompType(::FXType type);

private:
  Ui::StompEditorFrame *ui;

  Stomp* mpStomp;
};

#endif // STOMPEDITORFRAME_H
