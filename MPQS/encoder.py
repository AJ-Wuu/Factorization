# Taken from https://github.com/berkanegrice/Non-Official-MagmaAPI with the permission of Berkan Egrice
import xml.etree.ElementTree as ET
import urllib.parse
import os
import sys

# the magma file to be executed.
fn = sys.argv[1]
if os.path.exists(fn):
	query_file = open(fn, "r");    

raw_str = query_file.read();
query_file.close()

# To encode the given magma file.
encoded = urllib.parse.quote(raw_str, safe='') 

# add necesssary part to POST method.
final_str = "input="+encoded 
# write into a file encoded final magma file.
out = open("magmaquery.txt", "w+")
out.write(final_str)
out.close()

# call a magma api post method.
run_method = os.popen("curl -XPOST --data @magmaquery.txt http://magma.maths.usyd.edu.au/xml/calculator.xml")
# to get magma api result
magma_res = run_method.read()

# write into a file encoded magma result file.
out_enc_magma = open("magmares.xml", "w+")
out_enc_magma.write(magma_res)
out_enc_magma.close()

# decode the coming result from magma.
root_node = ET.parse("magmares.xml").getroot()

# find the result line/s in the result xml file.
temp = []
for tag in root_node.findall('results/line'):
	temp.append(tag.text)

for i in range(0, len(temp)-1):
	print(temp[i])

os.remove("magmaquery.txt")
os.remove("magmares.xml")
