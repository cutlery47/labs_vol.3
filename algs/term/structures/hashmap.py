from structures.arraylist import ArrayList
from tools import tools

class Hashmap:

    def __init__(self, capacity):
        self.capacity = capacity
        self.buckets = tools.fill(None, self.capacity)
        self.filled = 0

    def ensureCapacity(self):
        target = self.capacity * 2

        for i in range(target):
            self.buckets.push(ArrayList(None))

    def __setitem__(self, key, value):
        hashed_key = hash(key) % self.capacity

        while self.buckets[hashed_key] and self.buckets[hashed_key][0] != key:
            hashed_key += 1
            hashed_key %= self.capacity

        data = ArrayList()
        data.push(key)
        data.push(value)

        self.buckets[hashed_key] = data

        if self.capacity // 2 < self.filled:
            self.ensureCapacity()

    def __getitem__(self, key):
        hashed_key = hash(key) % self.capacity
        prev_key = hashed_key

        is_found = False

        while not is_found:
            if self.buckets[hashed_key] and self.buckets[hashed_key][0] == key:
                is_found = True
            else:
                hashed_key += 1
                hashed_key %= self.capacity

                if prev_key == hashed_key:
                    return None

        data = self.buckets[hashed_key]
        return data[1]





