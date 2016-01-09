.PHONY: all clean time

GPP = g++
OUTDIR = ./Release
OUTFILE = $(OUTDIR)/time.so

COMPILE_FLAGS = -c -std=c++11 -fPIC -m32 -O3 -w -D LINUX -I ./amx/

all: time

clean:
	-rm *.o
	-rm -r $(OUTDIR)

$(OUTDIR):
	mkdir -p $(OUTDIR)

time: clean $(OUTDIR)
	$(GPP) $(COMPILE_FLAGS) *.cpp
	$(GPP) -O2 -std=c++11 -fPIC -m32 -fshort-wchar -shared -o $(OUTFILE) *.o
	-rm *.o
