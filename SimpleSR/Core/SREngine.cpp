#include "SREngine.h"
#include "ModelFactory.h"

SREngine::~SREngine()
{
    ShutDown();
}

void SREngine::Init()
{
    m_Camera = new Camera();
    m_Camera->Transform->SetPosition(0, 0, -10);
    m_Camera->UpdateMatrix();
    m_Camera->SetNearClipPlane(1);
    m_Camera->SetFarClipPlane(50);
    //m_Target = ModelFactory::GetQuad();
    m_Target = ModelFactory::GetCube();
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
