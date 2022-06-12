import requests
import sys
import time


def send_question(id):
    status = 0
    try:
        while status != 200:
            response = requests.get(f'https://api.discogs.com/artists/{id}')
            status = response.status_code
            if status == 429:
                print(
                    "Timeout, waiting for 10 sec before sending another request", file=sys.stderr)
                time.sleep(10)
    except:
        print('Couldn\'t request artist', file=sys.stderr)
        sys.exit(1)
    return response


if len(sys.argv) != 2:
    print('Incorrect amount of arguments\nUsage:\npython artists.py <band_id>', file=sys.stderr)
    sys.exit(1)

band_id = int(sys.argv[1])
band_data = send_question(band_id).json()

members = {}

for item in band_data['members']:
    members[item['id']] = item['name']

artists_bands = {}
bands_names = {}

for id in members:
    arist_id = id
    artist_data = send_question(arist_id).json()
    all_bands = artist_data['groups']
    bands_set = set()
    for band in all_bands:
        bands_set.add(band['id'])
        bands_names[band['id']] = band['name']
    artists_bands[id] = bands_set

common_bands = {}

for artist in artists_bands:
    for band in artists_bands[artist]:
        common_bands.setdefault(bands_names[band], []).append(members[artist])

common_bands.pop(bands_names[band_id])

ordered_bands = list(common_bands.keys())
ordered_bands.sort()

for band in ordered_bands:
    if len(common_bands[band]) > 1:
        list_of_members = common_bands[band]
        list_of_members.sort()
        names_string = ", ".join(list_of_members)
        print(f'{band}: {names_string}')
