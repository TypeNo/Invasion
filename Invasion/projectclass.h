#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <cstdlib>

using namespace sf;
using namespace std;

//Used to generate Physical Appearance of the object of Player, Enemy and Bullet Classes
class Generate{
    public:
    //variables
        Sprite shape;//Composition to the in-built class of SFML Library:Sprite
        Vector2f pos;
        Vector2u windowSize;
        Texture* texture;//Aggregation to the in-built class of SFML Library:Texture
        
    //Constructor-------

    //Player Case 
    Generate(Texture* t,int y){
        texture=t;
        shape.setTexture(*texture);
        shape.setScale(0.3f,0.3f);
        float positiony=y/2; 
        shape.setPosition(0,positiony);
    }
    
    //Bullets Case
    Generate(Texture *t,Vector2f p){
        texture=t;
        shape.setTexture(*texture);
        pos=p;
        shape.setScale(0.07f,0.07f);
        shape.setPosition(pos);
    }
    
    //Enemy Case
    Generate(Texture* t,Vector2u p){
        texture=t;
        windowSize=p;
        shape.setTexture(*texture);
        shape.setScale(0.1f,0.1f);
        shape.setPosition(windowSize.x-shape.getGlobalBounds().width,rand()%(int)(windowSize.y-shape.getGlobalBounds().height));

    }
    
    //method function
    /*void bullettexturesetting(){

    }
    int GPS(){
    }
    void enemytexturesetting(){};

    int bound(){

    }*/
};

//Used as timer for Bullets Update and Enemies Update
class Timer{
    //variables
    public:
    int timer;

    //constructor
    Timer(int t):timer(t){}
    //method function

};

//Used to control the process of updating Bullets and Enemies
class UpdateControl:public Timer{   //Inheritance to the Timer class
    public:
    //variables
    int limit;

    //constructor
    UpdateControl(int t,int l):Timer(t),limit(l){ 
    }

    //method function
    void Updatetimer()//Update timer
    {
        if(timer<limit)
        timer++;
    }
    void reset(){//Reset timer
        timer=0;
    
    }

};

class Bullets{
    public:
    //variables
    Generate GenerateBullet;//Composition to Generate class
    Texture* texture;//Aggregation to in-built class of SFML Library : Texture
    
     //Constructor
     Bullets(Texture* t,Vector2f p):GenerateBullet(t,p){}
     
     //method function
     //void Erase(){}

     ~Bullets(){}



};

//Used for font style setting
class FontStyle{
    public:
    //variables
    Font font;//Composition to in-built class of SFML Library : Font
    string Source;//Used to determine textstyle
    
    //constructor
    FontStyle(string s):Source(s){font.loadFromFile(Source);}

};


//Used for Text appearance setting------------

//Settung for Displaying Score 
class TextStyle:public FontStyle{   //Inheritance to FontStyle Class
    public:
    //variables
    Text text;//Composition to in-built class of SFML Library : Text

    //constructor
    TextStyle(string s):FontStyle(s){
    }
    void virtual textsetting(int size){ //used for adjusting text setting //virtual method function
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(Color::White);
        text.setPosition(10.f,10.f);
    }
    
};


//Setting for Displaying GAMEOVER
class gameovertext:public TextStyle{    //Polymorphism to TextStyle class
    public:
    //variable
    int SelectedItemIndex;
    int No_Option;
    Text option[2];
    //constructor
    gameovertext(string s):TextStyle(s){
        SelectedItemIndex = 0;
    }

    //method function:Polymorphism
    void textsetting(int size)//Positiony=window.getSize().y/2
    {
    text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(Color::Red);
	text.setString("GAME OVER!");

    option[0].setFont(font);
    option[0].setCharacterSize(size/2);
    option[0].setFillColor(Color::Red);
    option[0].setString("Retry");
    
    option[1].setFont(font);
    option[1].setCharacterSize(size/2);
    option[1].setFillColor(Color::White);
    option[1].setString("Back to Menu");

    }

    void textposition(int Positionx,int Positiony){     //setting the position of appearance of GAMEOVER
    text.setPosition(Positionx/2, Positiony/(3+1)*1);
    option[0].setPosition(Positionx/2, Positiony/(3+1)*2);
    option[1].setPosition(Positionx/2,Positiony/(3+1)*3);

    }

