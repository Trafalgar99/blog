import collections

card = collections.namedtuple('card', ['rank', 'suit'])
a = card(3, 3)
print(a)