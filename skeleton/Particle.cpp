#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

Particle::Particle()
{
	vel = PxVec3(0, 0, 0);
	accel = PxVec3(0, 0, 0);
	transform = PxTransform(PxVec3(0, 0, 0));
	color = PxVec4(1, 0.5, 1, 1);

	if (visible) {
		PxShape* shape = CreateShape(PxSphereGeometry(2));
		renderItem = new RenderItem(shape, &transform, color);
	}

	mass = 1;
	center = PxVec3(0, 0, 0);
	ratio = 50;
	lifeTime = 50;
	damping = 0.995;
}

Particle::Particle(PxVec3 pos, PxVec3 velo, double m, PxVec4 col, PxGeometry& g, bool v)
	: transform(PxTransform(pos)), vel(velo), mass(m), color(col), visible(v)
{
	accel = PxVec3(0, 0, 0);
	if (visible) {
		PxShape* shape = CreateShape(g);
		renderItem = new RenderItem(shape, &transform, color);
	}
	center = PxVec3(0, 0, 0);
	ratio = 50;
	lifeTime = 50;
	damping = 0.995;
}


Particle::Particle(Particle const& p)
{
	vel = p.vel;
	accel = p.accel;
	transform = PxTransform(p.transform.p);
	color = p.color;


	visible = p.visible;

	if (visible) {
		PxShape* shape = CreateShape(PxSphereGeometry(1));
		renderItem = new RenderItem(shape, &transform, color);
	}

	mass = p.mass;
	center = p.center;
	ratio = p.ratio;
	lifeTime = p.lifeTime;
	damping = 0.995;
}

Particle::~Particle()
{
	delete renderItem;
	DeregisterRenderItem(renderItem);

}

void Particle::Integrate(double t, IntegrationType type)
{
	if (type == EULER) {
		vel = vel + accel * t;  
		vel = vel * pow(damping, t);
		transform.p = transform.p + vel * t;
	}
	else {  // SEMIEULER
		vel = vel * pow(damping, t) + accel * t;  // Aplica damping primero y luego la aceleración
		transform.p = transform.p + vel * t;  // Actualiza la posición con la nueva velocidad
	}
}

void Particle::isAlive(double t, ParticleSystem& system, IntegrationType type)
{
	Integrate(t, type);
	if (updateLifeTime(t) || !isOnRatio()) {
		system.destroyParticle(this);
	}
}

bool Particle::updateLifeTime(double t)
{
	lifeTime -= t;
	return (lifeTime <= 0);

}

bool Particle::isOnRatio()
{
	return (transform.p - center).magnitude() < ratio;
}