    void MoveUp(){  //Option Menu Upward Movement
        if(SelectedItemIndex-1>=0){
            option[SelectedItemIndex].setFillColor(Color::White);
            SelectedItemIndex--;
            option[SelectedItemIndex].setFillColor(Color::Red);
        }
    }

     void MoveDown(){      //Option Menu Downward Movement
        if(SelectedItemIndex + 1 < 2){
            option[SelectedItemIndex].setFillColor(Color::White);
            SelectedItemIndex++;
            option[SelectedItemIndex].setFillColor(Color::Red);
        }
    }

    int GetPressedItem(){return SelectedItemIndex;}     //Pressing the option to choose








    
};

//Setting for HPBar text
class hpText:public TextStyle{  //Polymorphism to TextStyle Class
    public:
    //constructor
    hpText(string s):TextStyle(s){}
    hpText():TextStyle("Fonts/PixellettersFull.ttf"){}

    //member function
    void textsetting(int size){
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(Color::White);

    }
    void textdisplay(int positionx,int positiony,int HP,int HPMax){//Setting for Displaying HPBar of Enemy and Player
        text.setPosition(positionx,positiony);
        text.setString(to_string(HP)+"/"+to_string(HPMax));

    }
};

/*class ehpText{
    public:
    //variable
    Text text;
    Font font;
	//constructor
    ehpText(){
    font.loadFromFile("Fonts/Dosis-Light.ttf");
    text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(Color::White);
    }
    //member function
    void textdisplay(int px,int py,int HP,int HPMax){
        text.setPosition(px,py);
        text.setString(to_string(HP)+"/"+to_string(HPMax));

    }
    
};*/

//Update Score;
class Score{    //Aggregation to TextStyle Class
    public:
    //variables
    int score;
    TextStyle* textstyle;
    //constructor
    Score(int s,TextStyle* ts):score(s),textstyle(ts){ }
    //method function
    void Update(){  //Update Player Score
       textstyle->text.setString ("Score: "+to_string(score));  
    }
};

class Player{
    public:
    //variables
        Generate GeneratePlayer;    //Composition to Generate Class
        int HP;
        int HPMax;
        vector<Bullets>bullets;     //Composition to Bullet Class
        UpdateControl bullettimer;  //Composition to UpdateControl Class
        hpText hpBar;               //Composition to hpText Class
        Score score;                //Composition to Score Class
        Texture* bullettex;         //Aggregation to Texture Class
       
        //Collision collision;
        //Interface* window; 

    //constructor
    Player(Vector2u pos,Texture* t,Texture* b,int s,TextStyle* ts,string hp,int spawntimer,int limit):GeneratePlayer(t,pos.y),bullettex(b),score(s,ts),hpBar(hp),bullettimer(spawntimer,limit){
        HPMax=10;
        HP=HPMax;
        hpBar.textsetting(12);
    }

    //member function
    void updatebullet(){//Update Bullets
        bullettimer.Updatetimer();
        if(Mouse::isButtonPressed(Mouse::Left)&&bullettimer.timer>=bullettimer.limit)
        {
            bullets.push_back(Bullets(bullettex,GeneratePlayer.shape.getPosition()));
            bullettimer.reset();
            
        }
    }

    ~Player(){}
};

class Enemy{
    public:
    //variable
    Generate GenerateEnemy; //Composition to Generate Class
    int HP;
    int HPMax;
    hpText HPBar;   //Composition to hpText Class
    //ehpText ehpbar;
    //Timer timer;
    //OnhitCollision EnemyOnhit ;
    //Bullets* bullet;

    //Constructor
    Enemy(Texture* t,Vector2u p,string s):GenerateEnemy(t,p),HPBar(s){
        HPMax= (rand()%3+1);
        HP=HPMax;
        HPBar.textsetting(12);
    }
    
    /*Enemy(Texture* t,Vector2u p):GenerateEnemy(t,p),HPBar(){
        HPMax= rand()%3+1;
        HP=HPMax;
        HPBar.textsetting(12);
        

    }*/
    
