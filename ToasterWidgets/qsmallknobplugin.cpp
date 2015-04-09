#include "qsmallknob.h"
#include "qsmallknobplugin.h"

#include <QtPlugin>

QSmallKnobPlugin::QSmallKnobPlugin(QObject *parent)
  : QObject(parent)
{
  m_initialized = false;
}

void QSmallKnobPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
  if (m_initialized)
    return;

  // Add extension registrations, etc. here

  m_initialized = true;
}

bool QSmallKnobPlugin::isInitialized() const
{
  return m_initialized;
}

QWidget *QSmallKnobPlugin::createWidget(QWidget *parent)
{
  return new QSmallKnob(parent);
}

QString QSmallKnobPlugin::name() const
{
  return QLatin1String("QSmallKnob");
}

QString QSmallKnobPlugin::group() const
{
  return QLatin1String("");
}

QIcon QSmallKnobPlugin::icon() const
{
  return QIcon();
}

QString QSmallKnobPlugin::toolTip() const
{
  return QLatin1String("");
}

QString QSmallKnobPlugin::whatsThis() const
{
  return QLatin1String("");
}

bool QSmallKnobPlugin::isContainer() const
{
  return false;
}

QString QSmallKnobPlugin::domXml() const
{
  return QLatin1String("<widget class=\"QSmallKnob\" name=\"qSmallKnob\">\n</widget>\n");
}

QString QSmallKnobPlugin::includeFile() const
{
  return QLatin1String("qsmallknob.h");
}

