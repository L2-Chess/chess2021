del bin\prog.exe
gcc src/test3.c -o bin/prog -I include -L ./lib -l mingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
start bin\prog.exe
end
exit /B 0
