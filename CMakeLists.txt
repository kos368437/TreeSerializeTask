cmake_minimum_required(VERSION 3.12)
project(TreeSerializeTestTask)

set(CMAKE_CXX_STANDARD 14)

add_executable(TreeSerializeTestTask main.cpp Node.cpp Node.h DataHolder.h ICloneable.h AnyData.cpp AnyData.h Tree.cpp Tree.h ISerializable.h)