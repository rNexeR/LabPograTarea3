#include "Sho.h"

Sho::Sho(SDL_Renderer* renderer)
{
    sho_standing.push_back(IMG_LoadTexture(renderer,"Sho/standing/1.png"));
    sho_standing.push_back(IMG_LoadTexture(renderer,"Sho/standing/2.png"));
    sho_standing.push_back(IMG_LoadTexture(renderer,"Sho/standing/3.png"));
    sho_standing.push_back(IMG_LoadTexture(renderer,"Sho/standing/4.png"));

    jum.push_back(IMG_LoadTexture(renderer,"Sho/jumping/salto1.png"));
    jum.push_back(IMG_LoadTexture(renderer,"Sho/jumping/salto2.png"));
    jum.push_back(IMG_LoadTexture(renderer,"Sho/jumping/salto3.png"));
    jum.push_back(IMG_LoadTexture(renderer,"Sho/jumping/salto4.png"));
    jum.push_back(IMG_LoadTexture(renderer,"Sho/jumping/salto5.png"));

    SDL_QueryTexture(sho_standing[0], NULL, NULL, &rect.w, &rect.h);
    rect.x = 100;
    rect.y = 250;
    jumps = 0;

    frame = 0;
    animacion_sho = 0;
    piso = rect.y;
}

void Sho::draw(SDL_Renderer* renderer)
{
    if (jumping){

        SDL_RenderCopy(renderer, jum[animacion_sho], NULL, &rect);
        if(frame%150==0)
        {
            if (jumps<3){
                rect.y-=50;
                jumps++;
            }else{
                cout<<"DESJUMPING"<<endl;
                rect.y+=50;
            }

            animacion_sho++;
            if(animacion_sho>=jum.size())
                animacion_sho=0;
        }
        frame++;
        if (rect.y>=piso){
            jumping = false;
        }
    }else{
        SDL_RenderCopy(renderer, sho_standing[animacion_sho], NULL, &rect);
        if(frame%100==0)
        {
            animacion_sho++;
            if(animacion_sho>=sho_standing.size())
                animacion_sho=0;
        }
        frame++;
    }
}

void Sho::act()
{
    if (!jumping){
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_W])
        {
            rect.y--;
        }

        if(currentKeyStates[SDL_SCANCODE_A])
        {
            rect.x--;
        }

        if(currentKeyStates[SDL_SCANCODE_S])
        {
            rect.y++;
        }

        if(currentKeyStates[SDL_SCANCODE_D])
        {
            rect.x++;
        }

        //RUN
        if (currentKeyStates[SDL_SCANCODE_L] && currentKeyStates[SDL_SCANCODE_D])
        {
            rect.x+=2;
        }

        if (currentKeyStates[SDL_SCANCODE_L] && currentKeyStates[SDL_SCANCODE_A])
        {
            rect.x-=2;
        }
        if (currentKeyStates[SDL_SCANCODE_L] && currentKeyStates[SDL_SCANCODE_W])
        {
            rect.y-=2;
        }

        if (currentKeyStates[SDL_SCANCODE_L] && currentKeyStates[SDL_SCANCODE_S])
        {
            rect.y+=2;
        }

        //JUMP
        if (currentKeyStates[SDL_SCANCODE_C] )
        {
            jump();
        }
    }

}

void Sho::jump(){
    piso = rect.y;
    jumps = 0;
    desjumps = 3;
    jumping = true;
}

//void Sho::jumping(int piso, int cant){
//
//}


Sho::~Sho()
{
    //dtor
}
