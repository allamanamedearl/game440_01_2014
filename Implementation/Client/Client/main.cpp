#include <ClientAPI.h>

#include "GameLobby.h"
#include "MainMenu.h"
#include "Credits.h"
#include "Options.h"

//-- Function Prototypes
void Update(double time);
void Draw();

int main(int argc, char* args[])
{
	////-- Initialize the API
	ClientAPI::Init();

	ClientAPI::SetCustomUpdate(Update);
	ClientAPI::SetCustomDraw(Draw);

	//--Call individual load methods
	MainMenu::Load();
	//Options::Load();
	//Credits::Load();
	//GameLobby::Load();

	//-- Start the APIs main loop
	ClientAPI::BeginMainLoop();

	//-- Quit the API once the APIs Main loop is over
	ClientAPI::Quit();
	return 0;
}

void Update(double time)
{
	//cout << "Entering Custom Update" << endl;
}

void Draw()
{
	//cout << "Entering Custom Draw" << endl;
}