#include "../include/Game.hpp"

#include <cpr/cpr.h>
#include <crow.h>

#include "../../Logger/Debug.hpp"

Game::Game(sf::RenderWindow& window)
	:m_windowWidth(tgui::bindWidth(m_gui)), m_windowHeight(tgui::bindHeight(m_gui))
{
	m_window = &window;

	if (!m_menuMusic.openFromFile("assets/audio/music/menu_song.ogg"))
	{
		Debug::LogError("Error loading menu music");
		m_window->close();
	}
	m_menuMusic.setLoop(true);

	if (!m_gameMusic.openFromFile("assets/audio/music/game_song.ogg"))
	{
		Debug::LogError("Error loading game music");
		m_window->close();
	}
	m_gameMusic.setLoop(true);

	if (!m_clickSoundBuffer.loadFromFile("assets/audio/sound_effects/click.ogg"))
	{
		Debug::LogError("Error loading click sound");
		m_window->close();
	}
	m_clickSound.setBuffer(m_clickSoundBuffer);

	if (!m_checkboxSoundBuffer.loadFromFile("assets/audio/sound_effects/checkbox.ogg"))
	{
		Debug::LogError("Error loading checkbox sound");
		m_window->close();
	}
	m_checkBoxSound.setBuffer(m_checkboxSoundBuffer);

	if (!m_correctSoundBuffer.loadFromFile("assets/audio/sound_effects/correct.ogg"))
	{
		Debug::LogError("Error loading correct sound");
		m_window->close();
	}
	m_correctSound.setBuffer(m_correctSoundBuffer);

	if (!m_incorrectSoundBuffer.loadFromFile("assets/audio/sound_effects/incorrect.ogg"))
	{
		Debug::LogError("Error loading incorrect sound");
		m_window->close();
	}
	m_incorrectSound.setBuffer(m_incorrectSoundBuffer);

	tgui::Picture::Ptr background = tgui::Picture::create("assets/images/background.png");
	background->setSize(m_windowWidth, m_windowHeight);

	m_gui.setTarget(window);
	m_gui.setFont(tgui::Font("assets/fonts/Inter-Medium.ttf"));
	m_gui.add(background);
}

