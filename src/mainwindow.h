#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <shooter.h>
#include <barrier.h>
#include <enemy.h>

namespace Ui {
class MainWindow;
}

class MyContactListener;
class Bird;
class Enemy;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int _highestScore = 0, QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void setupWindow();
    void addGameItem(GameItem *gameitem);
    void addBarrier(float32 x,float32 y,bool vertical,int barrierType);
    void addEnemy(float32 x,float32 y);
    void addBird(int birdType);
    void prepareRope();
    void extendRope(QMouseEvent *me);
    void shootBird();
    void bornBird(Bird *bird, b2Vec2 velocity);
    void restartGame();
    void clearWindow();

signals:
    // Signal for closing the game
    void quitGame();

public slots:
    void prepareBird();
    void dieEnemy();
    void setScore(int score);
    void gameOver();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();


private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsTextItem scoreText;
    int Score;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QList<Enemy *> enemyList;
    QList<Bird *> birdList;
    int birdIndex;
    Shooter *shooter;
    Shooter *shooter2;
    Rope *rope1;
    Rope *rope2;
    int clicked;
    MyContactListener *myContactListener;
    QTimer tim;
    QTimer quitTimer;
    bool isRestarted;
    int highestScore;
};

class MyContactListener : public b2ContactListener
{
public:
    //void BeginContact(b2Contact* contact);
    //void EndContact(b2Contact* contact);
    //void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // MAINWINDOW_H