    ~Enemy(){
        
    }

};


class Interface{
    public:
    //variables
    RenderWindow window;    //Composition to in-built class of SFML : RenderWindow
    Player* player;         //Aggregation to Player Class
    vector<Enemy> enemies;  //Composition to Enemy Class
    TextStyle* scoretext;   //Aggregation to TextStyle Class
    gameovertext* Gameovertext;     //Aggregation to gameovertext class
    UpdateControl updateenemy;      //Composition to UpdateControl class
    Texture* backgroundtex;         //Aggregation to in-built class of SFML :Texture

    

    //constructor
    Interface(int x,int y,string z,int t=0,int l=0):window(VideoMode(x,y),z,Style::Default),updateenemy(t,l){window.setFramerateLimit(60);}
    
    //member function
    void setplayer(Player* p){player=p;}//Link to Player
    
    //void setenemy(vector<Enemy>&e){enemies=e;}
    //void setscoretext(TextStyle* t){}
    //void setGameoverText(gameovertext* t){}
    //void checkingwindow(){}
    
    void etimersetting(int timer,int limit){//Enemy Spawn Timmer 
        updateenemy.timer=timer;
        updateenemy.limit=limit;
    }
    void enemygenerate(Texture* enemyTex){//The Process of Update Enemies
        if(updateenemy.timer>=updateenemy.limit){
            enemies.push_back(Enemy(enemyTex,window.getSize(),"Fonts/Dosis-Light.ttf"));
            //enemies.push_back(Enemy(enemyTex,window.getSize()));
            
            updateenemy.reset();
        }
    }

    void setBackground(Texture* t){ //Setting the background
        backgroundtex=t;
    }
    
    void drawbackground(){      //Drawing the background
        Sprite background;
        background.setTexture(*backgroundtex);
        //background.setScale(0.6f,0.835f);
        window.draw(background);

    }
    
   
    void draw(gameovertext GAMEOVER, Event &event){//Program Part:Drawing
        window.clear();
        //Background
        drawbackground();
        

        //Player
        window.draw(player->GeneratePlayer.shape);

        for(size_t i=0;i< player->bullets.size();i++){
            window.draw(player->bullets[i].GenerateBullet.shape);
        }
    
        //Bullets
        for(size_t i=0;i<player->bullets.size();i++){
            window.draw(player->bullets[i].GenerateBullet.shape);
        }

        //Enemy
        for (size_t i=0;i<enemies.size();i++){
            enemies[i].HPBar.textsetting(15);
            int px=enemies[i].GenerateEnemy.shape.getPosition().x;
            int y=enemies[i].GenerateEnemy.shape.getPosition().y;
            int height=enemies[i].HPBar.text.getGlobalBounds().height;
            int py=y-height;
            int HP=enemies[i].HP;
            int HPMax=enemies[i].HPMax;
           enemies[i].HPBar.textdisplay(px,py,HP,HPMax);
           window.draw(enemies[i].HPBar.text);
           window.draw(enemies[i].GenerateEnemy.shape);
        }
        //UI
        window.draw(player->score.textstyle->text);
        window.draw(player->hpBar.text);
        if(player->HP<=0)
        {
            window.draw(GAMEOVER.text);
            for(int i=0;i<2;i++){
                window.draw(GAMEOVER.option[i]);
            }


                /*if(event.type == Event::KeyReleased)
                {       
                    if(event.key.code == Keyboard::Up)
                    {
                    GAMEOVER.MoveUp();
                    }

                    if(event.key.code == Keyboard::Down)
                    {
                    GAMEOVER.MoveDown();
                    }
                }*/
            
        }
    window.display();
    }
};


