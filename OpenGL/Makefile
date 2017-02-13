CALLBACK = Callback/Callback.cpp
DATA = Data/Data.cpp
ENTITY = Entity/Entity.cpp
GAMESTATE = GameState/GameState.cpp
GLEW = GLEW/GLEW.cpp
GLFW = GLFW/GLFW.cpp
SHADER = Shader/Shader.cpp
TEXTURE = Texture/Texture.cpp
VAO = VAO/VAO.cpp
VIDEOMODE = VideoMode/VideoMode.cpp
WINDOW = Window/Window.cpp
MAIN = main.cpp

CODE = $(CALLBACK) $(DATA) $(ENTITY) $(GAMESTATE) $(GLEW) $(GLFW) $(SHADER) $(TEXTURE) $(VAO) $(VIDEOMODE) $(WINDOW) $(MAIN)
FLAGS = -lGLEW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -std=c++11 -ldl -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -lSOIL -lsqlite3

exec: main
	./main

main:	$(CODE)
	g++ $(CODE) -o main $(FLAGS)

main_debug:	$(CODE)
	g++ $(CODE) -o main $(FLAGS) | less

exec_debug:	main
	./main | less

test: test.cpp
	g++ test.cpp -o test $(FLAGS)

world: world.cpp
	g++ world.cpp Simplex.cpp -o world -lsqlite3 -std=c++11