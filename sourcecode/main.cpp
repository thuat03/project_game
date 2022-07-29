#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include<chrono>
#include<ctime>
using namespace std::chrono;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const int FAIL_MAX = 20;
int REDUCE_X = 5;
const int fps = 60;
int score = 0;
int fail = 0;
enum Status
{
	RUN = 0,
	UP = 1,
	DOWN_1 = 2,
	DOWN_2 = 3,
	DOWN_3 = 4,
	TOTAL = 5
};
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* bg = NULL;
SDL_Texture* up_icon = NULL;
SDL_Texture* down_icon = NULL;
Mix_Music* music = NULL;
Mix_Chunk* perfect = NULL;
Mix_Chunk* good = NULL;
SDL_Rect rectBG = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
SDL_Rect rect_up_icon = { 184,201,32,33 };
SDL_Rect rect_down_icon = { 184,331,32,33 };

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer*& renderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}
class Aya
{
	const int RUN_FRAME = 7;
	const int UP_FRAME = 12;
	const int DOWN_FRAME = 10;
	int frame_run = 0;
	int frame_up = 0;
	int frame_down_1 = 0;
	int frame_down_2 = 0;
	int frame_down_3 = 0;
	Status STATUS = RUN;


public:
	SDL_Texture* img_run[7];
	SDL_Texture* img_up[12];
	SDL_Texture* img_down_1[10];
	SDL_Texture* img_down_2[10];
	SDL_Texture* img_down_3[10];
	SDL_Rect rect_run[7];
	SDL_Rect rect_up[12];
	SDL_Rect rect_down_1[10];
	SDL_Rect rect_down_2[10];
	SDL_Rect rect_down_3[10];
	
