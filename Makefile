# CXXFLAGS = -I /usr/local/include/htmlcxx -L /usr/local/lib -lhtmlcxx


OBJDIR = bin
OUTPUTDIR = OUTPUT
# RUNSDIR = indexout indexoutAnchors searchfiles
# OBJS := $(addprefix $(OBJDIR)/,loaders.o main.o searcher.o vector.o)
OBJS := $(addprefix $(OBJDIR)/, main.o input.o)

all:clean $(OBJS) main

main: $(OBJS)
	g++ -std=c++11 $(OBJS) -o main

$(OBJDIR)/main.o: main.cpp 
	g++ -std=c++11 -c main.cpp -o bin/main.o

$(OBJDIR)/input.o: src/input.cpp lib/input.h 
	g++ -std=c++11 -c src/input.cpp -o bin/input.o

# $(OBJDIR)/searcher.o: utils/searcher.cpp utils/searcher.h 
# 	g++ -std=c++11 -c utils/searcher.cpp -o bin/searcher.o

# $(OBJDIR)/vector.o: models/vector_spacemodel.cpp models/vector_spacemodel.h 
# 	g++ -std=c++11 -c models/vector_spacemodel.cpp -o bin/vector.o

$(OBJS): | $(OBJDIR)

$(OBJDIR):
		mkdir $(OBJDIR)

$(OUTPUTDIR):
	mkdir -p $(OUTPUTDIR)

clean:
	rm -f bin/*.o
	@echo Old binaries deleted...
	@echo Creating new binaries ...


