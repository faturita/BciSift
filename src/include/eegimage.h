#ifndef EEGIMAGE_H
#define EEGIMAGE_H

#include <iostream>
#include <fstream>
#include <string>

int eegimage(double avg, double data);

int eegimage(double signal[], int imageheight, int signallength, int gammat, int gamma, bool normalize, int label);

int eegimage(float *descr,double signal[], int imageheight, int signallength, int gammat, int gamma, bool normalize, int label);

int eegimage(float *descr,double signal[], int imageheight, int signallength, int gammat, int gamma, bool normalize, std::string windowname);

void printdescriptor(float *descr);

void zscore(double *signal, int length);

#endif // EEGIMAGE_H


