cmake_minimum_required(VERSION 3.5)
project(cap)

# C++11 standartlarını kullan
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV paketini bul
find_package(OpenCV REQUIRED)

# Proje dosyalarını ekleyin
add_executable(cap main.cpp)

# OpenCV kütüphanesini ve gerekli diğer kütüphaneleri bağlayın
target_link_libraries(cap ${OpenCV_LIBS})
