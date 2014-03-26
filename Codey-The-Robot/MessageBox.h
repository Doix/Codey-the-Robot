#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include "Graphics.h"
#include <memory>
#include "Codey.h"
#include "Sprite.h"
#include <vector>

using std::vector;

class MessageBox
{
public:
	MessageBox(Graphics& graphics);
	~MessageBox();

	void draw(Graphics& graphics) const;
	void nextText();

	void setText(std::string message, int speakerId);
private:
	void renderTextBox(Graphics& graphics) const;
		
	vector<std::string> text;

	std::unique_ptr<Sprite> tutorialBox;

	int currentLineNo;	
	int currentNoOfLines;
	bool firstText;
	bool messageComplete;

};

#endif // MESSAGE_BOX_H