
# compiles a complete PS1Hero setup 
import mido
import microriff
import configparser
import baf
from baf.datatypes import *
import convertImage
import numpy as np
from numpy.typing import NDArray
from PIL          import Image
# classdefs for the binary format
from fileformat import *
from crc import Calculator, Crc32
#array of song folders to manipulate
list_of_song_folders = []

calculator = Calculator(Crc32.CRC32)



# SUMMARY:  given a list of folders containing song data,
# process midi info
# compile ini to a binary format
# stitch the ini and cover arts into a custom container
def compile(songs):
    songInfo = []
    for i,v in enumerate(songs):
        songInfo.append(process_to_binary_format(v + "/song.ini",i))
        process_midi(v + "/notes.mid", v+"/notesPS1")
    MetaDataFile = baf.build(MetaFile,
    {
        "tracks": songInfo
    }).get_bytes()
    # INFO: export to a file for embedding
    with open("out.bin","wb") as f:
        f.write(MetaDataFile)
        checksum = calculator.checksum(MetaDataFile)
        f.seek(0)
        print(checksum)
        f.write(MetaDataFile + checksum.to_bytes(4,"little"))
        f.truncate()
# SUMMARY: given an ini file, creates and returns a binary with them all represented
def process_to_binary_format(inputini,id):

    config = configparser.ConfigParser()
    config.read(inputini)
    # pull all the info needed
    song_name = bytes(config["song"]["name"],"UTF8")
    artist_name = bytes(config["song"]["artist"],"UTF8")
    album_name = bytes(config["song"]["album"],"UTF8")
    diff = 0
    # build the image
    with Image.open("album.jpg") as f:
        imageData: NDArray[np.uint8]= np.asarray(
            f.resize((64,64))
            .convert("RGBA"))
        imageData = convertImage.to16bpp(imageData)
    songInfoCompiled = baf.build(MetaSong,
    {"trackNum": id, 
    "songName_length": len(song_name), 
    "songName": song_name,
    "artistName_length": len(artist_name),
    "artistName": artist_name,
    "albumName_length": len(album_name),
    "albumName": album_name,
    "difficulty": diff,
    "imageLength": len(imageData.tobytes()),
    "image": imageData.tobytes()
    })
    return songInfoCompiled

# SUMMARY:  only pull the guitar sections from the midi and append a CRC32 checksum to the end
def process_midi(inputpath,outputpath):
    mid = mido.MidiFile(inputpath)
    new_midi = mido.MidiFile(ticks_per_beat=mid.ticks_per_beat)
    # only have the guitar track on the outputted midi
    for i, track in enumerate(mid.tracks):
        track_name = ""
        for msg in track:
                    if msg.type == 'track_name':
                        track_name = msg.name
                        break
        if track_name == "PART GUITAR":
            new_midi.tracks.append(track)
    new_midi.save(outputpath)
    with open(outputpath,"r+b") as f:
        data = f.read()

        checksum = calculator.checksum(data)
        f.seek(0)
        print(checksum)
        f.write(data + checksum.to_bytes(4,"little"))
        f.truncate()

compile(list_of_song_folders)