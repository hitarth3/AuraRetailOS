CXX = g++
CXXFLAGS = -std=c++11 -I.
TARGET = aura_demo
SRCS = main.cpp \
       core/CentralRegistry.cpp \
       core/EventBus.cpp \
       core/Kiosk.cpp \
       core/KioskFactory.cpp \
       core/KioskInterface.cpp \
       core/KioskState.cpp \
       inventory/InventoryManager.cpp \
       hardware/HardwareSimulator.cpp \
       payment/PaymentProcessor.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
