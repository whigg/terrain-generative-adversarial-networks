import requests
from bs4 import BeautifulSoup
from zipfile import ZipFile
from multiprocessing import Pool
import os

def getHTML(url) :
    html = ""
    res = requests.get(url)
    if res.status_code == 200:
        html = res.text
    return html

def extract_chunk(chunk, delimiter) :
    print(delimiter + " : " + str(len(chunk)))

    for hgt_line in chunk[1:]:
        hgt_soup = hgt_line.find("a")
        href_area = hgt_soup["href"]
        r = requests.get(delimiter + href_area)
        with open(href_area, 'wb') as f:
            f.write(r.content)
        with ZipFile(href_area, 'r') as zip:
            zip.extractall()
        os.remove(href_area)


def crawling(region_name, chunk_size) :
    base_url = "https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/"
    html = getHTML(base_url + region_name)
    soup = BeautifulSoup(html, "html.parser")
    hgt_area = soup.find_all("li")
    chunk_parts = [(base_url + region_name, hgt_area[i : i + chunk_size]) for i in range(0, len(hgt_area), chunk_size)]

    with Pool(len(chunk_parts)) as p :
        p.map(extract_chunk, chunk_parts)


if __name__ == "__main__" :
    for region in ["Africa/", "Australia/", "Eurasia/", "Islands/", "North_America/", "South_America/"] :
        crawling(region, 800)