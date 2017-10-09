//
//  surfaceExtraction.hpp
//  Homework8
//
//  Created by Ben Jones on 1/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//  
//  Abigail Bashore
//  Homework8
//  implement writeSTL function
//

#pragma once
#include <stdint.h>
#include <stdio.h>
#include "VoxelShape.h"
#include "SharedQueue.h"
#include <mutex>
enum FaceType {
    NX,
    NY,
    NZ,
    PX,
    PY,
    PZ
};

struct Triangle{
    float normal[3];
    float v1[3];
    float v2[3];
    float v3[3];
}; 

struct Range{
    int fromX, toX, fromY, toY;
};

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2);

// writing the STL file
void writeSTL(VoxelShape& model, const char * filename, unsigned numThreads);
void writeZ(int x, int y, MyArray<Triangle>* triangles, VoxelShape* model, std::mutex* lock);
void ThreadWorker(SharedQueue<Range>* workQ, MyArray<Triangle>* triangles, VoxelShape* model, std::mutex *lock);
