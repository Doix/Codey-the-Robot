#include "MessageBox.h"

#include <sstream>
#include <vector>
#include "Sprite.h"

namespace{
	const int TEXT_X_POS = 200;
	const int TEXT_Y_POS = 150;
	const int TEXT_WIDTH = 450;
	const int TEXT_HEIGHT = 200;

	const int MARGIN = 20;

	const int BOX_X_POS = TEXT_X_POS - MARGIN;
	const int BOX_Y_POS = TEXT_Y_POS - MARGIN;
	const int BOX_WIDTH = TEXT_WIDTH + 3 * MARGIN;
	const int BOX_HEIGHT = TEXT_HEIGHT + MARGIN;

	const std::string TEXT_BOX_PATH = "content/Font/textBox.png";
}

MessageBox::MessageBox(Graphics& graphics) :
currentLineNo(0),
currentNoOfLines(0),
firstText(true),
messageComplete(false)
{
	//get Sprite for the text/portrait box
	tutorialBox.reset(new Sprite(graphics, TEXT_BOX_PATH, 2, 2, 249, 40));
}


MessageBox::~MessageBox()
{
}

void MessageBox::draw(Graphics& graphics) const{
	renderTextBox(graphics);
	graphics.renderText(text[currentLineNo], TEXT_X_POS, TEXT_Y_POS, TEXT_WIDTH);
}
void MessageBox::nextText(){
	++currentLineNo;
	if (!(currentLineNo < currentNoOfLines)){
		messageComplete = true;
	}
}

void MessageBox::setText(std::string message){
	std::stringstream ss(message);
	std::string tutText;
	while (std::getline(ss, tutText)) {
		tutText += "\n\n Hit \'Enter\' to continue";
		text.push_back(tutText);
	}

	++currentNoOfLines;
}

void MessageBox::renderTextBox(Graphics& graphics) const{
	tutorialBox->draw(graphics, BOX_X_POS, BOX_Y_POS, BOX_WIDTH, BOX_HEIGHT);
}

