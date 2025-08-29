CMP=gcc
MAIN=project
FUNC=projfunc
EXEC=runproject

$(EXEC): $(MAIN).o $(FUNC).o 
	$(CMP) $(MAIN).o $(FUNC).o -lm -lX11 gfx2.o -o $(EXEC)

$(MAIN).o: $(MAIN).c $(FUNC).h 
	$(CMP) -c $(MAIN).c -o $(MAIN).o

$(FUNC).o: $(FUNC).c $(FUNC).h 
	$(CMP) -c $(FUNC).c -o $(FUNC).o

clean:
	rm $(EXEC) $(MAIN).o $(FUNC).o