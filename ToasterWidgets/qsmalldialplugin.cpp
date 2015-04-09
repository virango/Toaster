#include "qsmalldial.h"
#include "qsmalldialplugin.h"

#include <QtPlugin>

QSmallDialPlugin::QSmallDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QSmallDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QSmallDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QSmallDialPlugin::createWidget(QWidget *parent)
{
  return new QSmallDial(parent);
}

QString QSmallDialPlugin::name() const
{
  return QLatin1String("QSmallDial");
}

QString QSmallDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QSmallDialPlugin::icon() const
{
  return QIcon();
}

QString QSmallDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QSmallDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QSmallDialPlugin::isContainer() const
{
  return false;
}

QString QSmallDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QSmallDial\" name=\"qSmallDial\">\n</widget>\n");
}

QString QSmallDialPlugin::includeFile() const
{
  return QLatin1String("qsmalldial.h");
}

