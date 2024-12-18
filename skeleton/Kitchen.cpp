#include "Kitchen.h"

#include <algorithm>


Kitchen::Kitchen(PxPhysics* physics, PxScene* scene)
    : Scene(physics, scene)
{
    pSystem = new ParticleSystem();
    buoySystem = new ParticleSystem();

    systems.push_back(pSystem);
    systems.push_back(buoySystem);


    oilLevel = 0;


    //pSystem->addGravity(PxVec3(0,-9.8f,0));
    buoySystem->addGravity(PxVec3(0,-9.8f,0));

}

Kitchen::~Kitchen()
{
    for (auto rb : renderItems) {
        delete rb;
    }
}

void Kitchen::initScene()
{
    if (!defaultMaterial) {
        throw std::runtime_error("Default material no inicializado.");
    }

    // Vitro
    //createKitchen();

    // Sarten
    createPan();

    // Camara
    setupCamera();
}

void Kitchen::update(double t)
{
    for (auto s : systems) {
        s->update(t);
    }

    for (auto p : potatoesB) {
        if (p->isCooking) {
            p->cookingTime += t;
            PxVec4 newColor = calculateColor(p->cookingTime);
            p->setColor(newColor);
        }
    }
}

void Kitchen::keyPressed(unsigned char key, const PxTransform& camera)
{
    PX_UNUSED(camera);

    switch (toupper(key))
    {
    case 'O':
        addOil();
        break;

    case 'P':
        addPotatoes();
        break;

    default:
        break;
    }
}

void Kitchen::createKitchen()
{

    // Crear el plano para la encimera (marrón)
    PxRigidStatic* countertop = physics->createRigidStatic(PxTransform({ 0, -5, 0 }));
    PxShape* countertopShape = physics->createShape(PxBoxGeometry(50, 0.5, 50), *defaultMaterial);
    countertop->attachShape(*countertopShape);
    scene->addActor(*countertop);
    renderItems.push_back(new RenderItem(countertopShape, countertop, PxVec4(0.3f, 0.4f, 0.9f, 1.0f)));

    // Crear el plano para la vitrocerámica (negro clarito)
    PxRigidStatic* stovetop = physics->createRigidStatic(PxTransform({ 0, -4.9, 0 }));
    PxShape* stovetopShape = physics->createShape(PxBoxGeometry(30, 0.5, 30), *defaultMaterial);
    stovetop->attachShape(*stovetopShape);
    scene->addActor(*stovetop);
    renderItems.push_back(new RenderItem(stovetopShape, stovetop, PxVec4(0.1, 0.1, 0.1, 1.0f)));

}

