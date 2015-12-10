#pragma once

#include<Adina\IGameScreen.h>

#include<Adina\Window.h>
#include<Adina\Camera2D.h>
#include<Adina\GUI.h>
#include<Adina\SpriteBatch.h>
#include<Adina\GLSLProgram.h>

#include <Adina\SpriteFont.h>

#include<vector>
#include"Orb.h"

class Star;
class Planet;

class SimulationScreen : 
	public Adina::IGameScreen
{
private:
	Adina::Window* m_window;
	Adina::Camera2D m_camera;
	Adina::GUI m_gui;
	Adina::SpriteBatch m_spriteBatch; ///< Renders all the balls
	Adina::GLSLProgram m_textureProgram; ///< Shader for textures

	///// this is for the HUD
	Adina::SpriteBatch m_hudSpriteBatch;
	Adina::SpriteFont* m_spriteFont;
	Adina::Camera2D m_hudCamera; ///< Hud Camera

	std::vector<Orb*> m_orbs;
	std::vector<Orb*> m_planets;

	Star* m_star;

	Planet *m_planetRed;
	Planet *m_planetGreen;
public:
	SimulationScreen(Adina::Window* window);
	~SimulationScreen();

	virtual int getPreviousScreenIndex() const override;

	virtual int getNextScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update(float deltaTim) override;

	virtual void draw() override;

private:
	void initGUI();
	void initShaders();
	void drawHood();

	bool onPlusRedPlanetMassButton(const CEGUI::EventArgs& e);
	bool onPlusGreenPlanetSpeedButton(const CEGUI::EventArgs& e);
	bool onMinusGreenPlanetSpeedButton(const CEGUI::EventArgs& e);
};

