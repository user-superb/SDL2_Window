#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define VEL_X 1
#define VEL_Y 1

struct keyLayout
{
    int up;
    int down;
    int left;
    int right;
};


class Sprite
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect rect;
public:
    Sprite(std::string filePath, SDL_Renderer *rend, int PosX, int PosY, int scale);

    int getPosX(void) {
        return rect.x;
    }
    int getPosY(void) {
        return rect.y;
    }

    SDL_Texture* getTexture(void) {
        return texture;
    }
    SDL_Rect* getRect(void) {
        return &rect;
    }

    void setPosX(int PosX) {
        rect.x = PosX;
    }
    void setPosY(int PosY) {
        rect.y = PosY;
    }
};

Sprite::Sprite(std::string filePath, SDL_Renderer *rend, int PosX, int PosY, int scale)
{
    surface = IMG_Load(&filePath[0]);
    texture = SDL_CreateTextureFromSurface(rend, surface);
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_FreeSurface(surface);

    rect.w /= scale;
    rect.h /= scale;

    // std::cout << rect.h << std::endl;

    rect.x = PosX;
    rect.y = PosY;
}

int main(int argc, char** argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        std::cout << "SDL_Init " << SDL_GetError();
        return 0;
    }

    SDL_Window *window = SDL_CreateWindow("main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, SDL_WINDOW_OPENGL);
    
    if (!window) {
        std::cout << "SDL_CreateWindow" << SDL_GetError();
        SDL_Quit();
    }

    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!rend) {
        std::cout << "SDL_CreateRenderer" << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    /**/

    Sprite sprite0("./resources/dot.png", rend, 0, 0, 1);
    Sprite sprite1("./resources/dvd.png", rend, 0, 0, 2);

    /**/

    SDL_Color backgroudColour = { 255, 255, 255, 255};
    SDL_SetRenderDrawColor(rend, backgroudColour.r, backgroudColour.g, backgroudColour.b, backgroudColour.a);
    SDL_RenderClear(rend);
    SDL_RenderPresent(rend);

    /**/

    keyLayout keys = {0, 0, 0, 0};

    int speedX, speedY;

    int ballX, ballY;
    ballX = ballY = 5;

    /**/
    SDL_Event event;
    bool stop = 0;
    while (!stop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
            case SDL_QUIT:
                stop = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_W:
                    keys.up = 1;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    keys.down = 1;
                    break;
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    keys.left = 1;
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    keys.right = 1;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_UP:
                case SDL_SCANCODE_W:
                    keys.up = 0;
                    break;
                case SDL_SCANCODE_DOWN:
                case SDL_SCANCODE_S:
                    keys.down = 0;
                    break;
                case SDL_SCANCODE_LEFT:
                case SDL_SCANCODE_A:
                    keys.left = 0;
                    break;
                case SDL_SCANCODE_RIGHT:
                case SDL_SCANCODE_D:
                    keys.right = 0;
                    break;
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }

        speedX = speedY = 0;

        if ((keys.up == 1) && (keys.down == 0)) {
            speedY = -VEL_Y;
        } else if ((keys.up == 0) && (keys.down == 1)) {
            speedY = VEL_Y;
        }

        if ((keys.left == 0) && (keys.right == 1)) {
            speedX = VEL_X;
        } else if ((keys.left == 1) && (keys.right == 0)) {
            speedX = -VEL_X;
        }

        sprite0.setPosX(sprite0.getPosX() + speedX);
        sprite0.setPosY(sprite0.getPosY() + speedY);


        SDL_Rect* test;
        test = sprite1.getRect();
        test->w;

        if (((sprite1.getPosX() + sprite1.getRect()->w) > 1366) || sprite1.getPosX() < 0)
            ballX = -ballX;
        if (((sprite1.getPosY() + sprite1.getRect()->h) > 768) || sprite1.getPosY() < 0)
            ballY = -ballY;

        sprite1.setPosX(sprite1.getPosX() + ballX);
        sprite1.setPosY(sprite1.getPosY() + ballY);

        SDL_RenderCopy(rend, sprite0.getTexture(), NULL, sprite0.getRect());
        SDL_RenderCopy(rend, sprite1.getTexture(), NULL, sprite1.getRect());

        SDL_RenderPresent(rend);

        SDL_RenderClear(rend);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();

    return 0;
}