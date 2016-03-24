/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef QTOASTERLCD_H
#define QTOASTERLCD_H
#include <QWidget>
#include <QMap>
#include "ToasterWidgetsLib.h"
#include "Commons.h"

#ifdef _WIN32
#define ENABLED "background-color: rgb(50,50,50);%1;border-color: rgb(0, 0, 0);border-radius: 3px;padding-bottom: 2px;"
#define DISABLED "background-color: rgb(128,128,128);%1;border-color: rgb(0, 0, 0);border-radius: 3px;padding-bottom: 2px;"
#else
#define ENABLED "background-color: rgb(50,50,50);%1;border-color: rgb(0, 0, 0);border-radius: 3px;"
#define DISABLED "background-color: rgb(128,128,128);%1;border-color: rgb(0, 0, 0);border-radius: 3px;"
#endif

#define COLOR_STANDARD "color: rgb(208, 234, 222)"
#define COLOR_ORANGE   "color: rgb(227, 183, 159)"
#define COLOR_RED      "color: rgb(255, 128, 122)"
#define COLOR_YELLOW   "color: rgb(224, 224, 133)"
#define COLOR_CYAN     "color: rgb(0, 225, 225)"
#define COLOR_BLUE     "color: rgb(145, 145, 255)"
#define COLOR_PURPLE   "color: rgb(211, 132, 255)"
#define COLOR_WHITE    "color: rgb(209, 215, 222)"
#define COLOR_GREEN    "color: rgb(124, 233, 124)"

struct ICtxMenuProvider;

class TOASTERWIDGETS_EXPORT QToasterLCD : public QWidget
{
  Q_OBJECT
  Q_ENUMS(Color)
  Q_ENUMS(Page)
  Q_PROPERTY(Color color READ color WRITE setColor)
  Q_PROPERTY(Page currentPage READ currentPage WRITE setCurrentPage)
  Q_PROPERTY(Page maxPage READ maxPage WRITE setMaxPage)
public:
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

  enum Page
  {
    Page1 = 0,
    Page2 = 1,
    Page3 = 2,
    Page4 = 3,
    Page5 = 4,
    Page6 = 5
  };


  explicit QToasterLCD(QWidget *parent);
  ~QToasterLCD();

  Color color() const { return mColor; }
  Page currentPage() const { return mCurrentPage; }
  Page maxPage() const { return mMaxPage; }

  void setCtxMenuProvider(ICtxMenuProvider* ctxMenuProvider) { mpCtxMenuProvider = ctxMenuProvider; }

public slots:
  virtual void setColor(Color color);
  virtual void setCurrentPage(Page page);
  virtual void setMaxPage(Page page);

protected:
  void createSkin();
  void displayStompEnabled(QWidget& w, bool enabled);

  Color mColor;
  Page  mMaxPage;
  Page  mCurrentPage;

  ICtxMenuProvider* mpCtxMenuProvider;

  static QList<QPixmap> sSkinPixmaps;
  static QMap<Color, QString>  sColor2StyleSheetsMap;
  static QMap<FXType, QString> sFXType2ShortNameMap;
};




#endif // QTOASTERLCD_H
