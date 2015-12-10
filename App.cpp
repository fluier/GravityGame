#include "App.h"

#include <Adina\ScreenList.h>

#include <Adina\IGameScreen.h>

///////==============================================================
App::App()
{
}
///////==============================================================
App::~App()
{
}
///////==============================================================
// Called on initialization
void App::onInit()
{

}
///////==============================================================
// For adding all screens
void App::addScreens()
{
	// this have to be in a specific order
	m_simulationScreen = std::make_unique<SimulationScreen>(&m_window);

	m_screenList->addScreen(m_simulationScreen.get());

	m_screenList->setScreen(m_simulationScreen->getScreenIndex());
}
///////==============================================================
// Called when exiting
void App::onExit()
{

}
///////==============================================================