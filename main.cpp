#include <header.h>
#include <mainclass.h>
#include <bullet.h>
#include <enemy.h>
#include <mycircle.h>
#include <player.h>
#include <QList>
using namespace sf;

void drawInformation(Text &text, int PlayerPoint, int PlayerLevel, int CountEnemy);

int main()
{
    srand(time(0));

    mainClass data;

    //Font
    Font font;
    font.loadFromFile("Font/arial.ttf");

    //prepare text var
    Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setColor(Color::Black);
    text.setString("Hello world!");

    //create a dynamic lists (enemy and bullets)
    QList<Bullet*> bullets;
    QList<Enemy*> enemys;

    //create a Circles
    MyCircle PlayerBackground(data.getPlayerRadius(), 3, 190, 190, 190, 255, data.getWindowWidth() / 2 - data.getPlayerRadius(), data.getWindowHeight() / 2 - data.getPlayerRadius(), 240, 255, 240, 255);
    MyCircle WindowBackground(data.getWindowRadius(), 10, 70, 130, 180, 255, data.getWindowWidth() / 2 - data.getWindowRadius(), data.getWindowHeight() / 2 - data.getWindowRadius(), 30, 144, 255, 255);

    //create a window
    RenderWindow window(VideoMode(data.getWindowWidth(), data.getWindowHeight()), "Game");

    //create a baseX, baseY of Circle; create Clock
    float baseX = data.getWindowWidth() / 2 - data.getPlayerRadius() / 10;
    float baseY = data.getWindowHeight() / 2 - data.getPlayerRadius() / 10;
    Clock clock;

    //create a player pl
    Player pl(baseX, baseY, data.getPlayerRadius());

    //create an enemys
    for (int i = 0; i < data.getCountEnemy(); i++)
        enemys.push_back(new Enemy(baseX, baseY, data.getWindowRadius(), rand() % 4 + 1));

    //pointer (mouse)
    Texture textur;
    textur.loadFromFile("Image/Point.jpg");
    Sprite point;
    point.setTexture(textur);
    point.setPosition(baseX, baseY);

    //endGame
    Texture end, endBlack;
    end.loadFromFile("Image/End.jpg");
    endBlack.loadFromFile("Image/EndBlack.jpg");
    Sprite endGame;
    endGame.setTexture(end);
    endGame.setPosition(data.getWindowWidth() / 2 - end.getSize().x / 2, data.getWindowHeight() / 2 - end.getSize().y / 2);

    //sounds
    SoundBuffer buffer, buffer2, buffer3;
    buffer.loadFromFile("Sound/Piy.wav");
    buffer2.loadFromFile("Sound/Boom.wav");
    buffer3.loadFromFile("Sound/SuperBoom.wav");

    Sound piy(buffer), boom(buffer2), superboom(buffer3);
    piy.setVolume(data.getVolume());
    boom.setVolume(data.getVolume());
    superboom.setVolume(data.getVolume());

    Music back;
    back.openFromFile("Sound/Back.ogg");
    back.setVolume(data.getVolume() * 3 / 25);
    back.play();
    back.setLoop(true);

    //point, score
    int PlayerPoint = 0, PlayerLevel = 1;
    String PlStrPoint = "";

    //special for super kick
    bool SupBoomFl = false;

    //timer from clock
    float t;

    while (window.isOpen())
    {
        //main actions (events)
        Event event;
        while (window.pollEvent(event))
            switch(event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                switch(event.key.code)
                {
                case Mouse::Left:
                    bullets.push_back(new Bullet(pl.getX(), pl.getY(), pl.getAngle()));
                    piy.play();
                    break;
                }
                break;
            case Event::KeyPressed:
                switch(event.key.code)
                {
                case Keyboard::P:
                    if (data.getWinner() == 0)
                        data.setWinner(1);
                    else if (data.getWinner() == 1)
                        data.setWinner(0);
                    break;
                case Keyboard::Space:
                    if (!SupBoomFl && !data.getWinner())
                    {
                        SupBoomFl = true;
                        superboom.play();
                        for (int i = 0; i < 314; i++)
                        {
                            float j = i / 5;
                            bullets.push_back(new Bullet(baseX, baseY, j));
                        }
                    }
                    break;
                }
            }

        //set position of pointer (mouse)
        data.setMouseX(Mouse::getPosition(window).x);
        data.setMouseY(Mouse::getPosition(window).y);

        switch(data.getWinner())
        {
        case (0)://---- PLAYNG GAME ----- PLAYNG GAME ----- PLAYNG GAME ----- PLAYNG GAME ----- PLAYNG GAME -----
            //t - timer from clock, inside - time between two cicle of game
            t = clock.getElapsedTime().asMicroseconds();
            clock.restart();

            //if player kill all enemys, we will create new
            if (enemys.empty())
            {
                bullets.clear();//clear an old bullets
                data.setCountEnemy(data.getCountEnemy() + 2);//increase max count of enemys
                //create them
                for (int i = 0; i < data.getCountEnemy(); i++)
                {
                    enemys.push_back(new Enemy(baseX, baseY, data.getWindowRadius(), rand() % 4 + 1));
                    enemys[i]->setSpeed(enemys[i]->getSpeed() * data.getCountSpeedEnemy());
                }
                //and increase player level and set superkick to active
                PlayerLevel++;
                SupBoomFl = false;
            }

            //press right or left button
            if (Keyboard::isKeyPressed(Keyboard::Right))
                pl.setAngle(pl.getAngle() + data.getSpeed()*t);
            if (Keyboard::isKeyPressed(Keyboard::Left))
                pl.setAngle(pl.getAngle() - data.getSpeed()*t);

            //set player view
            if (data.getMouseY() > data.getWindowHeight() / 2)
                pl.setAngle(acos((data.getMouseX() - baseX) / sqrt((data.getMouseX() - baseX)*(data.getMouseX() - baseX) + (data.getMouseY() - baseY)*(data.getMouseY() - baseY))));
            else
                pl.setAngle(3.14 + acos((baseX - data.getMouseX()) / sqrt((data.getMouseX() - baseX)*(data.getMouseX() - baseX) + (data.getMouseY() - baseY)*(data.getMouseY() - baseY))));

            //enemy & bullets
            for (int i = 0; i < enemys.size();)
            {
                if (!enemys[i]->getLife())
                {
                    enemys.removeAt(i);
                    continue;
                }
                float Ex1 = enemys[i]->getX();
                float Ex2 = enemys[i]->getX() + enemys[i]->en.getSize().x;
                float Ey1 = enemys[i]->getY();
                float Ey2 = enemys[i]->getY() + enemys[i]->en.getSize().y;
                for (int j = 0; j < bullets.size();)
                {
                    if (!bullets[j]->getLife())
                    {
                        bullets.removeAt(j);
                        continue;
                    }
                    float Bx1 = bullets[j]->getX();
                    float Bx2 = bullets[j]->getX() + bullets[j]->getW();
                    float By1 = bullets[j]->getY();
                    float By2 = bullets[j]->getY() + bullets[j]->getH();
                    if (Bx1 >= Ex1 && Bx2 <= Ex2 && By1 >= Ey1 && By2 <= Ey2)
                    {
                        bullets[j]->die();
                        enemys[i]->damage(1);
                        boom.play();
                        PlayerPoint++;
                    }
                    j++;
                }
                if (enemys[i]->isOnCenter())
                {
                    data.setWinner(-1);
                    break;
                }
                i++;
            }

            //updates
            for (int i = 0; i < enemys.size(); i++)
                enemys[i]->update(baseX, baseY, t, data.getPlayerRadius());
            for (int i = 0; i < bullets.size(); i++)
                bullets[i]->update(t, baseX, baseY, data.getWindowRadius());
            pl.update(baseX, baseY);

            //cursor
            if (data.getMouseX() >= data.getWindowWidth() || data.getMouseX() <= 0 || data.getMouseY() >= data.getWindowHeight() || data.getMouseY() <= 0)
                window.setMouseCursorVisible(true);
            else
            {
                window.setMouseCursorVisible(false);
                point.setPosition(data.getMouseX(), data.getMouseY());
            }

            //draw all that we have
            window.clear(Color::White);
            WindowBackground.draw(window);
            PlayerBackground.draw(window);
            pl.show(window);
            for (int i = 0; i < enemys.size(); i++)
                if (enemys[i]->getLife())
                    enemys[i]->draw(window);
            for (int i = 0; i < bullets.size(); i++)
                if (bullets[i]->getLife())
                    bullets[i]->draw(window);
            window.draw(point);
            window.draw(text);
            window.display();

            //Point
            drawInformation(text, PlayerPoint, PlayerLevel, data.getCountEnemy());
            break;
        case (-1)://---- DEFEAT GAME ----- DEFEAT GAME ----- DEFEAT GAME ----- DEFEAT GAME ----- DEFEAT GAME -----
            window.setMouseCursorVisible(true);
            window.clear(Color::White);
            WindowBackground.draw(window);
            PlayerBackground.draw(window);
            pl.show(window);

            if (data.getMouseX() >= endGame.getPosition().x
                    && data.getMouseX() <= endGame.getPosition().x + end.getSize().x
                    && data.getMouseY() >= endGame.getPosition().y
                    && data.getMouseY() <= endGame.getPosition().y + end.getSize().y)
            {
                endGame.setTexture(endBlack);
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    data.setWinner(0);
                    enemys.clear();
                    data.setCountEnemy(3);
                    PlayerLevel = 0;
                    data.setCountSpeedEnemy(2);
                    PlayerPoint = 0;
                }
            }
            else
                endGame.setTexture(end);

            drawInformation(text, PlayerPoint, PlayerLevel, data.getCountEnemy());
            window.draw(text);
            window.draw(endGame);
            window.display();
            break;
        case (1)://---- PAUSING GAME ----- PAUSING GAME ----- PAUSING GAME ----- PAUSING GAME ----- PAUSING GAME -----
            clock.restart();
            RectangleShape BackGround(Vector2f(data.getWindowWidth(), data.getWindowHeight()));
            BackGround.setFillColor(Color(0, 0, 0, 100));

            window.setMouseCursorVisible(true);

            //draw all that we have
            window.clear(Color::White);
            WindowBackground.draw(window);
            PlayerBackground.draw(window);
            pl.show(window);
            for (int i = 0; i < enemys.size(); i++)
                if (enemys[i]->getLife())
                    enemys[i]->draw(window);
            for (int i = 0; i < bullets.size(); i++)
                if (bullets[i]->getLife())
                    bullets[i]->draw(window);
            window.draw(point);
            window.draw(text);
            window.draw(BackGround);
            window.display();
            drawInformation(text, PlayerPoint, PlayerLevel, data.getCountEnemy());
            break;
        }
    }
    return 0;
}

void drawInformation(Text &text, int PlayerPoint, int PlayerLevel, int CountEnemy)
{
    //Point
    char PlStrPoint[100], Score[6], Ene[10], Lvl[10];
    itoa(PlayerPoint, Score, 10);
    itoa(PlayerLevel, Lvl, 10);
    itoa(CountEnemy, Ene, 10);
    strcpy(PlStrPoint, "Your score is ");
    strcat(PlStrPoint, Score);
    strcat(PlStrPoint, "\nYou are at level ");
    strcat(PlStrPoint, Lvl);
    strcat(PlStrPoint, "\nNumber of Enemys = ");
    strcat(PlStrPoint, Ene);
    strcat(PlStrPoint, "\nP - Pause");
    text.setString(PlStrPoint);
}
