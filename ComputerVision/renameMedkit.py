# Script to read in all the files
# of the medkit and rename them to
# medkit1, medkit2, ...
# so that they are easy to process later

import os

# path where medkit images are located
path = '/home/jorge/Documents/mae342/images/medkit'
os.chdir(path)
filenames = os.listdir(path)
counter = 1

for file in filenames:
	f_new = 'medkit{}.jpg'.format(counter)
	os.rename(file,f_new)
	print '{}.'.format(counter), file, '->', f_new 
	counter += 1



