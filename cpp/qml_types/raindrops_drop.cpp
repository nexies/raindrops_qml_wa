#include "raindrops_drop.h"

namespace raindrops {

    void basic_drop::m_init()
    {
        QString unit;
        QString error;
        auto doub = _math_expression.evaluate(_error_str, unit);
        if(!_error_str.isEmpty()) {
            _answer = "NO ANSWER";
            _valid = false;
        }
        else {
            _answer = QString("%1 %2").arg(QString::number(doub), unit).simplified();
            _valid = true;
        }
    }

    basic_drop::basic_drop(const QString &p_expression, QQuickItem *p_parent) :
        QQuickItem(p_parent),
        _math_expression { p_expression }
    {
        m_init();
    }

drop_type basic_drop::type() const
    {
        return drop_type_undefined;
    }

    QString basic_drop::expression() const
    {
        return _math_expression.str;
    }

    QString basic_drop::answer() const
    {
        return _answer;
    }

    bool basic_drop::is_valid() const
    {
        return _valid;
    }

    QString basic_drop::error_str() const
    {
        return _error_str;
    }

}
