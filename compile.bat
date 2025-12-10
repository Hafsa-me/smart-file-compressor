@echo off
echo ====================================
echo Compiling Huffman Encoding System
echo ====================================

echo.
echo Step 1: Compiling HuffmanNode.cpp...
g++ -c HuffmanNode.cpp -o HuffmanNode.o
if errorlevel 1 (
    echo Error compiling HuffmanNode.cpp
    pause
    exit /b 1
)

echo Step 2: Compiling PriorityQueueMin.cpp...
g++ -c PriorityQueueMin.cpp -o PriorityQueueMin.o
if errorlevel 1 (
    echo Error compiling PriorityQueueMin.cpp
    pause
    exit /b 1
)

echo Step 3: Compiling HuffmanTree.cpp...
g++ -c HuffmanTree.cpp -o HuffmanTree.o
if errorlevel 1 (
    echo Error compiling HuffmanTree.cpp
    pause
    exit /b 1
)

echo Step 4: Compiling FileHandler.cpp...
g++ -c FileHandler.cpp -o FileHandler.o
if errorlevel 1 (
    echo Error compiling FileHandler.cpp
    pause
    exit /b 1
)

echo Step 5: Compiling JSONHelper.cpp...
g++ -c JSONHelper.cpp -o JSONHelper.o
if errorlevel 1 (
    echo Error compiling JSONHelper.cpp
    pause
    exit /b 1
)

echo Step 6: Compiling main.cpp...
g++ -c main.cpp -o main.o
if errorlevel 1 (
    echo Error compiling main.cpp
    pause
    exit /b 1
)

echo.
echo Step 7: Linking all object files...
g++ HuffmanNode.o PriorityQueueMin.o HuffmanTree.o FileHandler.o JSONHelper.o main.o -o huffman.exe
if errorlevel 1 (
    echo Error linking
    pause
    exit /b 1
)

echo.
echo Step 8: Cleaning up object files...
del *.o

echo.
echo ====================================
echo    COMPILATION SUCCESSFUL!
echo ====================================
echo.
echo Executable created: huffman.exe
echo.
echo Test it with:
echo   huffman.exe encode input.txt output.bin tree.huf
echo   huffman.exe decode output.bin tree.huf decoded.txt
echo.

pause
