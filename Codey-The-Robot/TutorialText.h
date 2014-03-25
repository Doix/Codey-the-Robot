#ifndef TUTORIAL_TEXT_H_
#define TUTORIAL_TEXT_H_

#include "Graphics.h"
#include <memory>
#include "Codey.h"
#include "Sprite.h"

#include <vector>


class TutorialText
{
public:
	TutorialText(Graphics& graphics, std::string message);
	~TutorialText();
	
	void draw(Graphics& graphics) const;
	void nextTutorialText();

	bool tutorialComplete;
private:
	void setTutorialText(std::string message);
	void setTutorialSpeaker();

	void renderTextBox(Graphics& graphics) const;

	std::vector<std::string> tutorialText;
	int tutorialLine;
	std::unique_ptr<Sprite> tutorialBox;

};

#endif //TUTORIAL_TEXT_H_