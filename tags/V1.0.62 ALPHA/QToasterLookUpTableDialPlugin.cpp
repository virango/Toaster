#include "QToasterLookUpTableDial.h"
#include "QToasterLookUpTableDialPlugin.h"

#include <QtPlugin>

QToasterLookUpTableDialPlugin::QToasterLookUpTableDialPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QToasterLookUpTableDialPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QToasterLookUpTableDialPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QToasterLookUpTableDialPlugin::createWidget(QWidget *parent)
{
  return new QToasterLookUpTableDial(parent);
}

QString QToasterLookUpTableDialPlugin::name() const
{
  return QLatin1String("QToasterLookUpTableDial");
}

QString QToasterLookUpTableDialPlugin::group() const
{
  return QLatin1String("");
}

QIcon QToasterLookUpTableDialPlugin::icon() const
{
  return QIcon(":/resources/DialIcon.png");
}

QString QToasterLookUpTableDialPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QToasterLookUpTableDialPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QToasterLookUpTableDialPlugin::isContainer() const
{
  return false;
}

QString QToasterLookUpTableDialPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QToasterLookUpTableDial\" name=\"qToasterLookUpTableDial\">\n</widget>\n");
}

QString QToasterLookUpTableDialPlugin::includeFile() const
{
  return QLatin1String("QToasterLookUpTableDial.h");
}

