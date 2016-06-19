#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
using namespace std;

MainWindow::MainWindow(int _highestScore, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),Score(0),clicked(0),isRestarted(false),highestScore(_highestScore)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    setupWindow();
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(clicked == 0 && birdList[birdIndex]->ready)
        {
            prepareRope();
            clicked = 1;
        }
        else if(clicked == 0 && birdList[birdIndex]->travel)
        {
            birdList[birdIndex]->feature();
            clicked = 2;
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent*>(event);
        if(clicked == 1)
        {
            extendRope(me);
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(clicked == 1)
        {
            shootBird();
            clicked = 0;
        }
        else if(clicked == 2) clicked = 0;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::setupWindow()
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->addPixmap(QPixmap(":/image/background.png").scaled(width(),height()));
    scoreText.setScale(1.5);
    scoreText.setFont(QFont("Arial"));
    scoreText.setPos(800,0);
    scene->addItem(&scoreText);
    setScore(0);

    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),(QSizeF)size());

    // Create ground (You can edit here)
    addGameItem(new Land(16,2,32,4,QPixmap().scaled(width()/32.0*32,height()/18.0*4),world,scene));
    shooter = new Shooter(4.0,6.25,1.5,4.5,QPixmap(":/image/shooter_back.png").scaled(width()/32.0*1.5,height()/18.0*4.5),world,scene);
    shooter->g_body->SetActive(false);
    addGameItem(shooter);

    // Create Barrier
    addBarrier(16.5,5,true,3);
    addBarrier(19.5,5,true,3);
    addBarrier(18,6.25,false,1);

    addBarrier(20.5,5,true,4);
    addBarrier(23.5,5,true,4);
    addBarrier(22,6.25,false,1);

    addBarrier(24.5,5,true,3);
    addBarrier(27.5,5,true,3);
    addBarrier(26,6.25,false,1);


    addBarrier(18.5,7.6,true,3);
    addBarrier(21.5,7.6,true,3);
    addBarrier(20,8.85,false,1);

    addBarrier(22.5,7.6,true,3);
    addBarrier(25.5,7.6,true,3);
    addBarrier(24,8.85,false,1);


    addBarrier(20.5,11.2,true,2);
    addBarrier(23.5,11.2,true,2);
    addBarrier(22,13.45,false,0);

    // Create Eneemy
    addEnemy(18,4);
    addEnemy(22,4);
    addEnemy(26,4);

    addEnemy(20,6.6);
    addEnemy(24,6.6);

    addEnemy(22,9.2);

    // Create Birds
    addBird(0);
    addBird(4);
    addBird(5);
    addBird(2);
    addBird(1);
    addBird(3);

    birdIndex = -1;
    prepareBird();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);

    myContactListener = new MyContactListener();
    world->SetContactListener(myContactListener);
}

void MainWindow::addGameItem(GameItem *gameitem)
{
    itemList.push_back(gameitem);
    connect(gameitem,SIGNAL(scoreSignal(int)),this,SLOT(setScore(int)));
}

void MainWindow::addBarrier(float32 x, float32 y, bool vertical, int barrierType)
{
    Barrier *barrier;
    switch(barrierType)
    {
    case 0: // long wood
        barrier = new Wood(x,y,4,0.5,vertical,&timer,QPixmap(":/image/long_wood.png").scaled(width()/32.0*4,height()/18.0*0.5),world,scene);
        break;
    case 1: // long rock
        barrier = new Rock(x,y,4,0.5,vertical,&timer,QPixmap(":/image/long_rock.png").scaled(width()/32.0*4,height()/18.0*0.5),world,scene);
        break;
    case 2: // long ice
        barrier = new Ice(x,y,4,0.5,vertical,&timer,QPixmap(":/image/long_ice.png").scaled(width()/32.0*4,height()/18.0*0.5),world,scene);
        break;
    case 3: // mid wood
        barrier = new Wood(x,y,2,0.5,vertical,&timer,QPixmap(":/image/mid_wood.png").scaled(width()/32.0*2,height()/18.0*0.5),world,scene);
        break;
    case 4: // mid rock
        barrier = new Rock(x,y,0.5,2,!vertical,&timer,QPixmap(":/image/mid_rock.png").scaled(width()/32.0*0.5,height()/18.0*2),world,scene);
        break;
    }
    addGameItem(barrier);
}

