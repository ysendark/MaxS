TARGETS  = roguelike
CC       = gcc
CFLAGS   = -std=c99 -Wall -I${SDL_INC_DIR}
LINKER   = gcc
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LFLAGS   = -Wall -I${SDL_INC_DIR} -lm -g -L${SDL_LIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer

# directories
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TRGS	 := $(TARGETS:%=$(BINDIR)/%)

DIRS	 = $(OBJDIR) $(BINDIR)

.PHONY: DIRS
all: $(DIRS) $(TRGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
MAINS	 := $(TARGETS:%=$(OBJDIR)/%.o)
# Liste des fichiers .o sans ceux contenant un main
OBJS	 := $(filter-out $(MAINS),$(OBJECTS))
rm       = rm -f


#$(BINDIR)/$(TARGET): $(OBJECTS)
$(TRGS): $(OBJECTS)
	@$(LINKER) $(subst $(BINDIR),$(OBJDIR),$@).o $(OBJS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGETS)
	@echo "Executable removed!"
