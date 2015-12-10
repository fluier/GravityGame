#include<GL\glew.h>

#include "SimulationScreen.h"

#include <Adina\IMainGame.h>

#include"ScreenIndices.h"

#include"Planet.h"
#include"Star.h"

SimulationScreen::SimulationScreen(Adina::Window* window)
	:m_window(window)
{
	m_screenIndex = SCREEN_INDEX_GAMEPLAY;
}


SimulationScreen::~SimulationScreen()
{
}


int SimulationScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_MAINMENU;
}

int SimulationScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void SimulationScreen::build()
{

}

void SimulationScreen::destroy()
{

}

void SimulationScreen::onEntry()
{
	m_spriteBatch.init();
	m_hudSpriteBatch.init();

	initShaders();
	initGUI();
	/// Init camera
	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_camera.setScaleFactor(0.1f);
	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2, m_window->getScreenHeight() / 2));
	
	// Initialize sprite font
	m_spriteFont = new Adina::SpriteFont("Fonts/COMICATE.TTF", 64);

	/// Add planet red
	glm::vec2 planetPos = glm::vec2(400.0f, 0.0f);
	float planetSpeed = 20.0f;
	float planetDirection = -3.14 / 2.0f;
	float planetRadius = 30;
	float planetMass = 50;
	Adina::ColorRGBA8 planetColor = Adina::ColorRGBA8(255, 255, 000, 255);
	m_planetRed = new Planet("Reed ",planetPos, planetSpeed, planetDirection, planetRadius, planetMass, planetColor);
	
	/// Add planet green
	planetPos = glm::vec2(100.0f, 0.0f);
	planetSpeed = 40.0f;
	planetDirection = -3.14 / 2.0f;
	planetRadius = 30.3;
	planetMass = 20.0f;
	planetColor = Adina::ColorRGBA8(000, 255, 000, 255);
	m_planetGreen = new Planet("Green",planetPos, planetSpeed, planetDirection, planetRadius, planetMass, planetColor);

	m_orbs.push_back(m_planetRed);
	m_orbs.push_back(m_planetGreen);


	for (int i = 0; i < m_orbs.size(); i++){
		m_planets.push_back(*&m_orbs[i]);
	}
	const glm::vec2 starPos = glm::vec2(0.0f, 0.0f);
	const float starRadius = 40.1f;
	const float starMass = 100000.0f;
	Adina::ColorRGBA8 starColor = Adina::ColorRGBA8(255, 255, 000, 255);
	m_star = new Star("Stea",starPos, starRadius, starMass, starColor);
	m_orbs.push_back(m_star);
}

void SimulationScreen::onExit()
{

}

void SimulationScreen::update(float deltaTim)
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt)) {
		m_game->onSDLEvent(evnt);
		m_camera.onSDLEvent(evnt);
		m_gui.onSDLEvent(evnt);
	}
	m_camera.update();
	m_hudCamera.update();
	m_gui.update();
	for (int i = 0; i < m_orbs.size() - 1; i++){
		m_orbs[i]->update();
		m_orbs[i]->gravitateTo(*m_orbs.back());
	}
}

void SimulationScreen::draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0
	m_textureProgram.setUniform1i("mySampler", 0);

	// Grab the camera matrix
	m_textureProgram.setUniformMatrix4fv("P", m_camera.getCameraMatrix());

	m_spriteBatch.begin();

	// Draw balls
	for (int i = 0; i < m_orbs.size(); i++){
		m_orbs[i]->draw(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	drawHood();

	m_textureProgram.unuse();
	m_gui.draw();
}
void SimulationScreen::initGUI()
{
	// Init the UI
	m_gui.init("GUI");
	m_gui.loadScheme("TaharezLook.scheme");
	m_gui.setFont("DejaVuSans-10");
	//// Aducem butoanele


	CEGUI::PushButton* plusRedPlanetMassButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.90f, 0.02f, 0.1f, 0.05f), glm::vec4(0.0f), "plusRedPlanetMassButton"));
	plusRedPlanetMassButton->setText("+ Planet Red Mass");
	// Set the event to be called when we click
	plusRedPlanetMassButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SimulationScreen::onPlusRedPlanetMassButton, this));



	CEGUI::PushButton* plusGreenPlanetSpeedButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.90f, 0.1f, 0.1f, 0.05f), glm::vec4(0.0f), "plusGreenPlanetSpeedButton"));
	plusGreenPlanetSpeedButton->setText("+ Green Speed");
	// Set the event to be called when we click
	plusGreenPlanetSpeedButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SimulationScreen::onPlusGreenPlanetSpeedButton, this));

	CEGUI::PushButton* minusGreenPlanetSpeedButton = static_cast<CEGUI::PushButton*>(m_gui.createWidget("TaharezLook/Button", glm::vec4(0.90f, 0.2f, 0.1f, 0.05f), glm::vec4(0.0f), "minusGreenPlanetSpeedButton"));
	minusGreenPlanetSpeedButton->setText("- Green Speed");
	// Set the event to be called when we click
	minusGreenPlanetSpeedButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&SimulationScreen::onMinusGreenPlanetSpeedButton, this));

}
void SimulationScreen::initShaders()
{
	// Compile our texture shader
	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();
}
void SimulationScreen::drawHood(){
	char buffer[256];
	char* planet[2];

	float offset = 36.0f;
	glm::mat4 projectionMatrix = m_hudCamera.getCameraMatrix();
	m_textureProgram.setUniformMatrix4fv("P", projectionMatrix);

	m_hudSpriteBatch.begin();

	sprintf_s(buffer, "%s mass: %f Distance %f", m_planetRed->getName(), m_planetRed->getMass(), m_planetRed->distanceTo(*m_star));
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, offset),
		glm::vec2(0.5), 0.0f, Adina::ColorRGBA8(255, 255, 255, 255));
	offset -= 36.0f;

	sprintf_s(buffer, "%s mass: %f Distance %f", m_planetGreen->getName(), m_planetGreen->getMass(), m_planetGreen->distanceTo(*m_star));
	m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(0, offset),
		glm::vec2(0.5), 0.0f, Adina::ColorRGBA8(255, 255, 255, 255));


	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();
}
bool SimulationScreen::onPlusRedPlanetMassButton(const CEGUI::EventArgs& e)
{
	m_planetRed->increaseMass(100.0f);
	return true;
}
bool SimulationScreen::onPlusGreenPlanetSpeedButton(const CEGUI::EventArgs& e)
{
	//m_planetGreen->increaseSpeed(0.00001f);
	return true;
}
bool SimulationScreen::onMinusGreenPlanetSpeedButton(const CEGUI::EventArgs& e)
{
	//m_planetGreen->decreaseSpeed(0.00001f);
	return true;
}