void Kitchen::createPan()
{
    // Crear la sartén (cuerpo cuadrado)
    PxRigidStatic* panBase = physics->createRigidStatic(PxTransform({ 0, -4.4, 0 }));
    PxShape* panBaseShape = physics->createShape(PxBoxGeometry(10, 1, 10), *defaultMaterial);
    panBase->attachShape(*panBaseShape);
    scene->addActor(*panBase);
    renderItems.push_back(new RenderItem(panBaseShape, panBase, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    // Bordes de la sartén
    PxRigidStatic* panEdge1 = physics->createRigidStatic(PxTransform({ -10, -2.4, 0 }));
    PxShape* panEdgeShape1 = physics->createShape(PxBoxGeometry(0.5, 3, 10), *defaultMaterial);
    panEdge1->attachShape(*panEdgeShape1);
    scene->addActor(*panEdge1);
    renderItems.push_back(new RenderItem(panEdgeShape1, panEdge1, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge2 = physics->createRigidStatic(PxTransform({ 10, -2.4, 0 }));
    PxShape* panEdgeShape2 = physics->createShape(PxBoxGeometry(0.5, 3, 10), *defaultMaterial);
    panEdge2->attachShape(*panEdgeShape2);
    scene->addActor(*panEdge2);
    renderItems.push_back(new RenderItem(panEdgeShape2, panEdge2, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge3 = physics->createRigidStatic(PxTransform({ 0, -2.4, -10 }));
    PxShape* panEdgeShape3 = physics->createShape(PxBoxGeometry(10, 3, 0.5), *defaultMaterial);
    panEdge3->attachShape(*panEdgeShape3);
    scene->addActor(*panEdge3);
    renderItems.push_back(new RenderItem(panEdgeShape3, panEdge3, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    PxRigidStatic* panEdge4 = physics->createRigidStatic(PxTransform({ 0, -2.4, 10 }));
    PxShape* panEdgeShape4 = physics->createShape(PxBoxGeometry(10, 3, 0.5), *defaultMaterial);
    panEdge4->attachShape(*panEdgeShape4);
    scene->addActor(*panEdge4);
    renderItems.push_back(new RenderItem(panEdgeShape4, panEdge4, PxVec4(0.5f, 0.5f, 0.5f, 1.0f)));

    // Mango de la sartén
    PxRigidStatic* panHandle = physics->createRigidStatic(PxTransform({ 0, -3, -15 }));
    PxShape* panHandleShape = physics->createShape(PxBoxGeometry(1, 1, 5), *defaultMaterial);
    panHandle->attachShape(*panHandleShape);
    scene->addActor(*panHandle);
    renderItems.push_back(new RenderItem(panHandleShape, panHandle, PxVec4(0.0f, 0.0f, 0.0f, 1.0f)));

}

void Kitchen::setupCamera()
{
    if (!GetCamera()) {
        throw std::runtime_error("Camara no inicializada.");
    }

    const PxVec3 eye(0.0f, 30.0f, -30.0f); // Posicion
    const PxVec3 dir(0.0f, -1.0f, 1.0f);   // Direccion

    Snippets::Camera* camera = GetCamera();
    *camera = Snippets::Camera(eye, dir);
}

void Kitchen::addOil() 
{
    if (oilLevel >= 12) return; // No llenar más si ya está completo

    // Dimensiones ajustadas a la sartén
    float oilHeight = (1.0f / 3.0f) * (oilLevel + 1); // Cada nivel llena un tercio de la base
    float panWidth = 19;
    float panDepth = 20.0f;

    // Crear la partícula que representa el aceite
    PxVec3 position(0, -4.0f + oilHeight / 2.0f, 0); // Ajustar al nivel correspondiente
    PxVec4 color(1.0f, 0.9f, 0.0f, 1.0f);            // Amarillo aceitoso
    PxBoxGeometry oilGeometry(panWidth / 2, oilHeight / 2, panDepth / 2);

    Particle* oil = new Particle(position, PxVec3(0, 0, 0), 1.0, color, oilGeometry, true);

    if (pSystem) {
        pSystem->addParticle(oil);
    }

    oilLevel++;
}

void Kitchen::addPotatoes()
{
    if (potatoes >= maxPotatoes) return;

    RigidBody* r = buoySystem->generateFloatingPotato(physics, scene);
    potatoesB.push_back(r);

    r->isCooking = true;

    potatoes++;
}

PxVec4 Kitchen::calculateColor(float elapsedTime)
{
    // Rango de tiempo (por ejemplo, de 0 a 10 segundos)
    const float maxTime = 10.0f;

    // Colores inicial y final
    PxVec4 startColor(1.0f, 1.0f, 0.0f, 1.0f);  // Amarillo claro
    PxVec4 endColor(0.5f, 0.3f, 0.0f, 1.0f);    // Marrón

    // Interpolación lineal
    float alpha = (elapsedTime / maxTime < 1.0f) ? elapsedTime / maxTime : 1.0f;

    return PxVec4(
        startColor.x * (1 - alpha) + endColor.x * alpha,
        startColor.y * (1 - alpha) + endColor.y * alpha,
        startColor.z * (1 - alpha) + endColor.z * alpha,
        1.0f
    );
}