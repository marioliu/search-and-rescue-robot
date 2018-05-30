# Resize to 500X375 size

import cv2
import os
import glob


#path where medkit images are located
path = '/home/jorge/Documents/mae342/images/medkit'
os.chdir(path)

#filenames = os.listdir(path)
filenames = glob.glob('*.jpg')

folder = 'resized'
if not os.path.exists(folder):
	os.makedirs(folder)

width = 400
count = 1;

for file in filenames:
	image = cv2.imread(file)
	height = int(width * image.shape[0] / image.shape[1] )
	f_new = 'medkit_resized{}.jpg'.format(count)
	image = cv2.resize(image, (width, height))
	cv2.imwrite(folder + '/' + f_new,image)
	count += 1
