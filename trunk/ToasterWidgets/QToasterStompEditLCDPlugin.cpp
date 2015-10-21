#include "QToasterStompEditLCD.h"
#include "QToasterStompEditLCDPlugin.h"

#include <QtPlugin>

QToasterStompEditLCDPlugin::QToasterStompEditLCDPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterStompEditLCDPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterStompEditLCDPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterStompEditLCDPlugin::createWidget(QWidget *parent)
{
  return new QToasterStompEditLCD(parent);
}

QString QToasterStompEditLCDPlugin::name() const
{
  return QLatin1String("QToasterStompEditLCD");
}

QString QToasterStompEditLCDPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterStompEditLCDPlugin::icon() const
{
  return QIcon();
}

QString QToasterStompEditLCDPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterStompEditLCDPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterStompEditLCDPlugin::isContainer() const
{
  return false;
}

QString QToasterStompEditLCDPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterLCD\" name=\"toasterStompEditLCD\">\n</widget>\n");
}

QString QToasterStompEditLCDPlugin::includeFile() const
{
  return QLatin1String("QToasterStompEditLCD.h");
}