	Aya()
	{
		this->img_run[0] = loadTexture("data/image/aya_run/aya1.png", renderer);
		this->img_run[1] = loadTexture("data/image/aya_run/aya2.png", renderer);
		this->img_run[2] = loadTexture("data/image/aya_run/aya3.png", renderer);
		this->img_run[3] = loadTexture("data/image/aya_run/aya4.png", renderer);
		this->img_run[4] = loadTexture("data/image/aya_run/aya5.png", renderer);
		this->img_run[5] = loadTexture("data/image/aya_run/aya6.png", renderer);
		this->img_run[6] = loadTexture("data/image/aya_run/aya7.png", renderer);

		this->img_up[0] = loadTexture("data/image/aya_up/aya1.png", renderer);
		this->img_up[1] = loadTexture("data/image/aya_up/aya2.png", renderer);
		this->img_up[2] = loadTexture("data/image/aya_up/aya3.png", renderer);
		this->img_up[3] = loadTexture("data/image/aya_up/aya4.png", renderer);
		this->img_up[4] = loadTexture("data/image/aya_up/aya5.png", renderer);
		this->img_up[5] = loadTexture("data/image/aya_up/aya6.png", renderer);
		this->img_up[6] = loadTexture("data/image/aya_up/aya7.png", renderer);
		this->img_up[7] = loadTexture("data/image/aya_up/aya8.png", renderer);
		this->img_up[8] = loadTexture("data/image/aya_up/aya9.png", renderer);
		this->img_up[9] = loadTexture("data/image/aya_up/aya10.png", renderer);
		this->img_up[10] = loadTexture("data/image/aya_up/aya11.png", renderer);
		this->img_up[11] = loadTexture("data/image/aya_up/aya12.png", renderer);

		this->img_down_1[0] = loadTexture("data/image/aya_down/down1/aya1.png", renderer);
		this->img_down_1[1] = loadTexture("data/image/aya_down/down1/aya2.png", renderer);
		this->img_down_1[2] = loadTexture("data/image/aya_down/down1/aya3.png", renderer);
		this->img_down_1[3] = loadTexture("data/image/aya_down/down1/aya4.png", renderer);
		this->img_down_1[4] = loadTexture("data/image/aya_down/down1/aya5.png", renderer);
		this->img_down_1[5] = loadTexture("data/image/aya_down/down1/aya6.png", renderer);
		this->img_down_1[6] = loadTexture("data/image/aya_down/down1/aya7.png", renderer);
		this->img_down_1[7] = loadTexture("data/image/aya_down/down1/aya8.png", renderer);
		this->img_down_1[8] = loadTexture("data/image/aya_down/down1/aya9.png", renderer);
		this->img_down_1[9] = loadTexture("data/image/aya_down/down1/aya10.png", renderer);

		this->img_down_2[0] = loadTexture("data/image/aya_down/down2/aya1.png", renderer);
		this->img_down_2[1] = loadTexture("data/image/aya_down/down2/aya2.png", renderer);
		this->img_down_2[2] = loadTexture("data/image/aya_down/down2/aya3.png", renderer);
		this->img_down_2[3] = loadTexture("data/image/aya_down/down2/aya4.png", renderer);
		this->img_down_2[4] = loadTexture("data/image/aya_down/down2/aya5.png", renderer);
		this->img_down_2[5] = loadTexture("data/image/aya_down/down2/aya6.png", renderer);
		this->img_down_2[6] = loadTexture("data/image/aya_down/down2/aya7.png", renderer);
		this->img_down_2[7] = loadTexture("data/image/aya_down/down2/aya8.png", renderer);
		this->img_down_2[8] = loadTexture("data/image/aya_down/down2/aya9.png", renderer);
		this->img_down_2[9] = loadTexture("data/image/aya_down/down2/aya10.png", renderer);

		this->img_down_3[0] = loadTexture("data/image/aya_down/down3/aya1.png", renderer);
		this->img_down_3[1] = loadTexture("data/image/aya_down/down3/aya2.png", renderer);
		this->img_down_3[2] = loadTexture("data/image/aya_down/down3/aya3.png", renderer);
		this->img_down_3[3] = loadTexture("data/image/aya_down/down3/aya4.png", renderer);
		this->img_down_3[4] = loadTexture("data/image/aya_down/down3/aya5.png", renderer);
		this->img_down_3[5] = loadTexture("data/image/aya_down/down3/aya6.png", renderer);
		this->img_down_3[6] = loadTexture("data/image/aya_down/down3/aya7.png", renderer);
		this->img_down_3[7] = loadTexture("data/image/aya_down/down3/aya8.png", renderer);
		this->img_down_3[8] = loadTexture("data/image/aya_down/down3/aya9.png", renderer);
		this->img_down_3[9] = loadTexture("data/image/aya_down/down3/aya10.png", renderer);



		this->rect_run[0] = { 73,297,93,103 };
		this->rect_run[1] = { 73,295,95,106 };
		this->rect_run[2] = { 76,295,87,106 };
		this->rect_run[3] = { 82,297,76,103 };
		this->rect_run[4] = { 82,295,75,107 };
		this->rect_run[5] = { 80,296,79,105 };
		this->rect_run[6] = { 78,296,85,105 };

		this->rect_up[0] = { 73,290,93,116 };
		this->rect_up[1] = { 73,246,93,103 };
		this->rect_up[2] = { 70,198,99,99 };
		this->rect_up[3] = { 73,170,93,95 };
		this->rect_up[4] = { 51,167,137,101 };
		this->rect_up[5] = { 54,167,131,102 };
		this->rect_up[6] = { 60,166,120,103 };
		this->rect_up[7] = { 64,158,112,120 };
		this->rect_up[8] = { 74,156,92,123 };
		this->rect_up[9] = { 77,169,86,98 };
		this->rect_up[10] = { 85,196,70,104 };
		this->rect_up[11] = { 73,244,93,108 };

		this->rect_down_1[0] = { 78,295,84,105 };
		this->rect_down_1[1] = { 63,299,113,97 };
		this->rect_down_1[2] = { 65,301,110,94 };
		this->rect_down_1[3] = { 65,303,109,91 };
		this->rect_down_1[4] = { 67,300,105,95 };
		this->rect_down_1[5] = { 71,296,97,104 };
		this->rect_down_1[6] = { 76,296,87,104 };
		this->rect_down_1[7] = { 77,297,85,101 };
		this->rect_down_1[8] = { 77,300,85,95 };
		this->rect_down_1[9] = { 75,297,89,101 };

		this->rect_down_2[0] = { 80,295,79,105 };
		this->rect_down_2[1] = { 67,298,106,100 };
		this->rect_down_2[2] = { 66,298,108,99 };
		this->rect_down_2[3] = { 66,300,107,96 };
		this->rect_down_2[4] = { 69,295,102,105 };
		this->rect_down_2[5] = { 69,294,102,108 };
		this->rect_down_2[6] = { 63,296,113,104 };
		this->rect_down_2[7] = { 60,296,120,104 };
		this->rect_down_2[8] = { 58,294,123,107 };
		this->rect_down_2[9] = { 61,294,117,108 };

		this->rect_down_3[0] = { 66,294,107,107 };
		this->rect_down_3[1] = { 65,296,109,103 };
		this->rect_down_3[2] = { 65,295,109,106 };
		this->rect_down_3[3] = { 66,294,108,108 };
		this->rect_down_3[4] = { 68,293,104,109 };
		this->rect_down_3[5] = { 71,294,98,108 };
		this->rect_down_3[6] = { 73,295,93,105 };
		this->rect_down_3[7] = { 72,294,95,107 };
		this->rect_down_3[8] = { 68,295,104,106 };
		this->rect_down_3[9] = { 67,295,106,106 };

	}
	~Aya()
	{
		for (int i = 0; i < 7; i++)
		{
			delete this->img_run[i];
		}
		for (int i = 0; i < 12; i++)
		{
			delete this->img_up[i];
		}
		for (int i = 0; i < 10; i++)
		{
			delete this->img_down_1[i];
			delete this->img_down_2[i];
			delete this->img_down_3[i];
		}
	}
	void render()
	{
		if (this->STATUS == RUN)
		{
			SDL_RenderCopy(renderer, img_run[frame_run / 6], NULL, &rect_run[frame_run / 6]);
			frame_run++;
			if (frame_run / 6 >= RUN_FRAME)
			{
				frame_run = 0;
			}
		}
		if (this->STATUS == UP)
		{
			SDL_RenderCopy(renderer, img_up[frame_up / 2], NULL, &rect_up[frame_up / 2]);
			frame_up++;
			if (frame_up / 2 >= UP_FRAME)
			{
				frame_up = 0;
				this->STATUS = RUN;
			}
		}
		if (this->STATUS == DOWN_1)
		{
			SDL_RenderCopy(renderer, img_down_1[frame_down_1 / 3], NULL, &rect_down_1[frame_down_1 / 3]);
			frame_down_1++;
			if (frame_down_1 / 3 >= DOWN_FRAME)
			{
				frame_down_1 = 0;
				this->STATUS = RUN;
			}
		}
		if (this->STATUS == DOWN_2)
		{
			SDL_RenderCopy(renderer, img_down_2[frame_down_2 / 3], NULL, &rect_down_2[frame_down_2 / 3]);
			frame_down_2++;
			if (frame_down_2 / 3 >= DOWN_FRAME)
			{
				frame_down_2 = 0;
				this->STATUS = RUN;
			}
		}
		if (this->STATUS == DOWN_3)
		{
			SDL_RenderCopy(renderer, img_down_3[frame_down_3 / 3], NULL, &rect_down_3[frame_down_3 / 3]);
			frame_down_3++;
			if (frame_down_3 / 3 >= DOWN_FRAME)
			{
				frame_down_3 = 0;
				this->STATUS = RUN;
			}
		}
		
	}
	void jump()
	{
		this->STATUS = UP;
		if (frame_up / 2 >= 1)
		{
			frame_up = 3;
		}
	}
	void down()
	{
		int i = rand() % 3 + 1;
		if (i == 1)
		{
			this->STATUS = DOWN_1;
			if (frame_down_1 / 3 >= 2)
			{
				frame_down_1 = 5;
			}
		}
		if (i == 2)
		{
			this->STATUS = DOWN_2;
			if (frame_down_2 / 3 >= 2)
			{
				frame_down_2 = 5;
			}
		}
		if (i == 3)
		{
			this->STATUS = DOWN_3;
			if (frame_down_3 / 3 >= 2)
			{
				frame_down_3 = 5;
			}
		}
	}
};

