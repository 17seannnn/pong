#ifndef TWO_PLAYERS_STATE
#define TWO_PLAYERS_STATE

#include "Player.h"
#include "Ball.h"

#include "GameState.h"

class TwoPlayersState : public GameState {
    Ball* m_pBall;
    Player* m_pPlayer1;
    Player* m_pPlayer2;

    int m_score1, m_score2;
public:
    TwoPlayersState();
    ~TwoPlayersState() {}

    virtual void Update();
    virtual void Render();
private:
    void DrawScores();
};

#endif
