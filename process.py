import cv2
import ctypes
import numpy as np
import glob
import tqdm
import sys
import multiprocessing
import os 
import time
import dataTransform
import functools
ll = ctypes.cdll.LoadLibrary
fun = ll("./process.so")
dt = dataTransform.dataTransform()
def process(img_name,path):
    img =cv2.imread(img_name,0)
    fun = ll("./process.so")
    points=np.zeros((80,5),dtype=np.int32)
    shape = img.shape[0:2]
    fun.c_test.restype = ctypes.c_int
    img_data = np.asarray(img,np.uint8) 
    img_data = img_data.ctypes.data_as(ctypes.c_char_p)
    points_data = points.ctypes.data_as(ctypes.c_void_p)
    line = fun.c_test(shape[0],shape[1],img_data,points_data)
    points = points[0:line]
    dt.writeXml(img_name,path,img,points.tolist())
if __name__ == "__main__":
    pool = multiprocessing.Pool(processes = int(sys.argv[1]))
    img_list  =glob.glob(os.path.join(sys.argv[2],"*.png") )
    save_where = sys.argv[3]
    if not os.path.exists(save_where):
        os.mkdir(save_where)
    fun_process = functools.partial(process,path=save_where)
    pool.map(fun_process,img_list)
    pool.close()
    pool.join()
