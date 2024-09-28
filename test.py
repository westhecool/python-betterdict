from betterdict import BetterDict
bd = BetterDict()

# basic test
bd.set('key', 'value')
print(bd.size())
print(bd.get('key'))
bd.remove('key')
print(bd.includes('key'))
bd.clear()

# type test
# int
bd.set('key', 1)
print(bd.get('key', True))
# str
bd.set('key', 'value')
print(bd.get('key', True))
# float
bd.set('key', 1.0)
print(bd.get('key', True))
# bool
bd.set('key', True)
print(bd.get('key', True))
# None
bd.set('key', None)
print(bd.get('key', True))
# list
bd.set('key', [1, 2, 3])
print(bd.get('key', True))
# tuple
bd.set('key', (1, 2, 3))
print(bd.get('key', True))
# dict
bd.set('key', {'a': 1, 'b': 2})
print(bd.get('key', True))
# bytes
bd.set('key', b'bytes')
print(bd.get('key', True))
# function
bd.set('key', lambda x: x + 1)
print(bd.get('key')(1), bd.get('key', True))