void printInfo()
{
	system("cls");
	std::cout << "Score: " << score << std::endl << std::endl;
	std::cout << "Speed: " << REDUCE_X << std::endl << std::endl;
	std::cout << "Failed: " << fail << std::endl << std::endl;
}

void do_perfect()
{
	Mix_PlayChannel(-1, perfect, 0);
	score += 2;
	printInfo();
}

void do_good()
{
	Mix_PlayChannel(-1, good, 0);
	score++;
	printInfo();
}

class Ballon
{
public:
	SDL_Texture* img;
	SDL_Rect rect={ 1500,170,53,60 };
	int v = 1;
	Ballon()
	{
		this->img = loadTexture("data/image/icon/ballon.png", renderer);
	}
	~Ballon()
	{
		delete this->img;
	}
	void reduceX()
	{
		rect.x -= REDUCE_X;
	}
	void reset()
	{
		if (rect.x < 0)
		{
			fail++;
			printInfo();
			rect.x = 1500;
			int i = rand() % 2;
			if (i == 1)
				rect.y = 170;
			else
				rect.y = 310;
		}
	}
	void resetBatBuoc()
	{
		rect.x = 1500;
		int i = rand() % 2;
		if (i == 1)
			rect.y = 170;
		else
			rect.y = 310;
	}
	void animation()
	{
		rect.y += v;
		if (rect.y > 315 || rect.y > 175 && rect.y < 180)
		{
			v = -v;
		}
		if (rect.y < 305 && rect.y>300 || rect.y < 165)
		{
			v = -v;
		}
	}
	void render()
	{
		int i = rand() % 2;
		if (i == 1)
		{
			animation();
		}
		SDL_RenderCopy(renderer, img, NULL, &rect);
		reduceX();
		reset();
	}
};
class Rainbow
{
public:
	SDL_Texture* img;
	SDL_Rect rect = { 1100,180,70,40 };
	int v = 1;
	Rainbow()
	{
		this->img = loadTexture("data/image/icon/rainbow.png", renderer);
	}
	~Rainbow()
	{
		delete this->img;
	}
	void reduceX()
	{
		rect.x -= REDUCE_X;
	}
	void reset()
	{
		if (rect.x < 0)
		{
			fail++;
			printInfo();
			rect.x = 1100;
			int i = rand() % 2;
			if (i == 1)
				rect.y = 180;
			else
				rect.y = 320;
		}
	}
	void resetBatBuoc()
	{
		rect.x = 1100;
		int i = rand() % 2;
		if (i == 1)
			rect.y = 180;
		else
			rect.y = 320;
	}
	void animation()
	{
		rect.y += v;
		if (rect.y > 325 || rect.y > 185 && rect.y < 190)
		{
			v = -v;
		}
		if (rect.y < 315 && rect.y>310 || rect.y < 175)
		{
			v = -v;
		}
	}
	void render()
	{
		int i = rand() % 2;
		if (i == 1)
		{
			animation();
		}
		SDL_RenderCopy(renderer, img, NULL, &rect);
		reduceX();
		reset();
	}
};

