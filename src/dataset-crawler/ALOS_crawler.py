import requests
from bs4 import BeautifulSoup
from zipfile import ZipFile
from multiprocessing import Pool
import os
from functools import partial
import pprint
import multiprocessing
import tarfile


base_url = "https://www.eorc.jaxa.jp/ALOS/en/aw3d30/data/"

def getHTML(url) :
    html = ""
    res = requests.get(url, auth=('sinjihng@pusan.ac.kr', 'aw3d30'))
    if res.status_code == 200:
        html = res.text
    return html

def extract_chunk(url, filename) :
    print("filename : ", filename)
    headers = { 'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.95 Safari/537.36'}

    r = requests.get(url, headers=headers, auth=('sinjihng@pusan.ac.kr', 'aw3d30'))
    with open(filename, 'wb') as f:
        f.write(r.content)
    with tarfile.open(filename, 'r') as tar:
        def is_within_directory(directory, target):
            
            abs_directory = os.path.abspath(directory)
            abs_target = os.path.abspath(target)
        
            prefix = os.path.commonprefix([abs_directory, abs_target])
            
            return prefix == abs_directory
        
        def safe_extract(tar, path=".", members=None, *, numeric_owner=False):
        
            for member in tar.getmembers():
                member_path = os.path.join(path, member.name)
                if not is_within_directory(path, member_path):
                    raise Exception("Attempted Path Traversal in Tar File")
        
            tar.extractall(path, members, numeric_owner=numeric_owner) 
            
        
        safe_extract(tar, ".\ALOS-dataset")
    os.remove(filename)

def parseContents(url) :
    html = getHTML(base_url + url)
    soup = BeautifulSoup(html, "html.parser")
    chunk_area = soup.find_all("area")
    contents = []
    for chunk in chunk_area :
        contents.append(chunk['href'])
    return contents

def crawling(chunk_part) :
    for chunk in chunk_part :
        url = base_url + str(chunk)[2:]
        html = getHTML(url)
        soup = BeautifulSoup(html, "html.parser")
        chunk_area = soup.find_all("div", {"class" : "evlist"})
        pprint.pprint(chunk_area)
        # contents = []
        # for chunk in chunk_area:
        #     contents.append(chunk['onclick'])

if __name__ == "__main__" :
    chunk_list = parseContents("index.htm")
    num_cores = multiprocessing.cpu_count()
    chunk_size = int(len(chunk_list) / (num_cores - 1))
    chunk_parts = [chunk_list[i: i + chunk_size] for i in range(0, len(chunk_list), chunk_size)]

    with Pool(num_cores - 1) as p :
        p.map(crawling, chunk_parts)