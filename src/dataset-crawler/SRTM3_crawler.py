import requests
from bs4 import BeautifulSoup
from zipfile import ZipFile
from multiprocessing import Pool
import os
from functools import partial
from pprint import pprint

def getHTML(url) :
    html = ""
    res = requests.get(url)
    if res.status_code == 200:
        html = res.text
    return html

def extract_chunk(suffix, chunk) :
    print(suffix + " : " + str(len(chunk)))

    for filename in chunk:
        r = requests.get(suffix + filename)
        with open(filename, 'wb') as f:
            f.write(r.content)
        with ZipFile(filename, 'r') as zip:
            zip.extractall(".\dataset")
        os.remove(filename)


def crawling(region_name, chunk_size) :
    base_url = "https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/"
    html = getHTML(base_url + region_name)
    soup = BeautifulSoup(html, "html.parser")
    hgt_area = soup.find_all("a")[1:]
    hgt_string  = [str(tag)[9:24] for tag in hgt_area]
    chunk_parts = [hgt_string[i : i + chunk_size] for i in range(0, len(hgt_string), chunk_size)]

    func = partial(extract_chunk, base_url + region_name)
    print("Start parsing region [{}].".format(region_name))

    with Pool(16) as p :
        p.map(func, chunk_parts)

if __name__ == "__main__" :
    for region in ["Africa/", "Australia/", "Eurasia/", "Islands/", "North_America/", "South_America/"] :
        crawling(region, 200)