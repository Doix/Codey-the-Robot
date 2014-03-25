#include "TutorialText.h"

#include <sstream>
#include <vector>
#include "Sprite.h"

namespace{
	const int TEXT_X_POS = 105;
	const int TEXT_Y_POS = 74;
	const int TEXT_WIDTH = 500;
	const int TEXT_HEIGHT = 200;

	const int MARGIN = 20;

	const int BOX_X_POS = TEXT_X_POS - MARGIN;
	const int BOX_Y_POS = TEXT_Y_POS - MARGIN;
	const int BOX_WIDTH = TEXT_WIDTH + MARGIN;
	const int BOX_HEIGHT = TEXT_HEIGHT + MARGIN;

	const std::string TEXT_BOX_PATH = "content/Font/textBox.png";
}


TutorialText::TutorialText(Graphics& graphics, std::string message) : tutorialLine(0), tutorialComplete(false){

	setTutorialText(message);

	tutorialBox.reset(new Sprite(graphics, TEXT_BOX_PATH, 2, 2, 249, 40));


}

TutorialText::~TutorialText(){


}

void TutorialText::draw(Graphics& graphics) const{
	renderTextBox(graphics);

	if (tutorialText.size() > tutorialLine){
		graphics.renderText(tutorialText.at(tutorialLine), TEXT_X_POS, TEXT_Y_POS, TEXT_WIDTH);
	}	
}


void TutorialText::setTutorialText(std::string message){
	std::stringstream ss(message);
	std::string tutText;
	while (std::getline(ss, tutText)) {
		tutText += "\n\n Hit \'Enter\' to continue";
		tutorialText.push_back(tutText);
	}
}

void TutorialText::setTutorialSpeaker(){
}

void TutorialText::renderTextBox(Graphics& graphics) const{
	tutorialBox->draw(graphics, BOX_X_POS, BOX_Y_POS, BOX_WIDTH, BOX_HEIGHT);
}

void TutorialText::nextTutorialText(){
	++tutorialLine;
	if (tutorialLine >= tutorialText.size()){
		tutorialComplete = true;
	}
}