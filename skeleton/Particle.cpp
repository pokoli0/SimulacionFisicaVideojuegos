#include "Particle.h"
#include <math.h>
#include <iostream>
#include "ParticleSystem.h"

Particle::Particle(PxVec3 pos, PxVec3 velo, PxVec3 accele)
	: transform(pos), vel(velo), accel(accele)
{
	damping = 0.99;
	transform = physx::PxTransform(pos);

	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);



	renderItem = new RenderItem(shape, &transform, Vector4(1, 0.5, 1, 1));
	RegisterRenderItem(renderItem);

}

Particle::Particle(PxVec3 pos, PxVec3 velo, PxVec3 accele, double lifetime)
	: transform(pos), vel(velo), accel(accele), lifeTime(lifetime)
{
	damping = 0.99;
	transform = physx::PxTransform(pos);
	
	PxSphereGeometry geo(1);
	PxShape* shape = CreateShape(geo);

	renderItem = new RenderItem(shape, &transform, Vector4(1, 0.5, 1, 1));
	RegisterRenderItem(renderItem);
	damping = 0.99;
}

Particle::Particle(Particle const& p)
{
	vel = p.vel;
	accel = p.accel;
	transform = PxTransform(p.transform.p);
	PxShape* shape = CreateShape(PxSphereGeometry(1));
	renderItem = new RenderItem(shape, &transform, Vector4(1, 0.5, 1, 1));

	mass = 1;
	center = p.center;
	ratio = p.ratio;
	lifeTime = p.lifeTime;
	damping = 0.995;
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::Integrate(double t, IntegrationType type)
{
	if (type == EULER) {
		vel = vel + accel * t;  // Actualiza la velocidad con la aceleración
		vel = vel * pow(damping, t);  // Aplica el damping a la velocidad
		transform.p = transform.p + vel * t;  // Actualiza la posición con la nueva velocidad
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