void Game::CreateMapMenu()
{
	m_mapMenu = tgui::Group::create();

	CreateNumberQuestionMenu();
	CreateMultipleAnswerQuestionMenu();

	m_gui.add(m_mapMenu);
	m_mapMenu->setVisible(false);

	return; // for now

	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:8080/map" });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();
		auto data = body["data"];

		for (auto& row : data.lo())
		{
			for (auto& cell : row.lo())
			{

				Debug::Log(cell["player"]);
				Debug::Log(cell["score"]);
				Debug::Log(cell["type"]);

				auto& player = cell["player"];

				Debug::Log(player["id"]);

				/*
				 * trebuie verificat daca playerul e altceva in afara de NONE
				 * daca da, atunci ar trebui facut un auto player = cell["player"]
				 * si abia apoi extreas din player datale cu player["id"]
				 * sau name sau etc, asa cred
				 */
			}
		}

		if (code == 200)
		{
			//m_matchSelectorMenu->setVisible(false);
			//m_mainMenu->setVisible(false);

			return;
		}
		else
		{
			return;
		}
	}
	catch (const std::exception&)
	{
		return;
	}
}
void Game::CreateNumberQuestionMenu()
{
	m_numberQuestionMenu = tgui::Group::create();

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(m_windowWidth * 1037.16 / 1270, m_windowHeight * 185.47 / 720);
	panel->setPosition(m_windowWidth * 116.41 / 1270, m_windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::EditBox::Ptr answerBox = tgui::EditBox::create();
	answerBox->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.84 / 720);
	answerBox->setPosition(m_windowWidth * 657.47 / 1270, m_windowHeight * 334.59 / 720);
	answerBox->setTextSize(20);
	answerBox->setInputValidator("[0-9]*");

	tgui::Button::Ptr submitButton = tgui::Button::create();
	submitButton->setSize(m_windowWidth * 177 / 1270, m_windowHeight * 177.03 / 720);
	submitButton->setPosition(m_windowWidth * 452 / 1270, m_windowHeight * 435 / 720);
	submitButton->setText("Submit");
	submitButton->setTextSize(20);

	tgui::Button::Ptr number0Button = tgui::Button::create();
	number0Button->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
	number0Button->setPosition(m_windowWidth * 452 / 1270, m_windowHeight * 335 / 720);
	number0Button->setText("0");
	number0Button->setTextSize(20);

	std::vector<tgui::Button::Ptr> numberButtons;

	std::vector<int> xPosition = { 161, 258, 355 };
	std::vector<int> yPosition = { 532, 433, 335 };

	for (uint8_t i = 1; i <= 3; i++)
	{
		for (auto j = 1; j <= 3; j++)
		{
			auto button = tgui::Button::create();
			button->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
			button->setPosition(m_windowWidth * xPosition[j - 1] / 1270, m_windowHeight * yPosition[i - 1] / 720);
			button->setText(std::to_string((i - 1) * 3 + j));
			button->setTextSize(20);

			numberButtons.push_back(button);
		}
	}

	tgui::Button::Ptr backspaceButton = tgui::Button::create();
	backspaceButton->setSize(m_windowWidth * 80 / 1270, m_windowHeight * 80 / 720);
	backspaceButton->setPosition(m_windowWidth * 549 / 1270, m_windowHeight * 335 / 720);
	backspaceButton->setText("Backspace");
	backspaceButton->setTextSize(20);

	m_numberQuestionMenu->add(panel);
	m_numberQuestionMenu->add(answerBox);
	m_numberQuestionMenu->add(submitButton);
	m_numberQuestionMenu->add(number0Button, "0");
	for (uint8_t i = 1; i <= 9; i++)
	{
		m_numberQuestionMenu->add(numberButtons[i - 1], std::to_string(i));
	}
	m_numberQuestionMenu->add(backspaceButton);

	submitButton->onClick([this, answerBox]()
		{
			m_clickSound.play();
	Debug::Log(answerBox->getText().toStdString());
	// submit to the server
		});

	for (auto i = 0; i <= 9; i++)
	{
		m_numberQuestionMenu->get<tgui::Button>(std::to_string(i))->onClick([this, answerBox, i]()
			{
				m_clickSound.play();
		answerBox->setText(answerBox->getText() + std::to_string(i)); });
	}

	backspaceButton->onClick([this, answerBox]()
		{
			m_clickSound.play();
	std::string text = answerBox->getText().toStdString();
	if (text.size() > 0) {
		text.pop_back();
	}
	answerBox->setText(text); });

	m_gui.add(m_numberQuestionMenu);
	m_numberQuestionMenu->setVisible(false);
}
void Game::CreateMultipleAnswerQuestionMenu()
{
	m_multipleAnswerQuestionMenu = tgui::Group::create();

	tgui::Button::Ptr panel = tgui::Button::create();
	panel->setEnabled(false);
	panel->setSize(m_windowWidth * 1037.16 / 1270, m_windowHeight * 185.47 / 720);
	panel->setPosition(m_windowWidth * 116.41 / 1270, m_windowHeight * 102 / 720);
	panel->setText("Question");
	panel->setTextSize(28);

	tgui::Button::Ptr answer1Button = tgui::Button::create();
	answer1Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer1Button->setPosition(m_windowWidth * 148.28 / 1270, m_windowHeight * 380.97 / 720);
	answer1Button->setText("Answer 1");
	answer1Button->setTextSize(20);

	tgui::Button::Ptr answer2Button = tgui::Button::create();
	answer2Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer2Button->setPosition(m_windowWidth * 675.28 / 1270, m_windowHeight * 380.97 / 720);
	answer2Button->setText("Answer 2");
	answer2Button->setTextSize(20);

	tgui::Button::Ptr answer3Button = tgui::Button::create();
	answer3Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer3Button->setPosition(m_windowWidth * 148.28 / 1270, m_windowHeight * 538.59 / 720);
	answer3Button->setText("Answer 3");
	answer3Button->setTextSize(20);

	tgui::Button::Ptr answer4Button = tgui::Button::create();
	answer4Button->setSize(m_windowWidth * 446.56 / 1270, m_windowHeight * 79.88 / 720);
	answer4Button->setPosition(m_windowWidth * 675.28 / 1270, m_windowHeight * 538.59 / 720);
	answer4Button->setText("Answer 4");
	answer4Button->setTextSize(20);

	m_multipleAnswerQuestionMenu->add(panel);

	m_multipleAnswerQuestionMenu->add(answer1Button);
	m_multipleAnswerQuestionMenu->add(answer2Button);
	m_multipleAnswerQuestionMenu->add(answer3Button);
	m_multipleAnswerQuestionMenu->add(answer4Button);

	int selected = NULL;

	answer1Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 1;

	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer1Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false); });

	answer2Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 2;

	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer2Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer3Button->setEnabled(false);
	answer4Button->setEnabled(false); });

	answer3Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 3;

	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer3Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer4Button->setEnabled(false); });

	answer4Button->onClick([&selected, answer1Button, answer2Button, answer3Button, answer4Button, this]()
		{
			m_clickSound.play();
	selected = 4;

	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Green);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Red);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Yellow);
	//answer4Button->getRenderer()->setBackgroundColor(tgui::Color::Blue);

	answer1Button->setEnabled(false);
	answer2Button->setEnabled(false);
	answer3Button->setEnabled(false); });

	m_gui.add(m_multipleAnswerQuestionMenu);
	m_multipleAnswerQuestionMenu->setVisible(false);
}

void Game::Update()
{
	auto response = cpr::Get(cpr::Url{ "http://localhost:8080/game_status" });
	auto body = crow::json::load(response.text);

	try
	{
		std::string message = body["message"].s();
		uint32_t code = body["code"].i();

		if (code == 200)
		{
			Debug::Log(message);
		}
	}
	catch (const std::exception& e)
	{
		Debug::Log(e.what());
	}
}
