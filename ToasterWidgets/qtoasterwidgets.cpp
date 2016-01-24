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
#include "qtoasterdialplugin.h"
#include "qtoasterenumdialplugin.h"
#include "QToasterBrowserLCDPlugin.h"
#include "QToasterStompEditLCDPlugin.h"
#include "QToasterTunerLCDPlugin.h"
//#include "qbigdialplugin.h"
//#include "qsmalldialplugin.h"
#include "qmulticolorledplugin.h"
//#include "qsmallknobplugin.h"
#include "qtoasterbuttonplugin.h"
#include "qchickenheaddialplugin.h"
#include "qtoasterwidgets.h"
#include "QToasterLookUpTableDialPlugin.h"

QToasterWidgets::QToasterWidgets(QObject *parent)
  : QObject(parent)
{
  m_widgets.append(new QToasterDialPlugin(this));
  m_widgets.append(new QToasterEnumDialPlugin(this));
  m_widgets.append(new QToasterLookUpTableDialPlugin(this));
  m_widgets.append(new QToasterBrowserLCDPlugin(this));
  m_widgets.append(new QToasterStompEditLCDPlugin(this));
  m_widgets.append(new QToasterTunerLCDPlugin(this));
//m_widgets.append(new QBigDialPlugin(this));
//  m_widgets.append(new QSmallDialPlugin(this));
  m_widgets.append(new QMultiColorLedPlugin(this));
//  m_widgets.append(new QSmallKnobPlugin(this));
  m_widgets.append(new QToasterButtonPlugin(this));
  m_widgets.append(new QChickenHeadDialPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> QToasterWidgets::customWidgets() const
{
  return m_widgets;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(qtoasterwidgetsplugin, QToasterWidgets)
#endif // QT_VERSION < 0x050000
