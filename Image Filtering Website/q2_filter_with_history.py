#!/usr/bin/python

import os, sys
from ctypes import *
import pickle



def FilterWithHistory():

    if len(sys.argv) <= 1:
        print "Please input correct arguement."
        sys.exit()

    if sys.argv[1] == "load":

        if len(sys.argv) != 3:
            print "Please input correct arguement."
            sys.exit()

        history = dict();
        f = open("history.pickle","w")
        # clear the history pickle file
        g = open("result.bmp","w")
        try:
            im = open(sys.argv[2],"r")
        except:
            print "Image name not passed."
            sys.exit()
        # open input image
        g.write(im.read())
        # write it to the result image
        g.close()

        g = open("result.bmp","r")
        history[0] = 1;
        history[1] = g.read()
        # store data to key 1
        pickle.dump(history,f)
        # dump data of result.bmp to f
        g.close()
        f.close()
        im.close()

    elif sys.argv[1] == "filter":

        if len(sys.argv) <= 4:
            print "Please input correct arguement."
            sys.exit()

        cdll.LoadLibrary("libfast_filter.so")
        libc = CDLL("libfast_filter.so")
        #print "hey"
        #importing library
        # importing function
        try:
            fhand = open("result.bmp","r")
        except:
            print "Image not loaded."
            sys.exit()

        inputImage = fhand.read()

        #copyfile(sys.argv[1], sys.argv[2])
        #copy the input image to the file named by the input output file name

        outImage = ' ' * len(inputImage)

        #print outImage

        width = int(sys.argv[2])
        width = c_int(width)

        weights = list()
        for num in sys.argv[3:]:
            weights.append(float(num))


        #CFloatArrayType = ctypes.c_float * len(weights)
        CFloatArrayType = c_float * len(weights)

        float_weights = CFloatArrayType(*weights)

        libc.doFiltering(inputImage, float_weights, width, outImage)
        ghand = open("result.bmp","w+")
        ghand.write(outImage)
        ghand.close()

        im = open("result.bmp","r")

        # write the filtered image data to the result.bmp
        f = open("history.pickle","r")
        # read and renew the dictionary stored
        history = pickle.load(f);
        #print history.keys()
        #print history[0]
        f.close()

        # get the dictionary from pickle
        size = len(history)

        # put the image data to the key correspoding to the current state
        history[0] += 1
        history[history[0]] = im.read()
        for key in history.keys():
            if key > history[0]:
                history.pop(key,None)
        # 2 when first filtering

        f = open("history.pickle","w")
        pickle.dump(history,f)
        f.close()
        fhand.close()
        im.close()




    elif sys.argv[1] == "undo":

        if len(sys.argv) != 2:
            print "Please input correct arguement."
            sys.exit()

        f = open("history.pickle","r")
        history = pickle.load(f);

        f.close()

        if history[0] == 1:
            #print "This is the original image, can't undo anymore."
            sys.exit()

        f = open("history.pickle","w+")
        history[0] -= 1
        # from 3 to 2
        currentImage = history[history[0]]
        # get the history[2]
        im = open("result.bmp","w+")
        im.write(currentImage);
        # write the filtered image data to the result.bmp
        # 2 when first filtering
        pickle.dump(history,f)

        f.close()
        im.close()


    elif sys.argv[1] == "redo":

        if len(sys.argv) != 2:
            print "Please input correct arguement."
            sys.exit()

        f = open("history.pickle","r")
        # read and renew the dictionary stored
        history = pickle.load(f);

        f.close()

        if history[0] == len(history)-1:
            #print "This is the last image, can't redo anymore."
            sys.exit()
        f = open("history.pickle","w+")
        history[0] += 1
        # from 3 to 2
        currentImage = history[history[0]]
        # get the history[2]
        im = open("result.bmp","w+")
        im.write(currentImage);
        # write the filtered image data to the result.bmp
        # 2 when first filtering
        pickle.dump(history,f)

        f.close()
        im.close()

    else:
        print "Please input correct arguement."
        sys.exit()

    #print history[0]
    #print history.keys()

FilterWithHistory()
