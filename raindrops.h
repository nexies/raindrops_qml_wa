#ifndef RAINDROPS_H
#define RAINDROPS_H

#include <QObject>

namespace raindrops
{
Q_NAMESPACE

    enum game_state
    {
        game_not_started = 0,
        game_running,
        game_paused,
        game_finished
    };
    Q_ENUM_NS(game_state);

    enum drop_type
    {
        drop_type_undefined = 0,
        normal_drop_type,
        super_drop_type,
        healing_drop_type
    };
    Q_ENUM_NS(drop_type);
};

#endif // RAINDROPS_H
