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

def crawling(region_name) :
    base_url = "https://dds.cr.usgs.gov/srtm/version2_1/SRTM3/"
    html = getHTML(base_url + region_name)
    soup = BeautifulSoup(html, "html.parser")
    hgt_area = soup.find_all("li")
    for hgt_line in hgt_area[1:]:
        hgt_soup = hgt_line.find("a")
        href_area = hgt_soup["href"]
        r = requests.get(base_url + region_name + href_area)
        with open(href_area, 'wb') as f:
            f.write(r.content)
        with ZipFile(href_area, 'r') as zip:
            zip.extractall()
        os.remove(href_area)

if __name__ == "__main__" :
    with Pool(32) as p:
        print(p.map(crawling, ["Africa/", "Australia/", "Eurasia/", "Islands/", "North_America/", "South_America/"]))