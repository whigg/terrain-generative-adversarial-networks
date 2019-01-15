import requests
from bs4 import BeautifulSoup
from zipfile import ZipFile
from multiprocessing import Pool
import os
from functools import partial
import multiprocessing

def getHTML(url) :
    html = ""
    res = requests.get(url)
    if res.status_code == 200:
        html = res.text
    return html

def extract_chunk(suffix, chunk) :
    print(suffix + " : " + str(len(chunk)))
    headers = { 'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36'}

    for filename in chunk:
        r = requests.get(suffix + filename, headers=headers)
        with open(filename, 'wb') as f:
            f.write(r.content)
        with ZipFile(filename, 'r') as zip:
            zip.extractall(".\dataset")
        os.remove(filename)


def crawling(region_name, num_cores) :
    base_url = "https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/"
    html = getHTML(base_url + region_name)
    soup = BeautifulSoup(html, "html.parser")
    hgt_area = soup.find_all("a")[1:]
    hgt_string = []
    for tag in hgt_area :
        tag_string = str(tag)
        start_idx = tag_string.find('>') + 2
        end_idx = tag_string.rfind("hgt") + 3
        hgt_string.append(tag_string[ start_idx : end_idx ] + ".zip")

    chunk_size = int(len(hgt_string) / (num_cores - 1))
    chunk_parts = [hgt_string[i : i + chunk_size] for i in range(0, len(hgt_string), chunk_size)]

    func = partial(extract_chunk, base_url + region_name)
    with Pool(num_cores - 1) as p :
        print("Start parsing region [{}].".format(region_name))
        print("length : {} and chunk size : {}".format(len(hgt_string), chunk_size))
        p.map(func, chunk_parts)

if __name__ == "__main__" :
    for region in ["Eurasia/", "Islands/", "North_America/", "South_America/"] : # already done "Africa/", "Australia/",
        crawling(region, num_cores=multiprocessing.cpu_count())