class Collision{   
    public:
    //method function
    void collisionwindow(Interface& interface,size_t i=0){//Player Movement Bound
        if(interface.player->GeneratePlayer.shape.getPosition().x<=0)//Left
           interface.player->GeneratePlayer.shape.setPosition(0.f,interface.player->GeneratePlayer.shape.getPosition().y);
        if(interface.player->GeneratePlayer.shape.getPosition().x>=interface.window.getSize().x-interface.player->GeneratePlayer.shape.getGlobalBounds().width)//Right
           interface.player->GeneratePlayer.shape.setPosition(interface.window.getSize().x - interface.player->GeneratePlayer.shape.getGlobalBounds().width,interface.player->GeneratePlayer.shape.getPosition().y);
        if(interface.player->GeneratePlayer.shape.getPosition().y<=0)//Top
           interface.player->GeneratePlayer.shape.setPosition(interface.player->GeneratePlayer.shape.getPosition().x,0.f);
        if(interface.player->GeneratePlayer.shape.getPosition().y>= interface.window.getSize().y-interface.player->GeneratePlayer.shape.getGlobalBounds().height)//Bottom
           interface.player->GeneratePlayer.shape.setPosition(interface.player->GeneratePlayer.shape.getPosition().x,interface.window.getSize().y-interface.player->GeneratePlayer.shape.getGlobalBounds().height);
    }
    
};

class OnhitCollision:Collision{//For the Case where the enemies hit by bullets      //Polymorphism to Collision Class

    public:
    //method function
    void collisionwindow(Interface& interface,size_t i=0){
        
        for(size_t k=0;k<interface.enemies.size();k++)
        {   
            if(interface.player->bullets[i].GenerateBullet.shape.getGlobalBounds().intersects(interface.enemies[k].GenerateEnemy.shape.getGlobalBounds())){
                if(interface.enemies[k].HP<=1){
                    interface.player->score.score+=interface.enemies[k].HPMax;
                    interface.enemies.erase(interface.enemies.begin()+k);
                }
                else
                    interface.enemies[k].HP--;//ENEMY TAKE DAMAGE

                interface.player->bullets.erase(interface.player->bullets.begin()+i);
                break;
            }
        }
    }
};

class PlayeronHit:Collision{//For the Case where Player Crashes with Enemies    //Polymorphism to Collision Class
    public:
    //method function
    void collisionwindow(Interface& interface,size_t i=0){
        if(interface.enemies[i].GenerateEnemy.shape.getGlobalBounds().intersects(interface.player->GeneratePlayer.shape.getGlobalBounds())){
            interface.enemies.erase(interface.enemies.begin()+i);

            interface.player->HP--;
            

        }
    }
};

//Player Movement
class Movement{
    public:
    //constructor
    Movement(){}

    //method function
    void virtual motion(Interface& interface)
    {
    if (Keyboard::isKeyPressed(Keyboard::W))
        interface.player->GeneratePlayer.shape.move(0.f,-10.f);
    if (Keyboard::isKeyPressed(Keyboard::A))
        interface.player->GeneratePlayer.shape.move(-10.f,0.f);
    if ((Keyboard::isKeyPressed)(Keyboard::S))
        interface.player->GeneratePlayer.shape.move(0.f,10.f);
    if ((Keyboard::isKeyPressed)(Keyboard::D))
        interface.player->GeneratePlayer.shape.move(10.f,0.f); 
           
    }
};


class BulletsMovement:public Movement{      //Polymorphism to Movement class    //Bullets Movement
    public:
    //constructor
    BulletsMovement(){}
    //method function
    void motion(Interface& interface){
        for(size_t i=0;i<interface.player->bullets.size();i++){
            //Move
            interface.player->bullets[i].GenerateBullet.shape.move(20.f,0.f);
            
            //Out of window bounds
            if(interface.player->bullets[i].GenerateBullet.shape.getPosition().x>interface.window.getSize().x)
            {
                interface.player->bullets.erase(interface.player->bullets.begin()+i);
                break;
            }

            //Bullets hit Enemies
            OnhitCollision enemyonhit;
            enemyonhit.collisionwindow(interface,i);
            
        }
    }
};

class EnemiesMovement:public Movement{      //Polymorphism to Movement Class    //Enemies Movement
    public:
    //constructor
    float Espeed=-5.0;
    int y = 10;
    int scoreCounter = 0;
    EnemiesMovement(){}