void MainWindow::addEnemy(float32 x, float32 y)
{
    Enemy *enemy = new Enemy(x,y,0.5,&timer,QPixmap(":/image/pig.png").scaled(width()/32.0*1,height()/18.0*1),this,world,scene);
    enemyList.push_back(enemy);
    addGameItem(enemy);
    connect(enemy,SIGNAL(dieSignal()),this,SLOT(dieEnemy()));
}

void MainWindow::addBird(int birdType)
{
    b2Vec2 pb;
    if(birdList.isEmpty()) pb=b2Vec2(5,4.5);
    else pb=b2Vec2(birdList.last()->g_body->GetPosition().x,4.5)+b2Vec2(1,0);
    Bird *bird;
    switch(birdType)
    {
    case 0:
        bird = new RedBird(pb.x,pb.y,0.5,&timer,QPixmap(":/image/red_bird.png").scaled(width()/32.0*1,height()/18.0*1),this,world,scene);
        break;
    case 1:
        bird = new YellowBird(pb.x,pb.y,0.5,&timer,QPixmap(":/image/yellow_bird.png").scaled(width()/32.0*1,height()/18.0*1),this,world,scene);
        break;
    case 2:
        bird = new GreenBird(pb.x,pb.y,0.5,&timer,QPixmap(":/image/green_bird.png").scaled(width()/32.0*1.4,height()/18.0*1),this,world,scene);
        break;
    case 3:
        bird = new BlackBird(pb.x,pb.y+0.34,0.5,&timer,QPixmap(":/image/black_bird.png").scaled(width()/32.0*1,height()/18.0*1.34),itemList,this,world,scene);
        break;
    case 4:
        bird = new BlueBird(pb.x,pb.y-0.1,0.4,&timer,QPixmap(":/image/blue_bird.png").scaled(width()/32.0*0.8,height()/18.0*0.8),this,world,scene);
        break;
    case 5:
        bird = new WhiteBird(pb.x,pb.y+0.2,0.5,&timer,QPixmap(":/image/white_bird.png").scaled(width()/32.0*1,height()/18.0*1.2),this,world,scene);
        break;
    }
    bird->g_body->SetActive(false);
    birdList.push_back(bird);
    addGameItem(bird);
    connect(bird,SIGNAL(nextItemSignal()),this,SLOT(prepareBird()));
}

void MainWindow::prepareRope()
{
    b2Vec2 pb = birdList[birdIndex]->g_body->GetPosition();
    b2Vec2 ps1 = shooter->g_body->GetPosition()+b2Vec2(0.5,1.45);
    b2Vec2 ps2 = shooter->g_body->GetPosition()+b2Vec2(-0.45,1.45);
    rope1 = new Rope(pb,ps1,0.1,QPixmap(":/image/rope.png").scaled(width()/32.0*(pb-ps1).Length(),height()/18.0*0.1),world,scene);
    rope2 = new Rope(pb,ps1,0.1,QPixmap(":/image/rope.png").scaled(width()/32.0*(pb-ps2).Length(),height()/18.0*0.1),world,scene);
    shooter2 = new Shooter(4.0,6.25,1.5,4.5,QPixmap(":/image/shooter_front.png").scaled(width()/32.0*1.5,height()/18.0*4.5),world,scene);
    shooter2->g_body->SetActive(false);
    pb+=0.5/(pb-ps2).Length()*(pb-ps2);
    rope1->setExtend(pb,ps1);
    rope2->setExtend(pb,ps2);
    addGameItem(rope1);
    addGameItem(rope2);
}

void MainWindow::extendRope(QMouseEvent *me)
{
    b2Vec2 pb = pix2box(QPointF(me->pos()));
    b2Vec2 ps1 = shooter->g_body->GetPosition()+b2Vec2(0.5,1.45);
    b2Vec2 ps2 = shooter->g_body->GetPosition()+b2Vec2(-0.45,1.45);
    float32 max = 3.5;
    if((pb-ps2).Length()>max) pb = ps1+max/(pb-ps2).Length()*(pb-ps2);
    if((pb-ps1).y<0)
    {
        if(1/(pb-ps2).Length()*(pb-ps1).x>-0.5 && 1/(pb-ps2).Length()*(pb-ps1).x<0.5)
        {
            pb = ps1 + b2Vec2(0.5*(pb-ps2).Length(),(pb-ps1).y);
        }
    }
    birdList[birdIndex]->g_body->SetTransform(pb,0);
    pb+=0.5/(pb-ps2).Length()*(pb-ps2);
    rope1->setExtend(pb,ps1);
    rope2->setExtend(pb,ps2);
}

