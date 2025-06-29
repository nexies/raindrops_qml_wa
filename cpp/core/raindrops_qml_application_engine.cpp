#include "raindrops_qml_application_engine.h"
#include "t_math_expression.h"
#include <QVariant>


namespace raindrops {

void qml_application_engine::m_init()
{
    qRegisterMetaType<T_Math_Expression>();
}

qml_application_engine::qml_application_engine() {}

}
