#include "Game.h"


void Game::load(){
    
    /* Load Game Object */{   
        GameBg.LoadImage(screen, "res/img/background.jpg");
        GameBg2.LoadImage(screen, "res/img/bg.png");

        for(int i = 0 ; i < 9 ; i++){
            string id = to_string(i);
            if(i < 10) id = '0' + id;
            string path = "res/img/bullet/b_" +  id + ".png";
            shot_img[i].LoadImage(screen, path);
        }
    }
    /* Load Character */{
        Hakurei.Set(8 , 5);
        Hakurei.SetPos(SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT - 200);
        Hakurei.Load(screen, "hakurei");
    }
    /* Load Enemy */{
        for(int i = 0 ; i < 2 ; i++){
            string path = "res/img/enemy/enemy_";
            string tmp = to_string(i);
            if(i < 10) tmp = '0' + tmp;

            enemy_img[i][0].LoadImage(screen, path + tmp + ".png");
            enemy_img[i][1].LoadImage(screen, path + tmp + "_left.png");
            enemy_img[i][2].LoadImage(screen, path + tmp + "_right.png");
            enemy_img[i][3].LoadImage(screen, path + tmp + "_attack_left.png");
            enemy_img[i][4].LoadImage(screen, path + tmp + "_attack_right.png");
        }

// 10 Enemy, co chay vong tron lan luot.    
/*    
    {
        Enemy Test;
        Enemy Test2;
        Enemy Test3;
        Enemy Test4;
        Enemy Test5;
        Enemy Test6;
        Enemy Test7;
        Enemy Test8;
        Enemy Test9;
        Enemy Test10;

        Test.SetPos(450,-100);
        Test2.SetPos(500,-100);
        Test3.SetPos(450,-70);
        Test4.SetPos(500,-70);
        Test5.SetPos(475,-40);
        Test6.SetPos(700,-100);
        Test7.SetPos(750,-100);
        Test8.SetPos(700,-70);
        Test9.SetPos(750,-70);
        Test10.SetPos(725,-40);

        Enemy ArrTest[10] = {Test,Test2,Test3,Test4,Test5,Test6,Test7,Test8,Test9,Test10};

        for (int i = 0; i < 10; i++) {
            ArrTest[i].Set(4, 12, 2);
            ArrTest[i].SetName(1);
            ArrTest[i].Load(enemy_img[1]);
            ArrTest[i].SetFitAttackFrame(11.0, 0.0);
            ArrTest[i].InitBullet(0 , 20, 1);
        }

        for (int i = 0; i < 10; i++) ArrTest[i].SetOrbit(2,0,{2,2},-0.01,90);

        for (int i = 0; i < 5; i++) ArrTest[i].SetOrbit(5,0,{1,1},0,60);
        for (int i = 5; i < 10; i++) ArrTest[i].SetOrbit(5,0,{1,1},0,120);

        for (int i = 0; i < 10; i++) ArrTest[i].SetOrbit(7,0,{0,0},0,0);
        
        int tmp = 8, tmp2 = 0;
        for (int j = -90 ; j < 270 ; j+=5) {
            for (int i = 0; i < 5; i++) ArrTest[i].SetOrbit(tmp+i, tmp2, {3,1}, 0,  j);
            for (int i = 5; i < 10; i++) ArrTest[i].SetOrbit(tmp+i-5, tmp2, {3,1}, 0,  j + 180);
            tmp2 += 5;
            if(tmp2 >= 60){
            tmp++;
            tmp2 = 0;
            }
        }

        for (int i = 0; i < 5; i++) ArrTest[i].SetOrbit(tmp+i,tmp2,{0,0},0,0);
        for (int i = 5; i < 10; i++) ArrTest[i].SetOrbit(tmp+i-5,tmp2,{0,0},0,0);

        for (int i = 0; i < 10; i++) enemy.push_back(ArrTest[i]);
*/
    // Stage 1

    // SCENE TEST
    /*
        for(int i = 500 ; i <= 700 ; i += 200){

            Test.SetPos(i , 200);
            Test.Set(4, 12, 2);
            Test.SetName(1);
            Test.Load(enemy_img[1]);
            Test.SetFitAttackFrame(11.0, 0.0);
            Test.InitBullet(0 , 20, 1);  

            Test.SetOrbit(2,0,{2,2},-0.01, 90);

            Test.SetOrbit(5, 0,{2,2}, 0, -90);
            Test.SetOrbit(7, 0,{0,0}, 0, 90);


            // Hinh elip //
            int tmp = 8, tmp2 = 0;
            for(int j = -90 ; j < 270 ; j+=5){
                if(i == 500) Test.SetOrbit(tmp, tmp2, {3,1}, 0,  j);
                if(i == 700) Test.SetOrbit(tmp, tmp2, {3,1}, 0,  j + 180);
                tmp2 += 5;
                if(tmp2 >= 60){
                    tmp++;
                    tmp2 = 0;
                }
            }
            Test.SetOrbit(tmp, tmp2, {0,0}, 0, 180);

            enemy.push_back(Test);
        }
    */
    


        // Real //
    }
 
    }
}

