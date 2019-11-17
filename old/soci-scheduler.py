#add pass info (polar diagram with arc)
#save image during pass
#https://www.4dsystems.com.au/product/uCAM_III/
#https://stackoverflow.com/questions/26906510/rotate-theta-0-on-matplotlib-polar-plot
#https://manpages.ubuntu.com/manpages/xenial/man8/rotctld.8.html
#https://www.decalage.info/en/python/html
# $ pip install pdfkit

import predict
import subprocess
import time
import scipy
#import pdfkit 
import numpy as np
import urllib.request
from io import BytesIO
import matplotlib.pyplot as plt
from pylab import imread, imshow, gray, mean



import scipy.misc

nextObs = 0
name = 'QB50P2' #test satellite

def main(args):
	TLE = pullTLE(name)
	qth = (47.654867,-122.306501,100)  # lat (N), long (W), alt (meters) (get real altitude later + building)
	predict.observe(tle, qth)
	#get time, doppler and window
	check_TLE = False
	while(True):#main loop
		if(2000>nextObs-time.time() and not check_TLE) #check TLE 30 minutes before 
			TLE = pullTLE(name)
			check_TLE = True
		if(nextObs-time.time()>100)
			#comms(tx_bytes,doppler,time_window,mode)
			#compute nextObs
			check_TLE = False
		end
	return 0
def comms(tx_bytes,doppler,time_window,mode):
	#subprocess.call("gs_downlink.py", shell=True)
	#subprocess.call("gs_uplink.py", shell=True)
	end
def pullTLE(name):
	url = 'https://www.celestrak.com/NORAD/elements/cubesat.txt'
	response = urllib.request.urlopen(url)
	data = response.read()
	text = data.decode('utf-8')
	lines = text.splitlines()
	TLE = ''
	ind = 0
	for line in lines:
		if (line.startswith(name)):
			TLE = '\n'.join(lines[ind:ind+3])
			break
		ind = ind + 1
	return TLE
	
if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
    
image = imread('no_image.png')
plt.imshow(image)
scipy.misc.imsave('outfile.bmp', image)
#pdfkit.from_file('test.html', 'out.pdf') 
#add transmission properties (SNR, doppler)
#add spectogram
#create sample


