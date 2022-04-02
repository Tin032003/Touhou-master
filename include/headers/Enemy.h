#if !defined(ENEMY_H_)
#define ENEMY_H_

#include "GameObject.h"
#include "Bullet.h"
#include "ImpTimer.h"

struct Plan{
    int start_time, end_time; // time
    int type;
    Plan(int start_time, int end_time, int type = 0){
        this->start_time = start_time;
        this->end_time = end_time;
        this->type = type;
    }
};

struct Orbit{
    double st; // time
    int step;   // frame

    double x_speed, y_speed;
    double angle;
    double a;

    Orbit(double st, int step,  double x_speed, double y_speed, double a, double angle){
        this->st = st;
        this->step = step;
        this->x_speed = x_speed;
        this->y_speed = y_speed;
        this->a = a;
        this->angle = angle;
    }
};

class Enemy{
public:
    // 0:    ENEMY_IDLE,
    // 1:    ENEMY_LEFT,
    // 2:    ENEMY_RIGHT,
    // 3:   ENEMY_ATTACK_LEFT
    // 4:   ENEMY_ATTACK_RIGHT
    enum{
        ENEMY_IDLE,
        ENEMY_LEFT,
        ENEMY_RIGHT,
        ENEMY_ATTACK_LEFT,
        ENEMY_ATTACK_RIGHT
    };

    Enemy();
    ~Enemy();

    void SetName(const int& name_){name = name_;};
    void SetType(const int& type_){ type = type_;};
    void SetPos(const double& x_, const double& y_) { x = x_; y = y_; };
    pair<double, double> GetPos() const { return {x , y}; };
    pair<double, double> GetCenterPos() const { return {center_x, center_y}; };

    void SetSpeed (const double& x_speed_, const double& y_speed_){ x_speed = x_speed_; y_speed = y_speed_;};
    void SetAngle(const double& angle_){ angle = angle_;};

    
    void SetRandomAngle(const int& st, const int& en);

    void InitBullet(int start_time, int end_time, int type);
    void HandleBullet(vector<Bullet> & shot);
    void MakeBullet(vector<Bullet> & shot, int ,int , int);

    void Set(int number_frames_, int time_per_frame_, int number_frame_attack_ = 0){
        number_frames = number_frames_;
        number_frame_attack = number_frame_attack_;

        if(number_frame_attack == 0) number_frame_attack = number_frames;

        time_per_frame = time_per_frame_;
    }
    void Load(Object * img){
        {
        // string path = "res/img/enemy/enemy_";
        // img[0].LoadImage(screen, path + id + ".png");
        // img[1].LoadImage(screen, path + id + "_left.png");
        // img[2].LoadImage(screen, path + id + "_right.png");
        }
        
        

        for(int i = 0 ; i < 5 ; i++){
            sizeImg[i] = img[i].GetRect();

            int imageWidth =sizeImg[i].w;
            int imageHeight = sizeImg[i].h;
            int frameWidth = imageWidth / number_frames;
            for(int k = 0 ; k < number_frames ; k++){
                frame_clip[i][k].x = k * frameWidth;
                frame_clip[i][k].y = 0;
                frame_clip[i][k].w = frameWidth;
                frame_clip[i][k].h = imageHeight;
            }
        }
    }
    void Update(){
        center_x = (x + sizeImg[current_status].w / number_frames + x) / 2;
        center_y = (y + sizeImg[current_status].h + y) / 2;

        if(current_status == ENEMY_LEFT or current_status == ENEMY_RIGHT)
            if(x_speed == 0 and y_speed == 0) 
                current_status = ENEMY_IDLE;

        EnemyTime.Update();
        time_count++;
        if(time_count % time_per_frame == 0){
            if(current_status == ENEMY_ATTACK_LEFT or current_status == ENEMY_ATTACK_RIGHT){
                current_frame ++;
                current_frame %= number_frame_attack;
                if(current_frame == 0) time_attack ++;
                if(time_attack == 2){
                    current_status -= 2;
                    current_frame = 0;
                }
            }
            if(current_status == ENEMY_LEFT or current_status == ENEMY_RIGHT){
                current_frame ++;
                current_frame %= number_frames;
            }

            if(current_status == ENEMY_IDLE){
                current_frame ++;
                current_frame %= number_frames;
            }

        }
   
    }
    void Show(SDL_Renderer * screen, Object& g){
        Update();

        SDL_Texture* p_object = g.GetObject();
        SDL_Rect rect = g.GetRect();
        SDL_Rect renderquad;

        if(current_status == ENEMY_ATTACK_LEFT or current_status == ENEMY_ATTACK_RIGHT)
            renderquad = { int(x - fit_attack_frame_x) , int(y - fit_attack_frame_y) , rect.w / number_frames, rect.h };
        else 
            renderquad = { int(x) , int(y) , rect.w / number_frames, rect.h };

        if(current_frame != -1)
            SDL_RenderCopy(screen, p_object, &frame_clip[current_status][current_frame], &renderquad);
        else
            SDL_RenderCopy(screen, p_object, &frame_clip[current_status][0], &renderquad);
    }

    int GetStatus() const { return current_status; };
    int GetName() const { return name; };

    void SetA(const double& _a){a = _a;};
    double GetA() const { return a; };


    void SetOrbit(double st, int step, pair<double,double> v, double a, double angle){
        orbit.push_back(Orbit(st, step,v.fi, v.se, a, angle));
    };
    void HandleMove();

    void ResetAttack(){
        time_attack = 0;
        current_status = current_direct + 2;
        current_frame = -1;
    }

    void SetFitAttackFrame(double x, double y){
        fit_attack_frame_x = x;
        fit_attack_frame_y = y;
    }

private:
    int type;
    int name;

    double x, y;
    double center_x, center_y;
    
    double x_speed, y_speed;
    double a;

    double angle; // degree

    /* Enemy Display */
    SDL_Rect sizeImg[20];

    int current_status; 
    int current_direct;
    int current_frame;
    int number_frames;
    int time_count;
    int time_per_frame;
    SDL_Rect frame_clip[10][20];
    int number_frame_attack;
    int time_attack;

    double fit_attack_frame_x;
    double fit_attack_frame_y;


    GameTime EnemyTime;
    /* Enemy move */
    bool is_move;
    bool num_bullet;

    vector<Plan> plan;

    vector<Orbit> orbit;


    int HP;
    bool is_deleted = 0;


};



#endif // ENEMY_H_