    //method function
    void motion(Interface& interface){

        if(interface.player->score.score >= y)
        {
            Espeed = Espeed -0.5;
            y = y + 10;
            if(interface.updateenemy.limit > 12)
            interface.updateenemy.limit = interface.updateenemy.limit - 0.8;
        }

        for(size_t i=0;i<interface.enemies.size();i++){
            
            interface.enemies[i].GenerateEnemy.shape.move(Espeed,0.f);
        


            //Enemies move out of bound
            if(interface.enemies[i].GenerateEnemy.shape.getPosition().x<=0-interface.enemies[i].GenerateEnemy.shape.getGlobalBounds().width){
                interface.enemies.erase(interface.enemies.begin()+i);
                break;
            }

            /*if(interface.enemies[i].GenerateEnemy.shape.getGlobalBounds().intersects(interface.player->GeneratePlayer.shape.getGlobalBounds())){
                interface.enemies.erase(interface.enemies.begin()+i);
                interface.player->HP--;
                break;
            }*/

            //Player crashes Enemies
            PlayeronHit crash;
            crash.collisionwindow(interface,i);
            if(interface.enemies[i].GenerateEnemy.shape.getGlobalBounds().intersects(interface.player->GeneratePlayer.shape.getGlobalBounds())){
                break;
            }
        }
    }

};

class Menu : public FontStyle   //Inheriance to FontStyle Class
{
    public:
        int selectedItemIndex;
        int No_Menu;
        Text menu[3];   //Composition to in-built Class of SFML Library : Text
        Menu(string s) : FontStyle(s)
        { 
            selectedItemIndex = 0;
            No_Menu = 0;
        }
        ~Menu() {};

        void textsetting(Interface &interface)// Menu Displaying Setting
        {
            menu[0].setFont(font);
            menu[0].setCharacterSize(20);
            menu[0].setFillColor(Color::Red);
            menu[0].setString("Play");
            menu[0].setPosition(Vector2f(interface.window.getSize().x / 2,interface.window.getSize().y / (3 + 1 ) * 1));

            menu[1].setFont(font);
            menu[1].setCharacterSize(20);
            menu[1].setFillColor(Color::White);
            menu[1].setString("Options");
            menu[1].setPosition(Vector2f(interface.window.getSize().x / 2, interface.window.getSize().y / (3 + 1 ) * 2));

            menu[2].setFont(font);
            menu[2].setCharacterSize(20);
            menu[2].setFillColor(Color::White);
            menu[2].setString("Exit");
            menu[2].setPosition(Vector2f(interface.window.getSize().x / 2, interface.window.getSize().y / (3 + 1 ) * 3));

        }
        void draw(Interface &interface,Texture* t) //Menu Drawing
        {
            interface.window.clear();
            interface.setBackground(t);
            interface.drawbackground();
            for(int i = 0; i < 3; i++)
            {
                interface.window.draw(menu[i]);
            }
            interface.window.display();
        }
        void MoveUp()   //Upward Movement through the options in the Menu Page
        {
            
            if (selectedItemIndex - 1 >= 0)
            {
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                selectedItemIndex--;
                menu[selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }
        void MoveDown() //Downward Movement through the options in the Menu Page
        {
            if (selectedItemIndex + 1 < 3)
            {
                menu[selectedItemIndex].setFillColor(sf::Color::White);
                selectedItemIndex++;
                menu[selectedItemIndex].setFillColor(sf::Color::Red);
            }
        }
        int GetPressedItem() { return selectedItemIndex; }  //Pressing the option to choose
        int NumberMenu() { return No_Menu; }    //To let the system know which option you choose
        void setNumberMenu(int number) { No_Menu = number; }    //To display the page that corresponding to the option you choose
        void reset(Interface &interface)    //Game Status Reset
        {
            interface.player->HP = 10;
            interface.enemies.clear();
            interface.player->bullets.clear();
            interface.player->score.score=0;
            interface.player->GeneratePlayer.shape.setPosition(0,interface.window.getSize().y/2);
            interface.updateenemy.limit = 25;
        }
        
        void resetSpeed(EnemiesMovement &emovement) //Enemies Movement speed reset
        {
            emovement.Espeed = -5.0;
            emovement.y = 10;
            emovement.scoreCounter = 0;
        }

};



/*int main(){
    srand(time(NULL));

    Interface interface(800,600,"Spaceship action!");
    interface.window.setFramerateLimit(60);
    


    return 0;
}*/


