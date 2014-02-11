#! /usr/bin/python

import sys

if len(sys.argv) != 2:
  print "Usage:", sys.argv[0],"zh_en_entran.lsda"
  sys.exit(1)
lsda_name = sys.argv[1]

in_file = open(lsda_name, 'r')
lines = in_file.readlines()

of = open("zh_en.snt", 'w')

for i in range(len(lines)):
  if i%3 == 0 or i%3 == 1:
    print >>of, lines[i].strip('\n')
  else:
    words = lines[i].split();
    for kk in range(len(words)):
      if kk%2 == 0:
        print >>of, words[kk],
    print>>of, ''



