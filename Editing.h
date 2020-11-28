#pragma once
#include "Subject.h"
#include "Point.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <unordered_map>
#include <unordered_set>
#include <memory>


class EditableLineNode;
class EditableLine;
class EditingGUI;
class LineFractal;
class StateMachine;
class Observer;
class EditingState;
struct Point;

class Editing : public Subject
{
public:
	Editing(EditingState* state, LineFractal* fractal);

	void handleEvent(sf::Event& event);

	const std::unordered_map<int, std::shared_ptr<EditableLineNode>>& getNodes() const;
	const std::unordered_map<int, std::shared_ptr<EditableLine>>& getLines() const;
	const std::shared_ptr<EditableLine> getBaseLine() const;
	const std::unordered_set<int>& getSelectedNodes() const;
	const LineFractal* getFractal() const;
	int getNumRecursions() const;
	void setNumRecursions(int num);
	sf::Vector2i getEditingFrameSize() const;
	sf::Vector2i getEditingFrameCenter() const;
	sf::Vector2i getMousePosInFrame() const;
	void recalcEditingFrameCenter(int window_width, int window_height);
	void fractalChanged();
	void moveNode(int node_id, double translation_x, double translation_y);

	void setHoveredNode(int node_id);
	int getHoveredNode() const;
	void clearHoveredNode();
	void selectOnlyHoveredNode();
	bool nodeIsHovered() const;

	void addLine();
	void removeSelectedLines();

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	enum Event{
		LINES_CHANGED, SELECTION_CHANGED, FRACTAL_CHANGED, MOUSE_MOVED, HOVERED_NODE_CHANGED
	};

	const int right_panel_width = 200;
	const int general_padding = 6;
	const int general_element_width = right_panel_width - (general_padding * 2);
private:

	void notifyAll(Event e) const;
	bool isWithinEditingFrame(sf::Vector2f point) const;

	std::list<Observer*> observers;
	std::unordered_map<int, std::shared_ptr<EditableLineNode>> nodes;
	std::unordered_set<int> selected_nodes;
	std::unordered_map<int, Point> dragging_nodes;
	std::unordered_map<int, std::shared_ptr<EditableLine>> lines;
	std::shared_ptr<EditableLine> base_line;

	// the id of the node that the user is hovering over in the gui
	int hovered_node;

	LineFractal* fractal;
	EditingState* state;

	int num_recursions = 7;
	bool mouse_moved_since_lpress = false;
	sf::Vector2i left_press_location;

	sf::Vector2i editing_frame_size;
	sf::Vector2i editing_frame_center;
	sf::Vector2i mouse_framepos;
};

