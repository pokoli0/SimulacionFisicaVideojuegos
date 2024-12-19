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


    pSystem->addGravity(PxVec3(0,-9.8f,0));

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
    createKitchen();

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
            PxVec4 newColor = calculatePotatoColor(p->cookingTime);
            p->setColor(newColor);
        }
    }

    for (auto it = potatoesB.begin(); it != potatoesB.end(); ) {
        RigidBody* potato = *it;

        // Actualizar tiempo de cocción
        if (potato->isCooking) {
            potato->cookingTime += t;

            // Cambiar color según el tiempo
            if (potato->cookingTime > 20) {
                potato->setColor(PxVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Negro
            }

            // Si pasa demasiado tiempo, generar fuego
            if (potato->cookingTime > 30 && !potato->isOnFire) {
                potato->isOnFire = true;
                generateFire(potato->getBody()->getGlobalPose().p);
            }
        }

        ++it;
    }

    checkPanLimits();
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

    case 'E':
        //pSystem.toggleWind();
        break;

    case 'L':
        addSalt();
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
    if (oilLevel >= 12) return; // limite

    // Dimensiones ajustadas a la sartén
    float oilHeight = (1.0f / 3.0f) * (oilLevel + 1);
    float panWidth = 19;
    float panDepth = 20.0f;

    // Crear la partícula que representa el aceite
    PxVec3 position(0, -4.0f + oilHeight / 2.0f, 0); // Ajustar al nivel correspondiente
    PxVec4 color(1.0f, 0.9f, 0.0f, 1.0f);            // Amarillo aceitoso
    PxBoxGeometry oilGeometry(panWidth / 2, oilHeight / 2, panDepth / 2);

    Particle* oil = new Particle(position, PxVec3(0, 0, 0), 1.0, color, oilGeometry, true);

    oilLevel++;
}

void Kitchen::addPotatoes()
{
    if (potatoes >= maxPotatoes) return;

    RigidBody* r = buoySystem->generateFloatingPotato(physics, scene);
    
    if (pSystem) pSystem->addRigidBody(r); // para que tengan gravedad

    potatoesB.push_back(r);

    r->isCooking = true;

    potatoes++;
}

void Kitchen::addSalt()
{
    const float radius = 5.0f;
    const float height = 20.0f; 
    const float mass = 5.0f;  
    const PxVec4 color(1.0f, 1.0f, 1.0f, 1.0f); 

    for (int i = 0; i < saltDensity; ++i) 
    {
        float angle = i * (2.0f * PxPi / saltDensity);
        const float x = radius * cos(angle);
        const float z = radius * sin(angle);
        PxVec3 position(x, height, z);

        // tensor de inercia aleatorio
        const PxVec3 inertiaTensor(
            0.05f + static_cast<float>(rand()) / RAND_MAX * 0.2f, // Entre 0.05 y 0.15
            0.05f + static_cast<float>(rand()) / RAND_MAX * 0.2f,
            0.05f + static_cast<float>(rand()) / RAND_MAX * 0.2f
        );

        PxBoxGeometry geometry(0.2f, 0.2f, 0.2f);

        RigidBody* salt = new RigidBody(physics, scene, geometry, PxTransform(position), mass, inertiaTensor, PxVec3(0, -2, 0), color);

        rigidBodies.push_back(salt);
    }
}


PxVec4 Kitchen::calculatePotatoColor(float elapsedTime)
{
    // Rango de tiempo (por ejemplo, de 0 a 10 segundos)
    const float maxTime = 10.0f;

    // Colores inicial y final
    const PxVec4 startColor(1.0f, 1.0f, 0.0f, 1.0f);  // Amarillo claro
    const PxVec4 endColor(0.5f, 0.3f, 0.0f, 1.0f);    // Marrón

    // Interpolación lineal
    float alpha = (elapsedTime / maxTime < 1.0f) ? elapsedTime / maxTime : 1.0f;

    return PxVec4(
        startColor.x * (1 - alpha) + endColor.x * alpha,
        startColor.y * (1 - alpha) + endColor.y * alpha,
        startColor.z * (1 - alpha) + endColor.z * alpha,
        1.0f
    );
}

void Kitchen::checkPanLimits()
{
    const float panWidth = 20.0f;
    const float panDepth = 20.0f;

    for (auto it = potatoesB.begin(); it != potatoesB.end(); ) {
        RigidBody* potato = *it;
        PxVec3 position = potato->getBody()->getGlobalPose().p;

        // Si la patata está fuera de los límites de la sartén
        if (std::abs(position.x) > panWidth / 2 || std::abs(position.z) > panDepth / 2) {
            // Eliminar del sistema de flotación
            buoySystem->removeRigidBody(potato);

            // Detener el cambio de color (desactivar cocción)
            potato->isCooking = false;

            // Eliminar la patata de la lista
            it = potatoesB.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Kitchen::generateFire(const PxVec3& position) 
{
    pSystem->addGenerator(NORMAL,
        position,                 // Posición del generador
        PxVec3(0, 5, 0),         // Dirección hacia arriba
        50,                       // Tasa de generación
        PxVec3(1,1,1),          // Desviación de velocidad
        10,                       // Rango
        5,                        // Rango de spawn
        GenDistribution::NORMALDIST, // Distribución normal
        50,                       // Ratio de partículas
        5,                         // Vida útil de las partículas
        30                          // radio vivo
    );

}