void init()
{
	window = SDL_CreateWindow("DUONG DUA AM NHAC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void loadSound()
{
	music = Mix_LoadMUS("data/music/sound/doan_tuyet_nang_di.wav");
	if (music == NULL)
	{
		std::cout << "Failed to load sound!";
	}
}

void close()
{
	Mix_FreeMusic(music);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Mix_Quit();
}
void check_crash_ballon_up(Ballon* ballon)
{
	if (abs(rect_up_icon.x - ballon->rect.x) < 60 && ballon->rect.y < 200)
	{
		if (abs(rect_up_icon.x - ballon->rect.x) < 30)
		{
			do_perfect();
		}
		else if (abs(rect_up_icon.x - ballon->rect.x) < 60)
		{
			do_good();
		}
		ballon->resetBatBuoc();
	}
}
void check_crash_ballon_down(Ballon* ballon)
{
	if (abs(rect_down_icon.x - ballon->rect.x) < 60 && ballon->rect.y > 290)
	{
		if (abs(rect_down_icon.x - ballon->rect.x) < 30)
		{
			do_perfect();
		}
		else if (abs(rect_down_icon.x - ballon->rect.x) < 60)
		{
			do_good();
		}
		ballon->resetBatBuoc();
	}
}
void check_crash_rainbow_up(Rainbow* rainbow)
{
	if (abs(rect_up_icon.x - rainbow->rect.x) < 60 && rainbow->rect.y < 200)
	{
		if (abs(rect_up_icon.x - rainbow->rect.x) < 30)
		{
			do_perfect();
		}
		else if (abs(rect_up_icon.x - rainbow->rect.x) < 60)
		{
			do_good();
		}
		rainbow->resetBatBuoc();
	}
}

void check_crash_rainbow_down(Rainbow* rainbow)
{
	if (abs(rect_down_icon.x - rainbow->rect.x) < 60 && rainbow->rect.y >290)
	{
		if (abs(rect_down_icon.x - rainbow->rect.x) < 30)
		{
			do_perfect();
		}
		else if (abs(rect_down_icon.x - rainbow->rect.x) < 60)
		{
			do_good();
		}
		rainbow->resetBatBuoc();
	}
}
void play(Aya* aya, Rainbow* rainbow, Ballon* ballon)
{
	SDL_Event e;
	bool running = true;
	if (ballon->img == NULL)
	{
		std::cout << "Unable to load file!";
	}
	while (running)
	{
		auto start = high_resolution_clock::now();

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			//if (e.key.repeat == 0 && e.type == SDL_KEYDOWN)
			if(e.type==SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_0)
				{
					Mix_PlayMusic(music, -1);
				}
				if (e.key.keysym.sym == SDLK_9)
				{
					Mix_HaltMusic();
				}
				if (e.key.keysym.sym == SDLK_w)
				{
					aya->jump();
					check_crash_ballon_up(ballon);
					check_crash_rainbow_up(rainbow);
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					aya->down();
					check_crash_ballon_down(ballon);
					check_crash_rainbow_down(rainbow);
				}
			}
			
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg, NULL, &rectBG);
		SDL_RenderCopy(renderer, up_icon, NULL, &rect_up_icon);
		SDL_RenderCopy(renderer, down_icon, NULL, &rect_down_icon);
		ballon->render();
		rainbow->render();
		aya->render();
		SDL_RenderPresent(renderer);
		REDUCE_X = 5 + score / 10;

		auto finish = high_resolution_clock::now();
		auto cal = duration_cast<milliseconds>(finish - start);

		if (fail == FAIL_MAX)return;

		if (cal.count() < 1000 / fps)
		{
			SDL_Delay(1000 / fps - cal.count());
		}
	}
}

int main(int argc, char* args[])
{
	srand(time(0));
	init();
	loadSound();
	Aya* aya = new Aya();
	Ballon* ballon = new Ballon();
	Rainbow* rainbow = new Rainbow();
	bg = loadTexture("data/image/image/background.png", renderer);
	up_icon = loadTexture("data/image/icon/up.png", renderer);
	down_icon = loadTexture("data/image/icon/down.png", renderer);
	perfect = Mix_LoadWAV("data/music/sfx/perfect.wav");
	good = Mix_LoadWAV("data/music/sfx/good.wav");
	printInfo();
	play(aya,rainbow,ballon);
	close();
	return 0;
}
