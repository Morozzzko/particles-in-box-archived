//
// Created by Mihail Orlov on 13/02/16.
//

#ifndef PARTICLE_IN_BOX_GENERATOR_GENERATOR_H
#define PARTICLE_IN_BOX_GENERATOR_GENERATOR_H

#include <vector>
#include <string>
#include <math.h>
#include <QObject>

const int nMaxParticles = 12000; //65536;		// Максимальное число частиц

struct SParticle {
    double x,y;		// position
    double vX, vY;	// velocity
    int color;		// 0 частица родилась слева, 1 - справа
};

struct SGeometry {
    double xLeft, particleXLeft;			// Левая граница (в метрах)
    double xCenter, particleWLeft, particleWRight;			// Перегородка (в метрах)
    double wThickness;		// Wall thickness
    double wLeft, wRight;
    double yGapTop;			// Верхний край перегородки
    double yGapBottom;		// Нижний край перегородки
    double particleHoleTop, particleHoleBottom;
    double holeSize, holePosition;
    double xRight, particleXRight;			// Правая граница (в метрах)
    double yMax, particleYMax;			// Верхняя граница (в метрах)
    double yMin, particleYMin;			// Нижняя граница (в метрах)
    double rParticle;		// Радиус одной частицы  (в метрах)
};

class Generator: public QObject {
    Q_OBJECT
public:
    Generator(int nLeftParticles, int nRightParticles, double rParticle, double vInit, double loss, double width,
              double height, double barrierX, double barrierWidth, double holeY,
              double holeHeight, double deltaVTop, double deltaVBottom, double deltaVSide, double g,
              int minToSimulate, double frames, std::string fileName, QObject* parent);
    ~Generator();

public:
    bool initialDistribution();
    double calcTimeStep();
    int getLeftParticleCount() { return nLeftParticles; }
    int getRightParticleCount() { return nRightParticles; }
    int getParticleCount() { return (nLeftParticles+nRightParticles); }
    SParticle *getParticle(int iParticle) { return particle + iParticle; }
    SGeometry *getGeometry() { return &geometry; }
    unsigned char *getLeftColor() { return mLeftColor.c; }
    unsigned char *getRightColor() { return mRightColor.c; }
    void simulate();

// Public members
public:
    double			time;				// Текущее время (в секундах)
    double			deltaTime;			// Шаг по времени (в секундах)
    unsigned long	nRight;				// Количество частиц в правой части
    unsigned long	nLeft;				// Количество частиц в левой части
    double			vAverageR;			// Средняя скорость частиц в правой части
    double			vAverageL;			// Средняя скорость частиц в левой части
    int nLeftParticles, nRightParticles;// Реальное число частиц


// Protected methods
protected:
    double random(double from, double to);
    double distance2(SParticle &p1, SParticle &p2);
    double distance(SParticle &p1, SParticle &p2) { return sqrt(distance2(p1, p2)); }
    bool inContact(SParticle &p1, SParticle &p2) { return (distance(p1, p2) < 2*geometry.rParticle); }
    bool approaching(SParticle &p1, SParticle &p2);
    void collision(SParticle &p1, SParticle &p2);
    void randomVelocity(SParticle &p);
    void moveParticle(SParticle &p, double dt);
    void bounceX(SParticle &p) { p.vX = -p.vX; }
    void bounceY(SParticle &p) { p.vY = -p.vY; }
    void writeStat();
    bool correctParticleByGeometry(SParticle &p);
    bool oneTimeStep(double);


protected:
    SParticle particle[nMaxParticles];		// Сами частицы
    SGeometry geometry;
    double vInit;			// Начальная скорость всех частиц (в метрах/сек)
    // Collisions
    double deltaVTop;		// Добавок скорости, который получает частица, ударяясь о верхнюю стенку
    double deltaVBottom;	// Добавок скорости, который получает частица, ударяясь о нижнюю стенку
    double deltaVSide;		// Добавок скорости, который получает частица, ударяясь о боковую стенку
    double loss;			// Коэффициент диссипации кинетической энергии

    double g;				// Ускорение свободного падения (в м/с**2)

    unsigned short minToSimulate;
    unsigned short frames;


    std::string fileName;		// Имя файла с записанной статистикой
    std::vector<double> heightDistrArr;
    std::vector<double> maxwellDistrArr;
    std::vector<double> particleDistrArr;

    // Вычисляемые величины (переменные)
    unsigned long	nTimeSteps;			// Количество пройденных шагов по времени

    double			lastTimeWritten;	// Время, которое было записано в файл последний раз
    int				nFluxFromLeft;
    int				nFluxFromRight;
    union {
        unsigned char c[4];
        unsigned int rgb;
    } mLeftColor, mRightColor;

signals:
    void onSimulationFinished();
    void onSimulationStep();
};
#endif //PARTICLE_IN_BOX_GENERATOR_GENERATOR_H
