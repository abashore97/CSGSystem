
//  surfaceExtraction.cpp
//  Homework8
//
//  Created by Ben Jones on 1/6/17.
//  Copyright © 2017 Ben Jones. All rights reserved.
//
//  Abigail Bashore
//  March 13, 2017
//  Homework 8
//  writing a STL file 
#include <stdint.h>
#include <stdio.h>
#include "surfaceExtraction.hpp"
#include "VoxelShape.h"
#include "MyArray.h"
#include "SharedQueue.h"
#include "Timer.h"
#include <mutex>
#include <thread>
inline void fillPlane(int a1, int a2, int b1, int b2, int c, int cInd, Triangle& t1, Triangle& t2){
    t1.v1[cInd] = c;
    t2.v1[cInd] = c;
    t1.v2[cInd] = c;
    t2.v2[cInd] = c;
    t1.v3[cInd] = c;
    t2.v3[cInd] = c;
    int aInd = (cInd +1) % 3;
    int bInd = (cInd +2) % 3;
    
    t1.v1[aInd] = a1;
    t1.v2[aInd] = a2;
    t1.v3[aInd] = a2;
    
    t2.v1[aInd] = a1;
    t2.v2[aInd] = a2;
    t2.v3[aInd] = a1;
    
    t1.v1[bInd] = b1;
    t1.v2[bInd] = b1;
    t1.v3[bInd] = b2;
    
    t2.v1[bInd] = b1;
    t2.v2[bInd] = b2;
    t2.v3[bInd] = b2;
    
}

void extractFace(int x, int y, int z, FaceType face, Triangle& t1, Triangle& t2){
    for(int i= 0; i < 3; i++){
        t1.normal[i] = 0;
        t2.normal[i] = 0;
    }
    switch(face){
        case NX:
            t1.normal[0] = -1;
            t2.normal[0] = -1;
            fillPlane(y + 1, y, z, z+1, x, 0, t1, t2);
            break;
        case NY:
            t1.normal[1] = -1;
            t2.normal[1] = -1;
            fillPlane(z + 1, z, x, x+1, y, 1, t1, t2);
            break;
        case NZ:
            t1.normal[2] = -1;
            t2.normal[2] = -1;
            fillPlane(x + 1, x, y, y + 1, z, 2, t1, t2);
            break;
        case PX:
            t1.normal[0] = 1;
            t2.normal[0] = 1;
            fillPlane(y, y + 1, z, z +1, x + 1, 0, t1, t2);
            break;
        case PY:
            t1.normal[1] = 1;
            t2.normal[1] = 1;
            fillPlane(z, z + 1, x, x + 1, y + 1, 1, t1, t2);
            break;
        case PZ:
            t1.normal[2] = 1;
            t2.normal[2] = 1;
            fillPlane(x, x +1, y, y + 1, z + 1, 2, t1, t2);
            break;
    }
}
void ThreadWorker(SharedQueue<Range>* workQ, MyArray<Triangle>* triangles, VoxelShape* model, std::mutex* lock){
    Range r;
    while(true){

        while(workQ->Remove(r) == false){
    	    std::this_thread::yield();
	}

	if((r.fromX == r.toX) && (r.fromY == r.toY)){
	    break;
	}

        writeZ(r.fromX, r.fromY, triangles, model, lock);
    }
}

void writeZ(int x, int y, MyArray<Triangle> *triangles, VoxelShape *model, std::mutex* lock){
    MyArray<Triangle> temp;	
    for(int z = 0; z < model->get_z(); z++){
        if(model->get_bit(x, y, z) == 1){

            if(((x - 1) < 0) || (model->get_bit((x - 1), y, z) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, NX, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);

            }

            if(((x + 1) > model->get_x() - 1) || (model->get_bit((x + 1), y, z) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, PX, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);
            }

            if(((y - 1) < 0) || (model->get_bit(x, (y - 1), z) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, NY, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);

            }

            if(((y + 1) > model->get_y() - 1) || (model->get_bit(x, (y + 1), z) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, PY, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);

            }

            if(((z - 1) < 0) || (model->get_bit(x, y, (z - 1)) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, NZ, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);

            }
            if(((z + 1) > model->get_z() - 1) || (model->get_bit(x, y, (z + 1)) == 0)){
                Triangle t1, t2;
                extractFace(x, y, z, PZ, t1, t2);
                temp.pushBack(t1);
                temp.pushBack(t2);
            }
        }
    }

    lock->lock();
    for(int i = 0; i < temp.getSize(); i++){
	Triangle current = temp.getItem(i);    
        triangles->pushBack(current);
    }
    lock->unlock();	    
}


void writeSTL(VoxelShape& model, const char* filename, unsigned numThreads){
    Timer time;
    time.StartTimer();

    std::mutex l;
    SharedQueue<Range> workQueue;
    MyArray<Triangle> triangles;

    std::thread** t;
    t = new std::thread*[numThreads];
    for(int i = 0; i < numThreads; i++){
	t[i] = new std::thread(ThreadWorker, &workQueue, &triangles, &model, &l);
    }

    for(int x = 0; x < model.get_x(); x++) {

        for(int y = 0; y < model.get_y(); y++){
            workQueue.Add({x, model.get_x(), y, model.get_y()});

        }

    }
    for(int i = 0; i < numThreads; i++){
        workQueue.Add({-1, -1, -1, -1});
    }
    for(int i = 0; i < numThreads; i++){
        t[i]->join();
	delete t[i];
    }
    delete[] t;
        	

    FILE * test;
    test = fopen(filename, "wb");


    for(int i = 0; i < 80; i++){
        char c = '0';
        fwrite(&c, sizeof(char), 1, test);

    }


    uint32_t num_triangles = triangles.getSize();
    fwrite(&num_triangles, sizeof(uint32_t), 1, test);
    uint16_t spacer = 0;

    for(int i = 0; i < num_triangles; i++){
        Triangle current = triangles.getItem(i);
        fwrite(&current, sizeof(Triangle), 1, test);
        fwrite(&spacer, sizeof(uint16_t), 1, test);

    }
    

    fclose(test);
    std::cout <<"It took " <<  time.EndTimer() << " seconds with " << numThreads << " thread(s) \n";	
}
