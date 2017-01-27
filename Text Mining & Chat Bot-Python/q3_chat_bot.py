#!/usr/bin/python
import sys
import re
import random

def constrcuPair():

    regex = re.compile('[^a-zA-Z]');
    if len(sys.argv) <= 1:
        print "Please enter correct arguement."
        sys.exit()
    pairs = list()
    for filename in sys.argv[1:]:
    #parsing files
        try:
            fhand=open(filename,"r")
        except:
            print "Please input a valid file name."
            sys.exit()
        text = fhand.read().lower()
        words = text.split()
        #temp = text.rsplit('\n')
        #words = list()
        #for sentence in temp:
        #    for word in sentence.split():
        #        words.append(word)
        #words are the collection of words splited by " "



        newWords=list();
        toCheck = ('.','!','?')
        for word in words:
            for punctuation in toCheck:
                #check if they each word contains !?.
                mark = 0;
                if punctuation in word:
                #if it is not the end of the sentence
                    mark = 1
                    newWords.append((word,1))
                    break
            if mark == 0:
                newWords.append((word,0))



        final=list()
        for (word,ifEnd) in newWords:
            word=regex.sub('',word)
            if word is not '':
                final.append((word,ifEnd));
        #strip the words containing non-alphabetic charaters

        length = len(final)
        for i in range(0,length-1):

            if final[i+1][1] == 1:                #append end pair
                pairs.append((final[i][0],final[i+1][0],1))

            else:
                pairs.append((final[i][0],final[i+1][0],0))

    #print pairs
    while True:
        try:
            sent = raw_input("Send:     ")
        except:
            print "\nSession terminated due to end of the input."
            break

        if len(sent) == 0:
            print "\nPlease input correct message."
            break

        QN = sent.split()[-1]
        found = 0;
        for pair in pairs:
            if QN in pair[0]:
                found = 1;
                cur = pair
                R1 = pair[1];
                break
        if found == 0:
            rand = random.randint(0,len(pairs)-1);
            cur = pairs[rand];
            R1 = cur[1]

        R1 = R1.capitalize();
        receive = ""
        receive += R1
        #append R1 to the receive string
        num = 1
        while True:
            if num == 20:
                receive += " "
                receive += "twenty"
                break;
            # case 3: if there are 20 words found, append "twenty"
            num += 1;
            if cur[2] == 1:
                #receive += cur[1]
                break
            # case 1: end pair

            found = 0;
            for pair in pairs:
                if cur[1] is pair[0]:
                    #print "found!", pair
                    found = 1
                    cur = pair
                    receive += ' '
                    receive = receive + cur[1]

                    #print receive
                    break

            if found == 0:
                #receive += cur[1]
                break
            # case 2: no pair found
        receive += '.'
        print "Received:",receive



constrcuPair()
