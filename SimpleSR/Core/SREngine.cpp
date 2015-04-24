#include "SREngine.h"
#include "ModelFactory.h"

SREngine::~SREngine()
{
    ShutDown();
}

void SREngine::Init()
{
    m_Camera = new Camera();
    m_Camera->Transform->SetPosition(0, 0, 0);
    m_Camera->UpdateMatrix();
    m_Target = ModelFactory::GetQuad();
}

void SREngine::Update()
{
    m_Camera->Render(m_Target);
}

void SREngine::ShutDown()
{
    delete m_Camera;
    m_Camera = nullptr;
}
