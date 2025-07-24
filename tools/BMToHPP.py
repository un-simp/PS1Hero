# BMfont XML to a header
# export font with 32bit and alpha, run this script to create the header and shove that in your c++
# example: const int asciiLookup[0x7f][5] =
# format
# xPos  yPos Width  Height  Advance
# shove your png into convertImage.py from https://github.com/spicyjpeg/ps1-bare-metal/blob/main/tools/convertImage.py
import json
import xmltodict
with open("funky.xml", "rb") as f:
    json_data = json.loads(json.dumps(xmltodict.parse(f)))
    characters_main = json_data["font"]["chars"]
    charNum = characters_main["@count"]
    chars = characters_main["char"]

print(chars)
output = []
for char in chars:
    print(chr(int(char["@id"])))
    print(f"id:{char['@id']} letter: {chr(int(char['@id']))} Xpos: {char['@x']} ypos: {char['@y']} width: {char['@width']} height: {char['@height']} advance: {char['@xadvance']}")
    output.append([int(char["@x"]), int(char["@y"]), int(char["@width"]), int(char["@height"]), int(char["@xadvance"])])

cpp_array = "{\n"
for i, item in enumerate(output):
    cpp_array += f"  {{{item[0]}, {item[1]}, {item[2]}, {item[3]}, {item[4]}}}"
    if i < len(output) - 1:
        cpp_array += ",\n"
cpp_array += "\n};"

with open("output.arr", "w") as f:
    f.write(cpp_array)
