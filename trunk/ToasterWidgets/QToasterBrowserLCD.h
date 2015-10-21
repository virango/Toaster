#ifndef QTOASTERBROWSERLCD_H
#define QTOASTERBROWSERLCD_H

#include <QWidget>
#include "Commons.h"
#include "ToasterWidgetsLib.h"

namespace Ui {
  class QToasterBrowserLCD;
}

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterBrowserLCD : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_PROPERTY(Color color READ color WRITE setColor)

public:
  explicit QToasterBrowserLCD(QWidget *parent = 0);
  ~QToasterBrowserLCD();

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

  QStringList getBrowserModeViews();

signals:
  void browserModeViewChanged(int view);

public slots:
  void setColor(QToasterBrowserLCD::Color color);

  void setStompAFXType(FXType fxType);
  void setStompBFXType(FXType fxType);
  void setStompCFXType(FXType fxType);
  void setStompDFXType(FXType fxType);
  void setStompXFXType(FXType fxType);
  void setStompModFXType(FXType fxType);

  void setStompAEnabled(bool enabled);
  void setStompBEnabled(bool enabled);
  void setStompCEnabled(bool enabled);
  void setStompDEnabled(bool enabled);
  void setStompXEnabled(bool enabled);
  void setStompModEnabled(bool enabled);
  void setDelayEnabled(bool enabled);
  void setReverbEnabled(bool enabled);

  void setBrowserModeBassValueText(const QString& value);
  void setBrowserModeMiddleValueText(const QString& value);
  void setBrowserModeTrebleValueText(const QString& value);
  void setBrowserModePresenceValueText(const QString& value);

  void setBrowserModeRigName(const QString& value);
  void setBrowserModeRigAuthor(const QString& value);
  void setBrowserModeAmpName(const QString& value);

  void setBrowserModeView(int view);

protected:
  void createSkin();
  void paintEvent(QPaintEvent*);
  void contextMenuEvent(QContextMenuEvent * cme);

  void setEnabled(QWidget& w, bool enabled);

private slots:
  void on_browserViewComboBox_currentIndexChanged(int index);

private:
  Ui::QToasterBrowserLCD *ui;

  QList<QPixmap> mSkinPixmaps;
  Color mColor;

  ICtxMenuProvider* mpCtxMenuProvider;
};

#endif // QTOASTERBROWSERLCD_H
