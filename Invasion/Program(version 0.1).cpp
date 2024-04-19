#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <cstdlib>

#include "projectclass.h"

using namespace sf;
using namespace std;

void play(Interface &interface, gameovertext &GameOver, Texture &enemyTex, Player &player, Movement &playermovement, BulletsMovement &bulletsmovement, EnemiesMovement &enemiesmovement, Collision &collisionwindow, Event &event)
{

        //Player Part 
        if(player.HP>0){

            //Player Movement
            playermovement.motion(interface);
            
            //Player hpBar
            player.hpBar.textdisplay(player.GeneratePlayer.shape.getPosition().x,player.GeneratePlayer.shape.getPosition().y-player.hpBar.text.getGlobalBounds().height,player.HP,player.HPMax);
            
            //Player Movement Bounds
            collisionwindow.collisionwindow(interface);//interface linking
            
            
            //Bullets Part-----Under Control of Player Part

            //Bullets Update
            player.updatebullet();

            //Bullet movement
            bulletsmovement.motion(interface);//Linked by Interface

            //Enemies Part

            //Enemies Update
            interface.updateenemy.Updatetimer();//enemyspawntimer update
            interface.enemygenerate(&enemyTex);//generate new enemy
            
            //enemy Movement
            enemiesmovement.motion(interface);
            player.score.Update();//Player Score update
        }
    
        //Program Part : Display
        interface.draw(GameOver, event);

}



int main(){

    

    int MenuNumber = 1;

    srand(time(NULL));
    
    //Init Interface
    Interface interface(1200,900,"Invasion");

    //Menu
    Menu menu("Fonts/Dosis-Light.ttf");
    menu.textsetting(interface);

    //Init Background
    Texture FrontTexture;
    FrontTexture.loadFromFile("Textures/front (2).png");
    Texture Playground;
    Playground.loadFromFile("Textures/Background2.jpg");

    //Init Option
    Texture Option;
    Option.loadFromFile("Textures/Option.png");

    //Init ScoreText
    TextStyle scoretext("Fonts/Dosis-Light.ttf");
    scoretext.textsetting(20);
    
    //Init GameoverText
    gameovertext GameOver("Fonts/Dosis-Light.ttf");
    GameOver.textsetting(40);
    GameOver.textposition(interface.window.getSize().x,interface.window.getSize().y);
    
    //Init bullet Part 
    Texture bulletTex;
    bulletTex.loadFromFile("Textures/bullet.png");

    //Init Player Part
    Texture playerTex;
    playerTex.loadFromFile("Textures/ship.png");
    int score=0;
    int shootTimer=20;
    int bulletlimit=15;
    Player player(interface.window.getSize(),&playerTex,&bulletTex,score,&scoretext,"Fonts/Dosis-Light.ttf",shootTimer,bulletlimit);
    
    //Init Enemy Part
    Texture enemyTex;
    enemyTex.loadFromFile("Textures/enemy.png");
    int enemySpawnTimer=0;//will be passed to Interface class
    int enemySpawnTimerLimit=25;//will be passed to Interface class

    //Interface Linking Part
    interface.setplayer(&player);
    //interface.setenemy(enemies);
    interface.etimersetting(enemySpawnTimer,enemySpawnTimerLimit);

    
    //-----All under the control of Interface------

    //Init Movement
    Movement playermovement;//playermovement
    BulletsMovement bulletsmovement;//bulletsmovement
    EnemiesMovement enemiesmovement;//enemiesmovement
    
    //Init Collision 
    Collision collisionwindow;//playerbounds
    
    //Program Part
    
    while(interface.window.isOpen())
    {
        Event event;
        while(interface.window.pollEvent(event)) //Keep the window opened until clicking "x" button to quit
        { 
            
			if(event.type == Event::KeyReleased)    //To execute instruction in the bracket if the button is released from pressing
            {       
                
                if(event.key.code == Keyboard::Up) //Upward Movement Through Option
                {
                    if(player.HP==0){
                        GameOver.MoveUp();  //in Game Over Page
                    }
                    else
                        menu.MoveUp();  //in Menu Page
                }

                if(event.key.code == Keyboard::Down)//Downward Movement Through Option
                {
                    if(player.HP==0){
                        GameOver.MoveDown();//in Game Over Page
                    }
                    else
                        menu.MoveDown()//In Menu Page
                ;
                }

                if(event.key.code == Keyboard::Return)
                {
                    
                        if(menu.GetPressedItem() == 0)  
                        {
                            menu.setNumberMenu(1);  //Menu Page
                        }
                        else if(menu.GetPressedItem() == 1) 
                        {
                            menu.setNumberMenu(2);  //Option Page
                            if(event.key.code == Keyboard::Escape){//Escape from Option Page to Main Menu
                            menu.setNumberMenu(0);
                    }
                        }
                        else if(menu.GetPressedItem() == 2)//Exit
                        
                        interface.window.close();
                    
                        if(player.HP == 0)
                        {
                            if(GameOver.SelectedItemIndex == 0){//Game Over Menu Option: Retry
                                menu.reset(interface);
                                menu.resetSpeed(enemiesmovement);
                                menu.setNumberMenu(1);
                            }
                            else if(GameOver.SelectedItemIndex == 1){//Game Over Menu Option: Back to Main Menu
                                menu.reset(interface);
                                menu.resetSpeed(enemiesmovement);
                                menu.setNumberMenu(0);

                            }
                           
                        }
			    }
                
            }
			if(event.type == Event::Closed)
			    interface.window.close();
        }

            if(menu.NumberMenu() == 0)
            {
                
                menu.draw(interface,&FrontTexture); //Drawing Main Menu
            }
            if(menu.NumberMenu() == 1)
            {   //Background setting
                interface.setBackground(&Playground);
                
                play(interface, GameOver, enemyTex, player, playermovement, bulletsmovement, enemiesmovement, collisionwindow, event);  //Gameplay Program
                if(player.HP == 0)
                {
                    //menu.setNumberMenu(0);
                    //menu.reset(interface);
                    
                    
                }
            }
            if(menu.NumberMenu() == 2)//Drawing Option Page
            {
                interface.setBackground(&Option);
                interface.window.clear();
                interface.drawbackground();
                interface.window.display();
                if(event.key.code==Keyboard::Escape )
                    menu.setNumberMenu(0);
           
                

            }
    
    
    }
    return 0;
}