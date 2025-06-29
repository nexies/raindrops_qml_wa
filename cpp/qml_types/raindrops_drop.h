#ifndef RAINDROPS_DROP_H
#define RAINDROPS_DROP_H

#include <QQuickItem>
#include <QString>

#include "t_math_expression.h"
#include "raindrops.h"

namespace raindrops {

    class basic_drop : public QQuickItem
    {
        Q_OBJECT

        Q_PROPERTY(drop_type type READ type CONSTANT)
        Q_PROPERTY(QString expression READ expression CONSTANT)
        Q_PROPERTY(bool valid READ is_valid CONSTANT);
        Q_PROPERTY(QString error_str READ error_str CONSTANT);
        Q_PROPERTY(QString answer READ answer CONSTANT)

        void m_init();

    public:
        explicit basic_drop(const QString & p_expression, QQuickItem * p_parent = nullptr);
        virtual drop_type type() const;

        QString expression() const;
        QString answer() const;
        bool is_valid() const;
        QString error_str() const;
        QString hint () const;

    private:
        T_Math_Expression _math_expression;
        QString _answer;
        bool _valid;
        QString _error_str;
    };


    ///
    /// \brief The drop class
    ///  Обычная капелька, при введении правильного ответа исчезает
    class drop : public basic_drop
    {
        Q_OBJECT
    public:
        explicit drop (const QString & p_expression, QQuickItem * p_parent = nullptr) :
            basic_drop(p_expression, p_parent)
        {}

        virtual drop_type type () const override
        { return normal_drop_type; }
    };

    ///
    /// \brief The super_drop class
    /// Супер-капля. При введении правильного ответа уничтожает все капли на экране
    class super_drop : public basic_drop
    {
        Q_OBJECT
    public:
        explicit super_drop (const QString & p_expression, QQuickItem * p_parent = nullptr) :
            basic_drop(p_expression, p_parent)
        {}

        virtual drop_type type () const override
        { return super_drop_type; }
    };

    ///
    /// \brief The healing_drop class
    /// Лечащая капля. При уничтожении уменишает количество пропущенных в игре капель.
    class healing_drop : public basic_drop
    {
        Q_OBJECT
    public:
        explicit healing_drop (const QString & p_expression, QQuickItem * p_parent = nullptr) :
            basic_drop(p_expression, p_parent)
        {}

        virtual drop_type type () const override
        { return healing_drop_type; }
    };


}

#endif // RAINDROPS_DROP_H
