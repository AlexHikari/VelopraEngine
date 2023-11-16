#ifndef VE_INPUT_EVENT_GENERATOR_H
#define VE_INPUT_EVENT_GENERATOR_H

#include <unordered_map>
#include <utility>
#include "InputTypes.h"
#include "VE_Event.h"

class InputEventGenerator {
public:
	void Update(); // Called every frame to update input states

	// Keyboard state methods
	bool IsKeyPressed(KeyCode key) const;
	bool IsKeyReleased(KeyCode key) const;

	// Mouse state methods
	bool IsMouseButtonPressed(MouseCode button) const;
	std::pair<float, float> GetMousePosition() const;
	float GetMouseX() const;
	float GetMouseY() const;

private:
	std::unordered_map<KeyCode, bool> keyStates;
	std::unordered_map<MouseCode, bool> mouseButtonStates;
	float mouseX, mouseY;

	// Methods to update internal state
	void UpdateKeyState(KeyCode key, bool pressed);
	void UpdateMouseButtonState(MouseCode button, bool pressed);
	void UpdateMousePosition(float x, float y);
};

#endif // VE_INPUT_EVENT_GENERATOR_H
