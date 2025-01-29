build:
	g++ -w -std=c++14 -Wfatal-errors -mconsole \
		./src/*.cpp \
		-o game.exe \
		-I"C:\libsdl\SDL2\include" \
		-L"C:\libsdl\SDL2\lib" \
		-I".\lib\lua" \
		-L".\lib\lua" \
		-llua54 \
		-lmingw32 \
		-lSDL2main \
		-lSDL2_image \
		-lSDL2_ttf \
		-lSDL2_mixer \
		-lSDL2

clean:
	del game.exe

run:
	game.exe