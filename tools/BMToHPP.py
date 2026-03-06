# BMfont XML to a header
# export font with 32bit and alpha, run this script to create the header and shove that in your c++
# example: const int asciiLookup[0x7f][5] =
# format
# xPos  yPos Width  Height  Advance
# shove your png into convertImage.py from https://github.com/spicyjpeg/ps1-bare-metal/blob/main/tools/convertImage.py
import json
import xmltodict
# INFO: using "with open()" will close the file automatically if the program crashes.
# This prevents issues when writing so that data isn't corrupted and when reading
# that the file is not locked in Operating Systems where that happens (eg. Windows)
with open("funky.xml", "rb") as f:
    json_data = json.loads(json.dumps(xmltodict.parse(f)))
    characters_main = json_data["font"]["chars"]
    charNum = characters_main["@count"]
    chars = characters_main["char"]
# DEBUG: print all the characters that we have detected
# print(chars)
output = []
for char in chars:
    # DEBUG: prints more information about detected characters
    # print(chr(int(char["@id"])))
    # print(f"id:{char['@id']} letter: {chr(int(char['@id']))} Xpos: {char['@x']} ypos: {char['@y']} width: {char['@width']} height: {char['@height']} advance: {char['@xadvance']}")

    # INFO: create a basic array that strips out unneeded information and converts data to the correct format,
    # this has no error checking since BMFont should always generate the correct information,
    # if not, something worse has happened and the program will crash
    output.append([int(char["@x"]), int(char["@y"]), int(char["@width"]), int(char["@height"]), int(char["@xadvance"])])
# INFO: define the start of the C++ array, this was created using a string instead of a dedicated library like ctypes due to the complexity of the setup
cpp_array = "{\n"
for i, item in enumerate(output):
    # INFO: append the correct array information to the end of the string
    cpp_array += f"  {{{item[0]}, {item[1]}, {item[2]}, {item[3]}, {item[4]}}}"
    # INFO: if it's not the end of the array, add a comma to comply with c++'s syntax on arrays
    if i < len(output) - 1:
        cpp_array += ",\n"
cpp_array += "\n};"
# INFO: ditto from line 12
with open("output.arr", "w") as f:
    f.write(cpp_array)
