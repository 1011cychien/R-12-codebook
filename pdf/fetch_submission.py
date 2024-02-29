from bs4 import BeautifulSoup
import requests

url = 'https://judge.yosupo.jp/submission/193525'
res = requests.get(url)
soup = BeautifulSoup(res.text, 'html.parser')

# code = soup.find_all('pre')[0]
print(soup.prettify())
