#ifndef QTOASTERBUTTON_H
#define QTOASTERBUTTON_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QMovie>
#include <QTimer>

#include "ToasterWidgetsLib.h"

#define MAP_INSERT(x, y, z) x[y] = z

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterButton : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Type)
  Q_ENUMS(State)
  Q_PROPERTY(Type type READ type WRITE setType)
  Q_PROPERTY(State state READ state WRITE setState)

public:
  QToasterButton(QWidget *parent = 0);

  enum Type
  {
    Big, Small
  };

  enum State
  {
    Off = 0,
    On = 1,
    Blinking = 2
  };

  Type type() const { return mType; }
  State state() const { return mGlobalState; }
  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

signals:
  void clicked(QToasterButton& bt, bool longClick);

public slots:
  void setType(Type type);
  void setState(State state);
  void resetToOnOffState();
  bool toggleOnOff();

private slots:
  void longClick();

protected:
  void createSkin();
  void paintEvent(QPaintEvent* pe);
  void mousePressEvent(QMouseEvent* me);
  void mouseReleaseEvent(QMouseEvent* me);
  void contextMenuEvent(QContextMenuEvent * cme);

private:
  QList<QPixmap> mSkinPixmaps;

  Type    mType;
  State   mGlobalState;
  State   mOnOffState;

  bool    mClickEmited;
  QTimer  mLongClickTimer;

  QLabel  mAnimLabel;
  QMovie  mMovie;

  ICtxMenuProvider* mpCtxMenuProvider;

  QMap<Type, QString> mSkins;
  QMap<Type, QString> mAnims;
  static const int mSkinNoOfFrames = 2;
};

#endif
