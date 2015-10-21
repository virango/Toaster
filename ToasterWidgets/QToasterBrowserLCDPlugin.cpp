#include "QToasterBrowserLCD.h"
#include "QToasterBrowserLCDPlugin.h"

#include <QtPlugin>

QToasterBrowserLCDPlugin::QToasterBrowserLCDPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterBrowserLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterBrowserLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterBrowserLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterBrowserLCD(parent);
}

QString QToasterBrowserLCDPlugin::name() const
{
  return QLatin1String("QToasterBrowserLCD");
}

QString QToasterBrowserLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterBrowserLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterBrowserLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterBrowserLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterBrowserLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterBrowserLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterLCD\" name=\"toasterBrowserLCD\">\n</widget>\n");
}

QString QToasterBrowserLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterBrowserLCD.h");
}