void Game::display(){
    GameBg.Render(screen);
    SDL_SetRenderDrawColor(screen, 0, 0, 0 , 100);
    SDL_RenderFillRect(screen, &MainBoard);

    Hakurei.Show(screen);
    Hakurei.HandleBullet(enemy);

    /* Display Enemy */
    HandleEnemy();

    /* Display Bullet and Shot */{
        for(auto &x : shot){
            x.HandleMove();
            int w = shot_img[x.GetName()].GetRect().w;
            int h = shot_img[x.GetName()].GetRect().h;

            shot_img[x.GetName()].SetRect(x.GetPos().fi - w / 2, x.GetPos().se - h / 2);
            shot_img[x.GetName()].Render(screen);
        }
        vector<Bullet> tmp;

        for(auto &s : shot){
            int w = shot_img[s.GetName()].GetRect().w;
            int h = shot_img[s.GetName()].GetRect().h;
            int x = s.GetPos().fi;
            int y = s.GetPos().se;

            if (x + w <= BOARD_X or y + h <= BOARD_Y or x >= BOARD_LIMITED_X or y >= BOARD_LIMITED_Y){
                continue;
            }else
                tmp.push_back(s);
        
        shot = tmp;
            
        }
    }

    GameBg2.Render(screen);

}

void Game::HandleEnemy(){

    for(auto &x : enemy){
        x.Show(screen, enemy_img[x.GetName()][x.GetStatus()]);
        x.HandleMove();
        x.HandleBullet(shot);
    }
}


void Game::HandleInput(SDL_Event e){
        if(e.type == SDL_KEYDOWN){

            switch (e.key.keysym.sym){
            case SDLK_RIGHT:
                Key.insert(K_RIGHT);
                Hakurei.SetMove(true);
                Hakurei.SetStatus(Hakurei.RIGHT);
                Hakurei.Move();

                
                break;
            case SDLK_LEFT:
                Key.insert(K_LEFT);
                Hakurei.SetMove(true);
                Hakurei.SetStatus(Hakurei.LEFT);
                Hakurei.Move();

                
                break;
            case SDLK_UP:
                Key.insert(K_UP);
                Hakurei.SetMove(true);
                Hakurei.SetStatus(Hakurei.UP);
                Hakurei.Move();
                break;
            case SDLK_DOWN:
                Key.insert(K_DOWN);
                Hakurei.SetMove(true);
                Hakurei.SetStatus(Hakurei.DOWN);
                Hakurei.Move();
                break;

            case SDLK_z:
                Hakurei.Shoot(true);
                break;
            
            default:
                break;
            }
            
        } 
        if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym){
            case SDLK_RIGHT:
                Key.erase(K_RIGHT);
                break;
            case SDLK_LEFT:
                Key.erase(K_LEFT);
                break;
            case SDLK_UP:
                Key.erase(K_UP);
                break;
            case SDLK_DOWN:
                Key.erase(K_DOWN);
                break;

            case SDLK_z:
                Hakurei.Shoot(false);
                break;

            default:
                break;
            }
            if (Key.empty()){
                Hakurei.SetMove(false);
                Hakurei.SetStatus(Hakurei.IDLE);
            }
            else{
                Hakurei.SetStatus(*Key.begin() + 1);
                Hakurei.Move();
            }
        }
}