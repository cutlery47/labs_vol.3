class ArrayList:

    def __init__(self):
        self.__arraylist = []

    def push(self, val):
        self.__arraylist.append(val)

    def pop(self):
        self.__arraylist.pop()

    def print(self):
        for el in self.__arraylist:
            print(el, end=" ")

    def remove(self, ind):
        self.__arraylist = self.__arraylist[:ind] + self.__arraylist[ind:]

    def insert(self, ind, val):
        self.__arraylist = self.__arraylist[:ind] + val + self.__arraylist[:ind]