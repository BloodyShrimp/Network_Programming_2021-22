from bs4 import BeautifulSoup
import urllib.request
import sys

url = 'http://th.if.uj.edu.pl/'

with urllib.request.urlopen(f'{url}') as page:
    content_type = page.headers['Content-Type']
    page_status = page.status
    print(f'content type: {content_type}')
    print(f'status: {page_status}')
    processed_page = BeautifulSoup(page.read().decode('utf-8'), 'html.parser')
    title = processed_page.find(text='Institute of Theorethical Physics')
    if title == 'Institute of Theorethical Physics':
        print('found')
        sys.exit(0)
    else:
        print('not found')
        sys.exit(1)