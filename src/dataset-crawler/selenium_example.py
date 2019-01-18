import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import requests
import pprint

def instagram_analysis(input_keyword, store, other_keyword1, other_keyword2, other_keyword3):
    starttime = time.time()
    print("instagram_analysis 시작")
    store_count = 0
    other_keyword1_count = 0
    other_keyword2_count = 0
    other_keyword3_count = 0
    # 크롤링할 url 주소
    url = "https://www.instagram.com/explore/tags/" + input_keyword

    options = webdriver.ChromeOptions()
    options.add_argument('headless')
    options.add_argument('window-size=1920x1080')
    options.add_argument("disable-gpu")

    # 크롬 드라이버를 이용해 임의로 크롬 브라우저를 실행시켜 조작한다.
    driver = webdriver.Chrome('C:\chromedriver_win32\chromedriver', chrome_options=options)
    # 암묵적으로 웹 자원을 (최대) 5초 기다리기
    driver.implicitly_wait(5)
    # 크롬 브라우저가 실행되며 해당 url로 이동한다.
    driver.get(url)

    # body 태그를 태그 이름으로 찾기
    elem = driver.find_element_by_tag_name("body")
    # tag 속성의 값을 담을 빈 리스트 선언
    tag_list = []

    # 페이지 스크롤을 위해 임시 변수 선언
    pagedowns = 1
    # 스크롤을 10번 진행한다.
    while pagedowns:
        # PAGE_DOWN(스크롤)에 따라서 결과 값이 달라진다.
        # 기본적으로 브라우저 조작을 통해 값을 얻어올 때는 실제 브라우저에 보이는 부분이어야 요소를 찾거나 특정 이벤트를 발생시킬 수 있다.
        elem.send_keys(Keys.PAGE_DOWN)
        # 페이지 스크롤 타이밍을 맞추기 위해 sleep
        time.sleep(1)
        pagedowns -= 1

    a_href = driver.find_elements_by_xpath("//div[@class='v1Nh3 kIKUG  _bz0w']/a")
    hrefs = []

    for i in a_href:  # 각 게시물들의 주소를 저장. 그래야 나중에 주소를 다 들어가서 게시글을 가져올 수 있으니까.
        hrefs.append(i.get_attribute('href'))
    print(len(hrefs))
    tag_str = []
    page_count = 0
    top_10 = [0, 0, 0, 0]  # [식당, 경쟁1, 경쟁2, 경쟁3]
    top_50 = [0, 0, 0, 0]
    top_100 = [0, 0, 0, 0]
    t = ""
    for p in hrefs:
        print(p)
        req = requests.get(p)
        html = req.text
        soup = BeautifulSoup(html, 'lxml')
        page_count += 1
        for tag in soup.find_all("meta"):
            if tag.get("property", None) == "instapp:hashtags":
                t = tag.get("content", None)
                # print(page_count)
                if store in t:
                    if page_count <= 10:
                        top_10[0] += 1
                    elif page_count <= 50:
                        top_50[0] += 1
                    elif page_count <= 100:
                        top_100[0] += 1
                elif other_keyword1 in t:
                    if page_count <= 10:
                        top_10[1] += 1
                    elif page_count <= 50:
                        top_50[1] += 1
                    elif page_count <= 100:
                        top_100[1] += 1
                elif other_keyword2 in t:
                    if page_count <= 10:
                        top_10[2] += 1
                    elif page_count <= 50:
                        top_50[2] += 1
                    elif page_count <= 100:
                        top_100[2] += 1
                elif other_keyword3 in t:
                    if page_count <= 10:
                        top_10[3] += 1
                    elif page_count <= 50:
                        top_50[3] += 1
                    elif page_count <= 100:
                        top_100[3] += 1

                tag_str.append(tag.get("content", None))
    pprint.pprint(tag_str)
    print("게시물 개수 : ", page_count)
    print("top10 : ", top_10)
    print("top50 : ", top_50)
    print("top100 : ", top_100)
    store_count = top_10[0] + top_50[0] + top_100[0]
    other_keyword1_count = top_10[1] + top_50[1] + top_100[1]
    other_keyword2_count = top_10[2] + top_50[2] + top_100[2]
    other_keyword3_count = top_10[3] + top_50[3] + top_100[3]

    percent = store_count + other_keyword1_count + other_keyword2_count + other_keyword3_count

    save_data = [[0 for rows in range(4)] for cols in range(4)]
    if store_count == 0:
        print(store, " : ", store_count, "(0.0%)")
    else:
        print(store, " : ", store_count, "(", store_count / percent * 100, "%)", " top10 : ", top_10[0], " top50 : ",
              top_50[0], " top100 : ", top_100[0])

    if other_keyword1_count == 0:
        print(other_keyword1, " : ", other_keyword1_count, "(0.0%)")
    else:
        print(other_keyword1, " : ", other_keyword1_count, "(", other_keyword1_count / percent * 100, "%)", " top10 : ",
              top_10[1], " top50 : ", top_50[1], " top100 : ", top_100[1])

    if other_keyword2_count == 0:
        print(other_keyword2, " : ", other_keyword2_count, "(0.0%)")
    else:
        print(other_keyword2, " : ", other_keyword2_count, "(", other_keyword2_count / percent * 100, "%)", " top10 : ",
              top_10[2], " top50 : ", top_50[2], " top100 : ", top_100[2])

    if other_keyword3_count == 0:
        print(other_keyword3, " : ", other_keyword3_count, "(0.0%)")
    else:
        print(other_keyword3, " : ", other_keyword3_count, "(", other_keyword3_count / percent * 100, "%)", " top10 : ",
              top_10[3], " top50 : ", top_50[3], " top100 : ", top_100[3])

    driver.close()
    print("--- %s seconds ---" % (time.time() - starttime))
    print("instagram_analysis 끝")