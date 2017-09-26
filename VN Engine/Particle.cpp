#include "stdafx.h"
#include "Engine.h"

float Engine::NRand()
{
	static int q = 15;
	static float c1 = (1 << q) - 1;
	static float c2 = ((int)(c1 / 3)) + 1;
	static float c3 = 1.f / c1;
	float random = 0.f;

	float noise = 0.f;
	random = ((float)(rand()) / (float)(RAND_MAX + 1));
	random = (2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3;
	return random;
}

void Engine::AddParticleExplosion(float xPos, float yPos)
{
	//Dodaj now¹ cz¹steczkê
	Particle par;
	par.r = abs(NRand());
	par.g = abs(NRand()) * 0.1 + 0.1;
	par.b = abs(NRand()) * 0.5 + 0.5;
	par.lifetime = 0;
	par.maximum_lifetime = 2 + (rand() % 10 / 10.0);
	par.xPos = xPos;
	par.yPos = yPos;
	par.xspeed = 0;
	par.yspeed = 0;
	par.angle = (rand() % 3600) * 3.14159265358979323846 / 1800.0;
	particlesExplosions.push_front(par);
}

void Engine::AddParticleFountain(int position)
{
	//Dodaj now¹ cz¹steczkê
	Particle par;
	par.b = 0.5f + abs(NRand()) * 0.5;
	par.g = 0.2f + abs(NRand()) * 0.4;
	par.r = 0.0f;
	par.lifetime = 0;
	par.maximum_lifetime = 5 + rand() % 10;
	par.xPos = 0.5f + position * 0.25f;
	par.yPos = 1.05f;
	par.xspeed = (500 - (rand() % 1000)) * 0.0005 / 1000;
	par.yspeed = -sqrtf(0.0018 * 0.0018 - par.xspeed*par.xspeed)+(0.0002-abs(par.xspeed)/10);
	par.xAcc = 0.0f;
	par.yAcc = 0.0000045f;
	particlesFountains.push_front(par);
}

void Engine::AnimateParticles()
{
	std::list<Particle> partToRemove;
	static clock_t oldtime = clock();
	clock_t newtime = clock();
	double timePassed = (double)(newtime - oldtime) / (double)CLOCKS_PER_SEC;

	//Eksplozje
	particleIterator = particlesExplosions.begin();
	while (particleIterator != particlesExplosions.end())
	{
		float random = 5000 * 0.0000001 * (particleIterator->lifetime);
		particleIterator->xspeed = random * cos(particleIterator->angle);
		particleIterator->yspeed = random * sin(particleIterator->angle);

		if (particleIterator->lifetime / particleIterator->maximum_lifetime > 0.7)
		{
			if (particleIterator->r > 0) particleIterator->r -= 0.1f;
			if (particleIterator->g > 0) particleIterator->g -= 0.1f;
			if (particleIterator->b > 0) particleIterator->b -= 0.1f;
		}

		particleIterator->xPos += particleIterator->xspeed;
		particleIterator->yPos += particleIterator->yspeed;

		//Usuwanie particli
		particleIterator->lifetime += timePassed;
		if (particleIterator->lifetime >= particleIterator->maximum_lifetime)
		{
			particleIterator = particlesExplosions.erase(particleIterator);
		}
		else
		{
			particleIterator++;
		}
	}

	//Fontanny
	particleIterator = particlesFountains.begin();
	while (particleIterator != particlesFountains.end())
	{
		//Zmiana parametrów cz¹steczki
		particleIterator->xPos += particleIterator->xspeed;
		particleIterator->yPos += particleIterator->yspeed;

		particleIterator->xspeed += particleIterator->xAcc;
		particleIterator->yspeed += particleIterator->yAcc;

		//Usuwanie cz¹steczki
		particleIterator->lifetime += timePassed;
		if (particleIterator->lifetime >= particleIterator->maximum_lifetime)
		{
			particleIterator = particlesFountains.erase(particleIterator);
		}
		else
		{
			particleIterator++;
		}
	}

	oldtime = newtime;

	glutPostRedisplay();
}

void Engine::DrawParticles()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_DEPTH_TEST);

	//Eksplozje
	std::list<Particle>::iterator parIter = particlesExplosions.begin();
	glPointSize(3.0f);
	for (uint32_t i = 0; i < particlesExplosions.size(); i++, parIter++)
	{
		glBegin(GL_POINTS);
		glColor3f(parIter->r, parIter->g, parIter->b);
		glVertex2f(parIter->xPos * displayWidth, parIter->yPos * displayHeight);
		glEnd();
	}

	//Fontanny
	parIter = particlesFountains.begin();
	glPointSize(3.0f);
	for (uint32_t i = 0; i < particlesFountains.size(); i++, parIter++)
	{
		glBegin(GL_POINTS);
		glColor3f(parIter->r, parIter->g, parIter->b);
		glVertex2f(parIter->xPos * displayWidth, parIter->yPos * displayHeight);
		glEnd();
	}

	glColor3f(1.0f, 1.0f, 1.0f);
}