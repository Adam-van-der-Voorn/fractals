#pragma once
#include <vector>
#include <memory>
#include <TGUI/TGUI.hpp>
#include "State.h"
#include "Subject.h"

class LineFractal;
class ZoomBox;
class StateMachine;
class ViewingState;

class Viewing : public EventHandler, public Subject<Viewing>
{
public:
	Viewing(ViewingState* state, LineFractal* fractal);
	~Viewing();

	//inherited via EventHandler
	void handleEvent(sf::Event& event);

	//getters & setters
	ZoomBox* getZoomBox() const;

	/**
	\return the fractal being viewed
	**/
	const LineFractal* getFractal() const;

	enum Event {
		
	};

private:
	ViewingState* state;
	LineFractal* fractal;
	ZoomBox* zoom_box;
};

