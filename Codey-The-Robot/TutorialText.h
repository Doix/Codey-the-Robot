#ifndef TUTORIAL_TEXT_H_
#define TUTORIAL_TEXT_H_

#include "Graphics.h"
#include <memory>
#include "Codey.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

#include <vector>

using std::vector;


class TutorialText
{
public:
	TutorialText(Graphics& graphics);
	~TutorialText();
	
	void draw(Graphics& graphics) const;
	void update(int elapsedTimeInMs);
	void nextText();

	bool tutorialComplete;
	void setText(std::string message, int speakerId);
private:
	void initSprites(Graphics& graphics);
	std::map<int, std::unique_ptr<Sprite>> speakerSprites;

	void renderTextBox(Graphics& graphics) const;

	//std::vector<std::string> tutorialText;
	vector<std::tuple<vector<std::string>, int>> tutorialText;
	int tutorialLine;
	std::unique_ptr<Sprite> tutorialBox;
	std::tuple<int, int, int> getSpriteDimension() const;

	int currentSpeakerNo;
	int currentLineNo;
	int totalSpeakers;
	int currentSpeakerNoOfLines;

	bool firstText;

	int currentSpeakerId;

};

#endif //TUTORIAL_TEXT_H_