from mss import mss
import win32api, win32con

def createScreenShot():
    sx = win32api.GetSystemMetrics(0) # native res on monitor
    sy = win32api.GetSystemMetrics(1)
    rx = 1280 # rendering res to send via network
    sy = 720
    compression = 0.4 # amount of compression
    file_name = "sc_shot.png"
    directory_ = "C:/temporary_screenshots"
    buffer_images = 5 # The amount of files we will have at max

    while True: # this absolutely doesnt work yet do not try it
        with mss as sc: 
            sc.shot()

def garbage_collection()

