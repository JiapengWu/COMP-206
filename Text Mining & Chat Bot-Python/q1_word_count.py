#!/usr/bin/python
import sys
import re


def countFrequency():
    regex = re.compile('[^a-zA-Z]');
    if len(sys.argv) <= 1:
        print "Please enter correct arguement."
        sys.exit()
    filename=sys.argv[1]
    try:
        fhand=open(filename,"r")
    except:
        print "Please input a valid file name."
        sys.exit()
    text = fhand.read().lower()
    words=text.split()
    #words are the collection of words splited by " "

    newWords=list();
    for word in words:
        for splitted in word.split("-")[0:]:
            newWords.append(splitted)

    #get rid of the words which contains no hyphen in "words

    final=list()
    for word in newWords:
        word=regex.sub('',word)
        if word is not '':
            final.append(word)
    #strip the words containing non-alphabetic charaters

    count=dict()
    length=float(len(final))
    for word in final:
        count[word]=count.get(word,0)+1
    #count word
    #for key in count.keys():
        #count[key]/=len(count)
    #calculate ratio
    sorted_count = sorted([(v,k) for (k,v) in count.items()],reverse = True)
    #sort the list
    for (v,k) in sorted_count[:]:
        print k,":",v


countFrequency()
