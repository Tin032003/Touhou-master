#if !defined(ENEMY_H_)
#define ENEMY_H_

#include "GameObject.h"
#include "Bullet.h"
#include "ImpTimer.h"

class Enemy{
public:
    Enemy();
    ~Enemy();

    void SetName(const int& name_){name = name_;};
    void SetType(const int& type_){ type = type_;};
    void SetPos(const double& x_, const double& y_) { x = x_; y = y_; };
    pair<double, double> GetPos() const { return {x , y}; };
    pair<double, double> GetSpeed() const {return {x_speed, y_speed} ;};

    void SetSpeed (const double& x_speed_, const double& y_speed_){ x_speed = x_speed_; y_speed = y_speed_;};
    void SetAngle(const double& angle_){ angle = angle_;};

    
    void SetRandomAngle(const int& st, const int& en);

    void HandleMove();

    void InitBullet();
    void HandleBullet(SDL_Renderer * screen);

private:
    int type;
    int name;

    double x, y;
    
    double x_speed, y_speed;

    double angle; // degree

    int num_bullet;
    double angle_bullet;

    vector<Bullet> shot;
    vector<Bullet> shot2;
    vector<Bullet> shot3;
    vector<Bullet> shot4;
    vector<Bullet> shot5;
    vector<Bullet> shot6;

    GameTime EnemyTime;

};



#endif // ENEMY_H_