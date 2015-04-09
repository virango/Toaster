#include "qchickenheaddial.h"
#include "qchickenheaddialplugin.h"

#include <QtPlugin>

QChickenHeadDialPlugin::QChickenHeadDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QChickenHeadDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QChickenHeadDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QChickenHeadDialPlugin::createWidget(QWidget *parent)
{
  return new QChickenHeadDial(parent);
}

QString QChickenHeadDialPlugin::name() const
{
  return QLatin1String("QChickenHeadDial");
}

QString QChickenHeadDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QChickenHeadDialPlugin::icon() const
{
  return QIcon();
}

QString QChickenHeadDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QChickenHeadDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QChickenHeadDialPlugin::isContainer() const
{
  return false;
}

QString QChickenHeadDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QChickenHeadDial\" name=\"qChickenHeadDial\">\n</widget>\n");
}

QString QChickenHeadDialPlugin::includeFile() const
{
  return QLatin1String("qchickenheaddial.h");
}

