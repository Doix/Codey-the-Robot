#include "TutorialText.h"

#include <sstream>
#include <vector>
#include "Sprite.h"
#include "Game.h"

namespace{
	const int TEXT_X_POS = 350;
	const int TEXT_Y_POS = 150;
	const int TEXT_WIDTH = 450;
	const int TEXT_HEIGHT = 200;

	const int MARGIN = 20;

	const int BOX_X_POS = TEXT_X_POS - MARGIN;
	const int BOX_Y_POS = TEXT_Y_POS - MARGIN;
	const int BOX_WIDTH = TEXT_WIDTH + 3*MARGIN;
	const int BOX_HEIGHT = TEXT_HEIGHT + MARGIN;
	
	const int PORTRAIT_BOX_WIDTH = 200;
	const int PORTRAIT_BOX_X_POS = BOX_X_POS - PORTRAIT_BOX_WIDTH;

	const int PORTRAIT_X_POS = PORTRAIT_BOX_X_POS + 60;
	const int PORTRAIT_Y_POS = BOX_Y_POS + 50;

	const int PORTRAIT_CODEY_HEIGHT = 80;
	const int PORTRAIT_CODEY_WIDTH = 80;
	const int PORTRAIT_LOOPY_HEIGHT = 80;
	const int PORTRAIT_LOOPY_WIDTH = 60;

	const std::string TEXT_BOX_PATH = "content/Font/textBox.png";

	const int CODEY_ID = 0;
	const int LOOPY_ID = 1;

	const std::string CODEY_FILE_PATH = "content/codey.png";

	const int LOOPY_HEIGHT = 60;
	const int LOOPY_WIDTH = 44;
	const std::string LOOPY_FILE_PATH = "content/loopy.png";
}


TutorialText::TutorialText(Graphics& graphics) : 
currentSpeakerNo(0), 
currentLineNo(0),
totalSpeakers(0),
currentSpeakerNoOfLines(0), 
firstText(true), 
currentSpeakerId(0) 
{
	
	//get Sprite for the text/portrait box
	tutorialBox.reset(new Sprite(graphics, TEXT_BOX_PATH, 2, 2, 249, 40));
	initSprites(graphics);


}

TutorialText::~TutorialText(){


}

void TutorialText::draw(Graphics& graphics) const{
	renderTextBox(graphics);
	graphics.renderText(std::get<0>(tutorialText[currentSpeakerNo])[currentLineNo], TEXT_X_POS, TEXT_Y_POS, TEXT_WIDTH);		
}

void TutorialText::update(int elapsedTimeInMs){
	speakerSprites[currentSpeakerId]->update(elapsedTimeInMs);
}


void TutorialText::setText(std::string message, int speakerId){
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
		currentSpeakerNoOfLines = std::get<0>(tutorialText[totalSpeakers - 1]).size();
		currentSpeakerId = speakerId;
		tutorialComplete = false;
		firstText = false;
	}
}

void TutorialText::renderTextBox(Graphics& graphics) const{
	tutorialBox->draw(graphics, PORTRAIT_BOX_X_POS, BOX_Y_POS, PORTRAIT_BOX_WIDTH, BOX_HEIGHT);
	speakerSprites.at(currentSpeakerId)->draw(graphics, std::get<0>(getSpriteDimension()), PORTRAIT_Y_POS, std::get<1>(getSpriteDimension()), std::get<2>(getSpriteDimension()));
	tutorialBox->draw(graphics, BOX_X_POS, BOX_Y_POS, BOX_WIDTH, BOX_HEIGHT);
}

void TutorialText::nextText(){
	
	++currentLineNo;
	if (!(currentLineNo < currentSpeakerNoOfLines)){
		++currentSpeakerNo;
		if (currentSpeakerNo < totalSpeakers){
			currentLineNo = 0;
			currentSpeakerNoOfLines = std::get<0>(tutorialText[currentSpeakerNo]).size();
			currentSpeakerId = std::get<1>(tutorialText[currentSpeakerNo]);
		}
		else{
			tutorialComplete = true;
		}
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
		150, 943,
		LOOPY_WIDTH, LOOPY_HEIGHT, 10, 3));
}

std::tuple<int, int, int> TutorialText::getSpriteDimension() const{
	std::tuple<int, int, int> temp;
	switch (currentSpeakerId){
	case(0) ://codey
		std::get<0>(temp) = PORTRAIT_X_POS - 20;
		std::get<1>(temp) = PORTRAIT_CODEY_WIDTH;
		std::get<2>(temp) = PORTRAIT_CODEY_HEIGHT;
		break;
	case(1)://loopy
		std::get<0>(temp) = PORTRAIT_X_POS;
		std::get<1>(temp) = PORTRAIT_LOOPY_WIDTH;
		std::get<2>(temp) = PORTRAIT_LOOPY_HEIGHT;
		break;
	}
	return temp;
}