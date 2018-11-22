#ifndef EEGIMAGE_H
#define EEGIMAGE_H

int eegimage(double avg, double data);

int eegimage(double signal[], int length, int gamma, int label);

int eegimage(float *descr,double signal[], int length, int gamma, int label);

int eegimage(float *descr,double signal[], int length, int gamma, int label);

void printdescriptor(float *descr);

#endif // EEGIMAGE_H


