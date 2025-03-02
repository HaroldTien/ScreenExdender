# 編譯器與參數
CXX         = clang++
CXXFLAGS    = -std=c++11 -Wall -g
INCLUDES    = -I../include

# 程式庫來源檔所在的目錄
SRCDIR      = ../src

# 要產生的目標物件檔（將放在 test 資料夾中）
OBJS = WebSocketServer.o WebSocketFrame.o SHA1.o Base64.o test_server.o

# 最終產生的可執行檔名稱
TARGET = test_server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# 將位於 src 資料夾的程式庫來源檔編譯成放在目前資料夾的物件檔
WebSocketServer.o: $(SRCDIR)/WebSocketServer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

WebSocketFrame.o: $(SRCDIR)/WebSocketFrame.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

SHA1.o: $(SRCDIR)/SHA1.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

Base64.o: $(SRCDIR)/Base64.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 編譯測試程式
test_server.o: test_server.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) 