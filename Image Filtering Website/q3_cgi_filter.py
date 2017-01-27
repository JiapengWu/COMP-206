#!/usr/bin/python

import sys
import struct
import copy
import cgitb; cgitb.enable()
import cgi
import ctypes

if __name__ == "__main__":

    print "Content-type: text/html\n"  # note HTTP transactions start with this!
    form = cgi.FieldStorage()	# parse query

    if form.has_key('photo'):
        img_in = form['photo'].file
    else:
        img_in = open( 'temp.bmp', 'rb' )

    FULL_HEADER = img_in.read(54)
    img_data = img_in.read()

    if form.has_key('load'):
        history = dict();
        f = open("history.pickle","w")
        # clear the history pickle file

        out_img_data = copy.deepcopy(img_data)
        img_out = open( 'temp.bmp', 'wb' )
        img_out.write(FULL_HEADER)
        history[0] = 1;
        history[1] = g.read()
        img_out.write(img_in)
        # store data to key 1
        pickle.dump(history,f)
        # dump data of result.bmp to f

        f.close()


    elif form.has_key('filter'):
        cdll.LoadLibrary("./libfast_filter.so")
        libc = CDLL("./libfast_filter.so")
        #print "hey"
        #importing library
        # importing function

        #copyfile(sys.argv[1], sys.argv[2])
        #copy the input image to the file named by the input output file name

        out_img_data = ' ' * len(img_data)

        #print outImage

        width = int(sys.argv[2])
        width = c_int(width)

        weights = list()
        for num in sys.argv[3:]:
            weights.append(float(num))


        #CFloatArrayType = ctypes.c_float * len(weights)
        CFloatArrayType = c_float * len(weights)

        float_weights = CFloatArrayType(*weights)

        libc.doFiltering(img_data, float_weights, width, out_img_data)

        img_out = open( 'temp.bmp', 'wb' )

        img_out.write(FULL_HEADER)


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
        history[history[0]] = FULL_HEADER

        for key in history.keys():
            if key > history[0]:
                history.pop(key,None)
        # 2 when first filtering

        img_out.write(img_in)
        f = open("history.pickle","w")
        pickle.dump(history,f)
        f.close()





    elif form.has_key('undo'):
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

        out_img_data = copy.deepcopy(img_data)

        img_out = open( 'temp.bmp', 'wb' )

        img_out.write(FULL_HEADER)

        # write the filtered image data to the result.bmp
        # 2 when first filtering
        pickle.dump(history,f)

        f.close()


    if form.has_key('redo'):
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
        out_img_data = copy.deepcopy(img_data)

        img_out = open( 'temp.bmp', 'wb' )

        img_out.write(FULL_HEADER)

        # write the filtered image data to the result.bmp
        # 2 when first filtering
        pickle.dump(history,f)

        f.close()

  img_out.close()
  img_in.close()

  print """<html>
<body>
<form name="input" action="./week11_image_cgi.py" method="post" enctype="multipart/form-data">

  <p>Next Filter:</p>
  <p><input type="text" name="00" value="%f"> <input type="text" name="01" value="%f"> <input type="text" name="02" value="%f"> </p>
  <p><input type="text" name="10" value="%f"> <input type="text" name="11" value="%f"> <input type="text" name="12" value="%f"> </p>
  <p><input type="text" name="20" value="%f"> <input type="text" name="21" value="%f"> <input type="text" name="22" value="%f"> </p>
  <input type="submit" value="Submit">

</form>

<hl>

<img src="temp.bmp"/>
</body>
</html>""" % ( blur_weight[0], blur_weight[1],blur_weight[2],blur_weight[3],blur_weight[4],blur_weight[5],blur_weight[6],blur_weight[7],blur_weight[8])
