CXXFLAGS =	-O3 -g -Wall -fmessage-length=0 `Magick++-config --cppflags --cxxflags --ldflags --libs` -lboost_filesystem-mt

OBJS =		make_logo.o

LIBS =   `Magick++-config --cppflags --cxxflags --ldflags --libs` -lboost_filesystem-mt

TARGET =	make_logo

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
