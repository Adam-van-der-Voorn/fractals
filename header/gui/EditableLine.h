#pragma once
#include "AbsLine.h"
#include <memory>


struct LFLine;
class EditableLineNode;

/**
Used to build a line fractal in the editing state.
Is made up of two selectable and transformable nodes- one for each endpoint on the line.
Only one node can be selected at a time.
**/
class EditableLine
{
public:
	EditableLine(int line_id, int node_id_1, int node_id_2, const AbsLine& line);
	
	/**
	Function allows access, unlike getBackNode()
	\return the back node
	**/
	EditableLineNode* backNode();

	/**
	Function allows access, unlike getFrontNode()
	\return the front node
	**/
	EditableLineNode* frontNode();

	/**
	\return the back node
	**/
	const EditableLineNode* getBackNode() const;

	/**
	\return the front node
	**/
	const EditableLineNode* getFrontNode() const;

	/**
	Sets the recusion status for this line.
	If true the line will recurse.
	**/
	void setRecursive(bool b);

	/**
	\return true if the line is recursive
	**/
	bool isRecursive() const;

	/**
	\param base_line the line that the LFLine will be based off
	\return a line fractal line relative to the given baseline
	**/
	LFLine toLFLine(AbsLine base_line) const;

	/**
	\return the absolute line
	**/
	AbsLine toAbsLine() const;

	/**
	\return this lines ID
	**/
	int getID() const;
	
private:
	int id;
	std::unique_ptr<EditableLineNode> back_node;
	std::unique_ptr<EditableLineNode> front_node;
	bool recursive = true;
};


