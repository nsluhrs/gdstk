import gdstk
import sys
import time
rp=gdstk.Polygon([[16.0, 16.0], [-16.0, 16.0], [-16.0, 0.0], [-12.0, 0.0], [-12.0, 12.0], [12.0, 12.0], [12.0, 0.0], [8.0, 0.0], [8.0, 8.0], [-8.0, 8.0], [-8.0, 0.0], [-4.0, 0.0], [-4.0, 4.0], [4.0, 4.0], [4.0, -4.0], [-4.0, -4.0], [-4.0, -0.0], [-8.0, -0.0], [-8.0, -8.0], [8.0, -8.0], [8.0, -0.0], [12.0, -0.0], [12.0, -12.0], [-12.0, -12.0], [-12.0, -0.0], [-16.0, -0.0], [-16.0, -16.0], [16.0, -16.0]],layer = 10, datatype=3)
rp2 = gdstk.rectangle((0.0,0.0),(10.0,10.0),5,5)
rp3 = gdstk.rectangle((10.0,10.0),(20.0,30.0),5,5)

if len(sys.argv)>1:
    time.sleep(int(sys.argv[1]))
gdstk.offset([rp2,rp3],2.0)
print('trying single rect')
print(gdstk.holes([rp2]))
print('trying single rect no array')
#print(gdstk.holes(rp3))
print("trying single rect untion true")
#print(gdstk.holes(rp3,True))
print("trying double rect")
print(gdstk.holes([rp2,rp3]))
print('trying nested holes')

#print(gdstk.holes([rp]))
