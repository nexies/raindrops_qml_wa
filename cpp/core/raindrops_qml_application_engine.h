#ifndef RAINDROPS_QML_APPLICATION_ENGINE_H
#define RAINDROPS_QML_APPLICATION_ENGINE_H

#include <QQmlApplicationEngine>

namespace raindrops {

class qml_application_engine : public QQmlApplicationEngine
{
    void m_init ();

public:
    qml_application_engine();
};

}

#endif // RAINDROPS_QML_APPLICATION_ENGINE_H
