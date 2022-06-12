import requests
from pprint import pprint
import sys

try:
    response = requests.get('https://api.discogs.com/artists/359282/releases?sort=year&sort_order=desc')
except:
    print('Couldn\'t request artist')
    sys.exit(1)

data = response.json()
album_titles = []
for item in data['releases']:
    print('Test: ' + item['title'])
    no_recent = False
    no_main = False
    try:
        album_data = requests.get(item['resource_url']).json()
    except:
        print('Couldn\'t get album')
        continue
    try:
        album_data_deeper = requests.get(album_data['most_recent_release_url']).json()
    except:
        print('No recent release')
        no_recent = True
    if no_recent:
        try:
            album_data_deeper = requests.get(album_data['main_release_url']).json()
        except:
            print('No main release')
            no_main = True
    if no_recent and no_main:
        continue
    else:
        if 'Album' in album_data_deeper['formats'][0]['descriptions']:
            print(album_data_deeper['title'])
            album_titles += str(album_data_deeper['title'])

# pprint(album_titles)