SHELL = cmd.exe

# -------------------------------------------
# Compilação normal (Windows + PowerShell)
# -------------------------------------------

CXX = g++
CXXFLAGS = -Wall -O2 -I"C:/msys64/mingw64/include"
LDFLAGS = -L"C:/msys64/mingw64/lib"

LIBS = \
    -lallegro \
    -lallegro_primitives \
    -lallegro_font \
    -lallegro_ttf \
    -lallegro_image \
    -lallegro_dialog \
    -lallegro_memfile \
    -lallegro_color

SOURCES = \
    bigTextLabel.cpp \
    button.cpp \
    config.cpp \
    gameScreenContext.cpp \
    hall.cpp \
    FPSCounter.cpp \
    informationPanel.cpp \
    main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = lifegame.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del *.o
	del $(TARGET)


# -------------------------------------------
# Build para distribuição (dist/)
# -------------------------------------------

# -------------------------------------------
# Distribuição compatível com Windows
# -------------------------------------------

DISTDIR = dist
BINDIR = C:/msys64/mingw64/bin

DLLS = allegro-5.dll allegro_primitives-5.dll allegro_font-5.dll allegro_ttf-5.dll allegro_image-5.dll allegro_dialog-5.dll allegro_color-5.dll allegro_memfile-5.dll zlib1.dll libpng16.dll libjpeg-8.dll freetype.dll

dist: $(TARGET)
	@if not exist "$(DISTDIR)" mkdir "$(DISTDIR)"
	@copy "$(TARGET)" "$(DISTDIR)" > nul

	@echo Copiando DLLs...
	@echo @echo Copiando DLLs... > copydlls.bat
	@for %%f in ($(DLLS)) do echo if exist "$(BINDIR)\%%f" copy "$(BINDIR)\%%f" "$(DISTDIR)" ^> nul >> copydlls.bat
	@cmd /C copydlls.bat
	@del copydlls.bat

	@echo Copiando fontes...
	@if exist "fonts" xcopy /E /I /Y "fonts" "$(DISTDIR)\fonts" > nul

	@echo Copiando imagens...
	@if exist "pictures" xcopy /E /I /Y "pictures" "$(DISTDIR)\pictures" > nul

	@echo Distribuicao criada em: $(DISTDIR)
