#include "SREngine.h"

SREngine::SREngine()
    :m_Camera(new Camera())
{}

SREngine::~SREngine()
{
    delete m_Camera;
    m_Camera = nullptr;
}

void SREngine::Init()
{
    m_Camera->Transform->SetPosition(0, 0, -10);
}

void SREngine::Update()
{
}

void SREngine::ShutDown()
{
}
