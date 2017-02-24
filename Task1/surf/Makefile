INC_DIR = include
SOURCE_DIR = src

surf: $(SOURCE_DIR)/main.o $(SOURCE_DIR)/load.o $(SOURCE_DIR)/fft.o \
            $(SOURCE_DIR)/Fourier.o $(SOURCE_DIR)/complex.o \
            $(SOURCE_DIR)/maths.o $(SOURCE_DIR)/error.o
	gcc -lm -o surf.exe $(SOURCE_DIR)/main.o $(SOURCE_DIR)/load.o \
          $(SOURCE_DIR)/fft.o $(SOURCE_DIR)/Fourier.o $(SOURCE_DIR)/complex.o \
          $(SOURCE_DIR)/maths.o $(SOURCE_DIR)/error.o
	mv surf.exe surf

$(SOURCE_DIR)/main.o: $(SOURCE_DIR)/main.c $(INC_DIR)/global.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/main.c
	cp main.o $(SOURCE_DIR)/main.o
	rm main.o

$(SOURCE_DIR)/load.o: $(SOURCE_DIR)/load.c $(INC_DIR)/global.h \
                        $(INC_DIR)/load.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/load.c
	cp load.o $(SOURCE_DIR)/load.o
	rm load.o

$(SOURCE_DIR)/fft.o: $(SOURCE_DIR)/fft.c $(INC_DIR)/global.h $(INC_DIR)/fft.h $(INC_DIR)/complex.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/fft.c
	cp fft.o $(SOURCE_DIR)/fft.o
	rm fft.o

$(SOURCE_DIR)/Fourier.o: $(SOURCE_DIR)/Fourier.c $(INC_DIR)/global.h $(INC_DIR)/maths.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/Fourier.c
	cp Fourier.o $(SOURCE_DIR)/Fourier.o
	rm Fourier.o

$(SOURCE_DIR)/complex.o: $(SOURCE_DIR)/complex.c $(INC_DIR)/global.h $(INC_DIR)/maths.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/complex.c
	cp complex.o $(SOURCE_DIR)/complex.o
	rm complex.o

$(SOURCE_DIR)/maths.o: $(SOURCE_DIR)/maths.c $(INC_DIR)/global.h $(INC_DIR)/maths.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/maths.c
	cp maths.o $(SOURCE_DIR)/maths.o
	rm maths.o

$(SOURCE_DIR)/error.o: $(SOURCE_DIR)/error.c $(INC_DIR)/global.h
	gcc -c -I$(INC_DIR) $(SOURCE_DIR)/error.c
	cp error.o $(SOURCE_DIR)/error.o
	rm error.o

clean:
	rm $(SOURCE_DIR)/*.o
