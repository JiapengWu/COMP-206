#!/usr/bin/python

import os, sys
from ctypes import *

def ImageFilter():

    if len(sys.argv) <= 4:
        print "Please input correct arguement."
        sys.exit()

    cdll.LoadLibrary("libfast_filter.so")
    libc = CDLL("libfast_filter.so")
    #print "hey"
    #importing library
    # importing function
    try:
        fhand=open(sys.argv[1],"r")
    except:
        print "Please input a valid file name."
	sys.exit()
    inputImage = fhand.read()

    #copyfile(sys.argv[1], sys.argv[2])
    #copy the input image to the file named by the input output file name

    outImage = ' ' * len(inputImage)

    #print outImage

    width = int(sys.argv[3])
    width = c_int(width)

    weights = list()
    for num in sys.argv[4:]:
        weights.append(float(num))


    #CFloatArrayType = ctypes.c_float * len(weights)
    CFloatArrayType = c_float * len(weights)

    float_weights = CFloatArrayType(*weights)
    #print fhand
    #print ghand
    #print float_weights
    #print width
    #libc.printf("hi\n");
    libc.doFiltering(inputImage, float_weights, width, outImage)
    ghand = open(sys.argv[2],"w+")
    ghand.write(outImage)
    fhand.close()
    ghand.close()




ImageFilter()
