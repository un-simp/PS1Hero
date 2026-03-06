import baf
from baf.datatypes import *


class MetaSong(Block):
    # INFO: unique identifier for the song, +1 gives the CD track
    # using CDLoader will give the chart data
    trackNum = U8()
    # INFO: need to know the length of each string before reading
    songName_length = U16()
    songName = Bytes()
    artistName_length = U16()
    artistName = Bytes()
    albumName_length = U16()
    albumName = Bytes()
    # INFO: setup as a nibble flag such as this
    # easy medium hard expert
    #  1     1      1    1
    difficulty = U8()
    # INFO: bitmap image for GPU upload
    imageLength = U16()
    image = Bytes()

class MetaFile(Block):
    # INFO: unique identifier for the file
    # 137 is used to prevent being picked up as a text file
    magic = Bytes(default=[137,"META".encode("UTF8")])
    # INFO: likely to not be that many versions but still good to have
    version = Bytes(default='01'.encode('UTF8'))
    num_of_tracks = U16()
    tracks = Array(MetaSong,num_of_tracks)


