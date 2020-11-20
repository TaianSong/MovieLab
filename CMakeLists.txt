cmake_minimum_required(VERSION 3.15)
project(HW5 C)

set(CMAKE_C_STANDARD 99)

add_executable(HW5 MovieLab.c Movie.c Movie.h MovieIO.c MovieIO.h DIPs.c DIPs.h FileIO.c FileIO.h IterativeFilter.c IterativeFilter.h Constants.h Image.h Image.c ImageList.c ImageList.h)