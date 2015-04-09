#include "qbigdial.h"
#include "qbigdialplugin.h"

#include <QtPlugin>

QBigDialPlugin::QBigDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QBigDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QBigDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QBigDialPlugin::createWidget(QWidget *parent)
{
  return new QBigDial(parent);
}

QString QBigDialPlugin::name() const
{
  return QLatin1String("QBigDial");
}

QString QBigDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QBigDialPlugin::icon() const
{
  return QIcon();
}

QString QBigDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QBigDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QBigDialPlugin::isContainer() const
{
  return false;
}

QString QBigDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QBigDial\" name=\"qBigDial\">\n</widget>\n");
}

QString QBigDialPlugin::includeFile() const
{
  return QLatin1String("qbigdial.h");
}

