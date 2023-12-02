class ArrayList:

    def __init__(self, values=None):
        if not values and values != 0:
            self.__arraylist = []
        else:
            self.__arraylist = [values]

    def get(self, index):
        return self.__arraylist[index]

    def insert(self, ind, val):
        tmp = [val]
        self.__arraylist = self.__arraylist[:ind] + tmp + self.__arraylist[ind:]

    def remove(self, ind):
        val = self.get(ind)
        self.__arraylist = self.__arraylist[:ind] + self.__arraylist[ind + 1:]
        return val

    def push(self, val):
        if len(self.__arraylist) != 0:
            self.__arraylist.insert(len(self.__arraylist), val)
        else:
            self.__arraylist.insert(0, val)

    def push_front(self, val):
        self.__arraylist.insert(0, val)

    def pop(self):
        return self.remove(len(self.__arraylist) - 1)

    def pop_front(self):
        return self.remove(0)

    def __str__(self):
        res = "<"

        for el in self.__arraylist:
            res += str(el) + ","

        if len(res) != 1:
            res = res[:-1]

        res += ">"
        return res

    def __len__(self):
        return len(self.__arraylist)

    def __getitem__(self, key):
        return self.__arraylist[key]

    def __setitem__(self, key, value):
        self.__arraylist[key] = value