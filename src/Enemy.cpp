#include "Enemy.h"

Enemy::Enemy(){
    EnemyTime.Start();
}

Enemy::~Enemy(){
    
}

void Enemy::InitBullet(){

    num_bullet = 3;
// Shot1
    for(int i = 0 ; i < 360 ; i += 6){
        Bullet b;

        b.SetPos(x, y);
        b.SetAngle(i);
        b.SetSpeed(1,1);
        b.SetType(b.VECTOR);

        shot.push_back(b);
        
    }

// 
}

void Enemy::HandleBullet(SDL_Renderer * screen){
    EnemyTime.Update();

    Object draw;
    draw.LoadImage(screen, "res/img/enemy/b_00.png");
    for(auto &x : shot){
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }

// Shot2
/*
    if (10 <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= 20 ){
        if (EnemyTime.GetSeconds()%1 == 0 and EnemyTime.CheckSeconds(60)) {
            Bullet b;

            b.SetPos(x, y);
            b.SetAngle(18 * (EnemyTime.GetSeconds() - 10));
            b.SetSpeed(1,1);
            b.SetType(b.VECTOR);
            shot2.push_back(b);
        }
    }     
    for(auto &x : shot2){
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }
    */

// Shot3
/*
    if (10 <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= 20){
        if (EnemyTime.GetSeconds()%1 == 0 and EnemyTime.CheckSeconds(60)){
            for (int i = 80; i <= 100; i += 10) {
                Bullet b;

                b.SetPos(x, y);
                b.SetAngle(i);
                b.SetSpeed(1,1);
                b.SetType(b.VECTOR);
                shot3.push_back(b);
            }
        }
    }

    for(auto &x : shot3){
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    } */
//Shot 4
/*
    if (5 <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= 15 ){
        if (EnemyTime.GetSeconds()%1 == 0 and EnemyTime.CheckSeconds(60)) {
            Bullet b;

            b.SetPos(x, y);
            b.SetAngle(18 * (EnemyTime.GetSeconds() - 5));
            b.SetSpeed(1,1);
            b.SetType(b.VECTOR);
            shot4.push_back(b);

            double base = 15;

            double angle_radian = 18.0 * (EnemyTime.GetSeconds() - 5)/180.0 * PI;
            

            b.SetPos(x + sin(angle_radian) * base, y - cos(angle_radian) * base);
            b.SetAngle(18 * (EnemyTime.GetSeconds() - 5));
            b.SetSpeed(1,1);
            b.SetType(b.VECTOR);
            shot4.push_back(b);
        }
    }     
    for(auto &x : shot4){
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }
*/

//Shot5
/*
    if (5 == EnemyTime.GetSeconds() and EnemyTime.CheckSeconds(60)) { 
        for(int i = 0 ; i < 360 ; i += 6){
            Bullet b;

            b.SetPos(x, y);
            b.SetAngle(i);
            b.SetSpeed(1,1);
            b.SetType(b.VECTOR);

            shot.push_back(b);
            
            double base = 15;

            double angle_radian =i/180.0 * PI;
                

            b.SetPos(x + sin(angle_radian) * base, y - cos(angle_radian) * base);
            b.SetAngle(i);
            b.SetSpeed(1,1);
            b.SetType(b.VECTOR);
            shot5.push_back(b);
        }
    }
    for(auto &x : shot5){
        x.HandleMove();
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }
    */
//Shot6
    if (5 <= EnemyTime.GetSeconds() and EnemyTime.GetSeconds() <= 15 ){ 
        if (EnemyTime.GetSeconds()%3 == 0 and EnemyTime.CheckSeconds(60)) {
            angle_bullet = rand() % (180 - 0 + 1) + 0;
            num_bullet = 3;
        }
	 	if (EnemyTime.CheckSeconds(20) and num_bullet){
	 		Bullet b;

            b.SetPos(x, y);
            b.SetAngle(angle_bullet);
            b.SetSpeed(2,2);
            b.SetType(b.VECTOR);
            shot6.push_back(b);

            num_bullet--;
	 	}

    }
    for(auto &x : shot6){
        x.HandleMove();           
        draw.SetRect(x.GetPos().fi, x.GetPos().se);
        draw.Render(screen);
    }
}