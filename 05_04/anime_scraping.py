from bs4 import BeautifulSoup
import urllib.request
import sys
import pprint
# import pandas as pd

url = 'https://myanimelist.net/topanime.php?limit='
pages = []

for page_number in range(0, 100, 50):
    try:
        with urllib.request.urlopen(f'{url}{page_number}') as resp:
            if resp.headers['Content-Type'].split(';')[0] != 'text/html':
                raise ValueError("Not a html site")
            if resp.status != 200:
                raise ValueError('Invalid status code')
            processed_page = BeautifulSoup(resp.read().decode('utf-8'), 'html.parser')
            pages.append(processed_page)
    except Exception as e:
        print(f'Pobieranie strony {page_number} nieudane\nError: {e}')
        sys.exit(1)

animes_data = []

for page in pages:
    rank_list = page.find_all('tr', {'class': 'ranking-list'})
    for item in rank_list:
        anime = {}
        details = item.find('div', {'class': 'detail'})
        title_tag = details.find('h3' ,{'class': 'hoverinfo_trigger fl-l fs14 fw-b anime_ranking_h3'})
        anime['title'] = title_tag.find('a').text
        score_tag = item.find('td', {'class': 'score ac fs14'})
        anime['score'] = float(score_tag.find('span').text)
        info_tag = details.find('div', {'class': 'information di-ib mt4'})
        anime['members'] = int(info_tag.text.splitlines()[3].replace(' ', '').replace(',', '').replace('members', ''))
        anime['type'] = info_tag.text.splitlines()[1].lstrip().split(' ')[0]
        try:
            anime['episodes'] = int(info_tag.text.splitlines()[1].lstrip().split(' ')[1].replace('(', ''))
        except:
            anime['episodes'] = 'unknown'
        anime['aired_start'] = info_tag.text.splitlines()[2].lstrip().split('-')[0].rstrip()
        anime['aired_end'] = info_tag.text.splitlines()[2].lstrip().split('-')[1].lstrip()
        if anime['aired_end'] == '':
            anime['aired_end'] = 'airing'
        rank_tag = item.find('td', {'class': 'rank ac'})
        anime['rank'] = int(rank_tag.find('span').text)
        animes_data.append(anime)

pprint.pprint(animes_data)
# df = pd.DataFrame(animes_data)
# df.to_csv('anime_data.csv', index=False, encoding='utf-8')