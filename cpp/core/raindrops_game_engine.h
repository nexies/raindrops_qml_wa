#ifndef RAINDROPS_GAME_ENGINE_H
#define RAINDROPS_GAME_ENGINE_H

#include <QObject>
#include <QList>
#include "raindrops.h"

namespace raindrops {

    class basic_drop;

    class game_engine : public QObject
    {
        Q_OBJECT
    private:

        Q_PROPERTY(int state READ game_state NOTIFY game_state_changed)
        Q_PROPERTY(int drops_missed READ drops_missed NOTIFY drops_missed_changed)
        Q_PROPERTY(int max_drops_missed READ max_drops_missed CONSTANT)
        Q_PROPERTY(int game_score READ game_score WRITE set_game_score NOTIFY game_score_schanged)
        Q_PROPERTY(QList<basic_drop *> drops_on_screen READ drops_on_screen NOTIFY drops_on_screen_changed)
        Q_PROPERTY(int difficulty_level READ difficulty_level WRITE set_difficulty_level NOTIFY difficulty_level_changed)

        void m_init ();

    public:
        explicit game_engine(QObject * parent = nullptr);

        int game_state() const;

        int drops_missed() const;
        int max_drops_missed() const;
        int game_score() const;
        void set_game_score(int newGame_score);
        QList<basic_drop *> drops_on_screen() const;
        int difficulty_level() const;
        void set_difficulty_level(int newDifficulty_level);

    protected slots:
        void spawn_raindrop ();

    public slots:
        void begin_game ();
        void pause_game (bool);
        void finish_game ();
        void drop_missed (basic_drop *);
        void process_answer (int);

    signals:
        void game_state_changed (int);
        void game_began ();
        void game_paused ();
        void game_unpased ();
        void game_finished ();
        void drops_missed_changed();
        void game_score_schanged();
        void drops_on_screen_changed();
        void difficulty_level_changed();

    private:
        int _state { game_not_started };
        int _drops_missed { 0 };
        int _max_drops_missed { 3 };
        int _game_score { 0 };
        QList<basic_drop *> _drops_on_screen;
        int _difficulty_level { 1 };
    };

}

#endif // RAINDROPS_GAME_ENGINE_H
