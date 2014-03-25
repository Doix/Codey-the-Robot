#include "TutorialText.h"

#include <sstream>
#include <vector>
#include "Sprite.h"
#include "Game.h"

namespace{
	const int TEXT_X_POS = 350;
	const int TEXT_Y_POS = 150;
	const int TEXT_WIDTH = 500;
	const int TEXT_HEIGHT = 200;

	const int MARGIN = 20;

	const int BOX_X_POS = TEXT_X_POS - MARGIN;
	const int BOX_Y_POS = TEXT_Y_POS - MARGIN;
	const int BOX_WIDTH = TEXT_WIDTH + MARGIN;
	const int BOX_HEIGHT = TEXT_HEIGHT + MARGIN;
	
	const int PORTRAIT_BOX_WIDTH = 200;
	const int PORTRAIT_BOX_X_POS = BOX_X_POS - PORTRAIT_BOX_WIDTH;

	const std::string TEXT_BOX_PATH = "content/Font/textBox.png";

	const int CODEY_ID = 0;
	const int LOOPY_ID = 1;

	const std::string CODEY_FILE_PATH = "content/codey.png";

	const int LOOPY_HEIGHT = 60;
	const int LOOPY_WIDTH = 44;
	const std::string LOOPY_FILE_PATH = "content/loopy.png";

}


TutorialText::TutorialText(Graphics& graphics) : tutorialLine(0), addSpeakerCount(-1), tutorialComplete(true), firstText(false){
	
	//get Sprite for the text/portrait box
	tutorialBox.reset(new Sprite(graphics, TEXT_BOX_PATH, 2, 2, 249, 40));
	initSprites(graphics);


}

TutorialText::~TutorialText(){


}

void TutorialText::draw(Graphics& graphics) const{
	renderTextBox(graphics);

	if (currentSpeakerNo < totalSpeakers){
		graphics.renderText(std::get<0>(tutorialText[currentSpeakerNo])[currentLineNo], TEXT_X_POS, TEXT_Y_POS, TEXT_WIDTH);
	}	
}


void TutorialText::setTutorialText(std::string message, int speakerId){
	++totalSpeakers;

	std::tuple < vector<std::string>, int > temp;

	tutorialText.push_back(temp);

	std::get<1>(tutorialText[totalSpeakers - 1]) = speakerId;
	std::stringstream ss(message);
	std::string tutText;
	while (std::getline(ss, tutText)) {
		tutText += "\n\n Hit \'Enter\' to continue";
		std::get<0>(tutorialText[totalSpeakers - 1]).push_back(tutText);
	}

	if (firstText){
		currentSpeakerNoOfLines = std::get<0>(tutorialText[addSpeakerCount]).size();
		tutorialComplete = false;
		firstText = false;
	}
}

int TutorialText::getSpeakerId(std::string speaker){
	if (speaker == "Codey"){
		return CODEY_ID;
	}
	else if (speaker == "Loopy"){
		return LOOPY_ID;
	}
}

void TutorialText::renderTextBox(Graphics& graphics) const{
	tutorialBox->draw(graphics, PORTRAIT_BOX_X_POS, BOX_Y_POS, PORTRAIT_BOX_WIDTH, BOX_HEIGHT);
	speakerSprites.at(currentSpeakerId)->draw(graphics, PORTRAIT_BOX_X_POS + 50, BOX_Y_POS+50, 80,80);
	tutorialBox->draw(graphics, BOX_X_POS, BOX_Y_POS, BOX_WIDTH, BOX_HEIGHT);
}

void TutorialText::nextTutorialText(){

	if (currentLineNo < currentSpeakerNoOfLines){
		++currentLineNo;
	}
	else if(currentSpeakerNo < totalSpeakers){
		++currentSpeakerNo;
		currentLineNo = 0;
		currentSpeakerNoOfLines = std::get<0>(tutorialText[currentSpeakerNo]).size();
		currentSpeakerId = std::get<1>(tutorialText[currentSpeakerNo]);
	}
	else{
		tutorialComplete = true;
	}		
}

void TutorialText::initSprites(Graphics& graphics){
	speakerSprites[CODEY_ID] = std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		CODEY_FILE_PATH,
		0, 0,
		Game::TILE_SIZE, Game::TILE_SIZE, 15, 2));

	speakerSprites[LOOPY_ID] = std::unique_ptr<Sprite>(new AnimatedSprite(
		graphics,
		LOOPY_FILE_PATH,
		150, 944,
		LOOPY_WIDTH, LOOPY_HEIGHT, 10, 3));
}
