# define the executable files
MAIN = cdc
MAIN_IMPROVED = cdc_improved

.PHONY: clean

$(MAIN): cdc.cpp
	g++ $(MAIN).cpp -o $(MAIN)
	@echo  Executable $(MAIN) compiled!

$(MAIN_IMPROVED): cdc_improved.cpp
	g++ $(MAIN_IMPROVED).cpp -o $(MAIN_IMPROVED)
	@echo  Executable $(MAIN_IMPROVED) compiled!

all: $(MAIN) $(MAIN_IMPROVED)

clean:
	rm -f $(MAIN) $(MAIN_IMPROVED)