void MainWindow::shootBird()
{
    // Setting the Velocity
    b2Vec2 velocity = (shooter->g_body->GetPosition()+b2Vec2(0,2) - birdList[birdIndex]->g_body->GetPosition());
    velocity *= 5;
    birdList[birdIndex]->setLinearVelocity(velocity);
    birdList[birdIndex]->g_body->SetActive(true);

    itemList.removeOne(rope1);
    itemList.removeOne(rope2);
    delete rope1;
    delete rope2;

    birdList[birdIndex]->ready = false;
    birdList[birdIndex]->travel = true;
}

void MainWindow::bornBird(Bird *bird, b2Vec2 velocity)
{
    bird->g_body->SetActive(false);
    addGameItem(bird);

    bird->setLinearVelocity(velocity);
    bird->g_body->SetActive(true);

    bird->ready = false;
    bird->travel = true;
}

void MainWindow::gameOver()
{
    if(!isRestarted)
    {
        isRestarted = true;
        QMessageBox msgBox;
        msgBox.setText("Total Score : "+QString::number(Score)+"\nHighest Score : "+QString::number(highestScore));
        msgBox.setInformativeText("Restart the Game?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        switch (ret)
        {
            case QMessageBox::Yes:
                restartGame();
                break;
            case QMessageBox::No:
                emit quitGame();
                break;
        }
    }
}

void MainWindow::restartGame()
{
    MainWindow *w = new MainWindow(highestScore);
    this->hide();
    w->show();

}

void MainWindow::clearWindow()
{
    for(int i = 0; i < itemList.size(); i++)
    {
        itemList[i]->g_pixmap.setPixmap(QPixmap());
        if(!itemList[i]->isDeleted) delete itemList[i];

    }
    disconnect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    delete world;
    itemList.clear();
    birdList.clear();
    delete myContactListener;
    scene->deleteLater();
}

void MainWindow::setScore(int score)
{
    Score += score;
    if(Score > highestScore) highestScore = Score;
    scoreText.setPlainText("Score\n"+QString::number(Score)+"\nHighest Score\n"+QString::number(highestScore));
}

void MainWindow::prepareBird()
{

    if(!enemyList.isEmpty() && birdList.size() - 1 > birdIndex)
    {
        birdIndex++;
        birdList[birdIndex]->g_body->SetTransform(b2Vec2(4.1,7.7),0);
        for(int i = birdIndex + 1; i < birdList.size(); i++)
            birdList[i]->g_body->SetTransform(birdList[i]->g_body->GetPosition()+b2Vec2(-1,0),0);
        birdList[birdIndex]->ready = true;
    }
    else if(!enemyList.isEmpty())
    {
        connect(&quitTimer,SIGNAL(timeout()),this,SLOT(gameOver()));
        quitTimer.start(5000);
    }
}

void MainWindow::dieEnemy()
{
    for(int i = 0; i < enemyList.size(); i++)
    {
        if(enemyList[i]->isDeleted) enemyList.removeAt(i);
    }
    if(enemyList.isEmpty())
    {
        while(birdList.size() > birdIndex)
        {
            setScore(10000);
            birdList[birdIndex]->remove = 1;
            birdList[birdIndex]->deleteItem(60);
            birdList[birdIndex]->nextItem();
            birdIndex++;
        }
        birdIndex--;
        connect(&quitTimer,SIGNAL(timeout()),this,SLOT(gameOver()));
        quitTimer.start(5000);
    }
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
    exit(0);
}


void MyContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    GameItem *gameItemA;
    GameItem *gameItemB;
    //check if fixture A was a gameitem
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
    {
        gameItemA = static_cast<GameItem*>( bodyUserData );
    }
    //check if fixture B was a gameitem
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
    {
        gameItemB = static_cast<GameItem*>( bodyUserData );
    }

    if(gameItemA && gameItemB && gameItemA->isContact==false)
    {
        gameItemA->isContact=true;
        gameItemA->Contact(b2Vec2(impulse->normalImpulses[0],impulse->normalImpulses[1]),gameItemB);
    }
    if(gameItemA && gameItemB && gameItemB->isContact==false)
    {
        gameItemB->isContact=true;
        gameItemB->Contact(b2Vec2(impulse->normalImpulses[0],impulse->normalImpulses[1]),gameItemA);
    }
}
