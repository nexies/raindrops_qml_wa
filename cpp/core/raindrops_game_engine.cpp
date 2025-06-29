#include "raindrops_game_engine.h"

namespace raindrops
{

void game_engine::m_init()
{
    _state = game_not_started;
    emit game_state_changed(_state);
    _drops_missed = 0;
    emit drops_missed_changed();
    _max_drops_missed = 0;
    set_game_score(0);
    qDeleteAll(_drops_on_screen);
    _drops_on_screen.clear();
    set_difficulty_level(1);
}

game_engine::game_engine(QObject *parent)
{
    m_init ();
}

void game_engine::spawn_raindrop()
{

}

void game_engine::begin_game()
{

}

void game_engine::pause_game(bool)
{

}

void game_engine::finish_game()
{

}

void game_engine::drop_missed(basic_drop *)
{

}

void game_engine::process_answer(int)
{

}

int game_engine::game_state() const
{
    return _state;
}

int game_engine::drops_missed() const
{
    return _drops_missed;
}

int game_engine::max_drops_missed() const
{
    return _max_drops_missed;
}

int game_engine::game_score() const
{
    return _game_score;
}

void game_engine::set_game_score(int newGame_score)
{
    if (_game_score == newGame_score)
        return;
    _game_score = newGame_score;
    emit game_score_schanged();
}

QList<basic_drop *> game_engine::drops_on_screen() const
{
    return _drops_on_screen;
}

int game_engine::difficulty_level() const
{
    return _difficulty_level;
}

void game_engine::set_difficulty_level(int newDifficulty_level)
{
    if (_difficulty_level == newDifficulty_level)
        return;
    _difficulty_level = newDifficulty_level;
    emit difficulty_level_changed();
}

}
