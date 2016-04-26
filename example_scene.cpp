/* Copyright: (c) Kayne Ruse 2013-2016
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "example_scene.hpp"

#include <iostream>
#include <list>
#include <map>
#include <stdexcept>
#include <string>

constexpr SDL_Color WHITE = {255, 255, 255, 255};

ExampleScene::ExampleScene() {
	TTF_Init();

	//resource files
	textureLoader.Load(GetRenderer(), "rsc/", "button_back_30.png");
	font = TTF_OpenFont("rsc/coolvetica rg.ttf", 20);

	try {
		//the button object
		button.SetBackgroundTexture(GetRenderer(), textureLoader.Find("button_back_30.png"));
		button.SetText(GetRenderer(), font, WHITE, "Button");
		button.SetX(50);
		button.SetY(100);

		//text line
		textLine.SetText(GetRenderer(), font, WHITE, "Text Line");
		textLine.SetX(50);
		textLine.SetY(200);

		//text box
		textBox.PushLine(GetRenderer(), font, WHITE, "TextBox 1");
		textBox.PushLine(GetRenderer(), font, WHITE, "TextBox 2");
		textBox.PushLine(GetRenderer(), font, WHITE, "TextBox 3");
		textBox.SetX(50);
		textBox.SetY(300);

		//text field
		textField.SetText(GetRenderer(), font, WHITE, "Username...");
		textField.SetBounds({0, 0, 100, 20});
		textField.SetX(50);
		textField.SetY(400);
	}
	catch(std::exception& e) {
		std::cerr << SDL_GetError() << std::endl;
	}

	//debug
	std::cout << "Loaded textures: " << textureLoader.Size() << std::endl;
}

ExampleScene::~ExampleScene() {
	TTF_CloseFont(font);
	TTF_Quit();
}

//-------------------------
//frame phases
//-------------------------

void ExampleScene::FrameStart() {
	//
}

void ExampleScene::Update() {
	//
}

void ExampleScene::FrameEnd() {
	//
}

void ExampleScene::RenderFrame(SDL_Renderer* renderer) {
	button.DrawTo(renderer);
	textLine.DrawTo(renderer);
	textBox.DrawTo(renderer);
	textField.DrawTo(renderer);
}

//-------------------------
//input events
//-------------------------

void ExampleScene::MouseMotion(SDL_MouseMotionEvent const& event) {
	button.MouseMotion(event);
}

void ExampleScene::MouseButtonDown(SDL_MouseButtonEvent const& event) {
	button.MouseButtonDown(event);
	if (textField.MouseButtonDown(event)) {
		textField.SetText(GetRenderer(), font, WHITE, "");
	}
}

void ExampleScene::MouseButtonUp(SDL_MouseButtonEvent const& event) {
	button.MouseButtonUp(event);
}

void ExampleScene::MouseWheel(SDL_MouseWheelEvent const& event) {
	//
}

void ExampleScene::KeyDown(SDL_KeyboardEvent const& event) {
	//preference as a default
	switch(event.keysym.sym) {
		case SDLK_ESCAPE:
			QuitEvent();
		break;

		case SDLK_BACKSPACE:
			if (textField.GetFocus()) {
				textField.PopChars(GetRenderer(), font, WHITE, 1);
			}
		break;

		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			std::cout << textField.GetText() << std::endl;
			textField.SetText(GetRenderer(), font, WHITE, "");

		case SDLK_SPACE:
			SetSceneSignal(SceneSignal::EXAMPLE_SCENE);
		break;
	}
}

void ExampleScene::KeyUp(SDL_KeyboardEvent const& event) {
	//
}

void ExampleScene::TextInput(SDL_TextInputEvent const& event) {
	if (textField.GetFocus()) {
		textField.PushText(GetRenderer(), font, WHITE, event.text);
	}
}

void ExampleScene::TextEdit(SDL_TextEditingEvent const& event) {
	//
}