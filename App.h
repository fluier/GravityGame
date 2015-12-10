#pragma once

#include<Adina\IMainGame.h>

#include"SimulationScreen.h"

class App : 
	public Adina::IMainGame
{
private:
	std::unique_ptr<SimulationScreen> m_simulationScreen = nullptr;
public:
	App();
	~App();
	// Called on initialization
	virtual void onInit() override;
	// For adding all screens
	virtual void addScreens() override;
	// Called when exiting
	virtual void onExit() override;
};

