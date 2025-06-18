#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <IconsForkAwesome.h>
#include <imguiTools.h>
#include <logs.h>
#include <glui/glui.h>
#include <hitRender.h>
#include <raudio.h>

struct GameData
{
	glm::vec2 rectPos = {100,100};

}gameData;

constexpr float hitCirclesSize = 250.f;
constexpr float hitCirclesOffsetInit = 0.65f; // the initial distance form the left for the hit circles
constexpr float hitCirclesOffset = 0.08f; // the distance between the hit circles

gl2d::Texture targetCirclesTexture;
gl2d::TextureAtlasPadding targetCirclesAtlas;

gl2d::Renderer2D renderer;

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	//loading the saved data. Loading an entire structure like this makes savind game data very easy.
	platform::readEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));

	targetCirclesTexture.loadFromFile(RESOURCES_PATH "game resc/stiched/hit circle-stitched.png");
	targetCirclesAtlas = gl2d::TextureAtlasPadding(2, 1,targetCirclesTexture.GetSize().x, targetCirclesTexture.GetSize().y);

	platform::log("Init");

	return true;
}


//IMPORTANT NOTICE, IF YOU WANT TO SHIP THE GAME TO ANOTHER PC READ THE README.MD IN THE GITHUB
//https://github.com/meemknight/cmakeSetup
//OR THE INSTRUCTION IN THE CMAKE FILE.
//YOU HAVE TO CHANGE A FLAG IN THE CMAKE SO THAT RESOURCES_PATH POINTS TO RELATIVE PATHS
//BECAUSE OF SOME CMAKE PROGBLMS, RESOURCES_PATH IS SET TO BE ABSOLUTE DURING PRODUCTION FOR MAKING IT EASIER.

bool gameLogic(float deltaTime, platform::Input &input)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h
	
	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion

	glm::vec4 inputs = {
		(input.isButtonHeld(platform::Button::Left) | input.isButtonHeld(platform::Button::D)) ? 1.0f : 0.0f,
		(input.isButtonHeld(platform::Button::Down) | input.isButtonHeld(platform::Button::F)) ? 1.0f : 0.0f,
		(input.isButtonHeld(platform::Button::Up) | input.isButtonHeld(platform::Button::J)) ? 1.0f : 0.0f,
		(input.isButtonHeld(platform::Button::Right) | input.isButtonHeld(platform::Button::K)) ? 1.0f : 0.0f,
	};

	std::cout << "Inputs: " << inputs.x << ", " << inputs.y << ", " << inputs.z << ", " << inputs.w << std::endl;	

#pragma region render UI

#pragma region UI

	renderer.pushCamera();
	{
		glui::Frame f({ 0,0,w,h });
		
		glui::Box left = glui::Box().xLeftPerc(hitCirclesOffsetInit).yBottomPerc(-0.05).xDimensionPercentage(0.08).yAspectRatio(1);
		glui::Box down = glui::Box().xLeftPerc(hitCirclesOffsetInit + hitCirclesOffset).yBottomPerc(-0.05).xDimensionPercentage(0.08).yAspectRatio(1);
		glui::Box up = glui::Box().xLeftPerc(hitCirclesOffsetInit + hitCirclesOffset*2).yBottomPerc(-0.05).xDimensionPercentage(0.08).yAspectRatio(1);
		glui::Box right = glui::Box().xLeftPerc(hitCirclesOffsetInit + hitCirclesOffset*3).yBottomPerc(-0.05).xDimensionPercentage(0.08).yAspectRatio(1);

#pragma region  render hit circles
		if (inputs.x == 1)
		{
			renderer.renderRectangle(left, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(0, 0));
		}
		else
		{
			renderer.renderRectangle(left, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(1, 0));
		}
		if (inputs.y == 1)
		{
			renderer.renderRectangle(down, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(0, 0));
		}
		else
		{
			renderer.renderRectangle(down, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(1, 0));
		}
		if (inputs.z == 1)
		{
			renderer.renderRectangle(up, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(0, 0));
		}
		else
		{
			renderer.renderRectangle(up, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(1, 0));
		}
		if (inputs.w == 1)
		{
			renderer.renderRectangle(right, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(0, 0));
		}
		else
		{
			renderer.renderRectangle(right, targetCirclesTexture, Colors_White, {}, 0.f, targetCirclesAtlas.get(1, 0));
		}
#pragma endregion
		
	}

#pragma endregion

	renderer.flush();


	//ImGui::ShowDemoWindow();
	ImGui::PushMakeWindowNotTransparent();
	ImGui::Begin("Debug: ");

	ImGui::Text("Inputs: %.1f", inputs.x);
	ImGui::Text("Inputs: %.1f", inputs.y);
	ImGui::Text("Inputs: %.1f", inputs.z);
	ImGui::Text("Inputs: %.1f", inputs.w);

	ImGui::PopMakeWindowNotTransparent();
	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{

	//saved the data.
	platform::writeEntireFile(RESOURCES_PATH "gameData.data", &gameData, sizeof(GameData));

}
