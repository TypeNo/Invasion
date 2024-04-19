all: compile link

compile:
	g++ -c main.cpp -IC:/Library\SFML-2.5.1/include -DSFML_STATIC

link:
	g++ main.o -o main.exe -LC:/Library\SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -lopenal32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main 

clean:
	rm -f main *.o