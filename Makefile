SYSCONF_LINK = g++
CPPFLAGS     =
CPPFLAGS     = -g -std=c++11
LDFLAGS      = -g -std=c++11
LIBS         = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread


DESTDIR = ./
TARGET  = VN

OBJECTS := $(patsubst %.cpp,%.o,$(wildcard *.cpp))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)


