/*Header User Interface
includes Texty or true text font and elements of spritedemo
*/
#include <SDL.h>
#include "SDL_ttf.h"
#include <vector>
#include <Texty.h>
#include <Sprite.h>


class UserInterface
{
public:
	UserInterface(int width, int height, SDL_Renderer* renderer, std::string fontName, int fontSize, bool visible, SDL_Color color);
	~UserInterface(void);

	//writes the text on the given coordinates
	void writeText(std::string text, int x, int y);
	

	//creates button and stores it in a vector of Button struc
	void makeButton(int x, int y, int, int height, SDL_Texture* texture, int id);

	// adds different sprites for a button when event like mouse click or over occurs
	void addSeqToButton(int index, std::string bEvent, int x, int y, SDL_Texture* texture);

	// show all buttons
	void showButtons();

	// takes an event and changes all the buttons' sprite frame
	void buttonhandler(SDL_Event event);



private:
		int width;
		int height;
		SDL_Renderer* renderer;
		
		TTF_Font* font;
		SDL_Color tColor; //default text color  is black
		bool visible;
		Texty* texty;
		Sprite* sprite;
		
		struct button
		{
			Sprite* Bsprite;
			SDL_Texture* bTexture;
			SDL_Rect box;
			std::string seqName;
			int id;
		};
	
	
		std::vector<button>Bvec;
		std::string seqList[4];
		int sbuttonIndex; 

		// might need a vector of integers
		//needs to send events to the gameboard and handle event with other teammates code.
		//need to load from rendered text to creat image

};
