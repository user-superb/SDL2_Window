# SDL2_Window
En este proyecto pongo a prueba algunas funcionalidades de SDL2, entre ellas esta la creación de ventanas, lectura de entrada (teclado y mouse), lectura de imagenes, control de eventos, ticks...

https://github.com/user-superb/SDL2_Window/assets/108239334/2410916d-fa34-47f0-8238-f97898aaddf6

# Como ejecutar
  Ejecutar el archivo ./executable.exe
# Como compilar
  Correr el comando
  ``g++ main.cpp $(pkg-config --cflags --libs sdl2) -lSDL2_image -o executable.exe``.
  Requiere dependencias:
    SDL2
    SDL_Image
